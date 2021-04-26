#include <iostream>
#include <algorithm>
#include <string>
#include "Board.h"

using namespace std;

Board::Board()
{
    Piece PieceController = Piece();
    char_pieces.pieces[BLACK_PAWNS] = 'p';
    char_pieces.pieces[BLACK_BISHOPS] = 'b';
    char_pieces.pieces[BLACK_KNIGHTS] = 'n';
    char_pieces.pieces[BLACK_ROOKS] = 'r';
    char_pieces.pieces[BLACK_QUEENS] = 'q';
    char_pieces.pieces[BLACK_KING] = 'k';

    char_pieces.pieces[WHITE_PAWNS] = 'P';
    char_pieces.pieces[WHITE_KNIGHTS] = 'N';
    char_pieces.pieces[WHITE_BISHOPS] = 'B';
    char_pieces.pieces[WHITE_ROOKS] = 'R';
    char_pieces.pieces[WHITE_QUEENS] = 'Q';
    char_pieces.pieces[WHITE_KING] = 'K';

    bit_board.data = 0x0;
    int index = 0;
    for (unsigned char i = 48; i < 56; i++) // White Pawns
    {
        bit_board.pawns[index] = i;
        bit_board.type[index] = WHITE_PAWNS;
        index++;
        //cout << "WHITE PAWN SET UP: " << (int)WHITE_PAWNS << endl;
    }
    for (unsigned char i = 8; i < 16; i++) // Black Pawns
    {
        bit_board.pawns[index] = i;
        bit_board.type[index] = BLACK_PAWNS;
        index++;
    }
    bit_board.pieces[WHITE_ROOKS] = 56;
    bit_board.pieces[WHITE_ROOKS + 1] = 63;
    bit_board.pieces[WHITE_KNIGHTS] = 57;
    bit_board.pieces[WHITE_KNIGHTS + 1] = 62;
    bit_board.pieces[WHITE_BISHOPS] = 58;
    bit_board.pieces[WHITE_BISHOPS + 1] = 61;
    bit_board.pieces[WHITE_QUEENS] = 59;
    bit_board.pieces[WHITE_KING] = 60;

    bit_board.pieces[BLACK_ROOKS] = 0;
    bit_board.pieces[BLACK_ROOKS + 1] = 7;
    bit_board.pieces[BLACK_KNIGHTS] = 1;
    bit_board.pieces[BLACK_KNIGHTS + 1] = 6;
    bit_board.pieces[BLACK_BISHOPS] = 2;
    bit_board.pieces[BLACK_BISHOPS + 1] = 5;
    bit_board.pieces[BLACK_QUEENS] = 3;
    bit_board.pieces[BLACK_KING] = 4;
    /*bit_board.pieces[BLACK_PAWNS] = 0xFF00;
    bit_board.pieces[BLACK_KNIGHTS] = 0x0042;
    bit_board.pieces[BLACK_BISHOPS] = 0x0024;
    bit_board.pieces[BLACK_ROOKS] = 0x0081;
    bit_board.pieces[BLACK_QUEENS] = 0x0008;
    bit_board.pieces[BLACK_KING] = 0x0010;
    bit_board.pieces[WHITE_PAWNS] = 0x00FF000000000000;
    bit_board.pieces[WHITE_KNIGHTS] = 0x4200000000000000;
    bit_board.pieces[WHITE_BISHOPS] = 0x2400000000000000;
    bit_board.pieces[WHITE_ROOKS] = 0x8100000000000000;
    bit_board.pieces[WHITE_QUEENS] = 0x0800000000000000;
    bit_board.pieces[WHITE_KING] = 0x1000000000000000;*/
    /*Black.pawn = 'p';
    Black.knight = 'n';
    Black.bishop = 'b';
    Black.rook = 'r';
    Black.queen = 'q';
    Black.king = 'k';*/
    /*black.pawns = 0xFF00;
    black.rooks = 0x0081;
    black.knights = 0x0042;
    black.bishops = 0x0024;
    black.queens = 0x0008;
    black.king = 0x0010;*/
    /*White.pawn = 'P';
    White.knight = 'N';
    White.bishop = 'B';
    White.rook = 'R';
    White.queen = 'Q';
    White.king = 'K';*/
    /*white.pawns = 0x00FF000000000000;
    white.rooks = 0x8100000000000000;
    white.knights = 0x4200000000000000;
    white.bishops = 0x2400000000000000;
    white.queens = 0x0800000000000000;
    white.king = 0x1000000000000000;*/
}

