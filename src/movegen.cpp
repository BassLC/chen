#include "../include/movegen.hpp"
#include <functional>
#include <iostream>

// @TODO:
// - Test for captures
// - Implement pawn move generator

// Because the sliding piece move generation method (Hyperbola Quintessence)
// uses masks to calculate all the attacks, it is best to have them all
// (64 * 4 different files) pre-computed, so it is only necessary
// to compute the index array
constexpr std::array<bitboard, 64> rank_mask{
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
    Rank::EIGHT, Rank::EIGHT, Rank::EIGHT, Rank::EIGHT,
};

constexpr std::array<bitboard, 64> file_mask{
    File::H, File::G, File::F, File::E, File::D, File::C, File::B, File::A,
    File::H, File::G, File::F, File::E, File::D, File::C, File::B, File::A,
    File::H, File::G, File::F, File::E, File::D, File::C, File::B, File::A,
    File::H, File::G, File::F, File::E, File::D, File::C, File::B, File::A,
    File::H, File::G, File::F, File::E, File::D, File::C, File::B, File::A,
    File::H, File::G, File::F, File::E, File::D, File::C, File::B, File::A,
    File::H, File::G, File::F, File::E, File::D, File::C, File::B, File::A,
    File::H, File::G, File::F, File::E, File::D, File::C, File::B, File::A,
};

constexpr std::array<bitboard, 64> diag_mask{
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

constexpr std::array<bitboard, 64> anti_diag_mask{
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

// Get all the possible moves of a file. Then the move generation of
// the sliding pieces is simply a composition of function calls with
// different masks passed.
bitboard generate_line_moves(Board& board, const bitboard& piece_board,
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

// Generate all knight pseudo-legal moves for ONE KNIGHT PIECE
bitboard generate_knight_moves(const bitboard& knights_board) {
    return (((knights_board << 17) & ~File::H) |             // UpUpLeft
            ((knights_board << 15) & ~File::A) |             // UpUpRight
            ((knights_board << 6) & ~(File::A | File::B)) |  // UpRightRight
            ((knights_board >> 10) & ~(File::A | File::B)) | // DownRightRight
            ((knights_board >> 17) & ~(File::A)) |           // DownDownRight
            ((knights_board >> 15) & ~(File::H)) |           // DownDownLeft
            ((knights_board >> 6) & ~(File::G | File::H)) |  // DownLeftLeft
            ((knights_board << 10) & ~(File::G | File::H))); // UpLeftLeft
}

// Generate all king pseudo-legal moves for the king piece
bitboard generate_king_moves(const bitboard& king_pos) {
    return (((king_pos << 8)) | ((king_pos << 7) & ~File::A) |
            ((king_pos >> 1) & ~File::A) | ((king_pos >> 9) & ~File::A) |
            ((king_pos >> 8)) | ((king_pos >> 7) & ~File::H) |
            ((king_pos << 1) & ~File::H) | ((king_pos << 9) & ~File::H));
}

bitboard pawns_not_moved_board(Board& b, const Color& side) {
    bitboard pawn_board = b.get_piece_board(Piece::Pawn, side);
    const bitboard starting_file =
        (side == Color::White) ? Rank::TWO : Rank::SEVEN;
    return pawn_board & ~starting_file;
}

// Returns all moves from piece query
std::vector<Move>
MoveGen::generate_moves(Board& board,
                        const std::vector<std::pair<Piece, Color>>& pieces) {

    std::vector<Move> possible_moves;
    std::vector<std::function<bitboard(bitboard)>> function_generators;

    // Iterate though piece query and store all the functions needed for this
    // piece generation
    for (auto pair : pieces) {
        using namespace std::placeholders;
        function_generators.clear();

        switch (pair.first) {
        case Piece::Knight:
            function_generators.emplace_back(generate_knight_moves);
            break;

        case Piece::Bishop:
            function_generators.emplace_back(
                std::bind(generate_line_moves, board, _1, diag_mask));
            function_generators.emplace_back(
                std::bind(generate_line_moves, board, _1, anti_diag_mask));
            break;

        case Piece::Rook:
            function_generators.emplace_back(
                std::bind(generate_line_moves, board, _1, file_mask));
            function_generators.emplace_back(
                std::bind(generate_line_moves, board, _1, rank_mask));
            break;

        case Piece::Queen:
            function_generators.emplace_back(
                std::bind(generate_line_moves, board, _1, file_mask));
            function_generators.emplace_back(
                std::bind(generate_line_moves, board, _1, rank_mask));
            function_generators.emplace_back(
                std::bind(generate_line_moves, board, _1, diag_mask));
            function_generators.emplace_back(
                std::bind(generate_line_moves, board, _1, anti_diag_mask));
            break;

        case Piece::King:
            function_generators.emplace_back(generate_king_moves);
            break;

        default:
            break;
        }

        bitboard all_pieces = board.get_piece_board(pair.first, pair.second);
        while (all_pieces != 0) {
            bitboard one_piece = BitBoard::pop_lsb(all_pieces);
            bitboard moves = 0;

            // All the piece moves are simply a composition of generators
            for (auto gen : function_generators) {
                moves |= gen(one_piece);
            }

            // It is impossible for two pieces be in the same square
            moves &= ~(board.get_color_board(pair.second));

            while (moves != 0) {
                possible_moves.emplace_back(
                    pair.first, pair.second, BitBoard::to_square(one_piece),
                    BitBoard::to_square(BitBoard::pop_lsb(moves)));
            }
        }
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
