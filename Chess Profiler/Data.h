#pragma once
typedef unsigned __int64 Bitboard;
static const char TOTAL_PIECES = 12;
static const char WHITE_INDEX_START = 0, WHITE_INDEX_END = 6;
static const char BLACK_INDEX_START = 6, BLACK_INDEX_END = 12;

const Bitboard All_Squares = ~Bitboard(0);
const Bitboard Dark_Squares = 0xAA55AA55AA55AA55;

const Bitboard VertA = 0x0101010101010101;
const Bitboard VertB = VertA << 1;
const Bitboard VertC = VertA << 2;
const Bitboard VertD = VertA << 3;
const Bitboard VertE = VertA << 4;
const Bitboard VertF = VertA << 5;
const Bitboard VertG = VertA << 6;
const Bitboard VertH = VertA << 7;

const Bitboard Verticals[] = { VertA, VertB, VertC, VertD, VertE, VertF, VertG, VertH };

const Bitboard Horz1 = 0xFF;
const Bitboard Horz2 = Horz1 << (8 * 1);
const Bitboard Horz3 = Horz1 << (8 * 2);
const Bitboard Horz4 = Horz1 << (8 * 3);
const Bitboard Horz5 = Horz1 << (8 * 4);
const Bitboard Horz6 = Horz1 << (8 * 5);
const Bitboard Horz7 = Horz1 << (8 * 6);
const Bitboard Horz8 = Horz1 << (8 * 7);

const Bitboard Horizontals[] = { Horz1, Horz2, Horz3, Horz4, Horz5, Horz6, Horz7, Horz8 };

const Bitboard QueenSide = VertA | VertB | VertC | VertD;
const Bitboard CenterFiles = VertC | VertD | VertE | VertF;
const Bitboard KingSide = ~QueenSide;
const Bitboard Center = (VertD | VertE) & (Horz4 | Horz5);

enum MoveType {
	NORMAL,
	PROMOTION = 1 << 14,
	ENPASSANT = 2 << 14,
	CASTLING = 3 << 14
};

enum Color {
	WHITE, BLACK, COLOR_NB = 2
};

enum Type : char {
	WHITE_PAWN = 0, WHITE_KNIGHT = 1, WHITE_BISHOP = 2, WHITE_ROOK = 3, WHITE_QUEEN = 4, WHITE_KING = 5,
	BLACK_PAWN = 6, BLACK_KNIGHT = 7, BLACK_BISHOP = 8, BLACK_ROOK = 9, BLACK_QUEEN = 10, BLACK_KING = 11,
	TYPE_NONE = 12
};

enum Direction : char {
    NORTH = 8,
    EAST = 1,
    SOUTH = -8,
    WEST = -1,

    NORTH_EAST = NORTH + EAST,
    SOUTH_EAST = SOUTH + EAST,
    NORTH_WEST = NORTH + WEST,
    SOUTH_WEST = SOUTH + WEST
};

enum File : int {
    FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NB
};

enum Square : char {
    SQ_A1 = 0, SQ_B1 = 1, SQ_C1 = 2, SQ_D1 = 3, SQ_E1 = 4, SQ_F1 = 5, SQ_G1 = 6, SQ_H1 = 7,
    SQ_A2 = 8, SQ_B2 = 9, SQ_C2 = 10, SQ_D2 = 11, SQ_E2 = 12, SQ_F2 = 13, SQ_G2 = 14, SQ_H2 = 15,
    SQ_A3 = 16, SQ_B3 = 17, SQ_C3 = 18, SQ_D3 = 19, SQ_E3 = 20, SQ_F3 = 21, SQ_G3 = 22, SQ_H3 = 23,
    SQ_A4 = 24, SQ_B4 = 25, SQ_C4 = 26, SQ_D4 = 27, SQ_E4 = 28, SQ_F4 = 29, SQ_G4 = 30, SQ_H4 = 31,
    SQ_A5 = 32, SQ_B5 = 33, SQ_C5 = 34, SQ_D5 = 35, SQ_E5 = 36, SQ_F5 = 37, SQ_G5 = 38, SQ_H5 = 39,
    SQ_A6 = 40, SQ_B6 = 41, SQ_C6 = 42, SQ_D6 = 43, SQ_E6 = 44, SQ_F6 = 45, SQ_G6 = 46, SQ_H6 = 47,
    SQ_A7 = 48, SQ_B7 = 49, SQ_C7 = 50, SQ_D7 = 51, SQ_E7 = 52, SQ_F7 = 53, SQ_G7 = 54, SQ_H7 = 55,
    SQ_A8 = 56, SQ_B8 = 57, SQ_C8 = 58, SQ_D8 = 59, SQ_E8 = 60, SQ_F8 = 61, SQ_G8 = 62, SQ_H8 = 63,
    SQ_NONE,

