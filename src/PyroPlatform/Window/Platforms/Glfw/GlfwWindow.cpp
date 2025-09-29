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

#include "GlfwWindow.hpp"
#include "GlfwShared.hpp"
#include <PyroCommon/Logger.hpp>
#include <PyroPlatform/Window/Platforms/Glfw/GlfwCursor.hpp>
#include <PyroPlatform/Window/Platforms/Glfw/GlfwMonitor.hpp>
#include <PyroPlatform/Window/Platforms/Glfw/GlfwWindowInput.hpp>
#ifdef PYRO_PLATFORM_WINDOWS
#include <Windows.h>

#define GLFW_EXPOSE_NATIVE_WIN32

#elif PYRO_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#elif PYRO_PLATFORM_MACOS

#else
#error glfw native not supported

#endif

#define GLFW_NATIVE_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <libassert/assert.hpp>

namespace PyroshockStudios {
    inline namespace Platform {
        GlfwWindow::GlfwWindow(u32 width, u32 height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
            : mWindow(glfwCreateWindow(width, height, title, monitor, share)) {
            // APPARENTLY in GCC fields dont get assigned until the constructor finished creating the members on top????? WHAT IS THIS
            glfwSetWindowUserPointer(mWindow, this);
            mInput = new GlfwWindowInput(this);
            glfwSetWindowRefreshCallback(mWindow, [](GLFWwindow* window) {
                GlfwWindow* self = reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
            });
        }
        GlfwWindow::~GlfwWindow() {
            delete mInput;
            glfwDestroyWindow(mWindow);
        }

        Size GlfwWindow::GetSize() const {
            int x, y;
            glfwGetWindowSize(mWindow, &x, &y);
            return Size(x, y);
        }

        Point GlfwWindow::GetPosition() const {
            int x, y;
            glfwGetWindowPos(mWindow, &x, &y);
            return Point(x, y);
        }

        Point GlfwWindow::GetCursorPosition() const {
            double x, y;
            glfwGetCursorPos(mWindow, &x, &y);
            return Point(static_cast<u32>(x), static_cast<u32>(y));
        }

        f32 GlfwWindow::GetOpacity() const {
            return glfwGetWindowOpacity(mWindow);
        }

        void GlfwWindow::SetSize(Size size) {
#if defined(PYRO_PLATFORM_MACOS) && !GLFW_HAS_OSX_WINDOW_POS_FIX
            int x, y, width, height;
            glfwGetWindowPos(mWindow, &x, &y);
            glfwGetWindowSize(mWindow, &width, &height);
            glfwSetWindowPos(mWindow, x, y - height + static_cast<int>(size.height));
#endif
            glfwSetWindowSize(mWindow, static_cast<int>(size.width), static_cast<int>(size.height));
        }

        void GlfwWindow::SetPosition(Point point) {
            glfwSetWindowPos(mWindow, static_cast<int>(point.x), static_cast<int>(point.y));
        }

        void GlfwWindow::SetCursorPosition(Point point) {
            glfwSetCursorPos(mWindow, static_cast<double>(point.x), static_cast<double>(point.y));
        }

        void GlfwWindow::SetCursorVisible(bool bVisible) {
            glfwSetInputMode(mWindow, GLFW_CURSOR, bVisible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
        }

        void GlfwWindow::SetCursorLockedToWindow(bool bLocked) {
            glfwSetInputMode(mWindow, GLFW_CURSOR, bLocked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
        }

        void GlfwWindow::SetOpacity(f32 opacity) {
            glfwSetWindowOpacity(mWindow, opacity);
        }

        void GlfwWindow::SetCursor(ICursor* cursor) {
            if (!cursor) {
                glfwSetCursor(mWindow, nullptr); // default cursor
                return;
            }
            auto* glfwCursor = static_cast<GlfwCursor*>(cursor);
            glfwSetCursor(mWindow, glfwCursor->GetGLFWCursor());
        }

        void GlfwWindow::SetFullscreen(IMonitor* monitor) {
            auto* glfwMonitor = static_cast<GlfwMonitor*>(monitor)->GetGLFWMonitor();
            const Size size = GetSize();
            glfwSetWindowMonitor(mWindow, glfwMonitor, 0, 0,
                static_cast<int>(size.width),
                static_cast<int>(size.height),
                GLFW_DONT_CARE);
        }

        void GlfwWindow::SetWindowState(WindowState state) {
            switch (state) {
            case WindowState::Minimized:
                glfwIconifyWindow(mWindow);
                break;
            case WindowState::Maximized:
                glfwMaximizeWindow(mWindow);
                break;
            case WindowState::Normal:
                glfwRestoreWindow(mWindow);
                break;
            }
        }

        WindowState GlfwWindow::GetWindowState() const {
            if (glfwGetWindowAttrib(mWindow, GLFW_ICONIFIED))
                return WindowState::Minimized;
            if (glfwGetWindowAttrib(mWindow, GLFW_MAXIMIZED))
                return WindowState::Maximized;
            return WindowState::Normal;
        }


        eastl::string GlfwWindow::GetTitle() const {
            return glfwGetWindowTitle(mWindow);
        }

        void GlfwWindow::SetTitle(eastl::string_view title) {
            glfwSetWindowTitle(mWindow, title.data());
        }

        Size GlfwWindow::GetFramebufferSize() const {
            int width, height;
            glfwGetFramebufferSize(mWindow, &width, &height);
            return Size(width, height);
        }

        f32 GlfwWindow::GetDPIScale() const {
            int fbWidth, fbHeight;
            int winWidth, winHeight;
            glfwGetFramebufferSize(mWindow, &fbWidth, &fbHeight);
            glfwGetWindowSize(mWindow, &winWidth, &winHeight);
            return static_cast<f32>(fbWidth) / static_cast<f32>(winWidth);
        }

        FSize GlfwWindow::GetContentScale() const {
            float x, y;
            glfwGetWindowContentScale(mWindow, &x, &y);
            return FSize(x, y);
        }

        CursorMode GlfwWindow::GetCursorMode() const {
            int mode = glfwGetInputMode(mWindow, GLFW_CURSOR);
            switch (mode) {
            case GLFW_CURSOR_NORMAL:
                return CursorMode::Normal;
            case GLFW_CURSOR_HIDDEN:
                return CursorMode::Hidden;
            case GLFW_CURSOR_DISABLED:
                return CursorMode::Locked;
            default:
                return CursorMode::Normal;
            }
        }

        bool GlfwWindow::IsStickyKeysEnabled() const {
            return glfwGetInputMode(mWindow, GLFW_STICKY_KEYS) == GLFW_TRUE;
        }

        bool GlfwWindow::IsStickyMouseButtonsEnabled() const {
            return glfwGetInputMode(mWindow, GLFW_STICKY_MOUSE_BUTTONS) == GLFW_TRUE;
        }

        bool GlfwWindow::IsRawMouseMotionEnabled() const {
            return glfwGetInputMode(mWindow, GLFW_RAW_MOUSE_MOTION) == GLFW_TRUE;
        }

        void GlfwWindow::SetCursorMode(CursorMode mode) {
            int glfwMode = GLFW_CURSOR_NORMAL;
            switch (mode) {
            case CursorMode::Normal:
                glfwMode = GLFW_CURSOR_NORMAL;
                break;
            case CursorMode::Hidden:
                glfwMode = GLFW_CURSOR_HIDDEN;
                break;
            case CursorMode::Locked:
                glfwMode = GLFW_CURSOR_DISABLED;
                break;
            }
            glfwSetInputMode(mWindow, GLFW_CURSOR, glfwMode);
        }

        void GlfwWindow::SetStickyKeysEnabled(bool bEnabled) {
            glfwSetInputMode(mWindow, GLFW_STICKY_KEYS, bEnabled ? GLFW_TRUE : GLFW_FALSE);
        }

        void GlfwWindow::SetStickyMouseButtonsEnabled(bool bEnabled) {
            glfwSetInputMode(mWindow, GLFW_STICKY_MOUSE_BUTTONS, bEnabled ? GLFW_TRUE : GLFW_FALSE);
        }

        void GlfwWindow::SetRawMouseMotionEnabled(bool bEnabled) {
            glfwSetInputMode(mWindow, GLFW_RAW_MOUSE_MOTION, bEnabled ? GLFW_TRUE : GLFW_FALSE);
        }

        void GlfwWindow::Show() {
            glfwShowWindow(mWindow);
        }

        void GlfwWindow::Hide() {
            glfwHideWindow(mWindow);
        }

        void GlfwWindow::Close() {
            glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
        }

        void GlfwWindow::CancelClose() {
            glfwSetWindowShouldClose(mWindow, GLFW_FALSE);
        }

        void GlfwWindow::Focus() {
            glfwSetWindowAttrib(mWindow, GLFW_FOCUSED, GLFW_TRUE);
        }

        void GlfwWindow::SetPassthrough(bool bPassthrough) {
            glfwSetWindowAttrib(mWindow, GLFW_MOUSE_PASSTHROUGH, bPassthrough ? GLFW_TRUE : GLFW_FALSE);
        }

        void GlfwWindow::SetTopMost(bool bTopMost) {
            glfwSetWindowAttrib(mWindow, GLFW_FLOATING, bTopMost ? GLFW_TRUE : GLFW_FALSE);
        }

        void GlfwWindow::RequestAttention() {
            glfwRequestWindowAttention(mWindow);
        }

        bool GlfwWindow::IsVisible() const {
            return glfwGetWindowAttrib(mWindow, GLFW_VISIBLE) == GLFW_TRUE;
        }

        bool GlfwWindow::ShouldClose() const {
            return glfwWindowShouldClose(mWindow);
        }

        bool GlfwWindow::IsFocused() const {
            return glfwGetWindowAttrib(mWindow, GLFW_FOCUSED) != 0;
        }

        bool GlfwWindow::IsHovered() const {
            return glfwGetWindowAttrib(mWindow, GLFW_HOVERED) != 0;
        }

        IWindowInput* GlfwWindow::GetInputHandler() {
            return mInput;
        }


#ifndef PYRO_PLATFORM_MACOS // Macos headers have objective c includes, those are in GlfwWindow.mm
        NativeHandle GlfwWindow::GetNativeWindow() const {
#ifdef PYRO_PLATFORM_WINDOWS
            return reinterpret_cast<NativeHandle>(glfwGetWin32Window(mWindow));
#elif PYRO_PLATFORM_LINUX
            NativeHandle handle = reinterpret_cast<NativeHandle>(glfwGetX11Window(mWindow));
            if (glfwGetError(nullptr) == GLFW_PLATFORM_UNAVAILABLE || !handle) {
                Logger::Fatal(gGlfwSink, "Failed to get X11 window handle! Is X11 installed, and are any possible translation servers running?");
            }
            return handle;
#else
#error Not supported
#endif
        }

        NativeHandle GlfwWindow::GetNativeInstance() const {
#ifdef PYRO_PLATFORM_WINDOWS
            return reinterpret_cast<NativeHandle>(GetModuleHandleA(nullptr));
#elif PYRO_PLATFORM_LINUX
            NativeHandle handle = reinterpret_cast<NativeHandle>(glfwGetX11Display());
            if (glfwGetError(nullptr) == GLFW_PLATFORM_UNAVAILABLE || !handle) {
                Logger::Fatal(gGlfwSink, "Failed to get X11 display handle! Is X11 installed, and are any possible translation servers running?");
            }
            return handle;
#else
#error Not supported
#endif
        }

#endif
    } // namespace Platform
} // namespace PyroshockStudios
