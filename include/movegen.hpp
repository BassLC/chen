#ifndef MOVEGEN_HPP
#define MOVEGEN_HPP

#include "board.hpp"
#include <vector>

struct Move {
    Piece piece_type;
    Color color;
    square from;
    square to;
    // bool is_castling;
    bool is_capture;

    Move(Piece p, Color c, square f, square t)
        : piece_type(std::move(p)), color(std::move(c)), from(std::move(f)),
          to(std::move(t)){};
};

namespace MoveGen {

void print_move(const Move& move);
bitboard movable_pawns(Board& board, const Color& side);

std::vector<Move> generate_pawn_moves(Board& board, const Color& side);
std::vector<Move> generate_bishop_moves(Board& board, const Color& side);
std::vector<Move> generate_knight_moves(Board& board, const Color& side);
std::vector<Move> generate_rook_moves(Board& board, const Color& side);
std::vector<Move> generate_queen_moves(Board& board, const Color& side);
std::vector<Move> generate_king_moves(Board& board, const Color& side);

} // namespace MoveGen
#endif
