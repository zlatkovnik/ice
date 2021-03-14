#pragma once
#include "defines.h"

static class util
{
public:
	static ULONG setMask[64];
	static ULONG clearMask[64];
	static const int bitTable[];

	static void initBitMasks();

	static int strToNum(const char* str, int count);
	static ULONG randomLong();
	static int countBits(ULONG b);
	static int popBit(ULONG* bb);
};

