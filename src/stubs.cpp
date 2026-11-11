/**
 * @file stubs.cpp
 * @brief Implementations and linker stubs for imagehl2.dll.
 *
 * Most functions are PE-forwarded directly to dbghelp.dll or imagehlp.dll via imagehl2.def.
 * The MSVC linker requires matching symbol definitions during export validation.
 * The functions below satisfy the linker; at runtime the forwarded exports point directly
 * to their respective target libraries in Windows.
 */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#if defined(_MSC_VER)
#pragma warning(disable: 4100 4206)
#endif

/* --- Functional stubs for non-forwarded legacy / signature-adjusting exports --- */

BOOL WINAPI CopyPdb(PCSTR SourcePdb, PCSTR TargetPdb, BOOL Replace)
{
    (void)SourcePdb;
    (void)TargetPdb;
    (void)Replace;
    return FALSE;
}

BOOL WINAPI MarkImageAsRunFromSwap(HANDLE FileHandle, DWORD Flags)
{
    (void)FileHandle;
    (void)Flags;
    return FALSE;
}

PVOID WINAPI MapDebugInformation64(HANDLE FileHandle, PCSTR FileName, PCSTR SymbolPath, DWORD64 ImageBase)
{
    typedef PVOID (WINAPI *PFN_MapDebugInfo)(HANDLE, PCSTR, PCSTR, ULONG);
    HMODULE hDbgHelp = GetModuleHandleA("dbghelp.dll");
    if (!hDbgHelp) {
        hDbgHelp = LoadLibraryA("dbghelp.dll");
    }
    if (hDbgHelp) {
        PFN_MapDebugInfo pfn = (PFN_MapDebugInfo)GetProcAddress(hDbgHelp, "MapDebugInformation");
        if (pfn) {
            return pfn(FileHandle, FileName, SymbolPath, (ULONG)ImageBase);
        }
    }
    return NULL;
}

BOOL WINAPI UnmapDebugInformation64(PVOID DebugInfo)
{
    typedef BOOL (WINAPI *PFN_UnmapDebugInfo)(PVOID);
    HMODULE hDbgHelp = GetModuleHandleA("dbghelp.dll");
    if (!hDbgHelp) {
        hDbgHelp = LoadLibraryA("dbghelp.dll");
    }
    if (hDbgHelp) {
        PFN_UnmapDebugInfo pfn = (PFN_UnmapDebugInfo)GetProcAddress(hDbgHelp, "UnmapDebugInformation");
        if (pfn) {
            return pfn(DebugInfo);
        }
    }
    return FALSE;
}

/* --- Linker symbol-resolution stubs for forwarded exports --- */
void BindImage(void) {}
void BindImageEx(void) {}
void CheckSumMappedFile(void) {}
void EnumerateLoadedModules(void) {}
void EnumerateLoadedModules64(void) {}
void FindDebugInfoFile(void) {}
void FindDebugInfoFileEx(void) {}
void FindExecutableImage(void) {}
void GetImageConfigInformation(void) {}
void GetImageUnusedHeaderBytes(void) {}
void GetTimestampForLoadedLibrary(void) {}
void ImageAddCertificate(void) {}
void ImageDirectoryEntryToData(void) {}
void ImageDirectoryEntryToDataEx(void) {}
void ImageEnumerateCertificates(void) {}
void ImageGetCertificateData(void) {}
void ImageGetCertificateHeader(void) {}
void ImageGetDigestStream(void) {}
void ImageLoad(void) {}
void ImageNtHeader(void) {}
void ImageRemoveCertificate(void) {}
void ImageRvaToSection(void) {}
void ImageRvaToVa(void) {}
void ImageUnload(void) {}
void ImagehlpApiVersion(void) {}
void ImagehlpApiVersionEx(void) {}
void MakeSureDirectoryPathExists(void) {}
void MapAndLoad(void) {}
void MapDebugInformation(void) {}
void MapFileAndCheckSumA(void) {}
void MapFileAndCheckSumW(void) {}
void ReBaseImage(void) {}
void RemovePrivateCvSymbolic(void) {}
void RemovePrivateCvSymbolicEx(void) {}
void RemoveRelocations(void) {}
void SearchTreeForFile(void) {}
void SetImageConfigInformation(void) {}
void SplitSymbols(void) {}
void StackWalk(void) {}
void StackWalk64(void) {}
void SymCleanup(void) {}
void SymEnumerateModules(void) {}
void SymEnumerateModules64(void) {}
void SymEnumerateSymbols(void) {}
void SymEnumerateSymbols64(void) {}
void SymFunctionTableAccess(void) {}
void SymFunctionTableAccess64(void) {}
void SymGetLineFromAddr(void) {}
void SymGetLineFromAddr64(void) {}
void SymGetLineFromName(void) {}
void SymGetLineFromName64(void) {}
void SymGetLineNext(void) {}
void SymGetLineNext64(void) {}
void SymGetLinePrev(void) {}
void SymGetLinePrev64(void) {}
void SymGetModuleBase(void) {}
void SymGetModuleBase64(void) {}
void SymGetModuleInfo(void) {}
void SymGetModuleInfo64(void) {}
void SymGetOptions(void) {}
void SymGetSearchPath(void) {}
void SymGetSymFromAddr(void) {}
void SymGetSymFromAddr64(void) {}
void SymGetSymFromName(void) {}
void SymGetSymFromName64(void) {}
void SymGetSymNext(void) {}
void SymGetSymNext64(void) {}
void SymGetSymPrev(void) {}
void SymGetSymPrev64(void) {}
void SymInitialize(void) {}
void SymLoadModule(void) {}
void SymLoadModule64(void) {}
void SymMatchFileName(void) {}
void SymRegisterCallback(void) {}
void SymRegisterCallback64(void) {}
void SymSetOptions(void) {}
void SymSetSearchPath(void) {}
void SymUnDName(void) {}
void SymUnDName64(void) {}
void SymUnloadModule(void) {}
void SymUnloadModule64(void) {}
void TouchFileTimes(void) {}
void UnDecorateSymbolName(void) {}
void UnMapAndLoad(void) {}
void UnmapDebugInformation(void) {}
void UpdateDebugInfoFile(void) {}
void UpdateDebugInfoFileEx(void) {}
