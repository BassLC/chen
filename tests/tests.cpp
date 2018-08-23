#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/board.hpp"
#include "../include/movegen.hpp"
#include <iostream>

TEST_CASE("BitBoard") {
    SUBCASE("pop_lsb") {
        for(bitboard i = 1; i != 0; i <<= 1) {
            bitboard temp = i;
            CHECK(BitBoard::pop_lsb(temp) == i);
            CHECK(temp == 0);
        }

        bitboard i = 0b1001;
        CHECK(BitBoard::pop_lsb(i) == 0b1);
        CHECK(i == 0b1000);
    }

    SUBCASE("pop_msb") {
        for(bitboard i = 1; i != 0; i <<= 1) {
            bitboard temp = i;
            CHECK(BitBoard::pop_msb(temp) == i);
            CHECK(temp == 0);
        }

        bitboard i = 0b1001;
        CHECK(BitBoard::pop_msb(i) == 0b1000);
        CHECK(i == 0b0001);
    }

    SUBCASE("to_square") {
        for(bitboard b = 1; b != 0; b <<= 1) {
            bitboard temp = b;
            for (square i = 0; i < 64; ++i) {
                if ((temp & 0b1) == 1) {
                    REQUIRE(BitBoard::to_square(b) == i);
                    break;
                }
                temp >>= 1;
            }
        }
    }
}
