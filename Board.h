#pragma once

#include "Undo.h"
#include "defines.h"

class Board
{
private:
//BOARD
	int pieces[120];			//Piece on each square
	ULONG pawns[3];				//Pawn bitboard for white=0, black=1, both=2
	int pieceCount[P_CNT];		//Number of each piece
	int pieceList[P_CNT][10];	//Position for every piece, pl[piece][index]
	Undo history[MAX_MOVES];	//History of moves for undo
//FLAGS
	int side;					//Who moves next
	int enPas;					//En passant square, if there is no enpas then it is NO_SQ
	int fiftyMove;				//Counter for 50 moves without capture
	int castlePerm;				//Is castle possible, check enums
//MISC
	int ply;					//Number of half moves for search
	int plyHis;					//How many half moves have been played
	int material[2];			//Material value of board for white=0 and black=1

	ULONG key;					//Zobrist key for current board state
//HASH KEYS
	//Randomly generated keys each time
	//But they stay the same as long as the application is open
	ULONG pieceKeys[P_CNT][SQ_CNT];
	ULONG sideKey;
	ULONG castleKeys[16];

//DISPLAY
	const static char pieceChar[];
	const static char sideChar[];
	const static char rankChar[];
	const static char fileChar[];
//UTILITY
    const static int sq120to64[];
    const static int sq64to120[];
	const static int sqToFile[];
	const static int sqToRank[];
	const static int pieceVal[];
	const static int pieceCol[];
//MOVEMENT
	const static int knightDir[];
	const static int rookDir[];
	const static int bishopDir[];
	const static int kingDir[];
//PIECE
	const static bool pKnight[];
	const static bool pKing[];
	const static bool pRookQueen[];
	const static bool pBishopQueen[];
public:
	void reset();
	void init();

	void loadFEN(const char*);
	void loadStart();

	void initHashKeys();
	ULONG generateKey(const Board* board);

	void print();
	void printBitBoards();

	bool squareAttacked(int sq, int side);
};

