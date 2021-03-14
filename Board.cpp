#include "Board.h"
#include "util.h"

#include "iostream"
#include "cassert"
#include "iomanip"

const int Board::sq120to64[] = {
    65, 65, 65, 65, 65, 65, 65, 65, 65, 65,
    65, 65, 65, 65, 65, 65, 65, 65, 65, 65,
    65, 0,  1,  2,  3,  4,  5,  6,  7,  65,
    65, 8,  9,  10, 11, 12, 13, 14, 15, 65,
    65, 16, 17, 18, 19, 20, 21, 22, 23, 65,
    65, 24, 25, 26, 27, 28, 29, 30, 31, 65,
    65, 32, 33, 34, 35, 36, 37, 38, 39, 65,
    65, 40, 41, 42, 43, 44, 45, 46, 47, 65,
    65, 48, 49, 50, 51, 52, 53, 54, 55, 65,
    65, 56, 57, 58, 59, 60, 61, 62, 63, 65,
    65, 65, 65, 65, 65, 65, 65, 65, 65, 65,
    65, 65, 65, 65, 65, 65, 65, 65, 65, 65
};
const int Board::sq64to120[] = {
        21, 22, 23, 24, 25, 26, 27, 28,
        31, 32, 33, 34, 35, 36, 37, 38,
        41, 42, 43, 44, 45, 46, 47, 48,
        51, 52, 53, 54, 55, 56, 57, 58,
        61, 62, 63, 64, 65, 66, 67, 68,
        71, 72, 73, 74, 75, 76, 77, 78,
        81, 82, 83, 84, 85, 86, 87, 88,
        91, 92, 93, 94, 95, 96, 97, 98
};
const int Board::sqToFile[] = {
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
        100,   0,   1,   2,   3,   4,   5,   6,   7, 100,
        100,   0,   1,   2,   3,   4,   5,   6,   7, 100,
        100,   0,   1,   2,   3,   4,   5,   6,   7, 100,
        100,   0,   1,   2,   3,   4,   5,   6,   7, 100,
        100,   0,   1,   2,   3,   4,   5,   6,   7, 100,
        100,   0,   1,   2,   3,   4,   5,   6,   7, 100,
        100,   0,   1,   2,   3,   4,   5,   6,   7, 100,
        100,   0,   1,   2,   3,   4,   5,   6,   7, 100,
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100
};
const int Board::sqToRank[] = {
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
        100,   0,   0,   0,   0,   0,   0,   0,   0, 100,
        100,   1,   1,   1,   1,   1,   1,   1,   1, 100,
        100,   2,   2,   2,   2,   2,   2,   2,   2, 100,
        100,   3,   3,   3,   3,   3,   3,   3,   3, 100,
        100,   4,   4,   4,   4,   4,   4,   4,   4, 100,
        100,   5,   5,   5,   5,   5,   5,   5,   5, 100,
        100,   6,   6,   6,   6,   6,   6,   6,   6, 100,
        100,   7,   7,   7,   7,   7,   7,   7,   7, 100,
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100
};

const int Board::pieceVal[] = { 0, 100, 325, 325, 550, 1000, 50000, 100, 325, 325, 550, 1000, 50000 };
const int Board::pieceCol[] = {
        BOTH,
        WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK
};

const char Board::pieceChar[] = ".pnbrqkPNBRQK";
const char Board::sideChar[] = "wb-";
const char Board::rankChar[] = "12345678";
const char Board::fileChar[] = "abcdefgh";

const int Board::knightDir[] = { -8, -19, -21, -12, 8, 19, 21, 12 };
const int Board::rookDir[] = { -1, -10, 1, 10 };
const int Board::bishopDir[] = { -9, -11, 11, 9 };
const int Board::kingDir[] = { -1, -10, 1, 10, -9, -11, 11, 9 };

const bool Board::pKnight[] = { false, false, true, false, false, false, false, false, true, false, false, false, false };
const bool Board::pKing[] = { false, false, false, false, false, false, true, false, false, false, false, false, true };
const bool Board::pRookQueen[] = { false, false, false, false, true, true, false, false, false, false, true, true, false };
const bool Board::pBishopQueen[] = { false, false, false, true, false, true, false, false, false, true, false, true, false };

void Board::loadStart()
{
    loadFEN(FEN_START);
}

