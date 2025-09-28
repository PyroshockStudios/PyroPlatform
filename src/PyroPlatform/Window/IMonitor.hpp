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

#pragma once
#include <EASTL/string.h>
#include <PyroCommon/Core.hpp>

namespace PyroshockStudios {
    inline namespace Platform {
        struct IWindowManager;

        struct IMonitor {
            IMonitor() = default;

            PYRO_NODISCARD virtual eastl::string GetName() const = 0;
            PYRO_NODISCARD virtual Point GetPosition() const = 0;
            PYRO_NODISCARD virtual Size GetPhysicalSize() const = 0;
            PYRO_NODISCARD virtual Size GetResolution() const = 0;
            PYRO_NODISCARD virtual Size GetWorkArea() const = 0;
            PYRO_NODISCARD virtual FSize GetContentScale() const = 0;
            PYRO_NODISCARD virtual u32 GetRefreshRate() const = 0;

        protected:
            virtual ~IMonitor() = default;
            friend struct IWindowManager;
        };
    } // namespace Platform
} // namespace PyroshockStudios