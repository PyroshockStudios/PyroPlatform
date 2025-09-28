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
        struct IWindowInput;
        struct ICursor;
        struct IMonitor;

        enum struct WindowState : i32 {
            Normal,
            Minimized,
            Maximized
        };

        enum struct CursorMode : i32 {
            Normal, // Cursor visible, free
            Hidden, // Cursor hidden, free
            Locked  // Cursor locked to window (disabled)
        };

        struct WindowCreateFlagsProperties {
            using Data = u32;
        };
        using WindowCreateFlags = Flags<WindowCreateFlagsProperties>;
        struct WindowCreateBits {
            static constexpr inline WindowCreateFlags NONE = { 0x00000000 };
            static constexpr inline WindowCreateFlags RESIZABLE = { 0x00000001 };
            static constexpr inline WindowCreateFlags DECORATED = { 0x00000002 };
            static constexpr inline WindowCreateFlags VISIBLE = { 0x00000004 };
            static constexpr inline WindowCreateFlags FOCUSED = { 0x00000008 };
            static constexpr inline WindowCreateFlags PASSTHROUGH = { 0x00000010 };
            static constexpr inline WindowCreateFlags TOP_MOST = { 0x00000020 };
            static constexpr inline WindowCreateFlags HIGH_DPI = { 0x00000040 };

            static constexpr inline WindowCreateFlags DEFAULT =
                RESIZABLE | DECORATED | VISIBLE | FOCUSED;
        };

        struct WindowInfo {
            u32 width = 0;
            u32 height = 0;
            eastl::string title = "";
            WindowState initialState = WindowState::Normal;
            WindowCreateFlags flags = WindowCreateBits::DEFAULT;
        };

        struct IWindow {
            IWindow() = default;

            PYRO_NODISCARD virtual Size GetSize() const = 0;
            PYRO_NODISCARD virtual Point GetPosition() const = 0;
            PYRO_NODISCARD virtual Point GetCursorPosition() const = 0;
            PYRO_NODISCARD virtual f32 GetOpacity() const = 0;

            virtual void SetSize(Size size) = 0;
            virtual void SetPosition(Point point) = 0;
            virtual void SetCursorPosition(Point point) = 0;
            virtual void SetCursorVisible(bool bVisible) = 0;
            virtual void SetCursorLockedToWindow(bool bLocked) = 0;
            virtual void SetOpacity(f32 opacity) = 0;

            virtual void SetCursor(ICursor* cursor) = 0;

            // if monitor is set to nullptr, then fullscreen is exited
            virtual void SetFullscreen(IMonitor* monitor) = 0;

            virtual void SetWindowState(WindowState state) = 0;
            PYRO_NODISCARD virtual WindowState GetWindowState() const = 0;

            PYRO_FORCEINLINE void Minimize() { SetWindowState(WindowState::Minimized); }
            PYRO_FORCEINLINE void Maximize() { SetWindowState(WindowState::Maximized); }
            PYRO_FORCEINLINE void Restore() { SetWindowState(WindowState::Normal); }

            PYRO_NODISCARD PYRO_FORCEINLINE bool IsMinimized() const { return GetWindowState() == WindowState::Minimized; }
            PYRO_NODISCARD PYRO_FORCEINLINE bool IsMaximized() const { return GetWindowState() == WindowState::Maximized; }

            PYRO_NODISCARD virtual eastl::string GetTitle() const = 0;
            virtual void SetTitle(eastl::string_view title) = 0;

            PYRO_NODISCARD virtual Size GetFramebufferSize() const = 0;
            PYRO_NODISCARD virtual f32 GetDPIScale() const = 0;
            PYRO_NODISCARD virtual FSize GetContentScale() const = 0;

            PYRO_NODISCARD virtual CursorMode GetCursorMode() const = 0;
            PYRO_NODISCARD virtual bool IsStickyKeysEnabled() const = 0;
            PYRO_NODISCARD virtual bool IsStickyMouseButtonsEnabled() const = 0;
            PYRO_NODISCARD virtual bool IsRawMouseMotionEnabled() const = 0;
            virtual void SetCursorMode(CursorMode mode) = 0;
            virtual void SetStickyKeysEnabled(bool enabled) = 0;
            virtual void SetStickyMouseButtonsEnabled(bool enabled) = 0;
            virtual void SetRawMouseMotionEnabled(bool enabled) = 0;

            virtual void Show() = 0;
            virtual void Hide() = 0;

            // marks ShouldClose
            virtual void Close() = 0;
            // unmarks ShouldClose
            virtual void CancelClose() = 0;
            virtual void Focus() = 0;
            // makes input pass through the window
            virtual void SetPassthrough(bool bPassthrough) = 0;
            // dynamic top-most toggle
            virtual void SetTopMost(bool bTopMost) = 0;
            // flash taskbar on Windows, bounce dock on macOS
            virtual void RequestAttention() = 0;

            PYRO_NODISCARD virtual bool IsVisible() const = 0;
            PYRO_NODISCARD virtual bool ShouldClose() const = 0;
            PYRO_NODISCARD virtual bool IsFocused() const = 0;
            PYRO_NODISCARD virtual bool IsHovered() const = 0;

            PYRO_NODISCARD virtual IWindowInput* GetInputHandler() = 0;

            // HWND on windows
            // Window* on X11
            PYRO_NODISCARD virtual NativeHandle GetNativeWindow() const = 0;

            // HINSTANCE on windows
            // Display* on X11
            PYRO_NODISCARD virtual NativeHandle GetNativeInstance() const = 0;

        protected:
            virtual ~IWindow() = default;
            friend struct IWindowManager;
        };
    } // namespace Platform
} // namespace PyroshockStudios