unsigned __int64 Board::getWhiteBitBoard(binary_board board)
{
    unsigned __int64 blank = 0;
    for (unsigned char i = WHITE_INDEX_START; i <= WHITE_INDEX_END; i++)
    {
        blank |= bit_locations[board.pawns[i]] | bit_locations[board.pieces[i]];
    }
    /*cout << "Get White Bit Board" << endl;
    printBitBoard(blank);*/
    return blank;
}

unsigned __int64 Board::getBlackBitBoard(binary_board board)
{
    unsigned __int64 blank = 0;
    for (unsigned char i = BLACK_INDEX_START; i < BLACK_INDEX_END; i++)
    {
        blank |= bit_locations[board.pawns[i]] | bit_locations[board.pieces[i]];
    }
    /*cout << "Get Black Bit Board" << endl;
    printBitBoard(blank);*/
    return blank;
}

unsigned __int64 Board::getAttackBoard(binary_board board, bool color)
{
    unsigned char start = (color) ? WHITE_INDEX_START : BLACK_INDEX_START;
    unsigned char end = (color) ? WHITE_INDEX_END : BLACK_INDEX_END;
    unsigned __int64 blank = 0;
    for (unsigned char i = start; i < end; i++)
    {
        blank |= getPieceMoveBoard(board.type[i], board.pawns[i]);
    }
    for (unsigned char i = start; i < end; i++)
    {
        blank |= getPieceMoveBoard(i, board.pieces[i]);
    }
    return blank;
}

unsigned __int64 Board::getBitAttackBoard(binary_board board, bool color)
{
    unsigned char start = (color) ? WHITE_INDEX_START : BLACK_INDEX_START;
    unsigned char end = (color) ? WHITE_INDEX_END : BLACK_INDEX_END;
    board = setPieceMoveBoard(board, color);
    unsigned __int64 test = getMoveBoard(board, color);
    printBitBoard(test);
    unsigned __int64 blank = 0;
    for (unsigned char index = start; index < end; index++)
    {
        cout << "TYPE: " << getTypeString(index) << endl;
        printBitBoard(board.bit_pieces[index]);
        cout << "--------------------" << endl;
        printBitBoard(board.bit_pawns[index]);
    }
    for (int loc = 0; loc < 64; loc++)
    {
        if (test & bit_locations[loc])
        {
            cout << "Location: " << (int)loc << endl;
            //printBitBoard(bit_locations[loc]);
            for (unsigned char i = start; i < end; i++)
            {
                if ((board.bit_pieces[i] & bit_locations[loc]) > 0) 
                {
                    
                    if (checkLegal(board, i, board.pieces[i], loc))
                    {
                        cout << "Bit Board: " << (int)i << endl;
                        printBitBoard(board.bit_pieces[i], loc);
                        blank |= bit_locations[i];
                    }
                }
                if (board.bit_pawns[i] & bit_locations[loc])
                {
                    if (checkLegal(board, board.type[i], board.pieces[i], loc))
                    {
                        blank |= bit_locations[i];
                    }
                }
            }
        }
    }
    cout << "\n\n\n\n\n";
    return blank;
}

Board::binary_board Board::setPieceMoveBoard(binary_board& board, bool color)
{
    unsigned char start = (color) ? WHITE_INDEX_START : BLACK_INDEX_START;
    unsigned char end = (color) ? WHITE_INDEX_END : BLACK_INDEX_END;
    for (unsigned char i = start; i < end; i++)
    {
        board.bit_pawns[i] = getPieceMoveBoard(board.type[i], board.pawns[i]);
        board.bit_pieces[i] = getPieceMoveBoard(i, board.pieces[i]);
        //cout << "PAWN" << endl;
        //printBitBoard(board.bit_pawns[i]);
    }
    return board;
}

unsigned __int64 Board::getMoveBoard(binary_board board, bool color)
{
    unsigned char start = (color) ? WHITE_INDEX_START : BLACK_INDEX_START;
    unsigned char end = (color) ? WHITE_INDEX_END : BLACK_INDEX_END;
    unsigned __int64 blank = 0;
    for (unsigned char i = start; i < end; i++)
    {
        blank |= board.bit_pawns[i];
        blank |= board.bit_pieces[i];
    }
    return blank;
}

