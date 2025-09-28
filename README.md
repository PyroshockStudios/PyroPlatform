[![CMake on multiple platforms](https://github.com/PyroshockStudios/ShockwaveEngine/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/PyroshockStudios/ShockwaveEngine/actions/workflows/cmake-multi-platform.yml)

## Shockwave Engine (PyroshockStudios © 2025)

### What is Shockwave Engine?
**Shockwave Engine** is a 22nd Century game engine, it aims to reach performance gains beyond what was thought to be possible, with a modular RHI abstraction (any API can be implemented!), use of modern c++ (C++23), SIMD intrinsics, and low overhead.
It's also designed around scalability and testability, to ensure the engine is as robust as possible.

## Programming Conventions:
clang-format is used for the indentations, include order, etc.
**P**ascal**C**ase is used for function names, and classes.
Enums must be declared as `enum struct`, and members be named as PascalCase.
Flags are an exception. They must be declared with the `Flags<>` template in Common/Core.hpp and be named TypeFlags, TypeFlagBits, TypeFlagsPropeties, and their members are named as UPPER_SNAKE_CASE
For numbers, this is an exception, and a prefix of `e` or `E` can be used.
We use some sort of Hungarian notation for variables:
- gGlobalVariable (any globally (static) accessible variables)
- mMemberName (any variables accessable within a class)
- kConstant (this includes constant members, constant global variables)
- bBoolean

Interfaces (abstract classes with no implementations) must be prefixed with `I` e.g. `IProgrammable`, and must be declared as _structs_. Remember to set a default destructor and constructor!
Everything else uses **c**amel**C**ase

Notes:
- Forward declare whenever possible
- Structs (and ONLY structs!) used as parameter arguments, do not adhere to the aforementioned naming conventions (Except for booleans, they should still be named bBoolean).

## Building
**Shockwave Engine** uses the cmake build system, setup is like usual.
There are certain build options, such as building tests, building RHI backends (currently only D3D12 and Vulkan work), building windowing systems (currently only GLFW works).
Aside from the automated build pipelines, building has been tested and verified on these platforms:
- **Visual Studio 2022 MSVCv143** on Windows 10 21H2 and 22H2
- **Clang++ (MSVC ABI)** on Windows 11
- **GCC 15.2** on Ubuntu 22 LTS
> Note: MinGW will NOT be supported, as certain libraries (such as EASTL) do not support these build tools. Support for the MSVC ABI is much larger for windows builds.
