#ifndef BOARD_HPP
#define BOARD_HPP

#include <cstdint>
#include <unordered_map>
#include "bitboard.hpp"

enum class Piece : char {
    Pawn = 'p',
    Bishop = 'b',
    Knight = 'n',
    Rook = 'r',
    Queen = 'q',
    King = 'k',
};

enum class Color : bool {
    White = 0,
    Black = 1,
};

class Board {

  public:
    Board(const std::string& fen_notation);
    Board();
    ~Board() = default;
    bitboard get_color_board(const Color& side) noexcept;
    bitboard get_piece_board(const Piece& piece_type,
                             const Color& side) noexcept;
    std::string pretty_string();
    void pretty_print();

  private:
    std::unordered_map<Color, std::unordered_map<Piece, bitboard>>
        m_board_state;
};

#endif
