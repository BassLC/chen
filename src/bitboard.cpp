#include "../include/bitboard.hpp"
#include <array>
#include <cassert>
#include <iostream>

bitboard BitBoard::pop_lsb(bitboard& b) {
    bitboard lsb = b & -b;
    b &= (b - 1);
    return lsb;
}

bitboard BitBoard::pop_msb(bitboard& b) {
    bitboard msb = b;
    msb |= msb >> 32;
    msb |= msb >> 16;
    msb |= msb >> 8;
    msb |= msb >> 4;
    msb |= msb >> 2;
    msb |= msb >> 1;
    msb = (msb >> 1) + 1;
    b &= ~msb;
    return msb;
}

void BitBoard::print(bitboard b) {
    for (int i = 0; i < 64; ++i) {
        std::cout << ((b & 0x8000000000000000) >> 63);
        if ((i + 1) % 8 == 0) {
            std::cout << '\n';
        }
        b <<= 1;
    }
}

square BitBoard::to_square(const bitboard& b) {
    // To see if there is only one bit set in the argument
    // (b has to be a power of two)
    assert((b && !(b & (b - 1))) == 1);

    // Using a DeBruijn Multiplication with an isolated LS1B
    // @LINK: http://chessprogramming.wikispaces.com/BitScan#Bitscan%20forward-De%20Bruijn%20Multiplication-With%20isolated%20LS1B
    const std::array<square, 64> index64 = {
        0,  1,  48, 2,  57, 49, 28, 3,  61, 58, 50, 42, 38, 29, 17, 4,
        62, 55, 59, 36, 53, 51, 43, 22, 45, 39, 33, 30, 24, 18, 12, 5,
        63, 47, 56, 27, 60, 41, 37, 16, 54, 35, 52, 21, 44, 32, 23, 11,
        46, 26, 40, 15, 34, 20, 31, 10, 25, 14, 19, 9,  13, 8,  7,  6};

    const bitboard debruijn64 = 0x03f79d71b4cb0a89;
    return index64[((b & -b) * debruijn64) >> 58];
}

bitboard BitBoard::reverse(bitboard b) {
    // Reverses a bitboard by 180 degrees (a1 is mapped to h8)
    // @LINK: https://www.chessprogramming.org/Flipping_Mirroring_and_Rotating#Rotating
    const bitboard h1 = 0x5555555555555555;
    const bitboard h2 = 0x3333333333333333;
    const bitboard h4 = 0x0F0F0F0F0F0F0F0F;
    const bitboard v1 = 0x00FF00FF00FF00FF;
    const bitboard v2 = 0x0000FFFF0000FFFF;
    b = ((b >> 1) & h1) | ((b & h1) << 1);
    b = ((b >> 2) & h2) | ((b & h2) << 2);
    b = ((b >> 4) & h4) | ((b & h4) << 4);
    b = ((b >> 8) & v1) | ((b & v1) << 8);
    b = ((b >> 16) & v2) | ((b & v2) << 16);
    b = (b >> 32) | (b << 32);
    return b;
}
