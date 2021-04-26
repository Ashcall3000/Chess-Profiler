#include <iostream>
#include "Piece.h"
using namespace std;

Piece::Piece()
{
    // White piece Chars
    w_pawn = 'P';
    w_knight = 'N';
    w_bishop = 'B';
    w_rook = 'R';
    w_queen = 'Q';
    w_king = 'K';
    // Black piece Chars
    b_pawn = 'p';
    b_knight = 'n';
    b_bishop = 'b';
    b_rook = 'r';
    b_queen = 'q';
    b_king = 'k';
    // How much to bit shift
    move_vertical = 8;
    move_horizontal = 1;
    move_south_east = move_vertical - move_horizontal;
    move_south_west = move_vertical + move_horizontal;
    move_north_east = move_vertical - move_horizontal;
    move_north_west = move_vertical + move_horizontal;
    // Movement Bits
    not_row_a = 0xFEFEFEFEFEFEFEFE;
    not_row_h = 0x7F7F7F7F7F7F7F7F;
    w_move_pawn = 1;
    w_move_pawn = w_move_pawn << (move_vertical * 4);
    w_start_move_pawn = w_move_pawn;
    w_start_move_pawn |= w_move_pawn << move_vertical;

    b_move_pawn = 1;
    b_move_pawn = b_move_pawn << (move_vertical * 2);
    b_start_move_pawn = b_move_pawn;
    b_start_move_pawn |= b_move_pawn << move_vertical;

    b_att_pawn = 1;
    b_att_pawn = b_att_pawn << (move_vertical * 2);
    b_att_pawn |= b_att_pawn << 2;

    w_move_pawn = 1;
    w_move_pawn = w_move_pawn << (move_vertical * 5);
    
    w_att_pawn = 1;
    w_att_pawn = w_att_pawn << (move_vertical * 5);
    w_att_pawn |= w_att_pawn << 2;

    bit_diag_down = 0x8040201008040201;
    bit_diag_up = 0x102040810204080;
    
    move_king = 0x70507;
    move_knight = 0xA1100110A;
}

unsigned __int64 Piece::getBitBlackPawnAttack(unsigned char location)
{
    // [ 0, 0, 0, 0, 0, 0, 0, 0,
    //   0, 0, 0, 0, 0, 0, 0, 0,
    //   1, 0, 1, 0, 0, 0, 0, 0,
    //   0, 0, 0, 0, 0, 0, 0, 0,
    //   0, 0, 0, 0, 0, 0, 0, 0,
    //   0, 0, 0, 0, 0, 0, 0, 0,
    //   0, 0, 0, 0, 0, 0, 0, 0,
    //   0, 0, 0, 0, 0, 0, 0, 0 ]
    if (location < 8 || location >= 56)
        return 0;
    switch (location)
    {
    case 9:
        return b_att_pawn;
        break;
    case 16:
    case 24:
    case 32:
    case 40:
    case 48:
        return (b_att_pawn << (location - 9)) & not_row_h;
        break;
    case 15:
    case 23:
    case 31:
    case 39:
    case 47:
    case 55:
        return (b_att_pawn << (location - 9)) & not_row_a;
        break;
    case 8:
        return (b_att_pawn >> 1) & not_row_h;
        break;
    default:
        return b_att_pawn << (location - 9);
    }
}
unsigned __int64 Piece::getBitWhitePawnAttack(unsigned char location)
{
    if (location < 8 || location >= 56)
        return 0;
    switch (location)
    {
    case 49:
        return w_att_pawn;
        break;
    case 16:
    case 24:
    case 32:
    case 40:
    case 48:
        return (w_att_pawn >> (49 - location)) & not_row_h;
        break;
    case 15:
    case 23:
    case 31:
    case 39:
    case 47:
        return (b_att_pawn >> (49 - location)) & not_row_a;
        break;
    case 55:
        return (w_att_pawn << (location - 49)) & not_row_a;
        break;
    }
    if (location > 49)
        return w_att_pawn << (location - 49);
    return w_att_pawn >> (49 - location);
}

