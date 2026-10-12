#include <gtest/gtest.h>

#include "physics/geometry_vector.h"

namespace Physics {

TEST(PhysicsGeometryVector, EuclideanVector2DIsVector) { static_assert(Vector<EuclideanVector2D>); }

TEST(PhysicsGeometryVector, EuclideanVector3DIsVector) { static_assert(Vector<EuclideanVector3D>); }

}  // namespace Physics