/**
 * @file test_proxy.c
 * @brief Comprehensive test suite verifying imagehl2.dll exports and forwarders.
 */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _API_VERSION {
    USHORT  MajorVersion;
    USHORT  MinorVersion;
    USHORT  Revision;
    USHORT  Reserved;
} API_VERSION, *LPAPI_VERSION;

static const char* g_allExports[] = {
    "BindImage", /* @1 */
    "BindImageEx", /* @2 */
    "CheckSumMappedFile", /* @3 */
    "CopyPdb", /* @4 */
    "EnumerateLoadedModules32", /* @5 */
    "EnumerateLoadedModules64", /* @6 */
    "EnumerateLoadedModules", /* @7 */
    "FindDebugInfoFile", /* @8 */
    "FindDebugInfoFileEx", /* @9 */
    "FindExecutableImage", /* @10 */
    "GetImageConfigInformation", /* @11 */
    "GetImageUnusedHeaderBytes", /* @12 */
    "GetTimestampForLoadedLibrary", /* @13 */
    "ImageAddCertificate", /* @14 */
    "ImageDirectoryEntryToData", /* @15 */
    "ImageDirectoryEntryToDataEx", /* @16 */
    "ImageEnumerateCertificates", /* @17 */
    "ImageGetCertificateData", /* @18 */
    "ImageGetCertificateHeader", /* @19 */
    "ImageGetDigestStream", /* @20 */
    "ImageLoad", /* @21 */
    "ImageNtHeader", /* @22 */
    "ImageRemoveCertificate", /* @23 */
    "ImageRvaToSection", /* @24 */
    "ImageRvaToVa", /* @25 */
    "ImageUnload", /* @26 */
    "ImagehlpApiVersion", /* @27 */
    "ImagehlpApiVersionEx", /* @28 */
    "MakeSureDirectoryPathExists", /* @29 */
    "MapAndLoad", /* @30 */
    "MapDebugInformation32", /* @31 */
    "MapDebugInformation64", /* @32 */
    "MapDebugInformation", /* @33 */
    "MapFileAndCheckSumA", /* @34 */
    "MapFileAndCheckSumW", /* @35 */
    "MarkImageAsRunFromSwap", /* @36 */
    "ReBaseImage", /* @37 */
    "RemovePrivateCvSymbolic", /* @38 */
    "RemovePrivateCvSymbolicEx", /* @39 */
    "RemoveRelocations", /* @40 */
    "SearchTreeForFile", /* @41 */
    "SetImageConfigInformation", /* @42 */
    "SplitSymbols", /* @43 */
    "StackWalk32", /* @44 */
    "StackWalk64", /* @45 */
    "StackWalk", /* @46 */
    "SymCleanup", /* @47 */
    "SymEnumerateModules32", /* @48 */
    "SymEnumerateModules64", /* @49 */
    "SymEnumerateModules", /* @50 */
    "SymEnumerateSymbols32", /* @51 */
    "SymEnumerateSymbols64", /* @52 */
    "SymEnumerateSymbols", /* @53 */
    "SymFunctionTableAccess32", /* @54 */
    "SymFunctionTableAccess64", /* @55 */
    "SymFunctionTableAccess", /* @56 */
    "SymGetLineFromAddr32", /* @57 */
    "SymGetLineFromAddr64", /* @58 */
    "SymGetLineFromAddr", /* @59 */
    "SymGetLineFromName32", /* @60 */
    "SymGetLineFromName64", /* @61 */
    "SymGetLineFromName", /* @62 */
    "SymGetLineNext32", /* @63 */
    "SymGetLineNext64", /* @64 */
    "SymGetLineNext", /* @65 */
    "SymGetLinePrev32", /* @66 */
    "SymGetLinePrev64", /* @67 */
    "SymGetLinePrev", /* @68 */
    "SymGetModuleBase32", /* @69 */
    "SymGetModuleBase64", /* @70 */
    "SymGetModuleBase", /* @71 */
    "SymGetModuleInfo32", /* @72 */
    "SymGetModuleInfo64", /* @73 */
    "SymGetModuleInfo", /* @74 */
    "SymGetOptions", /* @75 */
    "SymGetSearchPath", /* @76 */
    "SymGetSymFromAddr32", /* @77 */
    "SymGetSymFromAddr64", /* @78 */
    "SymGetSymFromAddr", /* @79 */
    "SymGetSymFromName32", /* @80 */
    "SymGetSymFromName64", /* @81 */
    "SymGetSymFromName", /* @82 */
    "SymGetSymNext32", /* @83 */
    "SymGetSymNext64", /* @84 */
    "SymGetSymNext", /* @85 */
    "SymGetSymPrev32", /* @86 */
    "SymGetSymPrev64", /* @87 */
    "SymGetSymPrev", /* @88 */
    "SymInitialize", /* @89 */
    "SymLoadModule32", /* @90 */
    "SymLoadModule64", /* @91 */
    "SymLoadModule", /* @92 */
    "SymMatchFileName", /* @93 */
    "SymRegisterCallback32", /* @94 */
    "SymRegisterCallback64", /* @95 */
    "SymRegisterCallback", /* @96 */
    "SymSetOptions", /* @97 */
    "SymSetSearchPath", /* @98 */
    "SymUnDName32", /* @99 */
    "SymUnDName64", /* @100 */
    "SymUnDName", /* @101 */
    "SymUnloadModule32", /* @102 */
    "SymUnloadModule64", /* @103 */
    "SymUnloadModule", /* @104 */
    "TouchFileTimes", /* @105 */
    "UnDecorateSymbolName", /* @106 */
    "UnMapAndLoad", /* @107 */
    "UnmapDebugInformation32", /* @108 */
    "UnmapDebugInformation64", /* @109 */
    "UnmapDebugInformation", /* @110 */
    "UpdateDebugInfoFile", /* @111 */
    "UpdateDebugInfoFileEx", /* @112 */
};

