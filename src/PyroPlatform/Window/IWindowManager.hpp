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

#include <EASTL/span.h>
#include <PyroCommon/Types.hpp>
#include <PyroPlatform/Window/ICursor.hpp>
#include <PyroPlatform/Window/IMonitor.hpp>
#include <PyroPlatform/Window/IWindow.hpp>
#include <PyroPlatform/Window/Input/Types.hpp>

namespace PyroshockStudios {
    inline namespace Platform {
        enum struct KeySource {
            Physical, // Layout-independent
            Logical   // Layout-dependent (after translation)
        };

        struct IWindowManager {
            IWindowManager() = default;
            virtual bool Init() = 0;
            virtual bool Terminate() = 0;

            virtual void PollEvents() = 0;
            virtual void WaitEvents() = 0;

            PYRO_NODISCARD virtual bool HasClipboardText() = 0;
            PYRO_NODISCARD virtual eastl::string GetClipboardText() = 0;
            virtual void SetClipboardText(eastl::string_view text) = 0;

            virtual eastl::span<IMonitor*> GetMonitors() = 0;
            virtual IMonitor* GetPrimaryMonitor() = 0;

            PYRO_NODISCARD virtual IWindow* CreateWindow(const WindowInfo& info) = 0;
            virtual void DestroyWindow(IWindow*& window) = 0;

            PYRO_NODISCARD virtual ICursor* CreateCursor(CursorType type) = 0;
            // PYRO_NODISCARD virtual ICursor* CreateCursorFromImage(const ImageDesc& img) = 0;
            virtual void DestroyCursor(ICursor*& cursor) = 0;

            PYRO_NODISCARD virtual KeyCode TranslateKey(i32 key, i32 scancode, KeySource source) = 0;
        };
    } // namespace Platform
} // namespace PyroshockStudios