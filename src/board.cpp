#include "../include/board.hpp"
#include <cassert>
#include <iostream>

Board::Board(const std::string& fen_notation) {
    // @TODO: Parse side to play, castling and moves played

    // Allocate all the space necessary in one go
    m_board_state.reserve(2);
    m_board_state[Color::White].reserve(6);
    m_board_state[Color::Black].reserve(6);

    // Zero the state
    m_board_state[Color::White][Piece::Pawn] = 0;
    m_board_state[Color::White][Piece::Bishop] = 0;
    m_board_state[Color::White][Piece::Knight] = 0;
    m_board_state[Color::White][Piece::Rook] = 0;
    m_board_state[Color::White][Piece::Queen] = 0;
    m_board_state[Color::White][Piece::King] = 0;
    m_board_state[Color::Black][Piece::Pawn] = 0;
    m_board_state[Color::Black][Piece::Bishop] = 0;
    m_board_state[Color::Black][Piece::Knight] = 0;
    m_board_state[Color::Black][Piece::Rook] = 0;
    m_board_state[Color::Black][Piece::Queen] = 0;
    m_board_state[Color::Black][Piece::King] = 0;

    int index = 0;
    for (auto c : fen_notation) {
        if (c == '/') {
            // Ignore the breaks
            continue;

        } else if (c == ' ') {
            break;

        } else if (std::isdigit(c)) {
            // Add the digit number to the index position and read next
            // character
            index += c - '0';
            continue;

        } else {
            if (std::toupper(c) == c) {
                // If it is a UPPERCASE letter, then it is a white piece
                // position
                m_board_state[Color::White]
                             [static_cast<Piece>(std::tolower(c))] |=
                    0x8000000000000000 >> index;
            } else {
                // Else, it is a black piece position
                m_board_state[Color::Black]
                             [static_cast<Piece>(std::tolower(c))] |=
                    0x8000000000000000 >> index;
            }
        }
        ++index;
    }
    m_side_to_play = Color::White;
}

// By default, initialize the starting position
Board::Board()
    : Board::Board(
          "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"){};

bitboard Board::get_color_board(const Color& side) noexcept {
    bitboard result = 0;
    for (const auto b : m_board_state[side]) {
        result |= b.second;
    }
    return result;
}

bitboard Board::get_piece_board(const Piece& piece_type,
                                const Color& side) noexcept {
    return m_board_state[side][piece_type];
}

std::string Board::pretty_string() {
    std::string board(64, '.');

    // Goes through each side's bitboards and inserts its corresponding letter
    // (defined in the Piece enum class) in the string.
    for (const auto side_state : m_board_state) {
        Color side = side_state.first;
        for (const auto piece_info : side_state.second) {
            bitboard b = piece_info.second;

            for (int i = 0; i < 64; ++i) {
                // Check most right bit
                if (b & 0x8000000000000000) {
                    // If it is a white piece, the letter is in uppercase,
                    // else the letter is in lowercase.
                    board[i] =
                        (side == Color::White) ?
                            std::toupper(static_cast<char>(piece_info.first)) :
                            static_cast<char>(piece_info.first);
                }

                b <<= 1;
            }
        }
    }
    return board;
}

void Board::apply_move(const Move& move) {
    assert(move.color == m_side_to_play);

    // Zero the internal bitboard of the appropriate color/piece
    // at the from position and set the to position
    const bitboard from_bitboard = static_cast<bitboard>(0b1) << move.from;
    const bitboard to_bitboard = static_cast<bitboard>(0b1) << move.to;

    const Color opposite_color =
        (move.color == Color::White) ? Color::Black : Color::White;

    // Check if there is an actual piece in the move place
    assert(from_bitboard & m_board_state[move.color][move.piece_type]);

    m_board_state[move.color][move.piece_type] &= ~(from_bitboard);
    m_board_state[move.color][move.piece_type] |= to_bitboard;

    if (move.is_capture) {
        // If it is a capture, it is necessary to zero the
        // corresponding color/piece attacked by our piece

        for (std::pair<Piece, bitboard> piece_bitboard :
             m_board_state[opposite_color]) {

            if (piece_bitboard.second & to_bitboard) {
                m_board_state[opposite_color][piece_bitboard.first] &=
                    ~(to_bitboard);
            }
        }
    }

    // Add the just-played move to the move list
    // and change the side to play
    m_move_list.push_back(move);
    m_side_to_play = opposite_color;
}

void Board::undo_last_move() {
    // @TODO: Find a way to reverse captures

    Move last_move = m_move_list.back();
    m_move_list.pop_back();

    // Reverse the process in apply_move
    const bitboard from_bitboard = static_cast<bitboard>(0b1) << last_move.from;
    const bitboard to_bitboard = static_cast<bitboard>(0b1) << last_move.to;
    m_board_state[last_move.color][last_move.piece_type] |= from_bitboard;
    m_board_state[last_move.color][last_move.piece_type] &= ~to_bitboard;
    m_side_to_play = last_move.color;
}

Color Board::get_side_to_play() const { return m_side_to_play; }

void Board::pretty_print() {
    const std::string b = Board::pretty_string();
    std::cout << "+--------+\n";
    for (int i = 0; i < 8; ++i) {
        std::cout << " " << b.substr(i * 8, 8) << '\n';
    }
    std::cout << "+--------+\n";
}
