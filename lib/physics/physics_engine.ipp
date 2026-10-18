namespace Physics {

template <Vector V>
inline State<V> PhysicsEngine<V>::Step(Time::TimePoint new_time) {
    auto frame_time = new_time - current_time_;
    // if (frame_time > 250ms) {  // TODO what is the purpose of this? Source: "Fix your timestep"
    //     frame_time = 250ms;
    // }
    current_time_ = new_time;

    accumulator_ += frame_time;

    while (accumulator_ >= Time::dt) {
        previous_state_ = current_state_;
        current_state_.Integrate(t, Time::dt);
        t += Time::dt;
        accumulator_ -= Time::dt;
    }

    const double alpha = std::chrono::duration<double>{accumulator_} / Time::dt;

    // return current_state_;
    
    State interpolated_state = current_state_ * alpha + previous_state_ * (1 - alpha);

    return std::move(interpolated_state);

}

}  // namespace Physics