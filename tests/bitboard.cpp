#include "doctest.h"
#include "../include/bitboard.hpp"
#include <random>

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

    SUBCASE("reverse") {
        srand(time(NULL));
        for (int i = 0; i < 10000; ++i) {
            bitboard rev = 0;
            const bitboard numb = rand();
            bitboard temp = numb; 
            for (int i = 0; i < 64; ++i) {
                rev += (temp & 0b1) << (63-i);
                temp >>= 1;
            }

            REQUIRE(BitBoard::reverse(numb) == rev);
        }
    }
}
