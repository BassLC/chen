#ifndef BOARD_HPP
#define BOARD_HPP

#include "bitboard.hpp"
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

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

struct Move {
    Piece piece_type;
    Color color;
    square from;
    square to;
    // bool is_castling;
    bool is_capture;

    Move(Piece p, Color c, square f, square t, bool cap)
        : piece_type(std::move(p)), color(std::move(c)), from(std::move(f)),
          to(std::move(t)), is_capture(std::move(cap)){};

    void print() const {
        std::cout << "\nPIECE: " << static_cast<char>(piece_type)
                  << "\nCOLOR: " << static_cast<bool>(color)
                  << "\nFROM: " << static_cast<int>(from)
                  << "\nTO: " << static_cast<int>(to)
                  << "\nIS CAPTURE: " << is_capture << "\n\n";
    }
};

class Board {

  public:
    Board(const std::string& fen_notation);
    Board();
    ~Board() = default;

    bitboard get_color_board(const Color& side) noexcept;
    bitboard get_piece_board(const Piece& piece_type,
                             const Color& side) noexcept;

    void apply_move(const Move& move);
    void undo_last_move();

    Color get_side_to_play() const;

    std::string pretty_string();
    void pretty_print();

  private:
    std::unordered_map<Color, std::unordered_map<Piece, bitboard>>
        m_board_state;
    Color m_side_to_play;
    std::vector<Move> m_move_list;
};

#endif
