#pragma once

#include "physics_entity_storage.h"
#include "time_types.h"

namespace Physics {

template <Vector V>
class IIntegrator {
   public:
    virtual void Integrate(PhysicsEntityStorage<V>& storage, Time::TimePoint t, Time::Duration dt) = 0;
};

template <Vector V>
class Integrator : public IIntegrator<V> {
   public:
    virtual void Integrate(PhysicsEntityStorage<V>& storage, Time::TimePoint t, Time::Duration dt) override;

   private:
    struct AccelerationStorage {
        using Scalar = V::Scalar;

        AccelerationStorage() = delete;

        AccelerationStorage(size_t size) : ax_(size), ay_(size) {}

        std::vector<Scalar> ax_;
        std::vector<Scalar> ay_;
    };

    void ApplyForces(PhysicsEntityStorage<V>& storage, AccelerationStorage& acceleration);
    void ApplyAcceleration(PhysicsEntityStorage<V>& storage, AccelerationStorage& acceleration);
    void DampSpeed(PhysicsEntityStorage<V>& storage);
    void ApplySpeed(PhysicsEntityStorage<V>& storage);

    void ApplyRepulsiveForce(PhysicsEntityStorage<V>& storage, AccelerationStorage& acceleration);
};

}  // namespace Physics

#include "integrator.ipp"