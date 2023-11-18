#include "Utils.h"

namespace Utils
{
    static UINT32 mempage_mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);

    bool IsBadReadPtrEx(void* p)
    {
        MEMORY_BASIC_INFORMATION mbi = { 0 };
        if (::VirtualQuery(p, &mbi, sizeof(mbi)))
        {
            bool b = !(mbi.Protect & mempage_mask);
            // check the page is not a guard page
            if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) b = true;
            return b;
        }
        return true; //Unable to Query
    }

    bool DataCompare(PBYTE pData, PBYTE bMask, char* szMask) {

        for (; *szMask; szMask++, pData++, bMask++) {
            if (*szMask == 'x' && *pData != *bMask)
                return false;
        }
        return (*szMask) == NULL;
    }

    DWORD_PTR FindPattern(HMODULE hMod, int startIndex, PBYTE bMask, char* szMask) {

        MODULEINFO info;
        ZeroMemory(&info, sizeof(MODULEINFO));

        if (!GetModuleInformation(GetCurrentProcess(), hMod, &info, sizeof(MODULEINFO)))
            return 0;

        printf("Module Info - Entrypoint: 0x%x \n", info.EntryPoint);
        printf("Module Info - lpBaseOfDll: 0x%x \n", info.lpBaseOfDll);
        printf("Module Info - SizeOfImage: 0x%x \n", info.SizeOfImage);

        DWORD i = startIndex;
        for (i; i < info.SizeOfImage; i++) {
            if (DataCompare((PBYTE)((DWORD_PTR)info.lpBaseOfDll + i), bMask, szMask))
                return (DWORD_PTR)((DWORD_PTR)info.lpBaseOfDll + i);
        }

        return 0;
    }

};