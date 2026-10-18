#pragma once

#include <stdexcept>
#include <vector>

#include "geometry_vector.h"
#include "physics_entity_storage.h"
#include "point_particle.h"

namespace Physics {

template <Vector V>
class State {  // TODO what is State?

   public:
    State operator*(double alpha);
    State operator+(const State& other);

    void Integrate(Time::TimePoint t, Time::Duration dt) { integrator_->Integrate(storage_, t, dt); }

    void SetIntegrator(std::shared_ptr<IIntegrator<V>> integrator) {
        if (!integrator) {
            throw std::runtime_error("State::SetInterator(): Integrator pointer empty");
        }

        integrator_ = integrator;
    }

    void AddPoint(const PointParticle<V>& point);

    const PhysicsEntityStorage<V>& GetStorage() const { return storage_; }

   private:
    PhysicsEntityStorage<V> storage_;

    std::shared_ptr<IIntegrator<V>> integrator_;
};

}  // namespace Physics

#include "physics_state.ipp"