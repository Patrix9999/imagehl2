/**
 * @file dllmain.cpp
 * @brief DllMain entry point for imagehl2.dll proxy library.
 *
 * imagehl2.dll is a drop-in proxy replacement for the original imagehlp.dll / imagehl2.dll
 * used by applications (such as the Gothic and Gothic II game engines) to forward all
 * debugging, symbol, and PE image helper calls directly to dbghelp.dll.
 */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    (void)lpReserved;

    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        /* Optimize thread creation performance by disabling thread library calls */
        DisableThreadLibraryCalls(hinstDLL);
        break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}
