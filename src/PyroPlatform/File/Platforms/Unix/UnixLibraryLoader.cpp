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

#include "UnixLibraryLoader.hpp"
#include <PyroPlatform/File/Platforms/Unix/UnixDynamicLibrary.hpp>
#include <dlfcn.h>

#include <libassert/assert.hpp>

namespace PyroshockStudios {
    inline namespace Platform {
        IDynamicLibrary* UnixLibraryLoader::Load(Path libraryPath) {
            void* handle = dlopen(libraryPath.c_str(), RTLD_LAZY | RTLD_LOCAL);
            if (!handle) {
                return nullptr;
            }
            return new UnixDynamicLibrary(handle);
        }

        bool UnixLibraryLoader::Unload(IDynamicLibrary*& library) {
            if (!library)
                return false;

            auto* unixLib = dynamic_cast<UnixDynamicLibrary*>(library);
            ASSERT(unixLib != nullptr && "Type must be of UnixDynamicLibrary!");
            if (!unixLib)
                return false;

            delete unixLib;
            library = nullptr;
            return true;
        }
    } // namespace Platform
} // namespace PyroshockStudios
