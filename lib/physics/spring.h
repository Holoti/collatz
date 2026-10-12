#pragma once

#include "geometry_vector.h"
#include "point_particle.h"

namespace Physics {

template <Vector V>
class Spring {
   public:
    Spring(const PointParticle<V>& point1, const PointParticle<V>& point2,
           const V::Scalar& rest_length = typename V::Scalar{})
        : point1_(point1), point2_(point2), rest_length_(rest_length), current_length_(Distance(point1_, point2_)) {}

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

}  // namespace Physics