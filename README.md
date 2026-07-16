# Arbitrary-Precision Integer in C++

A custom arbitrary-precision unsigned integer implementation written in C++. The `BigNum` class stores integers as a dynamic sequence of base-256 bytes, allowing values much larger than the limits of built-in integer types.

> Despite the repository name, the current implementation is written in **C++**, not C.

## Features

- Construction from decimal strings
- Internal little-endian base-256 representation
- Conversion from decimal text to the internal byte representation
- Conversion from the internal representation back to decimal text
- Addition between two `BigNum` objects
- Addition between a `BigNum` and a decimal string
- Subtraction between two `BigNum` objects
- Subtraction between a `BigNum` and a decimal string
- Equality comparison with another `BigNum`
- Equality comparison with a decimal string
- Raw-byte visualization for debugging
- Support for integers far larger than `unsigned long long`
- Stress-test example using a very large decimal value

## Technologies Used

- C++
- C++ Standard Library
- `std::vector<uint8_t>`
- `std::string`
- Operator overloading
- Base conversion
- Manual carry and borrow propagation
- File output with `std::ofstream`

## Project Structure

```text
.
├── BigNum.h      # BigNum class declaration
├── BigNum.cpp    # Arithmetic and conversion implementation
├── main.cpp      # Large-number demonstration and output-file generation
└── README.md     # Project documentation
```

## Internal Representation

Each number is stored in:

```cpp
std::vector<uint8_t> Big;
```

Every element represents one base-256 digit. The least significant byte is stored first, which makes carry and borrow propagation easier during arithmetic operations.

For example, the decimal number `513` is equivalent to:

```text
513 = 1 × 256 + 1
```

Its internal byte representation is therefore conceptually:

```text
[1, 2]
```

## Conversion Strategy

### Decimal string to base 256

For each decimal digit, the current byte vector is multiplied by `10`, the new digit is added, and carries are propagated in base 256.

### Base 256 to decimal string

The conversion processes the bytes from most significant to least significant using the recurrence:

```text
result = result × 256 + current_byte
```

Decimal multiplication and addition are performed manually with strings so that the conversion does not depend on fixed-width integer types.

## Requirements

- G++
- A C++17-compatible compiler

On Ubuntu or Debian:

```bash
sudo apt update
sudo apt install build-essential
```

## How to Compile

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp BigNum.cpp -o bignum_demo
```

## How to Run

Linux or macOS:

```bash
./bignum_demo
```

Windows with MinGW:

```powershell
.\bignum_demo.exe
```

The current demonstration creates a very large number, adds it to itself three times, converts the result back to decimal, and writes the result to:

```text
resultado1
```

To inspect the generated file on Linux or macOS:

```bash
cat resultado1
```

## Usage Example

```cpp
#include "BigNum.h"
#include <iostream>

int main() {
    BigNum first("123456789012345678901234567890");
    BigNum second("987654321098765432109876543210");

    BigNum sum = first + second;

    std::cout << sum.DesConverte() << '\n';
    return 0;
}
```

Compile the example together with `BigNum.cpp`:

```bash
g++ -std=c++17 example.cpp BigNum.cpp -o example
```

## What I Implemented

I implemented an arbitrary-precision integer class without using external big-number libraries. The project includes decimal parsing, a compact base-256 byte representation, manual carry and borrow propagation, overloaded arithmetic and comparison operators, and conversion back to a printable decimal string.

## Current Limitations

- The implementation currently supports only non-negative integers.
- Subtraction terminates the program when the result would be negative.
- Multiplication is not exposed as a `BigNum` operator.
- Division and modulo are not implemented.
- The greater-than operator is declared but not completed.
- Factorial and stream extraction are declared or started but not completed.
- Leading-zero normalization can be improved.
- The current `main.cpp` is a stress-test demonstration rather than an interactive calculator.

## What I Learned

- How arbitrary-precision arithmetic works internally
- How to represent large integers as arrays of smaller digits
- How base 10 and base 256 conversion can be implemented manually
- How carry and borrow propagation work across multiple bytes
- How operator overloading can make a custom numeric type easier to use
- How memory usage grows dynamically with the size of a number
- Why built-in numeric types are insufficient for extremely large values
- How to test arithmetic with numbers containing thousands of decimal digits

## Possible Improvements

- Implement multiplication, division, and modulo operators
- Add signed-number support
- Complete relational operators such as `<`, `>`, `<=`, and `>=`
- Normalize leading zero bytes after arithmetic operations
- Replace process termination with exceptions or error results
- Add automated tests using known large-number values
- Add a Makefile or CMake configuration
- Convert the demonstration into an interactive calculator
- Benchmark the implementation against established arbitrary-precision libraries

## Author

Developed by [Rafael Gonçalves Moreira](https://github.com/Rafaelgm04).
