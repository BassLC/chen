#ifndef BITBOARD_HPP
#define BITBOARD_HPP
#include <stdint.h>

using bitboard = uint64_t;
using square = uint8_t;

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

namespace BitBoard {
bitboard pop_lsb(bitboard& b);
bitboard pop_msb(bitboard& b);
void print(bitboard b);
square to_square(const bitboard& b);
} // namespace BitBoard

#endif
