#ifndef BOARD_H
#define BOARD_H

#include <string>
#include "Piece.h"


class Board
{
    public:
        Board();
        virtual ~Board();
        const unsigned __int64 dark_squares = 0xAA55AA55AA55AA55ULL;
        static const int TOTAL_PIECES = 18;
        static const unsigned char WHITE_INDEX_START = 0, WHITE_INDEX_END = 8;
        static const unsigned char BLACK_INDEX_START = 8, BLACK_INDEX_END = 16;
        static const unsigned char WHITE_PAWNS = 16, WHITE_KNIGHTS = 0, WHITE_BISHOPS = 2, WHITE_ROOKS = 4, WHITE_QUEENS = 6, WHITE_KING = 7;
        static const unsigned char BLACK_PAWNS = 17, BLACK_KNIGHTS = 8, BLACK_BISHOPS = 10, BLACK_ROOKS = 12, BLACK_QUEENS = 14, BLACK_KING = 15;
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
        const unsigned __int64 bit_locations[64] = { 0x1,               0x2,               0x4,               0x8,               0x10,               0x20,               0x40,               0x80,
                                                     0x100,             0x200,             0x400,             0x800,             0x1000,             0x2000,             0x4000,             0x8000,
                                                     0x10000,           0x20000,           0x40000,           0x80000,           0x100000,           0x200000,           0x400000,           0x800000,
                                                     0x1000000,         0x2000000,         0x4000000,         0x8000000,         0x10000000,         0x20000000,         0x40000000,         0x80000000,
                                                     0x100000000,       0x200000000,       0x400000000,       0x800000000,       0x1000000000,       0x2000000000,       0x4000000000,       0x8000000000,
                                                     0x10000000000,     0x20000000000,     0x40000000000,     0x80000000000,     0x100000000000,     0x200000000000,     0x400000000000,     0x800000000000,
                                                     0x1000000000000,   0x2000000000000,   0x4000000000000,   0x8000000000000,   0x10000000000000,   0x20000000000000,   0x40000000000000,   0x80000000000000,
                                                     0x100000000000000, 0x200000000000000, 0x400000000000000, 0x800000000000000, 0x1000000000000000, 0x2000000000000000, 0x4000000000000000, 0x8000000000000000 };

        static const unsigned char WHITE_MOVE = 0x1;
        static const unsigned char BLACK_MOVE = 0x2;

        struct binary_board {
            //unsigned __int64 pawns, bishops, knights, rooks, queens, king;
            //unsigned __int64 pieces[TOTAL_PIECES];
            unsigned char type[16];
            unsigned char pawns[16];
            unsigned char pieces[16];
            unsigned char data;
            unsigned __int64 white_attack;
            unsigned __int64 black_attack;
            unsigned __int64 bit_pawns[16];
            unsigned __int64 bit_pieces[16];
        };
        binary_board bit_board;
        inline unsigned __int64 getBitPiece(int index) { return (index < 64 && index >= 0) ? bit_locations[index] : 0; }
        unsigned __int64 getWhiteBitBoard(binary_board board);
        unsigned __int64 getBlackBitBoard(binary_board board);
        unsigned __int64 getAttackBoard(binary_board board, bool color);
        unsigned __int64 getBitAttackBoard(binary_board board, bool color);
        Board::binary_board setPieceMoveBoard(binary_board& board, bool color);
        unsigned __int64 getMoveBoard(binary_board board, bool color);
        unsigned __int64 getPieceMovement(unsigned char piece, unsigned char location);
        //inline unsigned __int64 getWhiteBoard(binary_board board)
        //{
        //    unsigned __int64 p = 0;
        //    for (int i = WHITE_INDEX_START; i < WHITE_INDEX_END; i++)
        //        p |= board.pieces[i];
        //    return p;
        //}
        //inline unsigned __int64 getBlackBoard(binary_board board)
        //{
        //    unsigned __int64 p = 0;
        //    for (int i = BLACK_INDEX_START; i < BLACK_INDEX_END; i++)
        //        p |= board.pieces[i];
        //    return p;
        //}
        //inline unsigned __int64 getBitBoard(binary_board board)
        //{
        //    unsigned __int64 p = 0;
        //    for (int i = 0; i < TOTAL_PIECES; i++)
        //        p |= board.pieces[i];
        //    return p;
        //    //return (board.pieces[PAWNS] | board.bishops | board.knights | board.rooks | board.queens | board.king);
        //}
        std::string getTypeString(unsigned char type);
        unsigned __int64 getBitBoard(binary_board board);
        void printBitBoard(binary_board board);
        void printBitBoard(unsigned __int64 board_to_print);
        void printBitBoard(unsigned __int64 board_to_print, int location);
        Board::binary_board moveTranslate(binary_board board, std::string start, std::string end);
        unsigned char getTypeConvert(unsigned char type);
        bool checkLegal(binary_board board, unsigned char type, unsigned char start, unsigned char end);
        unsigned char translatePostion(std::string position);
        int myPow(int x, int p);
        void printCharBoard();
        void printCharBoard(binary_board board);
        unsigned __int64 getAllAttackBoard(binary_board board, bool color);
        struct CharacterPieces {
            char pieces[TOTAL_PIECES];
            //char pawn, bishop, knight, rook, queen, king;
        };
    protected:

    private:
        unsigned __int64 getPieceMoveBoard(unsigned char type, unsigned char location);
        Piece PieceController;
        CharacterPieces char_pieces;
};

#endif // BOARD_H
