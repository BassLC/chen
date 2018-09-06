#ifndef MOVEGEN_HPP
#define MOVEGEN_HPP

#include "board.hpp"
#include <vector>

namespace MoveGen {

std::vector<Move>
generate_moves(Board& board,
               const std::vector<std::pair<Piece, Color>>& pieces);
} // namespace MoveGen
#endif
