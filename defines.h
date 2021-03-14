#pragma once

#define ULONG unsigned long long			//Unsigned 64 bit number

#define SQ_CNT 120							//Number of squares on board
#define P_CNT 13							//Number of piece types
#define MAX_MOVES 2048						//Maximum number of moves in game

#define FR2SQ(f,r) ( 21 + f + r * 10 )		//File rank to square
#define SQ64(sq) (sq120to64[sq])			//120 index square to 64
#define SQ120(sq) (sq64to120[sq])			//64 index square to 120
#define POP(b) PopBit(b)					//Pop bit in bitboard
#define CNT(b) CountBits(b)					//Count bits in bb
#define CLRBIT(bb,sq) (bb &= util::clearMask[sq])
#define SETBIT(bb,sq) (bb |= util::setMask[sq])

#define FEN_START "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"



enum { EMPTY = 0, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };

enum { WHITE = 0, BLACK, BOTH };

enum { FILE_A = 0, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, NO_FILE };

enum { RANK1 = 0, RANK2, RANK3, RANK4, RANK5, RANK6, RANK7, RANK8, NO_RANK };

enum {
	A1 = 21, B1, C1, D1, E1, F1, G1, H1,
	A2 = 31, B2, C2, D2, E2, F2, G2, H2,
	A3 = 41, B3, C3, D3, E3, F3, G3, H3,
	A4 = 51, B4, C4, D4, E4, F4, G4, H4,
	A5 = 61, B5, C5, D5, E5, F5, G5, H5,
	A6 = 71, B6, C6, D6, E6, F6, G6, H6,
	A7 = 81, B7, C7, D7, E7, F7, G7, H7,
	A8 = 91, B8, C8, D8, E8, F8, G8, H8,
	NO_SQ = 99, OFF_BOARD = 100
};

enum { WKC = 1, WQC = 2, BKC = 4, BQC = 8 };

