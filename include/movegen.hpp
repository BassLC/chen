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
std::vector<Move>
generate_moves(Board& board,
               const std::vector<std::pair<Piece, Color>>& pieces);

} // namespace MoveGen
#endif
