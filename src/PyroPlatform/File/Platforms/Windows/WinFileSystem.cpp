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

#include "WinFileSystem.hpp"
#include <Windows.h>
#include <libassert/assert.hpp>

#include <filesystem>

namespace PyroshockStudios {
    inline namespace Platform {
        eastl::string WinFileSystem::GetWorkingDirectory() {
            DWORD bufferSize = GetCurrentDirectoryA(0, nullptr);
            if (bufferSize == 0) {
                return {};
            }
            eastl::string buffer(bufferSize, '\0');
            DWORD result = GetCurrentDirectoryA(bufferSize, buffer.data());
            if (result == 0 || result >= bufferSize) {
                return {};
            }
            buffer.resize(result);
            return buffer;
        }
        eastl::string WinFileSystem::GetExecutableDirectory() {
            char path[256];
            DWORD size = GetModuleFileNameA(nullptr, path, sizeof(path));
            if (size == 0 || size == sizeof(path))
                return {};
            std::filesystem::path exePath(path);
            return eastl::string(exePath.parent_path().string().c_str());
        }
    }
}
