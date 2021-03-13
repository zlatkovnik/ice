#pragma once

#include "Undo.h"
#include "defines.h"

class Board
{
private:
	
	int pieces[120];			//Piece on each square
	ULONG pawns[3];				//Pawn bitboard for white=0, black=1, both=2
	int pieceCount[P_CNT];		//Number of each piece
	int pieceList[P_CNT][10];	//Position for every piece, pl[piece][index]
	Undo history[MAX_MOVES];	//History of moves for undo

	int side;					//Who moves next
	int enPas;					//En passant square, if there is no enpas then it is NO_SQ
	int fiftyMove;				//Counter for 50 moves without capture
	int castlePerm;				//Is castle possible, check enums

	int ply;					//Number of half moves for search
	int plyHis;					//How many half moves have been played
	int material[2];			//Material value of board for white=0 and black=1

	ULONG key;					//Zobrist key for current board state
};

