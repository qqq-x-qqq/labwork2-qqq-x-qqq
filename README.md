# int2025 Big Integer

Custom fixed-size signed integer type for working with 2025-bit values in C++.

## Features

- Conversion from `int32_t`
- Parsing from string
- Addition, subtraction, multiplication, and division
- Comparison operators
- Stream output
- Wrap-around overflow behavior

## Tech Stack

- C++
- Bitwise operations
- Custom arithmetic
- Operator overloading
- CMake

## Project Structure

- `lib/number.h` — type declaration
- `lib/number.cpp` — arithmetic implementation
- `tests/` — unit tests
- `bin/` — small demo executable

## Run Tests

```bash
cmake --build build --target number_tests
build/tests/number_tests
```

## Notes

The project demonstrates low-level arithmetic, memory-aware design, and implementation of a non-standard numeric type without using standard containers for the core logic.
