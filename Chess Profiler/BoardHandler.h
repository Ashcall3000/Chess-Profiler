#pragma once
#include "Data.h"
#include <iostream>
#include <algorithm>

class BoardHandler
{
public:
	BoardHandler();

    
    char char_board[64] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    char blank_board[64] = { ' ', '-', ' ', '-', ' ', '-', ' ', '-',
                             '-', ' ', '-', ' ', '-', ' ', '-', ' ',
                             ' ', '-', ' ', '-', ' ', '-', ' ', '-',
                             '-', ' ', '-', ' ', '-', ' ', '-', ' ',
                             ' ', '-', ' ', '-', ' ', '-', ' ', '-',
                             '-', ' ', '-', ' ', '-', ' ', '-', ' ',
                             ' ', '-', ' ', '-', ' ', '-', ' ', '-',
                             '-', ' ', '-', ' ', '-', ' ', '-', ' ' };

    static const unsigned char WHITE_MOVE = 0x1;
    static const unsigned char BLACK_MOVE = 0x2;

    void printCharBoard(Board bboard);

private:
    Board main_board;
    char char_pieces[TOTAL_PIECES];
};

