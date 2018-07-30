#include <iostream>
#include "../include/board.hpp"


// It initializes the board position
// to the normal starting postion
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


uint64_t Board::all_white_pieces() {
    return (m_white_pieces[Piece::Pawns] |
            m_white_pieces[Piece::Bishops] |
            m_white_pieces[Piece::Knights] |
            m_white_pieces[Piece::Rooks] |
            m_white_pieces[Piece::Queens] |
            m_white_pieces[Piece::King]);
}


uint64_t Board::all_black_pieces() {
    return (m_black_pieces[Piece::Pawns] |
            m_black_pieces[Piece::Bishops] |
            m_black_pieces[Piece::Knights] |
            m_black_pieces[Piece::Rooks] |
            m_black_pieces[Piece::Queens] |
            m_black_pieces[Piece::King]);
    
}


void Board::pretty_print() {
    uint64_t b = Board::all_white_pieces() | Board::all_black_pieces();
    for ( int i = 0; i < 64; ++i) {
        std::cout << static_cast<int>(b & 0b1);
        b >>= 1;

        if ( (i+1) % 8 == 0 ) {
            std::cout << '\n';
        }
    }
}