//unsigned __int64 Board::getPieceMoveBoard(unsigned char piece, unsigned char location)
//{
//    Piece pieces;
//    switch (getTypeConvert(piece))
//    {
//    case WHITE_QUEENS:
//    case BLACK_QUEENS:
//        return pieces.getBitQueenMove(location);
//        break;
//    case WHITE_KING:
//    case BLACK_KING:
//        return pieces.getBitKingMove(location);
//        break;
//    case WHITE_KNIGHTS:
//    case BLACK_KNIGHTS:
//        return pieces.getBitKnightMove(location);
//        break;
//    case WHITE_BISHOPS:
//    case BLACK_BISHOPS:
//        return pieces.getBitBishopMove(location);
//        break;
//    case WHITE_ROOKS:
//    case BLACK_ROOKS:
//        return pieces.getBitRookMove(location);
//        break;
//    case WHITE_PAWNS:
//        return pieces.getBitWhitePawnMove(location);
//        break;
//    case BLACK_PAWNS:
//        return pieces.getBitBlackPawnMove(location);
//        break;
//    }
//}

std::string Board::getTypeString(unsigned char type)
{
    switch (getTypeConvert(type))
    {
    case WHITE_QUEENS:
        return "White Queen";
        break;
    case BLACK_QUEENS:
        return "Black Queen";
        break;
    case WHITE_KING:
        return "White King";
        break;
    case BLACK_KING:
        return "Black King";
        break;
    case WHITE_KNIGHTS:
        return "White Knight";
        break;
    case BLACK_KNIGHTS:
        return "Black Knight";
        break;
    case WHITE_BISHOPS:
        return "White Bishop";
        break;
    case BLACK_BISHOPS:
        return "Black Bishop";
        break;
    case WHITE_ROOKS:
        return "White Rook";
        break;
    case BLACK_ROOKS:
        return "Black Rook";
        break;
    case WHITE_PAWNS:
        return "White Pawn";
        break;
    case BLACK_PAWNS:
        return "Black Pawn";
        break;
    }
}

unsigned __int64 Board::getBitBoard(binary_board board)
{
    unsigned __int64 blank = 0;
    for (unsigned char i = WHITE_INDEX_START; i < BLACK_INDEX_END; i++)
    {
        blank |= board.pieces[i] | board.pawns[i];
    }
    return blank;
}

void Board::printBitBoard(binary_board board)
{
    printBitBoard(getBitBoard(board));
}

void Board::printBitBoard(unsigned __int64 board_to_print)
{
    unsigned __int64 checker = 1;
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if ((checker & board_to_print) > 0)
                cout << 1;
            else
                cout << 0;
            cout << ' ';
            checker = checker << 1;
        }
        cout << endl;
    }
}

void Board::printBitBoard(unsigned __int64 board_to_print, int location)
{
    int i = 0;
    unsigned __int64 checker = 1;
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if (i != location)
            {
                if ((checker & board_to_print) > 0)
                    cout << 1;
                else
                    cout << 0;
            }
            else
                cout << '*';
            cout << ' ';
            checker = checker << 1;
            i++;
        }
        cout << endl;
    }
}

Board::binary_board Board::moveTranslate(binary_board board, std::string start, std::string end)
{
    unsigned char start_pos = translatePostion(start);
    unsigned char end_pos = translatePostion(end);
    unsigned char type = 0;
    unsigned char index = 0;
    for (unsigned char i = WHITE_INDEX_START; i < BLACK_INDEX_END; i++)
    {
        if (board.pawns[i] == start_pos)
        {
            type = board.type[i];
            index = i;
        }
        else if (board.pieces[i] == start_pos)
        {
            type = getTypeConvert(i);
        }
    }
    cout << endl;
    if (checkLegal(board, type, start_pos, end_pos))
    {
        if (type == WHITE_PAWNS || type == BLACK_PAWNS)
            board.pawns[index] = end_pos;
        else
            board.pieces[type] = end_pos;
        if (type < WHITE_INDEX_END || type == WHITE_PAWNS)
        {
            board.data &= ~WHITE_MOVE;
            board.data |= BLACK_MOVE;
        }
        else if (type > BLACK_INDEX_START || type == BLACK_PAWNS)
        {
            board.data &= ~BLACK_MOVE;
            board.data |= WHITE_MOVE;
        }
    }
    /*for (int i = 0; i < TOTAL_PIECES; i++)
    {
        if (board.pieces[i] & bit_locations[start_pos])
            type = i;
    }
    if (checkLegal(board, type, start_pos, end_pos))
    {
        board.pieces[type] ^= bit_locations[start_pos];
        board.pieces[type] |= bit_locations[end_pos];
        if (type < WHITE_INDEX_END)
            for (int i = BLACK_INDEX_START; i < BLACK_INDEX_END; i++)
                board.pieces[i] &= ~bit_locations[end_pos];
        else
            for (int i = WHITE_INDEX_START; i < WHITE_INDEX_END; i++)
                board.pieces[i] &= ~bit_locations[end_pos];
    }*/
    return board;
}

