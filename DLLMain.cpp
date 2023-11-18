#pragma warning( disable : 6031 )
#include "DLLMain.h"


using namespace std;
using namespace Utils;

// Function pointers for the original functions
using LoadLibraryWType = HMODULE(WINAPI*)(LPCWSTR);
LoadLibraryWType OriginalLoadLibraryW = nullptr;


void PatchCohtmlUnity3dPlugin(HMODULE hCohtml_Unity3DPlugin) {

    printf("Patching module 0x%x \n", hCohtml_Unity3DPlugin);

    DWORD patchAddress = (FindPattern(hCohtml_Unity3DPlugin, 0, (byte*)"\xCC\x40\xFF\x48\xFF\xFF\xFF\x80\xFF\xFF\xFF\x48\xFF\xFF\x0F\x84", "xx?x???x???x??xx") + 15);

    printf("PatchAddress {%x}", patchAddress);

    if (patchAddress) {
        DWORD oldProtect;
        VirtualProtect(reinterpret_cast<LPVOID>(patchAddress), 1, PAGE_EXECUTE_READWRITE, &oldProtect);

        *reinterpret_cast<BYTE*>(patchAddress) = 0x85;

        VirtualProtect(reinterpret_cast<LPVOID>(patchAddress), 1, oldProtect, &oldProtect);

        printf("Sucessfully patched! \n");

    }
    else {
        MessageBoxW(nullptr, L"Could not find patch address - please check https://github.com/manolz1/cities2-gptk-fix for an updated version", L"Error", MB_OK | MB_ICONINFORMATION);
    }
}

HMODULE WINAPI DetourLoadLibraryW(LPCWSTR lpLibFileName) {

    if (wcscmp(lpLibFileName, L"cohtml_Unity3DPlugin.dll") == 0) {

        HMODULE hCohtml_Unity3DPlugin = OriginalLoadLibraryW(lpLibFileName);

        PatchCohtmlUnity3dPlugin(hCohtml_Unity3DPlugin);

        return hCohtml_Unity3DPlugin;
    }

    return OriginalLoadLibraryW(lpLibFileName);
}

bool SetupVersionDllProxy() {

    wstring originalVersionDll = L"version_orig.dll";
    wstring copyFromPath = L"C:\\windows\\system32\\version.dll";

    // Check if "version_orig.dll" exists in the current directory
    if (GetFileAttributes(originalVersionDll.c_str()) == INVALID_FILE_ATTRIBUTES) {
        printf("version_orig.dll does not exist in the current directory \n");

        // Copy "version.dll" from "C:\windows\system32\" to the current directory
        if (CopyFile(copyFromPath.c_str(), originalVersionDll.c_str(), FALSE)) {
            printf("version_orig.dll has been created from version.dll in the windows folder \n");

            // Get the current executable path
            wchar_t buffer[MAX_PATH];
            GetModuleFileName(NULL, buffer, MAX_PATH);

            // Create a new process to restart the application
            STARTUPINFO si = { sizeof(STARTUPINFO) };
            PROCESS_INFORMATION pi;

            printf("Restarting the game so that we can load version_orig.dll correctly \n");

            // the new process will still crash at this point
            // as I believe it's not spawned correctly and won't find version.dll as a native dll
            // I believe it falls back to the wine built in DLL but not sure of a fix
            if (CreateProcess(NULL, buffer, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {

                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);
                TerminateProcess(GetCurrentProcess(), 0);
            }
            else {
                printf("Error restarting the game! \n");
            }

        }
        else {
            printf("Error copying version_orig.dll \n");
            return false;
        }
    }
    else {
        printf("version_orig.dll exists \n");
    }

    return true;
}

BOOL WINAPI DllMain(HMODULE hModule,
                    DWORD  ul_reason_for_call,
                    LPVOID lpReserved
                   )
{

    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        {
            DisableThreadLibraryCalls(hModule);
#ifdef DEBUG
            AllocConsole();
            SetConsoleTitleW(L"Cities Skylines II - GPTK Support Patch");
            freopen("CONOUT$", "w", stdout);
            freopen("CONOUT$", "w", stderr);
            printf("Cities Skylines II - GPTK Support Patch Loaded! \n");
#endif

            bool success = SetupVersionDllProxy();

            if (!success) {
                return TRUE;
            }

             // Initialize Detours
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            OriginalLoadLibraryW = LoadLibraryW;
            DetourAttach(reinterpret_cast<PVOID*>(&OriginalLoadLibraryW), DetourLoadLibraryW);
            DetourTransactionCommit();
            
            break;
        }
        case DLL_PROCESS_DETACH:
        {
            // Remove the detours
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourDetach(reinterpret_cast<PVOID*>(&OriginalLoadLibraryW), DetourLoadLibraryW);
            DetourTransactionCommit();
            
            printf("Version.dll proxy unloaded! \n");
#ifdef DEBUG
            FreeConsole();
#endif
            break;
        }
    }

    return TRUE;
}