#pragma once

#include "geometry_vector.h"

namespace Physics {

template <Vector V>
struct PhysicsEntityStorage;

template <>
struct PhysicsEntityStorage<EuclideanVector2D> {
    using Scalar = EuclideanVector2D::Scalar;

    std::vector<Scalar> x_;
    std::vector<Scalar> y_;

    std::vector<Scalar> vx_;
    std::vector<Scalar> vy_;
    
};

}  // namespace Physics