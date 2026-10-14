#include "physics_state.h"

#include <chrono>
#include <iostream>

namespace Physics {

State State::operator*(double alpha) { return State(); }

State State::operator+(const State& other) { return State(); }

void Render(const State& state) {
    // TODO: THIS IS PLACEHOLDER JUST FOR TESTING CORRECTNESS OF FPS/UPS RATIO
    // Source: https://stackoverflow.com/questions/59441699/gaffer-on-games-timestep-stdchrono-implementation
    using namespace std::chrono;
    static auto t = time_point_cast<seconds>(steady_clock::now());
    static int frame_count = 0;
    static int frame_rate = 0;
    auto pt = t;
    t = time_point_cast<seconds>(steady_clock::now());
    ++frame_count;
    if (t != pt) {
        frame_rate = frame_count;
        frame_count = 0;
    }
    std::cout << "Frame rate is " << frame_rate << " frames per second." << std::endl;
}

}  // namespace Physics