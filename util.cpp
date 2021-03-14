#include "util.h"
#include "stdlib.h"


const int util::bitTable[] = {
            63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
            51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
            26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
            58, 20, 37, 17, 36, 8
};

void util::initBitMasks()
{
    for (int i = 0; i < 64; i++)
    {
        setMask[i] = 0ULL;
        clearMask[i] = 0ULL;
    }

    for (int i = 0; i < 64; i++)
    {
        setMask[i] |= (1ULL << i);
        clearMask[i] = ~setMask[i];
    }
}

int util::strToNum(const char* str, int count)
{
    int num = 0;
    int exp = 1;
    for (int i = count - 1; i >= 0; i--)
    {
        num += exp * (int)(str[i] - '0');
        exp *= 10;
    }
    return num;
}

ULONG util::randomLong()
{
    ULONG rand1 = (ULONG)rand();
    ULONG rand2 = (ULONG)rand();
    rand1 = rand1 << (sizeof(int) * 8);
    return (rand1 | rand2);
}

int util::countBits(ULONG b)
{
    int r;
    for (r = 0; b != 0; r++, b &= b - 1);
    return r;
}

int util::popBit(ULONG* bb)
{
    ULONG b = *bb ^ (*bb - 1);
    unsigned int fold = (unsigned int)((b & 0xffffffff) ^ (b >> 32));
    *bb &= *bb - 1;
    return bitTable[(fold * 0x783a9b23) >> 26];
}
