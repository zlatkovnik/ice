#pragma once

enum { EMPTY = 0, WP, WN, WB, WR, WQ, WK, BP, BN, BB, BR, BQ, BK };

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