#pragma once
#include <cinttypes>
#include <iostream>


struct int2025_t {
    static const int size = 254;
    uint8_t data[size];
};

static_assert(sizeof(int2025_t) <= 254,  "Size of int2025_t must be no higher than 254 bytes");

int2025_t from_int(int32_t i);  

int2025_t from_string(const char* buff);

int2025_t operator+(const int2025_t& lhs, const int2025_t& rhs);

int2025_t operator-(const int2025_t& lhs, const int2025_t& rhs);

int2025_t operator*(const int2025_t& lhs, const int2025_t& rhs);

int2025_t operator/(const int2025_t& lhs, const int2025_t& rhs);

bool operator==(const int2025_t& lhs, const int2025_t& rhs);

bool operator!=(const int2025_t& lhs, const int2025_t& rhs);

std::ostream& operator<<(std::ostream& stream, const int2025_t& value);

bool is_zero(const int2025_t &num);
int get_bit(const int2025_t &num, int index);
int2025_t set_bit(const int2025_t &num, int bit_pos);
int2025_t shift_left(const int2025_t &num);
int compare(const int2025_t &a, const int2025_t &b);
int2025_t negate(const int2025_t &num);
bool is_negativ(const int2025_t &num);