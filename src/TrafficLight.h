#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <iostream>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;

// Define a class „MessageQueue“ which has the public methods send and receive. 
// Send should take an rvalue reference of type TrafficLightPhase whereas receive should return this type. 
// Also, the class should define an std::dequeue called _queue, which stores objects of type TrafficLightPhase. 
// Also, there should be an std::condition_variable as well as an std::mutex as private members. 
enum TrafficLightPhase { red, green };

template <class T>
class MessageQueue{
    public:
        //takes an rvalue reference
        void send(T &&msg);

        //public mehods per tasks
        T receive();
    
    private:
        std::condition_variable _condition;
        std::mutex _mtx;
        std::deque<T> _queue;
};

// Define a class „TrafficLight“ which is a child class of TrafficObject. 
// The class shall have the public methods „void waitForGreen()“ and „void simulate()“ 
// as well as „TrafficLightPhase getCurrentPhase()“, where TrafficLightPhase is an enum that 
// can be either „red“ or „green“. Also, add the private method „void cycleThroughPhases()“. 
// Furthermore, there shall be the private member _currentPhase which can take „red“ or „green“ as its value. 

class TrafficLight : TrafficObject{
    public:
        // constructor / desctructor
        TrafficLight();
        
        // getters / setters
        TrafficLightPhase getCurrentPhase();
        
        // typical behaviour methods
        void waitForGreen();
        void simulate();
    
    private:
        // typical behaviour methods
        void cycleThroughPhases();
        TrafficLightPhase _currentPhase;
        
        // Create a private member of type MessageQueue for messages of type TrafficLightPhase 
        // and use it within the infinite loop to push each new TrafficLightPhase into it by calling 
        // send in conjunction with move semantics.
        
        //message queue to be used in the infinite loop
        std::shared_ptr<MessageQueue<TrafficLightPhase>> _queue{new MessageQueue<TrafficLightPhase>};
        
        //existing variables
        std::condition_variable _condition;
        std::mutex _mutex;
};
#endif