unsigned char Board::getTypeConvert(unsigned char type)
{
    //cout << "TYPE: " << (int)type << endl;
    switch (type)
    {
    case WHITE_QUEENS:
    case BLACK_QUEENS:
    case WHITE_KING:
    case BLACK_KING:
    case WHITE_KNIGHTS:
    case BLACK_KNIGHTS:
    case WHITE_BISHOPS:
    case BLACK_BISHOPS:
    case WHITE_ROOKS:
    case BLACK_ROOKS:
    case WHITE_PAWNS:
    case BLACK_PAWNS:
        /*cout << "RETURN TYPE: " << (int)type << endl;
        cout << "____________________" << endl;*/
        return type;
        break;
    default:
        /*cout << "RETURN Type: " << (int)((type / 2) * 2) << endl;
        cout << "____________________" << endl;*/
        return (type / 2) * 2;
    }
}

bool Board::checkLegal(binary_board board, unsigned char type, unsigned char start, unsigned char end)
{
    unsigned __int64 move_board = 0;
    unsigned __int64 white_board = getWhiteBitBoard(board);
    unsigned __int64 black_board = getBlackBitBoard(board);
    bool can_move = false;
    // Check to see if end location is occupied by same color piece
    cout << "----------CheckLegal----------\n";
    cout << "Start: " << (int)start << endl;
    cout << "End: " << (int)end << endl;
    cout << "Type: " << getTypeString(type) << endl;
    cout << "Move Location:" << endl;
    printBitBoard(bit_locations[end], start);
    /*cout << "White Board:" << endl;
    printBitBoard(white_board);*/
    if (((white_board | black_board) & bit_locations[start]) == 0)
    {
        //cout << "There's no piece there to move.\n";
        return false;
    }
    else
    {
        white_board ^= bit_locations[start];
        black_board ^= bit_locations[start];
    }
    //if ((board.data & WHITE_MOVE) > 0 && type > BLACK_INDEX_START)
    //{
    //    //cout << "It's White's turn to move not Black's.\n";
    //    return false;
    //}
    //else if ((board.data & BLACK_MOVE) > 0 && type < WHITE_INDEX_END)
    //{
    //    //cout << "It's Black's turn to move not White's\n";
    //    return false;
    //}
    if (type < WHITE_INDEX_END && ((white_board & bit_locations[end]) > 0))
    {
        cout << "End location has a white piece in the spot." << endl;
        return false;
    }
    else if (type >= BLACK_INDEX_START && ((black_board & bit_locations[end]) > 0))
    {
        cout << "End location has a black piece in the spot." << endl;
        return false;
    }
    // Check to see if piece can move to location
    move_board = getPieceMoveBoard(type, start);
    cout << "Move Board:" << endl;
    printBitBoard(move_board);
    if ((move_board & bit_locations[end]) == 0) 
    {
        cout << "Piece Can't move to that square." << endl;
        return false;
    }
    unsigned __int64 piece_board = ((white_board | black_board) ^ bit_locations[start]) & ~bit_locations[end];
    unsigned __int64 overlap = (move_board & piece_board) & ~bit_locations[end];
    cout << "Piece Board:" << endl;
    printBitBoard(piece_board);
    cout << "Overlap:" << endl;
    printBitBoard(overlap);
    if (overlap > 0) // piece might be in the way
    {
        cout << "Piece might be in the way." << endl;
        int row = (end / 8) * 8;
        if (start > end) // Trying to move up the board
        {
            cout << "Piece is moving up the board." << endl;
            for (int i = 0; i < row; i += 8)
            {
                overlap &= ~PieceController.getBitHorizontal(i);
            }
            cout << "NEW Overlap:" << endl;
            printBitBoard(overlap);
            if (overlap > bit_locations[end]) // Good Chance piece is in the way
            {
                cout << "Good chance piece is in the way." << endl;
                switch (type)
                {
                case WHITE_QUEENS:
                case BLACK_QUEENS:
                case WHITE_BISHOPS:
                case BLACK_BISHOPS:
                    if (PieceController.getBitUpDiagonal(start) & bit_locations[end]) // If end location is on the up diagonal
                    { 
                        if ((PieceController.getBitUpDiagonal(start) & piece_board) > bit_locations[end]) // If the white pieces are before the end location
                        {
                            cout << "Diag Up: Piece was in the way" << endl;
                            return false;
                        }
                    }
                    else if (PieceController.getBitDownDiagonal(start) & bit_locations[end]) // If end location is on the down diagonal 
                    {
                        if ((PieceController.getBitDownDiagonal(start) & piece_board) > bit_locations[end]) // if the white pieces are before the end location
                        {
                            cout << "Diag Down:" << endl;
                            printBitBoard(PieceController.getBitDownDiagonal(start));
                            cout << "Diag Down: Piece was in the way" << endl;
                            return false;
                        }
                    }
                    break;
                }
                switch (type)
                {
                case WHITE_QUEENS:
                case BLACK_QUEENS:
                case WHITE_ROOKS:
                case BLACK_ROOKS:
                    if (PieceController.getBitHorizontal(start) & bit_locations[end]) // if end location is on the horizontal
                    {
                        if ((PieceController.getBitHorizontal(start) & piece_board) > bit_locations[end])
                        {
                            cout << "HORZ: Piece was in the way" << endl;
                            return false;
                        }
                    }
                    else // if end location is on the vertical
                    {
                        if ((PieceController.getBitVertical(start) & piece_board) > bit_locations[end])
                        {
                            cout << "VERT: Piece was in the way" << endl;
                            return false;
                        }
                    }
                    break;
                case WHITE_PAWNS:
                    if ((move_board & piece_board) > bit_locations[end]) 
                    {
                        cout << "PAWN: There's a piece in the way" << endl;
                        return false;
                    }
                }
            }
        }
        else // Trying to move down the board
        {
            cout << "Piece is moving down the board." << endl;
            for (int i = 56; i > row; i -= 8)
            {
                overlap &= ~PieceController.getBitHorizontal(i);
            }
            cout << "NEW Overlap:" << endl;
            printBitBoard(overlap);
            if (overlap < bit_locations[end]) // Good chance piece is in the way
            {
                cout << "Good chance piece is in the way." << endl;
                switch (type)
                {
                case WHITE_QUEENS:
                case BLACK_QUEENS:
                case WHITE_BISHOPS:
                case BLACK_BISHOPS:
                    if (PieceController.getBitUpDiagonal(start) & bit_locations[end]) // If end location is on the up diagonal
                    {
                        if ((PieceController.getBitUpDiagonal(start) & piece_board) < bit_locations[end] && (PieceController.getBitUpDiagonal(start) & piece_board) != 0) // If the white pieces are before the end location
                        {
                            cout << "Diag Up:" << endl;
                            printBitBoard(PieceController.getBitUpDiagonal(start));
                            cout << "Diag Up: Piece was in the way" << endl;
                            return false;
                        }
                    }
                    else if (PieceController.getBitDownDiagonal(start) & bit_locations[end]) // If end location is on the down diagonal 
                    {
                        if ((PieceController.getBitDownDiagonal(start) & piece_board) < bit_locations[end] && (PieceController.getBitDownDiagonal(start) & piece_board) != 0) // if the white pieces are before the end location
                        {
                            cout << "Diag Down: Piece was in the way" << endl;
                            return false;
                        }
                    }
                    break;
                }
                switch (type)
                {
                case WHITE_QUEENS:
                case BLACK_QUEENS:
                case WHITE_ROOKS:
                case BLACK_ROOKS:
                    if (PieceController.getBitHorizontal(start) & bit_locations[end]) // if end location is on the horizontal
                    {
                        if ((PieceController.getBitHorizontal(start) & piece_board) < bit_locations[end] && (PieceController.getBitHorizontal(start) & piece_board) != 0)
                        {
                            cout << "HORZ: Piece was in the way" << endl;
                            return false;
                        }
                    }
                    else // if end location is on the vertical
                    {
                        if ((PieceController.getBitVertical(start) & piece_board) < bit_locations[end] && (PieceController.getBitVertical(start) & piece_board) != 0)
                        {
                            cout << "VERT: Piece was in the way" << endl;
                            return false;
                        }
                    }
                    break;
                case BLACK_PAWNS:
                    if ((move_board & piece_board) < bit_locations[end])
                    {
                        cout << "PAWN: There's a piece in the way" << endl;
                        return false;
                    };
                }
            }
        }
    }
    return true;
}

