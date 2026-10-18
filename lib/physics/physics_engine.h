#pragma once

#include <chrono>
#include <memory>
#include <ratio>
#include <vector>

#include "integrator.h"
#include "physics_state.h"
#include "point_particle.h"
#include "spring.h"
#include "time_types.h"

namespace Physics {

namespace {

using namespace std::literals;

}

template <Vector V>
class PhysicsEngine {
    // static constexpr auto dt_ = std::chrono::duration<long long, std::ratio<1, 60>>{1};

   public:
    // using Clock = std::chrono::steady_clock;
    // using Duration = decltype(Clock::duration{} + dt_);
    // using TimePoint = std::chrono::time_point<Clock, Duration>;

    PhysicsEngine(std::shared_ptr<IIntegrator<V>> integrator, Time::TimePoint current_time)
        : t(), current_time_(current_time), accumulator_(0s) {
        current_state_.SetIntegrator(integrator);
    }

    State<V> Step(Time::TimePoint new_time);

    void AddPoint(const PointParticle<V>& point) {
        current_state_.AddPoint(point);
        previous_state_.AddPoint(point);
    }

   private:
    Time::TimePoint t;
    Time::TimePoint current_time_;
    Time::Duration accumulator_;

    State<V> previous_state_;
    State<V> current_state_;
};

}  // namespace Physics

#include "physics_engine.ipp"