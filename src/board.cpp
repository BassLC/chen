#include "../include/board.hpp"
#include <iostream>

// @TODO:
// - Make a constructor that allows to load a specific configuration (maybe from
// a PGN or FEN).
Board::Board() {
    // Allocate all the space necessary in one go
    m_board_state.reserve(2);
    m_board_state[Color::White].reserve(6);
    m_board_state[Color::Black].reserve(6);

    // // Setup the normal starting position
    m_board_state[Color::White][Piece::Pawn] =
        0b0000000000000000000000000000000000000000000000001111111100000000;
    m_board_state[Color::White][Piece::Bishop] =
        0b0000000000000000000000000000000000000000000000000000000000100100;
    m_board_state[Color::White][Piece::Knight] =
        0b0000000000000000000000000000000000000000000000000000000001000010;
    m_board_state[Color::White][Piece::Rook] =
        0b0000000000000000000000000000000000000000000000000000000010000001;
    m_board_state[Color::White][Piece::Queen] =
        0b0000000000000000000000000000000000000000000000000000000000010000;
    m_board_state[Color::White][Piece::King] =
        0b0000000000000000000000000000000000000000000000000000000000001000;

    m_board_state[Color::Black][Piece::Pawn] =
        0b0000000011111111000000000000000000000000000000000000000000000000;
    m_board_state[Color::Black][Piece::Bishop] =
        0b0010010000000000000000000000000000000000000000000000000000000000;
    m_board_state[Color::Black][Piece::Knight] =
        0b0100001000000000000000000000000000000000000000000000000000000000;
    m_board_state[Color::Black][Piece::Rook] =
        0b1000000100000000000000000000000000000000000000000000000000000000;
    m_board_state[Color::Black][Piece::Queen] =
        0b0001000000000000000000000000000000000000000000000000000000000000;
    m_board_state[Color::Black][Piece::King] =
        0b0000100000000000000000000000000000000000000000000000000000000000;
}

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

void Board::pretty_print() {
    const std::string b = Board::pretty_string();
    for (int i = 0; i < 8; ++i) {
        std::cout << b.substr(i * 8, 8) << '\n';
    }
}
