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

#include "LinuxFileSystem.hpp"
#include <limits.h>
#include <unistd.h>

#include <libassert/assert.hpp>

#include <filesystem>

namespace PyroshockStudios {
    inline namespace Platform {
        eastl::string LinuxFileSystem::GetWorkingDirectory() {
            char buffer[PATH_MAX];
            if (getcwd(buffer, sizeof(buffer)) == nullptr) {
                return {};
            }
            return eastl::string(buffer);
        }
        eastl::string LinuxFileSystem::GetExecutableDirectory() {
            char path[1024];
            isize size = readlink("/proc/self/exe", path, sizeof(path) - 1);
            ASSERT(size >= 0, "Failed too read path!");
            path[size] = '\0';
            std::filesystem::path exePath = std::filesystem::path(std::string(path));
            return eastl::string(exePath.parent_path().string().c_str());
        }
    } // namespace Platform

} // namespace PyroshockStudios
