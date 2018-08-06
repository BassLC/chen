#ifndef MOVEGEN_HPP
#define MOVEGEN_HPP

#include "board.hpp"
#include <vector>

using Square = uint8_t;

struct Move {
    Piece piece_type;
    Color color;
    Square from;
    Square to;
    // bool is_castling;
    // bool is_capture;
};

namespace MoveGen {

bitboard movable_pawns(Board& board, const Color& side);

std::vector<Move> generate_pawn_moves(Board& board, const Color& side);
std::vector<Move> generate_bishop_moves(Board& board, const Color& side);
bitboard generate_knight_moves(Board& board, const Color& side);
std::vector<Move> generate_rook_moves(Board& board, const Color& side);
std::vector<Move> generate_queen_moves(Board& board, const Color& side);
std::vector<Move> generate_king_moves(Board& board, const Color& side);

} // namespace MoveGen

#endif
