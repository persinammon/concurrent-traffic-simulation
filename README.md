# Concurrent Traffic Simulation

This project practices C++ concurrency.

I found this [resource](https://medium.com/codex/c-multithreading-the-simple-way-95aa1f7304a2) I really liked which introduced multithreading and concurrency, especially because this line -
>Multithreading often carries a reputation for being difficult. Compared with other concepts in software development, one could certainly make a case for that. However, multithreading isn’t really that different from general programming. It’s just potentially more dangerous . Learning to protect against the danger, though, can allow one to implement far more powerful algorithms and programs than you could in a single threaded manner."

Or, more or less, the data races are not 100% guaranteed to show up per run. You should be able to spot them on your own.

I was very interested in the fact that, because threads do not have a copy constructor, a vector of threads needs to be populated by the move constructor and therefore by using `emplace_back`; also, when multiple threads are running, interleaved work can present a bug such as interrupted print statements in `cout`- `cout` is a shared resource that can be accessed in the middle of executing the same method by another thread (??).

Notable code changes made in the project:
- The basic structure of the project was already implemented- vehicles heading to destinations, communicating with an open intersection, and passing through one at a time. What was implemented was the ability for a traffic light to have a red light, and therefore pause the flow of cars. In addition to FIFO of cars being let through, the lights cycle between red and green. Every `Intersection` owns a `TrafficLight` that owns a thread that runs an infinite loop sending color messages to a message queue also owned by and wrapped by `TrafficLight`.
- Fleshed out a generic message queue with implementation split across `TrafficLight.h` and `TrafficLight.cpp`. Added some connecting code in `Intersection`, with a notable lines being `L87` to `L91`. Every method in `TrafficLight.cpp` is newly implemented.
- This wasn't in the project spec at all, but I wanted to pass in a parameter to the driver that would allow CLI toggling
between the two cities Paris and NYC. The data and functions were already pre-written within the driver, so all it needed was a user argument.
I changed the `int main()` function in `TrafficSimulator-Final.cpp` to `int main(int argc, char** argv)` and used the string 
to toggle, with the default/for malformed input being Paris. Had to change a C-style string to an `std::string`.

<img src="data/traffic_simulation.gif"/>

## Dependencies for Running Locally
* cmake >= 2.8
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* OpenCV >= 4.1
  * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

Two Options - 
1. Only download the executable `traffic_simulation` from the `build` folder, and run it 
through the `./traffic_simulation` command in the same directory.


Or-
1. Clone repo to local.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it through the following command: `./traffic_simulation`.

To run with Paris as the background, either `./traffic_simulation` or `./traffic_simulation paris`.
To run with NYC as the background, `./traffic_simulation nyc`.