unsigned char Board::translatePostion(string position)
{
    cout << "----------TranslatePosition----------" << endl;
    cout << "POS: " << position << endl;
    int num = position[1];
    if ('0' <= num && num <= '9')
        num = num - '0';
    int loc = 64 - (8 * (num));
    cout << "NUM: " << num << endl;
    cout << "LOC: " << loc << endl;
    switch (position[0]) {
    case 'B':
        loc += 1;
        break;
    case 'C':
        loc += 2;
        break;
    case 'D':
        loc += 3;
        break;
    case 'E':
        loc += 4;
        break;
    case 'F':
        loc += 5;
        break;
    case 'G':
        loc += 6;
        break;
    case 'H':
        loc += 7;
        break;
    }
    if (loc > 64)
        return 0;
    cout << "FINAL LOC: " << loc << endl;
    cout << "-------------------------------------" << endl;
    return (unsigned char) loc;
}

int Board::myPow(int x, int p)
{
    int i = 1;
    for (int j = 1; j <= p; j++)
        i *= x;
    return i;
}

void Board::printCharBoard()
{
    copy(begin(blank_board), end(blank_board), begin(char_board));
    //for (int i = 0; i < 64; i++)
    //{
    //    /*if ((white.pawns & bit_locations[i]) > 0)
    //        char_board[i] = White.pawn;
    //    else if ((white.knights & bit_locations[i]) > 0)
    //        char_board[i] = White.knight;
    //    else if ((white.bishops & bit_locations[i]) > 0)
    //        char_board[i] = White.bishop;
    //    else if ((white.rooks & bit_locations[i]) > 0)
    //        char_board[i] = White.rook;
    //    else if ((white.queens & bit_locations[i]) > 0)
    //        char_board[i] = White.queen;
    //    else if ((white.king & bit_locations[i]) > 0)
    //        char_board[i] = White.king;
    //    else if ((black.pawns & bit_locations[i]) > 0)
    //        char_board[i] = Black.pawn;
    //    else if ((black.knights & bit_locations[i]) > 0)
    //        char_board[i] = Black.knight;
    //    else if ((black.bishops & bit_locations[i]) > 0)
    //        char_board[i] = Black.bishop;
    //    else if ((black.rooks & bit_locations[i]) > 0)
    //        char_board[i] = Black.rook;
    //    else if ((black.queens & bit_locations[i]) > 0)
    //        char_board[i] = Black.queen;
    //    else if ((black.king & bit_locations[i]) > 0)
    //        char_board[i] = Black.king;*/
    //    /*for (int w = 0; w < 6; w++)
    //        if ((white.pieces[w] & bit_locations[i]) > 0)
    //            char_board[i] = White.Pieces[w];
    //    for (int b = 0; b < 6; b++)
    //        if ((black.pieces[b] & bit_locations[i]) > 0)
    //            char_board[i] = Black.Pieces[b];*/
    //    for (int p = WHITE_INDEX_START; p < BLACK_INDEX_END; p++)
    //        if (bit_board.pieces[p] & bit_locations[i])
    //            char_board[i] = char_pieces.pieces[p];
    //}
    for (unsigned char i = WHITE_INDEX_START; i < BLACK_INDEX_END; i++)
    {
        char_board[bit_board.pawns[i]] = char_pieces.pieces[bit_board.type[i]];
        char_board[bit_board.pieces[i]] = char_pieces.pieces[getTypeConvert(i)];
    }
    cout << "   /===============================\\" << endl;
    int index = 0;
    int row = 8;
    for (int x = 0; x < 8; x++)
    {
        cout << row << ": | ";
        row--;
        for (int y = 0; y < 8; y++) {
            cout << char_board[index] << " | ";
            index++;
        }
        if (x != 7)
            cout << endl << "   +---+---+---+---+---+---+---+---+" << endl;
    }
    cout << endl << "   \\===============================/" << endl;
    cout << "     A   B   C   D   E   F   G   H" << endl;
}

