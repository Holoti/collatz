#pragma once

#include "geometry_vector.h"

namespace Physics {

template <Vector V>
class PointParticle {
   public:
    PointParticle(const V& position = V{}, const V& velocity = V{}) : position_(position), velocity_(velocity) {}

    const V& GetPosition() const { return position_; }
    void SetPosition(const V& v) { position_ = v; }

    const V& GetVelocity() const { return velocity_; }
    void SetVelocity(const V& v) { velocity_ = v; }

   private:
    V position_;
    V velocity_;
};

template <Vector V>
V::Scalar Distance(const PointParticle<V>& p1, const PointParticle<V>& p2) {
    return Distance(p1.GetPosition(), p2.GetPosition());
}

}  // namespace Physics