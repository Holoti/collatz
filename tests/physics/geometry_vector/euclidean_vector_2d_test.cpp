#include <gtest/gtest.h>

#include "physics/geometry_vector.h"

namespace {

using Scalar = EuclideanVector2D::Scalar;

TEST(PhysicsGeometryVectorEuclideanVector2D, DefaultInitialized) {
    EuclideanVector2D a;

    EXPECT_EQ(a.X(), Scalar{});
    EXPECT_EQ(a.Y(), Scalar{});
}

TEST(PhysicsGeometryVectorEuclideanVector2D, InitializedWithValues) {
    EuclideanVector2D a{Scalar{3}, Scalar{4}};

    EXPECT_EQ(a.X(), Scalar{3});
    EXPECT_EQ(a.Y(), Scalar{4});
}

TEST(PhysicsGeometryVectorEuclideanVector2D, VectorAddSubstract) {
    EuclideanVector2D a{Scalar{1}, Scalar{2}};
    EuclideanVector2D b{Scalar{3}, Scalar{4}};

    EuclideanVector2D got = a + b;
    EuclideanVector2D expected{Scalar{4}, Scalar{6}};

    EXPECT_EQ(got, expected);

    got = a - b;
    expected = EuclideanVector2D{Scalar{-2}, Scalar{-2}};

    EXPECT_EQ(got, expected);
}

TEST(PhysicsGeometryVectorEuclideanVector2D, MultiplyDivideOnScalar) {
    EuclideanVector2D a{Scalar{1}, Scalar{2}};
    Scalar s{3};

    EuclideanVector2D got = a * s;
    EuclideanVector2D expected{Scalar{3}, Scalar{6}};

    EXPECT_EQ(got, expected);

    got = a / s;
    expected = EuclideanVector2D{Scalar{1} / Scalar{3}, Scalar{2} / Scalar{3}};

    EXPECT_EQ(got, expected);
}

TEST(PhysicsGeometryVectorEuclideanVector2D, DotProduct) {
    EuclideanVector2D a{Scalar{1}, Scalar{2}};
    EuclideanVector2D b{Scalar{3}, Scalar{4}};

    Scalar got = a.Dot(b);
    Scalar expected{1 * 3 + 2 * 4};

    EXPECT_EQ(got, expected);
}

TEST(PhysicsGeometryVectorEuclideanVector2D, DotProductIsCommutative) {
    EuclideanVector2D a{Scalar{1}, Scalar{2}};
    EuclideanVector2D b{Scalar{3}, Scalar{4}};

    Scalar x = a.Dot(b);
    Scalar y = b.Dot(a);

    EXPECT_EQ(x, y);
}

}  // namespace