void Board::printCharBoard(binary_board board)
{
    copy(begin(blank_board), end(blank_board), begin(char_board));
    /*for (int i = 0; i < 64; i++)
        for (int p = WHITE_INDEX_START; p < BLACK_INDEX_END; p++)
            if (board.pieces[p] & bit_locations[i])
                char_board[i] = char_pieces.pieces[p];*/
    for (unsigned char i = WHITE_INDEX_START; i < BLACK_INDEX_END; i++)
    {
        char_board[board.pawns[i]] = char_pieces.pieces[board.type[i]];
        char_board[board.pieces[i]] = char_pieces.pieces[getTypeConvert(i)];
    }
    cout << "   /===============================\\" << endl;
    int index = 0;
    int row = 8;
    for (int x = 0; x < 8; x++)
    {
        cout << row << ": | ";
        row--;
        for (int y = 0; y < 8; y++) {
            cout << char_board[index] << " | ";
            index++;
        }
        if (x != 7)
            cout << endl << "   +---+---+---+---+---+---+---+---+" << endl;
    }
    cout << endl << "   \\===============================/" << endl;
    cout << "     A   B   C   D   E   F   G   H" << endl;
}

unsigned __int64 Board::getAllAttackBoard(binary_board board, bool color)
{
    unsigned __int64 test_board = 0;
    unsigned __int64 attack_board = 0;
    //if (color) // White
    //    test_board = getWhiteBoard(board);
    //else
    //    test_board = getBlackBoard(board);
    //for (int i = 0; i < 64; i++)
    //{
    //    if (bit_locations[i] & test_board)
    //    {
    //        if (color)
    //        {
    //            for (int y = WHITE_INDEX_START; y < WHITE_INDEX_END; y++)
    //                if (board.pieces[y] & bit_locations[i])
    //                    attack_board |= getPieceMoveBoard(y, i);
    //        }
    //        else
    //        {
    //            for (int y = BLACK_INDEX_START; y < BLACK_INDEX_END; y++)
    //                if (board.pieces[y] & bit_locations[i])
    //                    attack_board |= getPieceMoveBoard(y, i);
    //        }
    //    }
    //}
    return attack_board;
}

