#include "../include/movegen.hpp"
#include <iostream>

// @TODO:
// - Make generate_<piece> function modular
// - Test for captures
const std::array<bitboard, 64> rank_mask{
    Rank::ONE,   Rank::ONE,   Rank::ONE,   Rank::ONE,   Rank::ONE,
    Rank::ONE,   Rank::ONE,   Rank::ONE,   Rank::TWO,   Rank::TWO,
    Rank::TWO,   Rank::TWO,   Rank::TWO,   Rank::TWO,   Rank::TWO,
    Rank::TWO,   Rank::THREE, Rank::THREE, Rank::THREE, Rank::THREE,
    Rank::THREE, Rank::THREE, Rank::THREE, Rank::THREE, Rank::FOUR,
    Rank::FOUR,  Rank::FOUR,  Rank::FOUR,  Rank::FOUR,  Rank::FOUR,
    Rank::FOUR,  Rank::FOUR,  Rank::FIVE,  Rank::FIVE,  Rank::FIVE,
    Rank::FIVE,  Rank::FIVE,  Rank::FIVE,  Rank::FIVE,  Rank::FIVE,
    Rank::SIX,   Rank::SIX,   Rank::SIX,   Rank::SIX,   Rank::SIX,
    Rank::SIX,   Rank::SIX,   Rank::SIX,   Rank::SEVEN, Rank::SEVEN,
    Rank::SEVEN, Rank::SEVEN, Rank::SEVEN, Rank::SEVEN, Rank::SEVEN,
    Rank::SEVEN, Rank::EIGHT, Rank::EIGHT, Rank::EIGHT, Rank::EIGHT,
    Rank::EIGHT, Rank::EIGHT, Rank::EIGHT, Rank::EIGHT};

const std::array<bitboard, 64> file_mask{
    File::H, File::G, File::F, File::E, File::D, File::C, File::B, File::A,
    File::H, File::G, File::F, File::E, File::D, File::C, File::B, File::A,
    File::H, File::G, File::F, File::E, File::D, File::C, File::B, File::A,
    File::H, File::G, File::F, File::E, File::D, File::C, File::B, File::A,
    File::H, File::G, File::F, File::E, File::D, File::C, File::B, File::A,
    File::H, File::G, File::F, File::E, File::D, File::C, File::B, File::A,
    File::H, File::G, File::F, File::E, File::D, File::C, File::B, File::A,
    File::H, File::G, File::F, File::E, File::D, File::C, File::B, File::A,
};

const std::array<bitboard, 64> diag_mask{
    0x1,
    0x0102,
    0x010204,
    0x01020408,
    0x0102040810,
    0x010204081020,
    0x01020408102040,
    0x0102040810204080,
    0x0102,
    0x010204,
    0x01020408,
    0x0102040810,
    0x010204081020,
    0x01020408102040,
    0x0102040810204080,
    0x0204081020408000,
    0x010204,
    0x01020408,
    0x0102040810,
    0x010204081020,
    0x01020408102040,
    0x0102040810204080,
    0x0204081020408000,
    0x0408102040800000,
    0x01020408,
    0x0102040810,
    0x010204081020,
    0x01020408102040,
    0x0102040810204080,
    0x0204081020408000,
    0x0408102040800000,
    0x0810204080000000,
    0x0102040810,
    0x010204081020,
    0x01020408102040,
    0x0102040810204080,
    0x0204081020408000,
    0x0408102040800000,
    0x0810204080000000,
    0x1020408000000000,
    0x010204081020,
    0x01020408102040,
    0x0102040810204080,
    0x0204081020408000,
    0x0408102040800000,
    0x0810204080000000,
    0x1020408000000000,
    0x2040800000000000,
    0x01020408102040,
    0x0102040810204080,
    0x0204081020408000,
    0x0408102040800000,
    0x0810204080000000,
    0x1020408000000000,
    0x2040800000000000,
    0x4080000000000000,
    0x0102040810204080,
    0x0204081020408000,
    0x0408102040800000,
    0x0810204080000000,
    0x1020408000000000,
    0x2040800000000000,
    0x4080000000000000,
    0x8000000000000000,
};

const std::array<bitboard, 64> anti_diag_mask{
    0x8040201008040201,
    0x80402010080402,
    0x804020100804,
    0x8040201008,
    0x80402010,
    0x804020,
    0x8040,
    0x80,
    0x4020100804020100,
    0x8040201008040201,
    0x80402010080402,
    0x804020100804,
    0x8040201008,
    0x80402010,
    0x804020,
    0x8040,
    0x2010080402010000,
    0x4020100804020100,
    0x8040201008040201,
    0x80402010080402,
    0x804020100804,
    0x8040201008,
    0x80402010,
    0x804020,
    0x1008040201000000,
    0x2010080402010000,
    0x4020100804020100,
    0x8040201008040201,
    0x80402010080402,
    0x804020100804,
    0x8040201008,
    0x80402010,
    0x0804020100000000,
    0x1008040201000000,
    0x2010080402010000,
    0x4020100804020100,
    0x8040201008040201,
    0x80402010080402,
    0x804020100804,
    0x8040201008,
    0x0402010000000000,
    0x0804020100000000,
    0x1008040201000000,
    0x2010080402010000,
    0x4020100804020100,
    0x8040201008040201,
    0x80402010080402,
    0x804020100804,
    0x0201000000000000,
    0x0402010000000000,
    0x0804020100000000,
    0x1008040201000000,
    0x2010080402010000,
    0x4020100804020100,
    0x8040201008040201,
    0x80402010080402,
    0x0100000000000000,
    0x0201000000000000,
    0x0402010000000000,
    0x0804020100000000,
    0x1008040201000000,
    0x2010080402010000,
    0x4020100804020100,
    0x8040201008040201,
};

