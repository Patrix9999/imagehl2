# imagehl2 - Proxy Library imagehlp.dll -> dbghelp.dll

`imagehl2.dll` is a lightweight, zero-overhead 32-bit (x86) library proxy designed as a reimplementation and drop-in replacement for the original `imagehlp.dll` / `imagehl2.dll` (notably utilized by the *Gothic* and *Gothic II* game engines).

Instead of maintaining a legacy Microsoft binary, this reimplementation maps all 112 exported functions and original ordinals (1 to 112) directly to Windows' native `dbghelp.dll` and `imagehlp.dll` using native PE export forwarders and minimal compatibility stubs.

---

## Features

- **Zero Runtime Overhead**: Uses PE export forwarders (`dbghelp.<func>` / `imagehlp.<func>`), eliminating CPU instructions, stack adjustments, or calling convention mismatches (`__stdcall` vs `__cdecl`).
- **100% Export Compatibility**: Maps all 112 functions and original ordinals (from 1 to 112) identical to the original library (`IMAGEHL2.DLL`).
- **Ultra Lightweight**: Small binary footprint (~20 KB) with zero memory overhead.
- **Targeted Architecture**: Dedicated 32-bit (`x86`/`Win32`) configuration via CMake presets matching target applications.
- **Full Test Suite Included**: Validates exported symbol resolution across all 112 functions by name and ordinal, and tests live API calls (`ImagehlpApiVersion`, `ImageNtHeader`, `SymInitialize`, `SymCleanup`, `MakeSureDirectoryPathExists`, etc.).

## Motivation

This project was created to properly display callstack crashes in *Gothic Games*, currently they are using the old `imagehlp.dll` library interface utilized by `BugSlayerUtil.dll`.

The problem is that new compiled libraries have different debug symbols than `VC 6.0` built binaries (like native game executable), and they aren't displayed in the callstack.

To fix this problem, i've created a proxy library that utilized `dbghelp.dll` (newer revision of debug library) that is able to interpret old & new debug symbols correctly. 

---

## Building

Building requires **CMake 3.20+** and **Visual Studio 2022+** with C/C++ development tools.

### Using CMake Presets

To list available presets:
```cmd
cmake --list-presets
```

#### Build x86 Release:
```cmd
cmake --preset msvc-x86-release
cmake --build --preset msvc-x86-release
```

#### Build x86 Debug:
```cmd
cmake --preset msvc-x86-debug
cmake --build --preset msvc-x86-debug
```

#### Run the Test Suite:
```cmd
ctest --preset msvc-x86-release --output-on-failure
```

---

## License

[MIT License](./LICENSE.md).
