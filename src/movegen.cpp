#include "../include/movegen.hpp"
#include <cassert>

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

square to_square(bitboard b) {
    // To see if there is only one bit set in the argument
    // (b has to be a power of two)
    assert((b && !(b & (b - 1))) == 1);

    // Using a DeBruijn Multiplication with an isolated LS1B
    // For more info:
    // http://chessprogramming.wikispaces.com/BitScan#Bitscan%20forward-De%20Bruijn%20Multiplication-With%20isolated%20LS1B
    const square index64[64] = {
        0,  1,  48, 2,  57, 49, 28, 3,  61, 58, 50, 42, 38, 29, 17, 4,
        62, 55, 59, 36, 53, 51, 43, 22, 45, 39, 33, 30, 24, 18, 12, 5,
        63, 47, 56, 27, 60, 41, 37, 16, 54, 35, 52, 21, 44, 32, 23, 11,
        46, 26, 40, 15, 34, 20, 31, 10, 25, 14, 19, 9,  13, 8,  7,  6};

    const bitboard debruijn64 = 0x03f79d71b4cb0a89;
    return index64[((b & -b) * debruijn64) >> 58];
}

bitboard get_lsb(const bitboard& b) { return b & (-b); }
void clear_lsb(bitboard& b) { b &= (b - 1); }

std::vector<Move> MoveGen::generate_knight_moves(Board& board,
                                                 const Color& side) {
    // @TODO: Make the function work for the Black side
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
