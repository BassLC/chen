#include "../include/movegen.hpp"
#include <cassert>

bitboard get_knight_moves_board(const bitboard& knights_board,
                                const bitboard& own_color_board) {
    // Generates all knight pseudo-legal moves for ONE KNIGHT PIECE
    return ((((knights_board << 17) & ~File::H) |              // UpUpLeft
             ((knights_board << 15) & ~File::A) |              // UpUpRight
             ((knights_board << 6) & ~(File::A | File::B)) |   // UpRightRight
             ((knights_board >> 10) & ~(File::A | File::B)) |  // DownRightRight
             ((knights_board >> 17) & ~(File::A)) |            // DownDownRight
             ((knights_board >> 15) & ~(File::H)) |            // DownDownLeft
             ((knights_board >> 6) & ~(File::G | File::H)) |   // DownLeftLeft
             ((knights_board << 10) & ~(File::G | File::H))) & // UpLeftLeft
            ~own_color_board); // Two pieces of the same color can't be in the
                               // same square
}

std::vector<Move> MoveGen::generate_knight_moves(Board& board,
                                                 const Color& side) {
    // @TODO: Make the function work for the Black side

    std::vector<Move> possible_moves;

    bitboard all_knights = board.get_piece_board(Piece::Knight, side);
    const bitboard own_color_board = board.get_color_board(side);

    // While there are knights to generate moves from
    while (all_knights != 0) {
        const bitboard one_knight_pos = BitBoard::pop_lsb(all_knights);
        bitboard moves =
            get_knight_moves_board(one_knight_pos, own_color_board);

        // While there are moves to process
        while (moves != 0) {
            possible_moves.emplace_back(
                Piece::Knight, side, BitBoard::to_square(one_knight_pos),
                BitBoard::to_square(BitBoard::pop_lsb(moves)));
        }
    }

    return possible_moves;
}
