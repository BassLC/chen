#include "../include/board.hpp"
#include <iostream>

// @TODO:
// - Make a constructor that allows to load a specific configuration (maybe from
// a PGN or FEN).
Board::Board() {
    // Allocate all the space necessary in one go
    m_white_pieces.reserve(6);
    m_black_pieces.reserve(6);

    // Setup the normal starting position
    m_white_pieces[Piece::Pawns] =
        0b0000000000000000000000000000000000000000000000001111111100000000;
    m_white_pieces[Piece::Bishops] =
        0b0000000000000000000000000000000000000000000000000000000000100100;
    m_white_pieces[Piece::Knights] =
        0b0000000000000000000000000000000000000000000000000000000001000010;
    m_white_pieces[Piece::Rooks] =
        0b0000000000000000000000000000000000000000000000000000000010000001;
    m_white_pieces[Piece::Queens] =
        0b0000000000000000000000000000000000000000000000000000000000010000;
    m_white_pieces[Piece::King] =
        0b0000000000000000000000000000000000000000000000000000000000001000;

    m_black_pieces[Piece::Pawns] =
        0b0000000011111111000000000000000000000000000000000000000000000000;
    m_black_pieces[Piece::Bishops] =
        0b0010010000000000000000000000000000000000000000000000000000000000;
    m_black_pieces[Piece::Knights] =
        0b0100001000000000000000000000000000000000000000000000000000000000;
    m_black_pieces[Piece::Rooks] =
        0b1000000100000000000000000000000000000000000000000000000000000000;
    m_black_pieces[Piece::Queens] =
        0b0001000000000000000000000000000000000000000000000000000000000000;
    m_black_pieces[Piece::King] =
        0b0000100000000000000000000000000000000000000000000000000000000000;
}

bitboard Board::get_all_white_pieces() {
    return (m_white_pieces[Piece::Pawns] | m_white_pieces[Piece::Bishops] |
            m_white_pieces[Piece::Knights] | m_white_pieces[Piece::Rooks] |
            m_white_pieces[Piece::Queens] | m_white_pieces[Piece::King]);
}

bitboard Board::get_all_black_pieces() {
    return (m_black_pieces[Piece::Pawns] | m_black_pieces[Piece::Bishops] |
            m_black_pieces[Piece::Knights] | m_black_pieces[Piece::Rooks] |
            m_black_pieces[Piece::Queens] | m_black_pieces[Piece::King]);
}

void Board::pretty_print() {
    std::string board(64, '.');
    const std::array<Piece, 6> piece_type{
        Piece::Pawns, Piece::Bishops, Piece::Knights,
        Piece::Rooks, Piece::Queens,  Piece::King,
    };

    // @TODO:
    // - Get rid of this code duplication.
    // ? Make this function return a string, instead of printing info.

    // White pieces
    for (const auto p : piece_type) {
        bitboard b = m_white_pieces[p];
        for (auto i = 63; i >= 0; --i) {
            if (b & 0b1) {
                board[i] = std::toupper(static_cast<char>(p));
            }
            b >>= 1;
        }
    }

    // Black pieces
    for (const auto p : piece_type) {
        bitboard b = m_black_pieces[p];
        for (auto i = 63; i >= 0; --i) {
            if (b & 0b1) {
                board[i] = static_cast<char>(p);
            }
            b >>= 1;
        }
    }

    // Print it (and put spaces in each line)
    for (auto i = 0; i < 64; ++i) {
        std::cout << board[i];
        if ((i + 1) % 8 == 0) {
            std::cout << '\n';
        }
    }
}
