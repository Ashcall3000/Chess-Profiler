#pragma once
#include "Data.h"
const int SLIDES_TOTAL = 30;
const Bitboard SLIDES[] = { 0x102040810204080, 0x1020408102040, 0x10204081020, 0x102040810, 0x1020408, 0x10204, 0x102, 0x1,
							0x204081020408000, 0x408102040800000, 0x810204080000000, 0x1020408000000000, 0x2040800000000000, 0x4080000000000000, 0x8000000000000000,
							0x8040201008040201, 0x4020100804020100, 0x2010080402010000, 0x1008040201000000, 0x804020100000000, 0x402010000000000, 0x201000000000000, 0x100000000000000,
							0x80402010080402, 0x804020100804, 0x8040201008, 0x80402010, 0x804020, 0x8040, 0x80 };
class PieceHandler
{
public:

private:
	Bitboard getWhitePawnMove(Square origin);
	Bitboard getWhitePawnAttack(Square origin);
	Bitboard getBlackPawnMove(Square origin);
	Bitboard getBlackPawnAttack(Square origin);
	Bitboard getKnightMove(Square origin);
	Bitboard getBishopMove(Square origin);
	Bitboard getRookMove(Square origin);
	Bitboard getQueenMove(Square origin);
	Bitboard getKingMove(Square origin);
};

