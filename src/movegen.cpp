#include "../include/movegen.hpp"
#include <cassert>
#include <iostream> // @TODO: Remove this header

namespace File {
constexpr bitboard A = 0x8080808080808080;
constexpr bitboard B = 0x4040404040404040;
// constexpr bitboard C = 0x2020202020202020;
// constexpr bitboard D = 0x1010101010101010;
// constexpr bitboard E = 0x0808080808080808;
// constexpr bitboard F = 0x0404040404040404;
constexpr bitboard G = 0x0202020202020202;
constexpr bitboard H = 0x0101010101010101;
} // namespace File

bitboard get_knight_moves_board(const bitboard& knights_board,
                                const bitboard& side_board) {
    // Generates all knight pseudo-legal moves, clockwise starting from UpUpLeft
    // position
    // @TODO: Make it generate only legal moves

    return ((((knights_board << 17) & ~File::H) |              // UpUpLeft
             ((knights_board << 15) & ~File::A) |              // UpUpRight
             ((knights_board << 6) & ~(File::A | File::B)) |   // UpRightRight
             ((knights_board >> 10) & ~(File::A | File::B)) |  // DownRightRight
             ((knights_board >> 17) & ~(File::A)) |            // DownDownRight
             ((knights_board >> 15) & ~(File::H)) |            // DownDownLeft
             ((knights_board >> 6) & ~(File::G | File::H)) |   // DownLeftLeft
             ((knights_board << 10) & ~(File::G | File::H))) & // UpLeftLeft
            ~side_board); // Two pieces can't be in the same square
}

Square to_square(bitboard b) {
    // To see if there is only one bit set in the argument
    assert((b && !(b & (b - 1))) == 0);

    for (uint8_t i = 0; i < 64; ++i) {
        if ((b & 0b1) == 1) {
            return i;
        }
        b >>= 1;
    }

    return 0;
}

bitboard get_lsb(const bitboard& b) { return b & (-b); }
void clear_lsb(bitboard& b) { b &= (b - 1); }

std::vector<Move> MoveGen::generate_knight_moves(Board& board,
                                                 const Color& side) {
    std::vector<Move> possible_moves;
    for (bitboard all_knights_pos = board.get_piece_board(Piece::Knight, side);
         all_knights_pos != 0; clear_lsb(all_knights_pos)) {

        bitboard one_knight_pos = get_lsb(all_knights_pos);

        for (bitboard moves = get_knight_moves_board(
                 one_knight_pos, board.get_color_board(side));
             moves != 0; clear_lsb(moves)) {

            possible_moves.emplace_back(Piece::Knight, side,
                                        to_square(one_knight_pos),
                                        to_square(get_lsb(moves)));
        }
    }

    return possible_moves;
}
