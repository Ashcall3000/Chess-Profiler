#ifndef PIECE_H
#define PIECE_H


class Piece
{
    public:
        /** Default constructor */
        Piece();
        unsigned __int64 getBitBlackPawnAttack(unsigned char location);
        unsigned __int64 getBitWhitePawnAttack(unsigned char location);
        /** Default destructor */
        virtual ~Piece();
        void printBitBoard(unsigned __int64 board_to_print);
        unsigned __int64 getBitWhitePawnMove(unsigned char location);
        unsigned __int64 getBitBlackPawnMove(unsigned char location);
        unsigned __int64 getBitKnightMove(unsigned char location);
        unsigned __int64 getBitBishopMove(unsigned char location);
        unsigned __int64 getBitRookMove(unsigned char location);
        unsigned __int64 getBitQueenMove(unsigned char location);
        unsigned __int64 getBitKingMove(unsigned char location);
        unsigned __int64 getBitUpDiagonal(unsigned char location);
        unsigned __int64 getBitDownDiagonal(unsigned char location);
        unsigned __int64 getBitHorizontal(unsigned char location);
        unsigned __int64 getBitVertical(unsigned char location);

        int move_vertical, move_horizontal, move_south_east, move_south_west, move_north_east, move_north_west;
        char w_pawn, w_knight, w_bishop, w_rook, w_queen, w_king;
        char b_pawn, b_knight, b_bishop, b_rook, b_queen, b_king;
        unsigned __int64 not_row_a, not_row_h;
        unsigned __int64 w_att_pawn, b_att_pawn;
        unsigned __int64 w_move_bishop, b_move_bishop;
        unsigned __int64 bit_diag_up, bit_diag_down, w_start_move_pawn;
        const unsigned __int64 bit_locations[64] = { 0x1,               0x2,               0x4,               0x8,               0x10,               0x20,               0x40,               0x80,
                                                     0x100,             0x200,             0x400,             0x800,             0x1000,             0x2000,             0x4000,             0x8000,
                                                     0x10000,           0x20000,           0x40000,           0x80000,           0x100000,           0x200000,           0x400000,           0x800000,
                                                     0x1000000,         0x2000000,         0x4000000,         0x8000000,         0x10000000,         0x20000000,         0x40000000,         0x80000000,
                                                     0x100000000,       0x200000000,       0x400000000,       0x800000000,       0x1000000000,       0x2000000000,       0x4000000000,       0x8000000000,
                                                     0x10000000000,     0x20000000000,     0x40000000000,     0x80000000000,     0x100000000000,     0x200000000000,     0x400000000000,     0x800000000000,
                                                     0x1000000000000,   0x2000000000000,   0x4000000000000,   0x8000000000000,   0x10000000000000,   0x20000000000000,   0x40000000000000,   0x80000000000000,
                                                     0x100000000000000, 0x200000000000000, 0x400000000000000, 0x800000000000000, 0x1000000000000000, 0x2000000000000000, 0x4000000000000000, 0x8000000000000000 };
        const unsigned __int64 bit_diag_ups[15] = { 0x102040810204080, 0x1020408102040, 0x10204081020, 0x102040810, 0x1020408, 0x10204, 0x102, 0x1,
                                                    0x204081020408000, 0x408102040800000, 0x810204080000000, 0x1020408000000000, 0x2040800000000000, 0x4080000000000000, 0x8000000000000000};
        const unsigned __int64 bit_diag_downs[15] = { 0x8040201008040201, 0x4020100804020100, 0x2010080402010000, 0x1008040201000000, 0x804020100000000, 0x402010000000000, 0x201000000000000, 0x100000000000000,
                                                      0x80402010080402, 0x804020100804, 0x8040201008, 0x80402010, 0x804020, 0x8040, 0x80 };
        unsigned __int64  w_move_pawn, w_move_bishop_left, w_move_bishop_right;
        unsigned __int64 b_start_move_pawn, b_move_pawn, b_move_bishop_left, b_move_bishop_right;
        unsigned __int64 move_knight, move_rook, move_queen, move_king;
    protected:

    private:

        
};

#endif // PIECE_H
