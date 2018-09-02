#include "../include/movegen.hpp"
#include "doctest.h"

TEST_CASE("MoveGen") {
    SUBCASE("Sliding Pieces Generation") {

        SUBCASE("Generate Bishop Moves") {
            SUBCASE("edge of the board") {
                Board b("b");
                auto move_list =
                    MoveGen::generate_moves(b, {{Piece::Bishop, Color::Black}});
                REQUIRE(move_list.size() == 7);
            }

            SUBCASE("middle of the board") {
                Board b("8/8/8/8/4b3/8/8/8");
                auto move_list =
                    MoveGen::generate_moves(b, {{Piece::Bishop, Color::Black}});
                REQUIRE(move_list.size() == 13);
            }
        }

        SUBCASE("Generate Queen Moves") {
            SUBCASE("edge of the board") {
                Board b("q");
                auto move_list = MoveGen::generate_moves(b, {{Piece::Queen, Color::Black}});
                REQUIRE(move_list.size() == 21);
            }

            SUBCASE("middle of the board") {
                Board b("8/8/8/8/4q3/8/8/8");
                auto move_list = MoveGen::generate_moves(b, {{Piece::Queen, Color::Black}});
                REQUIRE(move_list.size() == 27);
            }
        }

        SUBCASE("Generate Rook Moves") {
            SUBCASE("edge of the board") {
                Board b("r");
                auto move_list = MoveGen::generate_moves(b, {{Piece::Rook, Color::Black}});
                REQUIRE(move_list.size() == 14);
            }

            SUBCASE("middle of the board") {
                Board b("8/8/8/8/4r3/8/8/8");
                auto move_list = MoveGen::generate_moves(b, {{Piece::Rook, Color::Black}});
                REQUIRE(move_list.size() == 14);
            }
        }
    }

    SUBCASE("Generate Knight Moves") {
        SUBCASE("edge of the board") {
            Board b("n");
            auto move_list = MoveGen::generate_moves(b, {{Piece::Knight, Color::Black}});
            REQUIRE(move_list.size() == 2);
        }

        SUBCASE("middle of the board") {
            Board b("8/8/8/8/4n3/8/8/8");
            auto move_list = MoveGen::generate_moves(b, {{Piece::Knight, Color::Black}});
            REQUIRE(move_list.size() == 8);
        }
    }

    SUBCASE("Generate King Moves") {
        SUBCASE("edge of the board") {
            Board b("k");
            auto move_list = MoveGen::generate_moves(b, {{Piece::King, Color::Black}});
            REQUIRE(move_list.size() == 3);
        }

        SUBCASE("middle of the board") {
            Board b("8/8/8/8/4k3/8/8/8");
            auto move_list = MoveGen::generate_moves(b, {{Piece::King, Color::Black}});
            REQUIRE(move_list.size() == 8);
        }
    }
}