void Board::printBitBoards()
{
        ULONG shift = 1UL;
        int rank = 0;
        int file = 0;
        int sq = 0;
        int sq64 = 0;

        for (int i = 0; i < 3; i++)
        {
            for (rank = RANK8; rank >= RANK1; --rank)
            {
                for (file = FILE_A; file <= FILE_H; file++)
                {
                    sq = FR2SQ(file, rank);
                    sq64 = SQ64(sq);
                    if (((shift << sq64) & pawns[i]) != 0UL)
                        std::cout << 'X';
                    else
                        std::cout << '-';
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
}

void Board::reset()
{
    for (int i = 0; i < SQ_CNT; i++)
    {
        pieces[i] = OFF_BOARD;
    }
    for (int i = 0; i < 64; i++)
    {
        pieces[SQ120(i)] = EMPTY;
    }

    for (int i = 0; i < 13; ++i)
    {
        pieceCount[i] = 0;
    }

    for (int i = 0; i < 3; i++) {
        pawns[i] = 0ULL;
    }

    side = BOTH;
    enPas = NO_SQ;
    fiftyMove = 0;

    ply = 0;
    plyHis = 0;

    castlePerm = 0;

    key = 0UL;
}

void Board::init()
{
    util::initBitMasks();
    initHashKeys();
}

void Board::loadFEN(const char* fen)
{
    reset();
    int file = FILE_A;
    int rank = RANK8;
    const char* c = fen;
    int sq;
    while (*c != ' ')
    {
        sq = FR2SQ(file, rank);
        switch (*c)
        {
        case '/': {
            rank--;
            file = FILE_A;
            break;
        }
        case 'r': {
            pieces[sq] = bR;
            pieceList[bR][pieceCount[bR]] = sq;
            pieceCount[bR]++;

            file++;
            break;
        }
        case 'n': {
            pieces[sq] = bN;
            pieceList[bN][pieceCount[bN]] = sq;
            pieceCount[bN]++;
            file++;
            break;
        }
        case 'b': {
            pieces[sq] = bB;
            pieceList[bB][pieceCount[bB]] = sq;
            pieceCount[bB]++;
            file++;
            break;
        }
        case 'q': {
            pieces[sq] = bQ;
            pieceList[bQ][pieceCount[bQ]] = sq;
            pieceCount[bQ]++;
            file++;
            break;
        }
        case 'k': {
            pieces[sq] = bK;
            pieceList[bK][pieceCount[bK]] = sq;
            pieceCount[bK]++;
            file++;
            break;
        }
        case 'p': {
            pieces[sq] = bP;
            pieceList[bP][pieceCount[bP]] = sq;
            pieceCount[bP]++;
            ULONG bp = 1ULL << SQ64(sq);
            pawns[BLACK] |= bp;
            pawns[BOTH] |= bp;
            file++;
            break;
        }
        case 'R': {
            pieces[sq] = wR;
            pieceList[wR][pieceCount[wR]] = sq;
            pieceCount[wR]++;
            file++;
            break;
        }
        case 'N': {
            pieces[sq] = wN;
            pieceList[wN][pieceCount[wN]] = sq;
            pieceCount[wN]++;
            file++;
            break;
        }
        case 'B': {
            pieces[sq] = wB;
            pieceList[wB][pieceCount[wB]] = sq;
            pieceCount[wB]++;
            file++;
            break;
        }
        case 'Q': {
            pieces[sq] = wQ;
            pieceList[wQ][pieceCount[wQ]] = sq;
            pieceCount[wQ]++;
            file++;
            break;
        }
        case 'K': {
            pieces[sq] = wK;
            pieceList[wK][pieceCount[wK]] = sq;
            pieceCount[wK]++;
            file++;
            break;
        }
        case 'P': {
            pieces[sq] = wP;
            pieceList[wP][pieceCount[wP]] = sq;
            pieceCount[wP]++;
            ULONG wp = 1ULL << SQ64(sq);
            pawns[WHITE] |= wp;
            pawns[BOTH] |= wp;
            file++;
            break;
        }
        default: {
            file += *c - '0';
            for (int i = 0; i < *c - '0'; i++)
            {
                pieces[sq + i] = EMPTY;
            }
            break;
            }
        }
        c++;
    }
    c++;
    side = (*c == 'w') ? WHITE : BLACK;
    c++;
    c++;
    while (*c != ' ')
    {
        switch (*c)
        {
        case 'K':
            castlePerm |= WKC;
            break;
        case 'Q':
            castlePerm |= WQC;
            break;
        case 'k':
            castlePerm |= BKC;
            break;
        case 'q':
            castlePerm |= BQC;
            break;
        default:
            break;
        }
        c++;
    }
    c++;
    if (*c != '-')
    {
        file = *c - 'a';
        rank = *(c + 1) - '1';
        assert(file >= FILE_A && file <= FILE_H);
        assert(file >= RANK1 && file <= RANK8);
        enPas = FR2SQ(file, rank);
    }
    c++;
    char str[10];
    int i = 0;
    while (*c != ' ')
    {
        assert(i < 10);
        str[i++] = *c;
        c++;
    }
    fiftyMove = util::strToNum(str, i);

    key = generateKey(this);
}

void Board::initHashKeys()
{
    for (int i = 0; i < 13; ++i)
    {
        for (int j = 0; j < 120; ++j)
        {
            pieceKeys[i][j] = util::randomLong();
        }
    }
    sideKey = util::randomLong();
    for (int i = 0; i < 16; ++i)
    {
        castleKeys[i] = util::randomLong();
    }
}

ULONG Board::generateKey(const Board* board)
{
    ULONG finalKey = 0;
    int piece = EMPTY;

    // Key for pieces
    for (int sq = 0; sq < 120; ++sq)
    {
        piece = board->pieces[sq];
        if (piece != EMPTY && piece != OFF_BOARD)
        {
            assert(piece >= wP && piece <= bK);
            finalKey ^= pieceKeys[piece][sq];
        }
    }

    if (board->side == WHITE)
    {
        finalKey ^= sideKey;
    }

    if (board->enPas != NO_SQ)
    {
        assert(board->enPas >= 0 && board->enPas < 120);
        finalKey ^= pieceKeys[EMPTY][board->enPas];
    }

    assert(board->castlePerm >= 0 && board->castlePerm <= 15);

    finalKey ^= castleKeys[board->castlePerm];

    return finalKey;
}

void Board::print()
{
    for (int rank = RANK8; rank >= RANK1; rank--)
    {
        std::cout << std::endl;
        std::cout << rankChar[rank] << " ";
        for (int file = FILE_A; file <= FILE_H; file++)
        {
            int sq = FR2SQ(file, rank);
            int piece = pieces[sq];
            std::cout << std::setw(3) << pieceChar[piece];
        }
        std::cout << std::endl;
    }
    std::cout << std::setw(4) << std::endl;
    for (int file = FILE_A; file <= FILE_H; file++)
    {
        std::cout << ' ' << fileChar[file] << ' ';
    }
    std::cout << std::endl;
}


bool Board::squareAttacked(int sq, int side) {
    // pawns
    if (side == WHITE)
    {
        if (pieces[sq - 11] == wP || pieces[sq - 9] == wP)
        {
            return true;
        }
    }
    else
    {
        if (pieces[sq + 11] == bP || pieces[sq + 9] == bP)
        {
            return true;
        }
    }

    //Knights
    for (int i = 0; i < 8; i++)
    {
        int piece = pieces[sq + knightDir[i]];
        if (piece != OFF_BOARD && pKnight[piece] && pieceCol[piece] == side)
        {
            return true;
        }
    }

    //Rooks Queens
    for (int i = 0; i < 4; ++i)
    {
        int dir = rookDir[i];
        int tempSq = sq + dir;
        int piece = pieces[tempSq];
        while (piece != OFF_BOARD)
        {
            if (piece != EMPTY)
            {
                if (piece != OFF_BOARD && pRookQueen[piece] && pieceCol[piece] == side)
                {
                    return true;
                }
                break;
            }
            tempSq += dir;
            piece = pieces[tempSq];
        }
    }

    // bishops, queens
    for (int i = 0; i < 4; ++i)
    {
        int dir = bishopDir[i];
        int tempSq = sq + dir;
        int piece = pieces[tempSq];
        while (piece != OFF_BOARD)
        {
            if (piece != EMPTY)
            {
                if (piece != OFF_BOARD && pBishopQueen[piece] && pieceCol[piece] == side)
                {
                    return true;
                }
                break;
            }
            tempSq += dir;
            piece = pieces[tempSq];
        }
    }

    // kings
    for (int i = 0; i < 8; ++i)
    {
        int piece = pieces[sq + kingDir[i]];
        if (piece != OFF_BOARD && pKing[piece] && pieceCol[piece] == side)
        {
            return true;
        }
    }

    return false;
}