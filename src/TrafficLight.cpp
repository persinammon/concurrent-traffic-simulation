#include <iostream>
#include <cstdlib>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */

/* 
template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
}
*/

/* Implementation of class "TrafficLight" */


TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // use 1 thread to run the traffic light by giving it cycleThroughPhases
    // no need to pass in data to run the simulation, so no need to use a lambda
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));  
    // all threads owned by TrafficLight are destroyed by the thread barrier implemented
    // in the parent class
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{    
    // cycle duration is a random integer between 4 and 6 seconds
    srand(time(NULL));
    std::chrono::duration cycleDuration = std::chrono::seconds((std::rand() % 3) + 4);
    //std::cout << " cycle duration" << cycleDuration.count() << std::endl;
    while (true) {
        std::this_thread::sleep_for(cycleDuration);
        _currentPhase = (_currentPhase == TrafficLightPhase::red) ? TrafficLightPhase::green : TrafficLightPhase::red;
        // update method to the message queue using move semantics
        // owning a message queue, send it a new instance of TrafficLightPhase enum

        // without a small thread wait function, the processor burns fast and hard through an infinite while loop
        // this sleep_for instruction reduces processor load
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

