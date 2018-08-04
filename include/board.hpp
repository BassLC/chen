#ifndef BOARD_HPP
#define BOARD_HPP

#include <cstdint>
#include <unordered_map>

using bitboard = uint64_t;

enum class Piece : char {
    Pawns = 'p',
    Bishops = 'b',
    Knights = 'n',
    Rooks = 'r',
    Queens = 'q',
    King = 'k',
};

enum class Color : bool {
    White = 0,
    Black = 1,
};

class Board {

  public:
    Board();
    ~Board() = default;
    bitboard get_side_board(const Color& side) noexcept;
    bitboard get_piece_board(const Color& side,
                             const Piece& piece_type) noexcept;
    std::string pretty_string();
    void pretty_print();

  private:
    std::unordered_map<Color, std::unordered_map<Piece, bitboard>>
        m_board_state;
};

#endif
