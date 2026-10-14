#pragma once

namespace Physics {

struct State {  // TODO what is State?
    State operator*(double alpha);
    State operator+(const State& other);

    friend void Render(const State& state);
};

void Render(const State& state);

}  // namespace Physics