bitboard get_line_moves_board(Board& board, const bitboard& piece_board,
                              const std::array<bitboard, 64>& masks) {
    const square sq = BitBoard::to_square(piece_board);
    const bitboard mask = masks[sq] & ~piece_board;
    const bitboard occupancy = (board.get_color_board(Color::White) |
                                board.get_color_board(Color::Black)) &
                               mask;

    const bitboard forward = occupancy - 2 * piece_board;
    const bitboard reverse =
        BitBoard::reverse(occupancy) - 2 * BitBoard::reverse(piece_board);
    return ((forward ^ BitBoard::reverse(reverse)) & mask);
}

std::vector<Move> MoveGen::generate_rook_moves(Board& board,
                                               const Color& side) {
    std::vector<Move> possible_moves;

    bitboard all_rooks = board.get_piece_board(Piece::Rook, side);
    const bitboard own_color_board = board.get_color_board(side);

    while (all_rooks != 0) {
        const bitboard one_rook = BitBoard::pop_lsb(all_rooks);
        bitboard moves = (get_line_moves_board(board, one_rook, file_mask) |
                          get_line_moves_board(board, one_rook, rank_mask)) &
                         ~own_color_board;
        while (moves != 0) {
            possible_moves.emplace_back(
                Piece::Rook, side, BitBoard::to_square(one_rook),
                BitBoard::to_square(BitBoard::pop_lsb(moves)));
        }
    }

    return possible_moves;
}

std::vector<Move> MoveGen::generate_bishop_moves(Board& board,
                                                 const Color& side) {
    std::vector<Move> possible_moves;

    bitboard all_bishops = board.get_piece_board(Piece::Bishop, side);
    const bitboard own_color_board = board.get_color_board(side);

    while (all_bishops != 0) {
        bitboard one_bishop_pos = BitBoard::pop_lsb(all_bishops);
        bitboard moves =
            (get_line_moves_board(board, one_bishop_pos, diag_mask) |
             get_line_moves_board(board, one_bishop_pos, anti_diag_mask)) &
            ~own_color_board;
        while (moves != 0) {
            possible_moves.emplace_back(
                Piece::Bishop, side, BitBoard::to_square(one_bishop_pos),
                BitBoard::to_square(BitBoard::pop_lsb(moves)));
        }
    }

    return possible_moves;
}

std::vector<Move> MoveGen::generate_queen_moves(Board& board,
                                                const Color& side) {
    std::vector<Move> possible_moves;

    bitboard all_queens = board.get_piece_board(Piece::Queen, side);
    const bitboard own_color_board = board.get_color_board(side);

    while (all_queens != 0) {
        bitboard one_queen_pos = BitBoard::pop_lsb(all_queens);
        bitboard moves =
            (get_line_moves_board(board, one_queen_pos, diag_mask) |
             get_line_moves_board(board, one_queen_pos, anti_diag_mask) |
             get_line_moves_board(board, one_queen_pos, file_mask) |
             get_line_moves_board(board, one_queen_pos, rank_mask)) &
            ~own_color_board;

        while (moves != 0) {
            possible_moves.emplace_back(
                Piece::Queen, side, BitBoard::to_square(one_queen_pos),
                BitBoard::to_square(BitBoard::pop_lsb(moves)));
        }
    }

    return possible_moves;
}

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

bitboard get_king_moves_board(const bitboard& king_pos,
                              const bitboard& own_color_board) {

    return (((king_pos << 8)) | ((king_pos << 7) & ~File::A) |
            ((king_pos >> 1) & ~File::A) | ((king_pos >> 9) & ~File::A) |
            ((king_pos >> 8)) | ((king_pos >> 7) & ~File::H) |
            ((king_pos << 1) & ~File::H) | ((king_pos << 9) & ~File::H)) &
           ~own_color_board;
}

std::vector<Move> MoveGen::generate_king_moves(Board& board,
                                               const Color& side) {
    std::vector<Move> possible_moves;
    const bitboard king_pos = board.get_piece_board(Piece::King, side);
    const bitboard own_color_board = board.get_color_board(side);
    bitboard moves = get_king_moves_board(king_pos, own_color_board);
    
    // While there are moves to process
    while (moves != 0) {
        possible_moves.emplace_back(
            Piece::King, side, BitBoard::to_square(king_pos),
            BitBoard::to_square(BitBoard::pop_lsb(moves)));
    }

    return possible_moves;
}

void MoveGen::print_move(const Move& m) {
    std::cout << "\nPIECE: " << static_cast<char>(m.piece_type)
              << "\nCOLOR: " << static_cast<bool>(m.color)
              << "\nFROM: " << static_cast<int>(m.from)
              << "\nTO: " << static_cast<int>(m.to)
              << "\nIS CAPTURE: " << m.is_capture << "\n\n";
}
