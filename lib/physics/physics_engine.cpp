#include "physics_engine.h"

namespace Physics {

State PhysicsEngine::Step(TimePoint new_time) {
    auto frame_time = new_time - current_time_;
    if (frame_time > 250ms) { // TODO what is the purpose of this? Source: "Fix your timestep"
        frame_time = 250ms;
    }
    current_time_ = new_time;

    accumulator_ += frame_time;

    while (accumulator_ >= dt_) {
        previous_state_ = current_state_;
        // TODO Integrate(currentState, t, dt);
        time_passed_ += dt_;
        accumulator_ -= dt_;
    }

    const double alpha = std::chrono::duration<double>{accumulator_} / dt_;

    State interpolated_state = current_state_ * alpha + previous_state_ * (1 - alpha);

    return interpolated_state;
}

}  // namespace Physics