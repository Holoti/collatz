#pragma once

#include "geometry_vector.h"
#include "point_particle.h"

template <Vector V>
class Spring {
    Spring(const PointParticle<V>& point1, const PointParticle<V>& point2) : point1_(point1), point2_(point2) {}

    const V::Scalar& GetRestLength() { return rest_length_; }
    void SetRestLength(const V::Scalar& rest_length) { rest_length_ = rest_length; }

    const V::Scalar& GetCurrentLength() { return current_length_; }
    void SetCurrentLength(const V::Scalar& current_length) { current_length_ = current_length; }

   private:
    PointParticle<V> point1_;
    PointParticle<V> point2_;

    V::Scalar rest_length_;
    V::Scalar current_length_;
};