#include "../include/movegen.hpp"
#include "doctest.h"

uint64_t perft(Board& b, int depth) {
    const Color side = b.get_side_to_play();
    auto moves = MoveGen::generate_moves(b, {{Piece::Pawn, side},
                                             {Piece::Bishop, side},
                                             {Piece::Knight, side},
                                             {Piece::Rook, side},
                                             {Piece::Queen, side},
                                             {Piece::King, side}});
    uint64_t nodes = 0;
    if (depth == 0) {
        return 1;
    }
    for (auto move : moves) {
        b.apply_move(move);
        nodes += perft(b, depth - 1);
        b.undo_move();
    }
    return nodes;
};

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

            SUBCASE("capture") {
                Board b("P5P1/1P3P2/2P1P3/3b4/2P1P3/1P3P2/P5P1/7P");
                auto move_list =
                    MoveGen::generate_moves(b, {{Piece::Bishop, Color::Black}});
                REQUIRE(move_list.size() == 4);
                for (auto m : move_list) {
                    REQUIRE(m.is_capture == 1);
                }
            }
        }

        SUBCASE("Generate Queen Moves") {
            SUBCASE("edge of the board") {
                Board b("q");
                auto move_list =
                    MoveGen::generate_moves(b, {{Piece::Queen, Color::Black}});
                REQUIRE(move_list.size() == 21);
            }

            SUBCASE("middle of the board") {
                Board b("8/8/8/8/4q3/8/8/8");
                auto move_list =
                    MoveGen::generate_moves(b, {{Piece::Queen, Color::Black}});
                REQUIRE(move_list.size() == 27);
            }

            SUBCASE("capture") {
                Board b(
                    "P2P2P1/1P1P1P2/2PPP3/PPPqPPPP/2PPP3/1P1P1P2/P2P2P1/3P3P");
                auto move_list =
                    MoveGen::generate_moves(b, {{Piece::Queen, Color::Black}});
                REQUIRE(move_list.size() == 8);
                for (auto m : move_list) {
                    REQUIRE(m.is_capture == 1);
                }
            }
        }

        SUBCASE("Generate Rook Moves") {
            SUBCASE("edge of the board") {
                Board b("r");
                auto move_list =
                    MoveGen::generate_moves(b, {{Piece::Rook, Color::Black}});
                REQUIRE(move_list.size() == 14);
            }

            SUBCASE("middle of the board") {
                Board b("8/8/8/8/4r3/8/8/8");
                auto move_list =
                    MoveGen::generate_moves(b, {{Piece::Rook, Color::Black}});
                REQUIRE(move_list.size() == 14);
            }

            SUBCASE("capture") {
                Board b("3P4/3P4/3P4/PPPrPPPP/3P4/3P4/3P4/3P4");
                auto move_list =
                    MoveGen::generate_moves(b, {{Piece::Rook, Color::Black}});
                REQUIRE(move_list.size() == 4);
                for (auto m : move_list) {
                    REQUIRE(m.is_capture == 1);
                }
            }
        }
    }

    SUBCASE("Generate Knight Moves") {
        SUBCASE("edge of the board") {
            Board b("n");
            auto move_list =
                MoveGen::generate_moves(b, {{Piece::Knight, Color::Black}});
            REQUIRE(move_list.size() == 2);
        }

        SUBCASE("middle of the board") {
            Board b("8/8/8/8/4n3/8/8/8");
            auto move_list =
                MoveGen::generate_moves(b, {{Piece::Knight, Color::Black}});
            REQUIRE(move_list.size() == 8);
        }

        SUBCASE("capture") {
            Board b("2P1P3/1P3P2/3n4/1P3P2/2P1P3");
            auto move_list =
                MoveGen::generate_moves(b, {{Piece::Knight, Color::Black}});
            REQUIRE(move_list.size() == 8);
            for (auto m : move_list) {
                REQUIRE(m.is_capture == 1);
            }
        }
    }

    SUBCASE("Generate King Moves") {
        SUBCASE("edge of the board") {
            Board b("k");
            auto move_list =
                MoveGen::generate_moves(b, {{Piece::King, Color::Black}});
            REQUIRE(move_list.size() == 3);
        }

        SUBCASE("middle of the board") {
            Board b("8/8/8/8/4k3/8/8/8");
            auto move_list =
                MoveGen::generate_moves(b, {{Piece::King, Color::Black}});
            REQUIRE(move_list.size() == 8);
        }

        SUBCASE("capture") {
            Board b("2PPP3/2PkP3/2PPP3");
            auto move_list =
                MoveGen::generate_moves(b, {{Piece::King, Color::Black}});
            REQUIRE(move_list.size() == 8);
            for (auto m : move_list) {
                REQUIRE(m.is_capture == 1);
            }
        }
    }

    SUBCASE("Generate Pawn Moves") {
        SUBCASE("starting position") {
            Board b;
            auto move_list =
                MoveGen::generate_moves(b, {{Piece::Pawn, Color::Black}});
            REQUIRE(move_list.size() == 16);
        }

        SUBCASE("middle of the board") {
            Board b("8/8/8/8/4p3/8/8/8");
            auto move_list =
                MoveGen::generate_moves(b, {{Piece::Pawn, Color::Black}});
            REQUIRE(move_list.size() == 1);
        }

        SUBCASE("capture") {
            Board b("4p3/3NPN2");
            auto move_list =
                MoveGen::generate_moves(b, {{Piece::Pawn, Color::Black}});
            REQUIRE(move_list.size() == 2);
            for (auto m : move_list) {
                REQUIRE(m.is_capture == 1);
            }
        }
    }
    SUBCASE("Perft") {
        Board b;
        REQUIRE(perft(b, 0) == 1);
        REQUIRE(perft(b, 1) == 20);
        REQUIRE(perft(b, 2) == 400);
        REQUIRE(perft(b, 3) == 8902);
    }
}