    SQUARE_NB = 64
};

// A move needs 16 bits to be stored
//
// bit  0- 5: destination square (from 0 to 63)
// bit  6-11: origin square (from 0 to 63)
// bit 12-13: promotion piece type - 2 (from KNIGHT-2 to QUEEN-2)
// bit 14-15: special move flag: promotion (1), en passant (2), castling (3)
// NOTE: EN-PASSANT bit is set only when a pawn can be captured
//
// Special cases are MOVE_NONE and MOVE_NULL. We can sneak these in because in
// any normal move destination square is always different from origin square
// while MOVE_NONE and MOVE_NULL have the same origin and destination square.
enum Move : int {
    MOVE_NONE,
    MOVE_NULL = 65
};

constexpr Square Origin(Move m) {
    return Square((m >> 6) & 0x3F);
}

constexpr Square Destination(Move m) {
    return Square(0x3F & m);
}

const Bitboard bit_locations[64] = { 0x1,               0x2,               0x4,               0x8,               0x10,               0x20,               0x40,               0x80,
                                    0x100,             0x200,             0x400,             0x800,             0x1000,             0x2000,             0x4000,             0x8000,
                                    0x10000,           0x20000,           0x40000,           0x80000,           0x100000,           0x200000,           0x400000,           0x800000,
                                    0x1000000,         0x2000000,         0x4000000,         0x8000000,         0x10000000,         0x20000000,         0x40000000,         0x80000000,
                                    0x100000000,       0x200000000,       0x400000000,       0x800000000,       0x1000000000,       0x2000000000,       0x4000000000,       0x8000000000,
                                    0x10000000000,     0x20000000000,     0x40000000000,     0x80000000000,     0x100000000000,     0x200000000000,     0x400000000000,     0x800000000000,
                                    0x1000000000000,   0x2000000000000,   0x4000000000000,   0x8000000000000,   0x10000000000000,   0x20000000000000,   0x40000000000000,   0x80000000000000,
                                    0x100000000000000, 0x200000000000000, 0x400000000000000, 0x800000000000000, 0x1000000000000000, 0x2000000000000000, 0x4000000000000000, 0x8000000000000000 };

template<Direction dir>
constexpr Bitboard shift(Bitboard bit) {
    return dir == NORTH ? bit >> NORTH
        : dir == SOUTH ? bit << SOUTH
        : dir == EAST ? (bit & ~VertH) >> 1
        : dir == WEST ? (bit & ~VertA) << 1
        : dir == NORTH_EAST ? (bit & ~VertH) >> 7
        : dir == NORTH_WEST ? (bit & ~VertA) >> 9
        : dir == SOUTH_EAST ? (bit & ~VertH) << 7
        : dir == SOUTH_WEST ? (bit & ~VertA) << 9
        : 0;
}

template<Direction dir>
constexpr Bitboard shift(char location) {
    return shift<dir>(bit_locations[location]);
}

struct Board {
    char piece_types[TOTAL_PIECES];
    char piece_locations[TOTAL_PIECES];
    char data;
    Move move_data;
    Bitboard white_board, white_attack;
    Bitboard black_board, black_attack;
};

constexpr bool operator&(Square a, Bitboard b) { return ((bit_locations[a] & b) != 0); }
constexpr Bitboard operator^(Square a, Bitboard b) { return (bit_locations[a] ^ b); }
constexpr Bitboard operator|(Square a, Bitboard b) { return (bit_locations[a] | b); }