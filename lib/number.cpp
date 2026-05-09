#include "number.h"

int2025_t from_int(int32_t i) {
    int2025_t result;

    for (int j = 0;j < int2025_t::size; j++) {
        result.data[j] = 0;
    }

    for (int j = 0; j < 4; j++){
        result.data[j] = (i >> (j * 8)) & 0xFF;
    }

    if (i < 0) {
        for (int j = 4; j < int2025_t::size; j++) {
            result.data[j] = 0xFF;
        }
    }
    return result;
}

int2025_t from_string(const char* buff) {
    int2025_t result;
    int2025_t ten = from_int(10);
    for (int j = 0; j < int2025_t::size; j++)
    {
        result.data[j] = 0;
    }
    bool negativ = false;
    if (*buff == '-') {
        negativ = true;
        buff++;
    }
    if (*buff == '+') buff++;
    while (*buff >= '0' && *buff <= '9')
    {
        int digit = *buff - '0';
        result = result * ten + from_int(digit);
        buff++;
    }
    if (negativ) {
        return negate(result);
    }

    return result;
}

int2025_t operator+(const int2025_t& lhs, const int2025_t& rhs) {
    int2025_t result;
    for (int j = 0; j < int2025_t::size; j++) {
        result.data[j] = 0;
    }
    uint16_t transfer = 0;
    for (int i = 0; i < int2025_t::size; i++) {
        uint16_t sum = (uint16_t)lhs.data[i] + (uint16_t)rhs.data[i] + transfer;
        result.data[i] = sum & 0xFF;
        transfer = sum >> 8;
    }

    return result; 
}

int2025_t operator-(const int2025_t &lhs, const int2025_t &rhs)
{
    return lhs + negate(rhs);
}

int2025_t operator*(const int2025_t& lhs, const int2025_t& rhs) {
    int2025_t result;
    int2025_t copy_lhs = lhs;
    for (int j = 0; j < int2025_t::size; j++) {
        result.data[j] = 0;
    }
    for (int i = 0; i < int2025_t::size*8; i++) {
        if (get_bit(rhs, i)) {
            result = result + copy_lhs;
        }
        copy_lhs = copy_lhs + copy_lhs;
    }
    return result;
}


int2025_t operator/(const int2025_t& lhs, const int2025_t& rhs) {
    int2025_t result;
    for (int j = 0; j < int2025_t::size; j++) {
        result.data[j] = 0;
    }
    if (is_zero(rhs)) return result;

    bool negative = is_negativ(lhs) != is_negativ(rhs);
    int2025_t dividend = is_negativ(lhs) ? negate(lhs) : lhs;
    int2025_t divisor = is_negativ(rhs) ? negate(rhs) : rhs;
    if (compare(dividend,divisor) == -1) {
        return from_int(0);
    }

    int2025_t quotient = from_int(0);
    int2025_t remainder = from_int(0);

    for(int bit_pos = int2025_t::size * 8 - 1; bit_pos >= 0; bit_pos--) {
        remainder = shift_left(remainder); 
        if (get_bit(dividend, bit_pos)) {
            remainder = set_bit(remainder, 0);
        }
        if (compare(remainder, divisor) >= 0) {
            remainder = remainder - divisor;
            quotient = set_bit(quotient, bit_pos);
        }
    }

    return negative ? negate(quotient) : quotient;
}

int2025_t set_bit(const int2025_t& num, int bit_pos) {
    int2025_t result = num;
    int byte_index = bit_pos / 8;
    int bit_index = bit_pos % 8;
    result.data[byte_index] |= (1 << bit_index);
    return result;
}

int2025_t shift_left (const int2025_t& num) {
    int2025_t result;
    for (int j = 0; j < int2025_t::size; j++)
    {
        result.data[j] = 0;
    }
    uint8_t next = 0;
    for (int i = 0; i < int2025_t::size; i++) {
        uint16_t temp = ((uint16_t)num.data[i] << 1) | next;
        result.data[i] = temp & 0xFF;
        next = (temp >> 8) & 1;
    }
    return result;
}


int compare(const int2025_t& a, const int2025_t& b) {
    bool a_neg = (a.data[int2025_t::size - 1] & 0x80) != 0;
    bool b_neg = (b.data[int2025_t::size - 1] & 0x80) != 0;

    // если знаки разные
    if (a_neg != b_neg)
        return a_neg ? -1 : 1;

    // если оба >= 0 — обычное сравнение
    // если оба < 0 — инвертированная логика в старших байтах
    for (int i = int2025_t::size - 1; i >= 0; i--)
    {
        if (a.data[i] != b.data[i])
        {
            if (!a_neg)
                return a.data[i] < b.data[i] ? -1 : 1;
            else
                return a.data[i] < b.data[i] ? 1 : -1;
        }
    }
    return 0;
}

int2025_t negate (const int2025_t& x) {
    int2025_t r;
    uint16_t carry = 1;
    for (int i = 0; i < int2025_t::size; i++)
    {
        uint16_t v = (~x.data[i] & 0xFF) + carry;
        r.data[i] = v & 0xFF;
        carry = v >> 8;
    }
    return r;
}

bool is_zero(const int2025_t& num) {
    for (int i = 0; i < int2025_t::size; i++) {
        if (num.data[i] != 0) {
            return false;
        }
    }
    return true;
}

bool operator==(const int2025_t& lhs, const int2025_t& rhs) {
    for (int i = 0; i < int2025_t::size; i++) {
        if (lhs.data[i] != rhs.data[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const int2025_t& lhs, const int2025_t& rhs) {
    for (int i = 0; i < int2025_t::size; i++)
    {
        if (lhs.data[i] != rhs.data[i])
        {
            return true;
        }
    }
    return false;
}

std::ostream &operator<<(std::ostream &stream, const int2025_t &value)
{
    bool have_zero = false;

    for (int i = int2025_t::size - 1; i >= 0; i--)
    {
        if (value.data[i] != 0 || have_zero)
        {
            stream << std::hex << (int)value.data[i];
            have_zero = true;
        }
    }
    if (!have_zero)
    {
        stream << "0";
    }
    return stream;
}

bool is_negativ(const int2025_t &num)
{
    return (num.data[int2025_t::size - 1] & 0x80) != 0;
}

int get_bit(const int2025_t &num, int index)
{
    int byte_index = index / 8;
    int bit_index = index % 8;
    return (num.data[byte_index] >> bit_index) & 1;
}

// uint8_t binpow(uint8_t base, uint8_t exp)
// {
//     uint8_t res = 1;
//     while (exp > 0)
//     {
//         if (exp % 2 == 1)
//         {
//             res *= base;
//         }
//         base *= base;
//         exp /= 2;
//     }
//     return res;
// }