#pragma once

#include "CommonCRT.h"

namespace Utils
{
    bool IsBadReadPtrEx(void* p);
    DWORD_PTR FindPattern(HMODULE hMod, int startIndex, PBYTE bMask, char* szMask);
};