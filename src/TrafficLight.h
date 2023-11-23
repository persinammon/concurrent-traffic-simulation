#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;

template <class T>
class MessageQueue
{
    public:
        void send(T &&msg);
        T receive();

    private:
        std::deque<T> _queue;
        std::condition_variable _cond;
        std::mutex _mutex;
};

// fyi, enum class and enum struct are functionally equivalent aka the same thing
// avoiding using global scope, for clean code convention rather than a practical reason
enum class TrafficLightPhase {
    red,
    green
};

class TrafficLight : public TrafficObject
{
public:
    // constructor / desctructor
    TrafficLight();
    ~TrafficLight();

    // getters / setters
    TrafficLightPhase getCurrentPhase();

    // typical behaviour methods
    void waitForGreen();
    void simulate();

private:
    // typical behaviour methods
    void cycleThroughPhases();


    // FP.4b : create a private member of type MessageQueue for messages of type TrafficLightPhase 
    // and use it within the infinite loop to push each new TrafficLightPhase into it by calling 
    // send in conjunction with move semantics.
    TrafficLightPhase _currentPhase;
    std::condition_variable _condition;
    std::mutex _mutex;
};

#endif