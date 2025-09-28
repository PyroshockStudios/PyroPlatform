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
#include <PyroCommon/Core.hpp>
#include <PyroPlatform/Window/IWindow.hpp>

extern "C" struct GLFWwindow;
extern "C" struct GLFWmonitor;
namespace PyroshockStudios {
    inline namespace Platform {
        class GlfwWindowManager;
        class GlfwWindowInput;
        class GlfwWindow : public IWindow, DeleteCopy, DeleteMove {
        public:
            GlfwWindow(u32 width, u32 height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
            ~GlfwWindow();

            Size GetSize() const override;
            Point GetPosition() const override;
            Point GetCursorPosition() const override;
            f32 GetOpacity() const override;
            void SetSize(Size size) override;
            void SetPosition(Point point) override;
            void SetCursorPosition(Point point) override;
            void SetCursorVisible(bool bVisible) override;
            void SetCursorLockedToWindow(bool bLocked) override;
            void SetOpacity(f32 opacity) override;
            void SetCursor(ICursor* cursor) override;
            void SetFullscreen(IMonitor* monitor) override;
            void SetWindowState(WindowState state) override;
            WindowState GetWindowState() const override;
            eastl::string GetTitle() const override;
            void SetTitle(eastl::string_view title) override;
            Size GetFramebufferSize() const override;
            f32 GetDPIScale() const override;
            FSize GetContentScale() const override;
            CursorMode GetCursorMode() const override;
            bool IsStickyKeysEnabled() const override;
            bool IsStickyMouseButtonsEnabled() const override;
            bool IsRawMouseMotionEnabled() const override;
            void SetCursorMode(CursorMode mode) override;
            void SetStickyKeysEnabled(bool bEnabled) override;
            void SetStickyMouseButtonsEnabled(bool bEnabled) override;
            void SetRawMouseMotionEnabled(bool bEnabled) override;
            void Show() override;
            void Hide() override;
            void Close() override;
            void CancelClose() override;
            void Focus() override;
            void SetPassthrough(bool bPassthrough) override;
            void SetTopMost(bool bTopMost) override;
            void RequestAttention() override;
            bool IsVisible() const override;
            bool ShouldClose() const override;
            bool IsFocused() const override;
            bool IsHovered() const override;

            IWindowInput* GetInputHandler() override;

            NativeHandle GetNativeWindow() const override;
            NativeHandle GetNativeInstance() const override;

            GLFWwindow* GetGLFWWindow() const {
                return mWindow;
            }

        private:
            GlfwWindowInput* mInput = nullptr;
            GLFWwindow* mWindow = nullptr;
        };
    } // namespace Platform
} // namespace PyroshockStudios
