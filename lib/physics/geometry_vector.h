#pragma once

#include <cmath>
#include <concepts>

template <typename V>
concept Vector = requires(const V a, const V b, V::Scalar s) {
    typename V::Scalar;
    V{};

    { a + b } -> std::same_as<V>;
    { a - b } -> std::same_as<V>;

    { a * s } -> std::same_as<V>;
    { a / s } -> std::same_as<V>;

    { a.Dot(b) } -> std::same_as<typename V::Scalar>;
};

class EuclideanVector2D {
   public:
    using Scalar = double;

    EuclideanVector2D() : x_(Scalar{0}), y_(Scalar{0}) {}

    EuclideanVector2D(Scalar x, Scalar y) : x_(x), y_(y) {}

    EuclideanVector2D operator+(const EuclideanVector2D& other) const {
        return EuclideanVector2D{x_ + other.x_, y_ + other.y_};
    };
    EuclideanVector2D operator-(const EuclideanVector2D& other) const {
        return EuclideanVector2D{x_ - other.x_, y_ - other.y_};
    };

    EuclideanVector2D operator*(const Scalar& scalar) const { return EuclideanVector2D{x_ * scalar, y_ * scalar}; }
    EuclideanVector2D operator/(const Scalar& scalar) const { return EuclideanVector2D{x_ / scalar, y_ / scalar}; };

    Scalar Dot(const EuclideanVector2D& other) const { return Scalar{x_ * other.x_ + y_ * other.y_}; };

    Scalar X() const { return x_; };
    Scalar Y() const { return y_; };

    bool operator==(const EuclideanVector2D& other) const { return x_ == other.x_ && y_ == other.y_; }

   private:
    Scalar x_;
    Scalar y_;
};

class EuclideanVector3D {
   public:
    using Scalar = double;

    EuclideanVector3D() : x_(Scalar{0}), y_(Scalar{0}), z_(Scalar{0}) {}

    EuclideanVector3D(Scalar x, Scalar y, Scalar z) : x_(x), y_(y), z_(z) {}

    EuclideanVector3D operator+(const EuclideanVector3D& other) const {
        return EuclideanVector3D{x_ + other.x_, y_ + other.y_, z_ + other.z_};
    }
    EuclideanVector3D operator-(const EuclideanVector3D& other) const {
        return EuclideanVector3D{x_ - other.x_, y_ - other.y_, z_ - other.z_};
    }

    EuclideanVector3D operator*(const Scalar& scalar) const {
        return EuclideanVector3D{x_ * scalar, y_ * scalar, z_ * scalar};
    }
    EuclideanVector3D operator/(const Scalar& scalar) const {
        return EuclideanVector3D{x_ / scalar, y_ / scalar, z_ / scalar};
    }

    Scalar Dot(const EuclideanVector3D& other) const { return Scalar{x_ * other.x_ + y_ * other.y_ + z_ * other.z_}; }

    EuclideanVector3D Cross(const EuclideanVector3D& other) const {
        return EuclideanVector3D{
            y_ * other.z_ - z_ * other.y_,
            z_ * other.x_ - x_ * other.z_,
            x_ * other.y_ - y_ * other.x_,
        };
    }

    Scalar X() const { return x_; }
    Scalar Y() const { return y_; }
    Scalar Z() const { return z_; }

    bool operator==(const EuclideanVector3D& other) const { return x_ == other.x_ && y_ == other.y_ && z_ == other.z_; }

   private:
    Scalar x_;
    Scalar y_;
    Scalar z_;
};

template <Vector V>
V::Scalar Norm(const V& v) {
    return std::sqrt(v.Dot(v));
}

template <Vector V>
V::Scalar Distance(const V& lhs, const V& rhs) {
    return Norm(lhs - rhs);
}