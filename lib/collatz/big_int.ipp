#include <cstdint>

template <typename T>
    requires std::integral<T>
inline BigInt::BigInt(T other) {
    bool negative = other < 0;

    // size_t j = 0;
    while (other != 0) {
        // bytes[j++] = other % kBitMask;
        bytes.emplace_back(other % kBitMask);
        other /= kBitMask;
    }

    if (negative) {
        *this = -*this;
    }
}
