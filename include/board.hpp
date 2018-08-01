#ifndef BOARD_HPP
#define BOARD_HPP

#include <cstdint>
#include <unordered_map>

using bitboard = uint64_t;

enum class Piece : char{
    Pawns = 'p',
    Bishops = 'b',
    Knights = 'n',
    Rooks = 'r',
    Queens = 'q',
    King = 'k',
};


class Board {

  public:
    Board();
    ~Board() = default;
    bitboard get_all_white_pieces();
    bitboard get_all_black_pieces();
    void pretty_print();

  private:
    std::unordered_map<Piece, bitboard> m_white_pieces;
    std::unordered_map<Piece, bitboard> m_black_pieces;
};

#endif
