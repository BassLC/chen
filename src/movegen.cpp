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

bitboard pawns_not_moved(const bitboard& piece_board, const Color& side) {
    const bitboard starting_file =
        (side == Color::White) ? Rank::TWO : Rank::SEVEN;
    return piece_board & starting_file;
}

// There are three types of pawn movement: a single push (which all non-blocked
// pawns can make), a double push (which all not-moved non-blocked pawns can
// make) and pawns attacks (which all pawns with an adversary piece in its
// diagonal or anti-diagonal square can make)
bitboard generate_pawn_moves(Board& board, const bitboard& piece_board,
                             const Color& side) {
    const bitboard empty = ~(board.get_color_board(Color::White) |
                             board.get_color_board(Color::Black));

    bitboard single_push, double_push, pawn_attacks = 0;

    if (side == Color::White) {
        // A pawn can single push if there is no piece in front of it
        single_push = (piece_board << 8) & empty;

        // Only pawns that have not been moved (basically pawns that never left
        // the starting position, since a pawn can not get back to a square) AND
        // can single push AND do not have any piece in front of them after a
        // single push can double push
        double_push =
            (((pawns_not_moved(piece_board, side) << 8) & empty) << 8) &
            Rank::FOUR;

        // Every pawn can attack if there is an other color piece in its
        // diagonal or anti-diagonal adjacent square
        pawn_attacks = (((piece_board << 9) & ~File::H) |
                        ((piece_board << 7) & ~File::A)) &
                       board.get_color_board(Color::Black);
    } else {
        // For Black, operations are reversed
        single_push = (piece_board >> 8) & empty;
        double_push =
            (((pawns_not_moved(piece_board, side) >> 8) & empty) >> 8) &
            Rank::FIVE;
        pawn_attacks = (((piece_board >> 9) & ~File::A) |
                        ((piece_board >> 7) & ~File::H)) &
                       board.get_color_board(Color::White);
    }
    return (single_push | double_push | pawn_attacks);
}

// Returns all moves from piece query
std::vector<Move>
MoveGen::generate_moves(Board& board,
                        const std::vector<std::pair<Piece, Color>>& pieces) {

    std::vector<Move> possible_moves;
    std::function<bitboard(bitboard)> move_generator;

    // Iterate though piece query and store all the functions needed for this
    // piece generation
    for (auto pair : pieces) {
        switch (pair.first) {
        case Piece::Knight:
            move_generator = generate_knight_moves;
            break;

        case Piece::Bishop:
            // Bishop moves are a composition of the diagonal moves
            // and anti-diagonal moves
            move_generator = [&](const bitboard& b) {
                return (generate_line_moves(board, b, diag_mask) |
                        generate_line_moves(board, b, anti_diag_mask));
            };
            break;

        case Piece::Rook:
            // Rook moves are a composition of the file moves
            // and rank moves
            move_generator = [&](const bitboard& b) {
                return (generate_line_moves(board, b, file_mask) |
                        generate_line_moves(board, b, rank_mask));
            };
            break;

        case Piece::Queen:
            // Queen moves are a composition os the file moves,
            // rank moves, diagonal moves and anti-diagonal moves
            move_generator = [&](const bitboard& b) {
                return (generate_line_moves(board, b, file_mask) |
                        generate_line_moves(board, b, rank_mask) |
                        generate_line_moves(board, b, diag_mask) |
                        generate_line_moves(board, b, anti_diag_mask));
            };
            break;

        case Piece::King:
            move_generator = generate_king_moves;
            break;

        case Piece::Pawn:
            move_generator = [&](const bitboard& b) {
                return generate_pawn_moves(board, b, pair.second);
            };
            break;
        default:
            break;
        }

        bitboard all_pieces = board.get_piece_board(pair.first, pair.second);
        const bitboard other_color_board =
            (pair.second == Color::White) ?
                board.get_color_board(Color::Black) :
                board.get_color_board(Color::White);
        while (all_pieces != 0) {
            const bitboard one_piece = BitBoard::pop_lsb(all_pieces);
            const square piece_square = BitBoard::to_square(one_piece);

            // All the moves are a combination of the appropriate move_generator
            // and the removal of the already occupied squares
            bitboard moves =
                move_generator(one_piece) & ~board.get_color_board(pair.second);

            while (moves != 0) {
                const bitboard move = BitBoard::pop_lsb(moves);
                possible_moves.emplace_back(
                    pair.first, pair.second, piece_square,
                    BitBoard::to_square(move), move & other_color_board);
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
