#include "../include/movegen.hpp"
#include "doctest.h"

TEST_CASE("MoveGen") {
    SUBCASE("Sliding Pieces Generation") {

        SUBCASE("Generate Bishop Moves") {
            SUBCASE("edge of the board") {
                Board b("b");
                auto move_list =
                    MoveGen::generate_bishop_moves(b, Color::Black);
                REQUIRE(move_list.size() == 7);
            }

            SUBCASE("middle of the board") {
                Board b("8/8/8/8/4b3/8/8/8");
                auto move_list =
                    MoveGen::generate_bishop_moves(b, Color::Black);
                REQUIRE(move_list.size() == 13);
            }
        }

        SUBCASE("Generate Queen Moves") {
            SUBCASE("edge of the board") {
                Board b("q");
                auto move_list = MoveGen::generate_queen_moves(b, Color::Black);
                REQUIRE(move_list.size() == 21);
            }

            SUBCASE("middle of the board") {
                Board b("8/8/8/8/4q3/8/8/8");
                auto move_list = MoveGen::generate_queen_moves(b, Color::Black);
                REQUIRE(move_list.size() == 27);
            }
        }

        SUBCASE("Generate Rook Moves") {
            SUBCASE("edge of the board") {
                Board b("r");
                auto move_list = MoveGen::generate_rook_moves(b, Color::Black);
                REQUIRE(move_list.size() == 14);
            }

            SUBCASE("middle of the board") {
                Board b("8/8/8/8/4r3/8/8/8");
                auto move_list = MoveGen::generate_rook_moves(b, Color::Black);
                REQUIRE(move_list.size() == 14);
            }
        }
    }

    SUBCASE("Generate Knight Moves") {
        SUBCASE("edge of the board") {
            Board b("n");
            auto move_list = MoveGen::generate_knight_moves(b, Color::Black);
            REQUIRE(move_list.size() == 2);
        }

        SUBCASE("middle of the board") {
            Board b("8/8/8/8/4n3/8/8/8");
            auto move_list = MoveGen::generate_knight_moves(b, Color::Black);
            REQUIRE(move_list.size() == 8);
        }
    }
}