unsigned __int64 Board::getPieceMoveBoard(unsigned char type, unsigned char location)
{
    type = getTypeConvert(type);
    switch (type)
    {
    case WHITE_PAWNS:
        /*cout << "White Pawn Location: " << (int)location << endl;
        printBitBoard(PieceController.getBitWhitePawnMove(location), location);*/
        return PieceController.getBitWhitePawnMove(location);
        break;
    case BLACK_PAWNS:
        /*cout << "Black Pawn Location: " << (int)location << endl;
        printBitBoard(PieceController.getBitBlackPawnMove(location), location);*/
        return PieceController.getBitBlackPawnMove(location);
        break;
    case WHITE_KNIGHTS:
    case BLACK_KNIGHTS:
        /*cout << "Knight Location: " << (int)location << endl;
        printBitBoard(PieceController.getBitKnightMove(location), location);*/
        return PieceController.getBitKnightMove(location);
        break;
    case WHITE_BISHOPS:
    case BLACK_BISHOPS:
        /*cout << "Bishop Location: " << (int)location << endl;
        printBitBoard(PieceController.getBitBishopMove(location), location);*/
        return PieceController.getBitBishopMove(location);
        break;
    case WHITE_ROOKS:
    case BLACK_ROOKS:
        /*cout << "Rook Location: " << (int)location << endl;
        printBitBoard(PieceController.getBitRookMove(location), location);*/
        return PieceController.getBitRookMove(location);
        break;
    case WHITE_QUEENS:
    case BLACK_QUEENS:
        /*cout << "Queen Location: " << (int)location << endl;
        printBitBoard(PieceController.getBitQueenMove(location), location);*/
        return PieceController.getBitQueenMove(location);
        break;
    case WHITE_KING:
    case BLACK_KING:
        /*cout << "King Location: " << (int)location << endl;
        printBitBoard(PieceController.getBitKingMove(location), location);*/
        return PieceController.getBitKingMove(location);
        break;
    }
}

Board::~Board()
{
}
