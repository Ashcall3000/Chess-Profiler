#include "BoardHandler.h"
BoardHandler::BoardHandler() {
    char_pieces[BLACK_PAWN] = 'p';
    char_pieces[BLACK_BISHOP] = 'b';
    char_pieces[BLACK_KNIGHT] = 'n';
    char_pieces[BLACK_ROOK] = 'r';
    char_pieces[BLACK_QUEEN] = 'q';
    char_pieces[BLACK_KING] = 'k';

    char_pieces[WHITE_PAWN] = 'P';
    char_pieces[WHITE_KNIGHT] = 'N';
    char_pieces[WHITE_BISHOP] = 'B';
    char_pieces[WHITE_ROOK] = 'R';
    char_pieces[WHITE_QUEEN] = 'Q';
    char_pieces[WHITE_KING] = 'K';

    char index = 0;
    char location = SQ_A2;
    // White Pawns
    for (char i = WHITE_INDEX_START; i < 8; i++) {
        main_board.piece_types[i] = WHITE_PAWN;
        main_board.piece_locations[i] = location;
        location += EAST;
        index++;
    }
    // White Knights
    main_board.piece_types[++index] = WHITE_KNIGHT;
    main_board.piece_locations[index] = SQ_B1;
    main_board.piece_types[++index] = WHITE_KNIGHT;
    main_board.piece_locations[index] = SQ_G1;
    // White Bishops
    main_board.piece_types[++index] = WHITE_BISHOP;
    main_board.piece_locations[index] = SQ_C1;
    main_board.piece_types[++index] = WHITE_BISHOP;
    main_board.piece_types[index] = SQ_F1;
    // White Rooks
    main_board.piece_types[++index] = WHITE_ROOK;
    main_board.piece_locations[index] = SQ_A1;
    main_board.piece_types[++index] = WHITE_ROOK;
    main_board.piece_locations[index] = SQ_H1;
    // White Queen
    main_board.piece_types[++index] = WHITE_QUEEN;
    main_board.piece_locations[index] = SQ_D1;
    // White King
    main_board.piece_types[++index] = WHITE_KING;
    main_board.piece_locations[index] = SQ_E1;
    // Black Pawns
    location = SQ_H7;
    index = BLACK_INDEX_START;
    for (char i = BLACK_INDEX_START; i < BLACK_INDEX_START + 8; i++) {
        main_board.piece_types[i] = BLACK_PAWN;
        main_board.piece_locations[location];
        location += EAST;
        index++;
    }
    // Black Knights
    main_board.piece_types[++index] = BLACK_KNIGHT;
    main_board.piece_locations[index] = SQ_B8;
    main_board.piece_types[++index] = BLACK_KNIGHT;
    main_board.piece_locations[index] = SQ_G8;
    // Black Bishops
    main_board.piece_types[++index] = BLACK_BISHOP;
    main_board.piece_locations[index] = SQ_C8;
    main_board.piece_types[++index] = BLACK_BISHOP;
    main_board.piece_locations[index] = SQ_F8;
    // Black Rooks
    main_board.piece_types[++index] = BLACK_ROOK;
    main_board.piece_locations[index] = SQ_A8;
    main_board.piece_types[++index] = BLACK_ROOK;
    main_board.piece_locations[index] = SQ_H8;
    // Black Queen
    main_board.piece_types[++index] = BLACK_QUEEN;
    main_board.piece_locations[index] = SQ_D8;
    // Black King
    main_board.piece_types[++index] = BLACK_KING;
    main_board.piece_locations[index] = SQ_E8;
}

void BoardHandler::printCharBoard(Board bboard)
{
    std::copy(std::begin(blank_board), std::end(blank_board), std::begin(char_board));
    for (char i = WHITE_INDEX_START; i < BLACK_INDEX_END; i++) {
        if (bboard.piece_locations[i] != SQ_NONE || bboard.piece_types[i] != TYPE_NONE) {
            char_board[bboard.piece_locations[i]] = char_pieces[bboard.piece_types[i]];
        }
    }
    std::cout << "   /===============================\\" << std::endl;
    int index = 0;
    int row = 8;
    for (int x = 0; x < 8; x++)
    {
        std::cout << row << ": | ";
        row--;
        for (int y = 0; y < 8; y++) {
            std::cout << char_board[index] << " | ";
            index++;
        }
        if (x != 7)
            std::cout << std::endl << "   +---+---+---+---+---+---+---+---+" << std::endl;
    }
    std::cout << std::endl << "   \\===============================/" << std::endl;
    std::cout << "     A   B   C   D   E   F   G   H" << std::endl;
}