#pragma once
#include <chrono>

namespace Physics {

namespace Time {

// TODO: dt is hard-coded right now. Moreover, Duration and TimePoint types are derived from dt. What if I want to change dt?

static constexpr auto dt = std::chrono::duration<long long, std::ratio<1, 60>>{1};

using Clock = std::chrono::steady_clock;
using Duration = decltype(Clock::duration{} + dt);
using TimePoint = std::chrono::time_point<Clock, Duration>;

}  // namespace Time

}  // namespace Physics