namespace Physics {

template <Vector V>
inline State<V> State<V>::operator*(double alpha) {
    State<V> result(*this);

    size_t size = storage_.x_.size();

    for (size_t i = 0; i < size; ++i) {
        result.storage_.x_[i] *= alpha;
        result.storage_.y_[i] *= alpha;
    }

    return result;
}

template <Vector V>
inline State<V> State<V>::operator+(const State& other) {
    State<V> result(*this);

    size_t size = storage_.x_.size();

    for (size_t i = 0; i < size; ++i) {
        result.storage_.x_[i] += other.storage_.x_[i];
        result.storage_.y_[i] += other.storage_.y_[i];
    }

    return result;
}

template <Vector V>
inline void State<V>::AddPoint(const PointParticle<V>& point) {
    storage_.x_.emplace_back(point.GetPosition().X());
    storage_.y_.emplace_back(point.GetPosition().Y());

    storage_.vx_.emplace_back(point.GetVelocity().X());
    storage_.vy_.emplace_back(point.GetVelocity().Y());
}

}  // namespace Physics