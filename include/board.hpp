#ifndef BOARD_HPP
#define BOARD_HPP

#include <unordered_map>
#include <cstdint>


// A mapping of array indexes
// to recognizable names
enum class Piece {
    Pawns,
    Bishops,
    Knights,
    Rooks,
    Queens,
    King,
}; 


class Board {

public:
    Board();
    ~Board() = default;
    uint64_t all_white_pieces();
    uint64_t all_black_pieces();
    void pretty_print();
        
private:
    std::unordered_map<Piece, uint64_t> m_white_pieces;
    std::unordered_map<Piece, uint64_t> m_black_pieces;
};



#endif