unsigned __int64 Piece::getBitWhitePawnMove(unsigned char location)
{
    // [ 0, 0, 0, 0, 0, 0, 0, 0,
    //   0, 0, 0, 0, 0, 0, 0, 0,
    //   0, 0, 0, 0, 0, 0, 0, 0,
    //   0, 0, 0, 0, 0, 0, 0, 0,
    //   1, 0, 0, 0, 0, 0, 0, 0,
    //   1, 0, 0, 0, 0, 0, 0, 0,
    //   0, 0, 0, 0, 0, 0, 0, 0,
    //   0, 0, 0, 0, 0, 0, 0, 0 ]
    if (location > 48 && location < 56)
        return w_start_move_pawn << (location - 48);
    if (location < 48)
        return w_move_pawn >> (48 - location);
    return w_start_move_pawn;
}

unsigned __int64 Piece::getBitBlackPawnMove(unsigned char location)
{
    // [ 0, 0, 0, 0, 0, 0, 0, 0,
    //   1, 0, 0, 0, 0, 0, 0, 0,
    //   1, 0, 0, 0, 0, 0, 0, 0,
    //   0, 0, 0, 0, 0, 0, 0, 0,
    //   0, 0, 0, 0, 0, 0, 0, 0,
    //   0, 0, 0, 0, 0, 0, 0, 0,
    //   0, 0, 0, 0, 0, 0, 0, 0,
    //   0, 0, 0, 0, 0, 0, 0, 0 ]
    if (location > 8 && location < 16)
        return b_start_move_pawn << (location - 8);
    else if (location >= 16)
        return b_move_pawn >> (16 - location);
    else
        return b_start_move_pawn;
}

unsigned __int64 Piece::getBitKnightMove(unsigned char location)
{
    // [ 0, 1, 0, 1, 0, 0, 0, 0,
    //   1, 0, 0, 0, 1, 0, 0, 0,
    //   0, 0, 1, 0, 0, 0, 0, 0,
    //   1, 0, 0, 0, 1, 0, 0, 0,
    //   0, 1, 0, 1, 0, 0, 0, 0,
    //   0, 0, 0, 0, 0, 0, 0, 0,
    //   0, 0, 0, 0, 0, 0, 0, 0,
    //   0, 0, 0, 0, 0, 0, 0, 0 ]
    if (location == 18)
        return move_knight;
    int row = (location / 8);
    int placeholder = (row * 8) + 2;
    //cout << "Row: " << row << endl << "Placeholder: " << placeholder << endl;
    unsigned __int64 blank = move_knight;
    if (location < 8)
        blank = move_knight >> (move_vertical * 2);
    else if (location < 16)
        blank = move_knight >> (row * move_vertical);
    else if (location > 23 && row != 0)
        blank = move_knight << ((row - 2) * move_vertical);
    for (int i = placeholder; i < location; i++)
    {
        //cout << "I: " << i << endl;
        blank = (blank << 1) & not_row_a;
    }
    for (int i = placeholder; i > location; i--)
        blank = (blank >> 1) & not_row_h;
    return blank;
}

unsigned __int64 Piece::getBitBishopMove(unsigned char location)
{
    return (getBitDownDiagonal(location) ^ getBitUpDiagonal(location));
}

unsigned __int64 Piece::getBitRookMove(unsigned char location)
{
    return (getBitHorizontal(location) ^ getBitVertical(location));
}

unsigned __int64 Piece::getBitQueenMove(unsigned char location)
{
    return (getBitBishopMove(location) | getBitRookMove(location));
}

unsigned __int64 Piece::getBitKingMove(unsigned char location)
{
    if (location == 9)
        return move_king;
    unsigned __int64 blank = move_king;
    int row = 0;
    if (location >= 8)
        row = (location / 8);
    for (int i = 1; i < row; i++)
        blank = blank << move_vertical;
    int placeholder = row * 8;
    //cout << "Row: " << row << endl << "Placeholder: " << placeholder << endl;
    if (row == 0)
        blank = blank >> move_vertical;
    if (placeholder == location)
        blank = (blank >> 1) & not_row_h;
    else if (placeholder + 1 == location)
        return blank;
    else
        for (int i = placeholder + 1; i < location; i++)
            blank = (blank << 1) & not_row_a;
    return blank;
}

