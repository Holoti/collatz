#pragma once

#include <compare>
#include <concepts>
#include <cstdint>
#include <ostream>
#include <vector>

class BigInt {
   public:
    BigInt();

    BigInt(std::string_view other);

    template <typename T>
        requires std::integral<T>
    BigInt(T other);

    BigInt(const BigInt& other);

    BigInt& operator=(const BigInt& other) = default;

    // BigInt& operator=(BigInt&& other);

    BigInt operator+(const BigInt& other) const;

    BigInt operator-(const BigInt& other) const;

    BigInt operator-() const;

    BigInt operator*(const BigInt& other) const;

    BigInt operator/(const BigInt& other) const;

    BigInt& operator++();

    BigInt operator++(int);

    std::strong_ordering operator<=>(const BigInt& other) const;

    bool operator==(const BigInt& other) const;

    friend std::ostream& operator<<(std::ostream& stream, const BigInt& value);

    std::ostream& PrintBytes(std::ostream& stream) const;

   private:
    std::vector<uint8_t> bytes;

    BigInt Normalize(size_t size) const;

    static constexpr uint16_t kBitMask = 256;
};

#include "big_int.ipp"