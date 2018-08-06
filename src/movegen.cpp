#include "../include/movegen.hpp"

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

bitboard MoveGen::generate_knight_moves(Board& board, const Color& side) {

    const bitboard b = board.get_piece_board(side, Piece::Knights);
    // Generates all knight moves, clockwise starting from UpUpLeft position
    // @TODO: Implement pin awareness
    return ((((b << 17) & ~File::H) |              // UpUpLeft
             ((b << 15) & ~File::A) |              // UpUpRight
             ((b << 6) & ~(File::A | File::B)) |   // UpRightRight
             ((b >> 10) & ~(File::A | File::B)) |  // DownRightRight
             ((b >> 17) & ~(File::A)) |            // DownDownRight
             ((b >> 15) & ~(File::H)) |            // DownDownLeft
             ((b >> 6) & ~(File::G | File::H)) |   // DownLeftLeft
             ((b << 10) & ~(File::G | File::H))) & // UpLeftLeft
            ~board.get_side_board(side));
}