unsigned __int64 Piece::getBitDownDiagonal(unsigned char location)
{
    // [ 1, 0, 0, 0, 0, 0, 0, 0,
    //   0, 1, 0, 0, 0, 0, 0, 0,
    //   0, 0, 1, 0, 0, 0, 0, 0,
    //   0, 0, 0, 1, 0, 0, 0, 0,
    //   0, 0, 0, 0, 1, 0, 0, 0,
    //   0, 0, 0, 0, 0, 1, 0, 0,
    //   0, 0, 0, 0, 0, 0, 1, 0,
    //   0, 0, 0, 0, 0, 0, 0, 1 ]
    if (bit_locations[location] & bit_diag_down)
        return bit_diag_down;
    for (int i = 0; i < 15; i++)
        if (bit_locations[location] & bit_diag_downs[i])
            return bit_diag_downs[i];
    /*if (location == 7)
        return 0;
    int row = 0;
    if (location >= 8)
        row = (location / 8);
    int placeholder = (row * 8) + row;
    unsigned __int64 blank = bit_diag_down;
    if (location < placeholder)
        for (int i = location; i < placeholder; i++)
            blank = (blank >> 1) & not_row_h;
    else if (location > placeholder)
        for (int i = placeholder; i < location; i++)
            blank = (blank << 1) & not_row_a;
    return blank;*/
}

unsigned __int64 Piece::getBitUpDiagonal(unsigned char location)
{
    // [ 0, 0, 0, 0, 0, 0, 0, 1,
    //   0, 0, 0, 0, 0, 0, 1, 0,
    //   0, 0, 0, 0, 0, 1, 0, 0,
    //   0, 0, 0, 0, 1, 0, 0, 0,
    //   0, 0, 0, 1, 0, 0, 0, 0,
    //   0, 0, 1, 0, 0, 0, 0, 0,
    //   0, 1, 0, 0, 0, 0, 0, 0,
    //   1, 0, 0, 0, 0, 0, 0, 0 ]
    if (bit_locations[location] & bit_diag_up)
        return bit_diag_up;
    for (int i = 0; i < 15; i++)
        if (bit_locations[location] & bit_diag_ups[i])
            return bit_diag_ups[i];
    /*int row = (location / 8) + 1;
    int placeholder = (row * 8) - row;
    unsigned __int64 blank = bit_diag_up;
    if (location < placeholder)
        for (int i = location; i < placeholder; i++)
            blank = (blank >> 1) & not_row_h;
    else if (location > placeholder)
        for (int i = placeholder; i < location; i++)
            blank = (blank << 1) & not_row_a;
    return blank;*/
}

unsigned __int64 Piece::getBitVertical(unsigned char location)
{
    switch (location)
    {
    case 0:
    case 8:
    case 16:
    case 24:
    case 32:
    case 40:
    case 48:
    case 56:
        return ~not_row_a;
        break;
    case 7:
    case 15:
    case 23:
    case 31:
    case 39:
    case 47:
    case 55:
    case 63:
        return ~not_row_h;
        break;
    }
    unsigned __int64 blank = ~not_row_a;
    int placeholder = 0;
    if (location > 8)
        placeholder = location / 8;
    int column = location - (placeholder * 8);
    return (blank << column);
}

unsigned __int64 Piece::getBitHorizontal(unsigned char location)
{
    unsigned _int64 blank = 0xFF;
    if (location < 8)
        return blank;
    int row = location / 8;
    return (blank << (row * move_vertical));
}

void Piece::printBitBoard(unsigned __int64 board_to_print)
{
    unsigned long int checker = 1;
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if ((checker & board_to_print) > 0)
                cout << 1;
            else
                cout << 0;
            checker << 1;
        }
        cout << endl;
    }
}

Piece::~Piece()
{
    //dtor
}
