#include "integrator.h"
namespace Physics {

template <Vector V>
inline void Integrator<V>::Integrate(PhysicsEntityStorage<V>& storage, Time::TimePoint t, Time::Duration dt) {
    size_t size = storage.x_.size();

    AccelerationStorage acceleration(size);

    ApplyForces(storage, acceleration);
    ApplyAcceleration(storage, acceleration);
    DampSpeed(storage);
    ApplySpeed(storage);
}

template <Vector V>
inline void Integrator<V>::ApplyForces(PhysicsEntityStorage<V>& storage, AccelerationStorage& acceleration) {
    ApplyRepulsiveForce(storage, acceleration);
    ApplyCenterAttraction(storage, acceleration);
}

template <Vector V>
inline void Integrator<V>::ApplyRepulsiveForce(PhysicsEntityStorage<V>& storage, AccelerationStorage& acceleration) {
    static typename V::Scalar repulsive_force_coefficient = 80;

    size_t size = storage.x_.size();

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < i; ++j) {
            EuclideanVector2D position1(storage.x_[i], storage.y_[i]);
            EuclideanVector2D position2(storage.x_[j], storage.y_[j]);

            auto distance_vector = position1 - position2;
            auto distance_scalar = Norm(distance_vector);

            auto repulsive_force1 =
                (distance_vector / distance_scalar) * repulsive_force_coefficient / (distance_scalar * distance_scalar);

            acceleration.ax_[i] += repulsive_force1.X();
            acceleration.ay_[i] += repulsive_force1.Y();

            acceleration.ax_[j] -= repulsive_force1.X();
            acceleration.ay_[j] -= repulsive_force1.Y();
        }
    }
}

template <Vector V>
inline void Integrator<V>::ApplyCenterAttraction(PhysicsEntityStorage<V>& storage, AccelerationStorage& acceleration) {
    static typename V::Scalar gravity_coefficient = 0.1;

    size_t size = storage.x_.size();

    for (size_t i = 0; i < size; ++i) {
        EuclideanVector2D position(storage.x_[i], storage.y_[i]);

        auto distance = Norm(position);
        if (distance == 0) {
            continue;
        }

        auto gravity_force = position / distance * gravity_coefficient;

        acceleration.ax_[i] -= gravity_force.X();
        acceleration.ay_[i] -= gravity_force.Y();
    }
}

template <Vector V>
inline void Integrator<V>::ApplyAcceleration(PhysicsEntityStorage<V>& storage, AccelerationStorage& acceleration) {
    size_t size = storage.x_.size();

    for (size_t i = 0; i < size; ++i) {
        storage.vx_[i] += acceleration.ax_[i];
        storage.vy_[i] += acceleration.ay_[i];
    }
}

template <Vector V>
inline void Integrator<V>::DampSpeed(PhysicsEntityStorage<V>& storage) {
    static typename V::Scalar damping_coefficient = .99;

    size_t size = storage.x_.size();

    for (size_t i = 0; i < size; ++i) {
        storage.vx_[i] *= damping_coefficient;
        storage.vy_[i] *= damping_coefficient;
    }
}

template <Vector V>
inline void Integrator<V>::ApplySpeed(PhysicsEntityStorage<V>& storage) {
    size_t size = storage.x_.size();

    for (size_t i = 0; i < size; ++i) {
        storage.x_[i] += storage.vx_[i];
        storage.y_[i] += storage.vy_[i];
    }
}

}  // namespace Physics