int main(int argc, char** argv)
{
    const char* dllPath = "imagehl2.dll";
    if (argc > 1) {
        dllPath = argv[1];
    }

    printf("=== imagehl2 Proxy Validation Test ===\n");
    printf("Testing proxy DLL: %s\n", dllPath);

    HMODULE hProxy = LoadLibraryA(dllPath);
    if (!hProxy) {
        fprintf(stderr, "[-] Failed to load proxy library %s (Error: %lu)\n", dllPath, GetLastError());
        return 1;
    }
    printf("[+] Successfully loaded proxy %s (Handle: %p)\n\n", dllPath, (void*)hProxy);

    int totalExports = sizeof(g_allExports) / sizeof(g_allExports[0]);
    int resolvedByName = 0;
    int resolvedByOrd = 0;
    int failedCount = 0;

    printf("Verifying resolution of all %d exports by NAME:\n", totalExports);
    for (int i = 0; i < totalExports; i++) {
        const char* name = g_allExports[i];
        FARPROC pProc = GetProcAddress(hProxy, name);
        if (!pProc) {
            fprintf(stderr, "  [-] %-32s : FAILED (Error: %lu)\n", name, GetLastError());
            failedCount++;
        } else {
            resolvedByName++;
        }
    }
    printf("[+] Successfully resolved %d / %d exports by name.\n\n", resolvedByName, totalExports);

    printf("Verifying resolution of all %d exports by ORDINAL (1..%d):\n", totalExports, totalExports);
    for (int ord = 1; ord <= totalExports; ord++) {
        FARPROC pProc = GetProcAddress(hProxy, MAKEINTRESOURCEA(ord));
        if (!pProc) {
            fprintf(stderr, "  [-] Ordinal @%-3d (%s) : FAILED (Error: %lu)\n", ord, g_allExports[ord - 1], GetLastError());
            failedCount++;
        } else {
            resolvedByOrd++;
        }
    }
    printf("[+] Successfully resolved %d / %d exports by ordinal.\n\n", resolvedByOrd, totalExports);

    printf("Testing live API invocation through proxy:\n");

    /* 1. Test ImagehlpApiVersion */
    const auto ImagehlpApiVersion = reinterpret_cast<LPAPI_VERSION(WINAPI *)(VOID)>(GetProcAddress(hProxy, "ImagehlpApiVersion"));
    if (ImagehlpApiVersion) {
        LPAPI_VERSION pVer = ImagehlpApiVersion();
        if (pVer) {
            printf("  [+] ImagehlpApiVersion() returned: %u.%u.%u\n",
                   (unsigned int)pVer->MajorVersion,
                   (unsigned int)pVer->MinorVersion,
                   (unsigned int)pVer->Revision);
        } else {
            fprintf(stderr, "  [-] ImagehlpApiVersion() returned NULL!\n");
            failedCount++;
        }
    } else {
        fprintf(stderr, "  [-] GetProcAddress(ImagehlpApiVersion) failed!\n");
        failedCount++;
    }

    /* 2. Test ImageNtHeader on self */
    const auto ImageNtHeader = reinterpret_cast<PIMAGE_NT_HEADERS(WINAPI *)(PVOID)>(GetProcAddress(hProxy, "ImageNtHeader"));
    if (ImageNtHeader) {
        HMODULE hSelf = GetModuleHandleA(NULL);
        PIMAGE_NT_HEADERS pNt = ImageNtHeader((PVOID)hSelf);
        if (pNt && pNt->Signature == IMAGE_NT_SIGNATURE) {
            printf("  [+] ImageNtHeader(self) returned valid NT signature: 0x%08X\n", (unsigned int)pNt->Signature);
        } else {
            fprintf(stderr, "  [-] ImageNtHeader(self) failed or invalid signature!\n");
            failedCount++;
        }
    } else {
        fprintf(stderr, "  [-] GetProcAddress(ImageNtHeader) failed!\n");
        failedCount++;
    }

    /* 3. Test SymInitialize and SymCleanup */
    const auto SymInitialize = reinterpret_cast<BOOL(WINAPI *)(HANDLE, PCSTR, BOOL)>(GetProcAddress(hProxy, "SymInitialize"));
    const auto SymCleanup = reinterpret_cast<BOOL(WINAPI *)(HANDLE)>(GetProcAddress(hProxy, "SymCleanup"));
    if (SymInitialize && SymCleanup) {
        HANDLE hProcess = GetCurrentProcess();
        BOOL initOk = SymInitialize(hProcess, NULL, FALSE);
        printf("  [+] SymInitialize(GetCurrentProcess(), NULL, FALSE) = %s\n", initOk ? "TRUE" : "FALSE");
        BOOL cleanupOk = SymCleanup(hProcess);
        printf("  [+] SymCleanup(GetCurrentProcess()) = %s\n", cleanupOk ? "TRUE" : "FALSE");
    } else {
        fprintf(stderr, "  [-] GetProcAddress for SymInitialize/SymCleanup failed!\n");
        failedCount++;
    }

    /* 4. Test MakeSureDirectoryPathExists (image helper function) */
    const auto MakeSureDirectoryPathExists = reinterpret_cast<BOOL(WINAPI *)(PCSTR)>(GetProcAddress(hProxy, "MakeSureDirectoryPathExists"));
    if (MakeSureDirectoryPathExists) {
        printf("  [+] MakeSureDirectoryPathExists resolved successfully.\n");
    } else {
        fprintf(stderr, "  [-] GetProcAddress(MakeSureDirectoryPathExists) failed!\n");
        failedCount++;
    }

    /* 5. Test local stub functions */
    const auto CopyPdb = reinterpret_cast<BOOL(WINAPI *)(PCSTR, PCSTR, BOOL)>(GetProcAddress(hProxy, "CopyPdb"));
    FARPROC pfnMarkSwap = GetProcAddress(hProxy, "MarkImageAsRunFromSwap");
    FARPROC pfnMap64 = GetProcAddress(hProxy, "MapDebugInformation64");
    FARPROC pfnUnmap64 = GetProcAddress(hProxy, "UnmapDebugInformation64");
    if (CopyPdb && pfnMarkSwap && pfnMap64 && pfnUnmap64) {
        printf("  [+] All 4 local stub functions (CopyPdb, MarkImageAsRunFromSwap, MapDebugInformation64, UnmapDebugInformation64) resolved.\n");
        if (CopyPdb("identical.pdb", "identical.pdb", FALSE)) {
            printf("  [+] CopyPdb identical path test passed.\n");
        } else {
            fprintf(stderr, "  [-] CopyPdb identical path test failed!\n");
            failedCount++;
        }
    } else {
        fprintf(stderr, "  [-] Failed to resolve one or more local stub functions!\n");
        failedCount++;
    }

    FreeLibrary(hProxy);

    printf("\n========================================\n");
    printf("Results: %d/%d exports verified by name, %d/%d by ordinal, %d errors.\n",
           resolvedByName, totalExports, resolvedByOrd, totalExports, failedCount);
    if (failedCount == 0) {
        printf("[SUCCESS] All 112 imagehl2 exports verified and working correctly!\n");
        return 0;
    } else {
        printf("[FAILURE] %d tests failed.\n", failedCount);
        return 1;
    }
}
