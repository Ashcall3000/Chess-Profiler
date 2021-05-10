#include "PieceHandler.h"
Bitboard PieceHandler::getWhitePawnMove(Square origin) {
	Bitboard bboard = 0;
	bboard = shift<NORTH>(origin);
	if (origin & Horz2) {
		bboard |= shift<NORTH>(bboard);
	}
	return bboard;
}

Bitboard PieceHandler::getWhitePawnAttack(Square origin) {
	return shift<NORTH_EAST>(origin) | shift<NORTH_WEST>(origin);
}

Bitboard PieceHandler::getBlackPawnMove(Square origin) {
	Bitboard bboard = 0;
	bboard = shift<SOUTH>(origin);
	if (origin & Horz7) {
		bboard |= shift<SOUTH>(bboard);
	}
	return bboard;
}

Bitboard PieceHandler::getBlackPawnAttack(Square origin) {
	return shift<SOUTH_EAST>(origin) | shift<SOUTH_WEST>(origin);
}

Bitboard PieceHandler::getKnightMove(Square origin) {
	Bitboard bboard = 0xA1100110A;
	if (origin == SQ_C3) {
		return bboard;
	}
	// Move North and South
	if (origin > SQ_H3) {
		for (int i = 3; i < 8 && origin & ~Horizontals[i]; i++) {
			bboard = shift<NORTH>(bboard);
		}
	}
	else if (origin < SQ_A3) {
		for (int i = 3; i >= 0 && origin & ~Horizontals[i]; i--) {
			bboard = shift<SOUTH>(bboard);
		}
	}
	if (origin & VertC) {
		// If it's on the Left
		if (origin & ~(VertA | VertB)) {
			for (int i = 3; i >= 0 && origin & ~Verticals[i]; i--) {
				bboard = shift<WEST>(bboard);
			}
		} else {
			for (int i = 3; i < 8 && origin & ~Verticals[i]; i++) {
				bboard = shift<EAST>(bboard);
			}
		}
	}
	return bboard;
}

Bitboard PieceHandler::getBishopMove(Square origin) {
	Bitboard bboard = 0;
	for (int i = 0; i < SLIDES_TOTAL; i++) {
		if (origin & SLIDES[i]) {
			bboard |= SLIDES[i];
		}
	}
	return origin ^ bboard;
}

Bitboard PieceHandler::getRookMove(Square origin) {
	Bitboard bboard = 0;
	for (int i = 0; i < 8; i++) {
		if (origin & Horizontals[i]) {
			bboard |= Horizontals[i];
		}
		if (origin & Verticals[i]) {
			bboard |= Verticals[i];
		}
	}
	return origin ^ bboard;
}

Bitboard PieceHandler::getQueenMove(Square origin) {
	return getBishopMove(origin) | getRookMove(origin);
}

Bitboard PieceHandler::getKingMove(Square origin) {
	Bitboard bboard = 0;
	bboard = shift<NORTH_WEST>(origin);
	bboard |= shift<NORTH>(origin);
	bboard |= shift<NORTH_EAST>(origin);
	bboard |= shift<WEST>(origin);
	bboard |= shift<EAST>(origin);
	bboard |= shift<SOUTH_WEST>(origin);
	bboard |= shift<SOUTH>(origin);
	bboard |= shift<SOUTH_EAST>(origin);
	return bboard;
}