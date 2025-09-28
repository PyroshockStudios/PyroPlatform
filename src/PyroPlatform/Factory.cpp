// MIT License
//
// Copyright (c) 2025 Pyroshock Studios
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "Factory.hpp"

#ifndef PYRO_PLATFORM_DUMMY_INTERFACE
// FILE
#ifdef PYRO_PLATFORM_FILE

#ifdef PYRO_PLATFORM_WINDOWS
#include <PyroPlatform/File/Platforms/Windows/WinFileSystem.hpp>
#include <PyroPlatform/File/Platforms/Windows/WinLibraryLoader.hpp>

#define LibraryLoader WinLibraryLoader
#define FileSystem WinFileSystem

#endif


#ifdef PYRO_PLATFORM_LINUX
#include <PyroPlatform/File/Platforms/Linux/LinuxFileSystem.hpp>

#define FileSystem LinuxFileSystem

#endif


#ifdef PYRO_PLATFORM_MACOS
#include <PyroPlatform/File/Platforms/Macos/MacFileSystem.hpp>

#define FileSystem MacFileSystem

#endif


#ifdef PYRO_PLATFORM_FAMILY_UNIX
#include <PyroPlatform/File/Platforms/Unix/UnixLibraryLoader.hpp>

#define LibraryLoader UnixLibraryLoader

#endif

#ifndef FileSystem
#error IFileSystem not implemented!
#endif
#ifndef LibraryLoader
#error ILibraryLoader not implemented!
#endif

#endif

// TIME
#ifdef PYRO_PLATFORM_TIME

#ifdef PYRO_PLATFORM_WINDOWS
#include <PyroPlatform/Time/Platforms/Windows/WinClock.hpp>

#define Clock WinClock

#endif

#ifdef PYRO_PLATFORM_FAMILY_UNIX
#include <PyroPlatform/Time/Platforms/Unix/UnixClock.hpp>

#define Clock UnixClock

#endif

#ifndef Clock
#error IClock not implemented!
#endif
#endif


// WINDOWING
#ifdef PYRO_PLATFORM_WINDOWING
#ifdef PYRO_PLATFORM_WINDOWING_GLFW
#include <PyroPlatform/Window/Platforms/Glfw/GlfwWindowManager.hpp>
#define WindowManager GlfwWindowManager
#endif

#ifndef WindowManager
#error IWindowManager not implemented!
#endif
#endif

#endif

namespace PyroshockStudios {
    inline namespace Platform {
#ifdef PYRO_PLATFORM_FILE
#ifndef PYRO_PLATFORM_DUMMY_INTERFACE
        static FileSystem gFileSystem;
        static LibraryLoader gLibraryLoader;
        template <>
        PYRO_PLATFORM_API IFileSystem* PlatformFactory::Get<IFileSystem>() {
            return &gFileSystem;
        }
        template <>
        PYRO_PLATFORM_API ILibraryLoader* PlatformFactory::Get<ILibraryLoader>() {
            return &gLibraryLoader;
        }
#else
        template <>
        PYRO_PLATFORM_API IFileSystem* PlatformFactory::Get<IFileSystem>() {
            return nullptr;
        }
        template <>
        PYRO_PLATFORM_API ILibraryLoader* PlatformFactory::Get<ILibraryLoader>() {
            return nullptr;
        }
#endif
#endif

#ifdef PYRO_PLATFORM_TIME
#ifndef PYRO_PLATFORM_DUMMY_INTERFACE
        static Clock gClock;
        template <>
        PYRO_PLATFORM_API IClock* PlatformFactory::Get<IClock>() {
            return &gClock;
        }
#else
        template <>
        PYRO_PLATFORM_API IClock* PlatformFactory::Get<IClock>() {
            return nullptr;
        }
#endif
#endif

#ifdef PYRO_PLATFORM_WINDOWING
#ifndef PYRO_PLATFORM_DUMMY_INTERFACE
        static WindowManager gWindowManager;
        template <>
        PYRO_PLATFORM_API IWindowManager* PlatformFactory::Get<IWindowManager>() {
            return &gWindowManager;
        }
#else
        template <>
        PYRO_PLATFORM_API IWindowManager* PlatformFactory::Get<IWindowManager>() {
            return nullptr;
        }
#endif
#endif

    }; // namespace Platform
} // namespace PyroshockStudios