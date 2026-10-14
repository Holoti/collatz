#pragma once

#include <chrono>
#include <memory>
#include <ratio>
#include <vector>

#include "geometry_vector.h"
#include "physics_state.h"
#include "point_particle.h"
#include "spring.h"

namespace Physics {

namespace {

using namespace std::literals;

}

class PhysicsEngine {
    static constexpr auto dt_ = std::chrono::duration<long long, std::ratio<1, 60>>{1};

   public:
    using Clock = std::chrono::steady_clock;
    using Duration = decltype(Clock::duration{} + dt_);
    using TimePoint = std::chrono::time_point<Clock, Duration>;

    PhysicsEngine(TimePoint current_time) : time_passed_(), current_time_(current_time), accumulator_(0s) {}

    State Step(TimePoint new_time);

   private:
    TimePoint time_passed_;
    TimePoint current_time_;
    Duration accumulator_;

    State previous_state_;
    State current_state_;
};

}  // namespace Physics