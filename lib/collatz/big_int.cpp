#include "big_int.h"

#include <algorithm>
#include <limits>
#include <iomanip>

BigInt::BigInt() {}

BigInt::BigInt(const BigInt& other) { bytes = other.bytes; }

BigInt BigInt::operator+(const BigInt& other) const {
    size_t size = std::max(bytes.size(), other.bytes.size());

    BigInt lhs = Normalize(size);
    BigInt rhs = other.Normalize(size);

    BigInt result;
    result.bytes.resize(size + 1);

    uint16_t carry = 0;
    uint16_t sum = 0;
    uint8_t i = 0;

    // for (i; i < size - 1; ++i) {
    //     sum = lhs.bytes[i] + rhs.bytes[i] + carry;
    //     result.bytes[i] = sum % kBitMask;
    //     carry = sum / kBitMask;
    // }

    // sum = lhs.bytes[i] + rhs.bytes[i] + carry;
    // result.bytes[i] = sum % 2;
    // carry = sum / 2;

    // FIXME this only supports positive + positive due to 2's complement behaviour
    
    for (i; i < size; ++i) {
        sum = lhs.bytes[i] + rhs.bytes[i] + carry;
        result.bytes[i] = sum % kBitMask;
        carry = sum / kBitMask;
    }

    return result;
}

BigInt BigInt::operator-(const BigInt& other) const { return *this + (-other); }

BigInt BigInt::operator-() const {
    BigInt result;
    result.bytes.resize(bytes.size());

    uint8_t i = 0;
    for (i; i < bytes.size() - 1; ++i) {
        result.bytes[i] = ~bytes[i];
    }

    if (bytes[i] == 1) {
        result.bytes[i] = 0;
    } else {
        result.bytes[i] = 1;
    }

    result = result + 1;

    return result;
}

BigInt BigInt::operator*(const BigInt& other) const {
    size_t size = std::max(bytes.size(), other.bytes.size());

    BigInt lhs = Normalize(size);
    BigInt rhs = other.Normalize(size);

    std::vector<uint32_t> tmp(2 * size + 2);
    for (uint8_t i = 0; i < size; ++i) {
        for (uint8_t j = 0; j < size; ++j) {
            tmp[i + j] += uint16_t(lhs.bytes[i]) * uint16_t(rhs.bytes[j]);
        }
    }

    uint32_t carry = 0;
    for (uint16_t k = 0; k < 2 * size + 2; ++k) {
        uint32_t sum = tmp[k] + carry;
        tmp[k] = sum % kBitMask;
        carry = sum / kBitMask;
    }

    BigInt result;
    result.bytes.resize(2 * size + 2);

    for (uint8_t i = 0; i < size; ++i) {
        result.bytes[i] = tmp[i];
    }

    result.bytes[2 * size + 1] &= 1;

    return result;
}

BigInt BigInt::operator/(const BigInt& other) const {
    throw std::runtime_error("BigInt::operator/(): not implemented");
}

BigInt& BigInt::operator++() {
    *this = *this + 1;
    return *this;
}

BigInt BigInt::operator++(int) {
    BigInt result = *this;
    *this = *this + 1;
    return result;
}

std::strong_ordering BigInt::operator<=>(const BigInt& other) const {
    size_t size = std::max(bytes.size(), other.bytes.size());

    BigInt lhs = Normalize(size);
    BigInt rhs = other.Normalize(size);

    bool lhs_negative = lhs.bytes[size - 1];
    bool rhs_negative = rhs.bytes[size - 1];

    if (lhs_negative && !rhs_negative) {
        return std::strong_ordering::less;
    } else if (!lhs_negative && rhs_negative) {
        return std::strong_ordering::greater;
    }

    if (lhs_negative) {
        lhs = -lhs;
    }
    if (rhs_negative) {
        rhs = -rhs;
    }

    bool abs_less;
    bool equal = true;
    for (size_t i = 0; i < size; ++i) {
        if (lhs.bytes[i] == rhs.bytes[i]) {
            continue;
        }
        equal = false;
        abs_less = lhs.bytes[i] < rhs.bytes[i];
        break;
    }

    if (equal) {
        return std::strong_ordering::equal;
    }

    bool less = abs_less != lhs_negative;
    if (less) {
        return std::strong_ordering::less;
    } else {
        return std::strong_ordering::greater;
    }
}

bool BigInt::operator==(const BigInt& other) const { return operator<=>(other) == 0; }

std::ostream& BigInt::PrintBytes(std::ostream& stream) const {
    for (const auto& i : bytes) {
        stream << +i << ' ';
    }
    stream << std::endl;

    return stream;
}

BigInt BigInt::Normalize(size_t size) const {
    if (size < bytes.size()) {
        throw std::invalid_argument("BigInt::Normalize(): size must be greater or equal than current size");
    }

    if (size == bytes.size()) {
        return *this;
    }

    BigInt result(*this);

    size_t old_size = result.bytes.size();
    result.bytes.resize(size);

    bool negative = result.bytes[old_size - 1] == 1;
    if (negative) {
        result.bytes[old_size - 1] = 0;
        result.bytes[size - 1] = 1;
    }

    return result;
}

std::ostream& operator<<(std::ostream& stream, const BigInt& value) {
    std::ios::fmtflags f(stream.flags());

    size_t size = value.bytes.size();
    
    if (value.bytes[size - 1] == 1) {
		stream << '-' << (-value);
	} else {
		bool leading_zeros = true;
		for (int16_t i = size - 2; i >= 0; --i) {
			if (leading_zeros) {
				if (value.bytes[i] == 0) {
					continue;
				}
				leading_zeros = false;
				stream << std::hex << std::uppercase << +value.bytes[i];
				continue;
			}
			stream << std::setfill('0') << std::setw(2) << +value.bytes[i];
		}
		if (leading_zeros) {
			stream << 0;
		}
	}

	stream.flags(f);

    return stream;
}
