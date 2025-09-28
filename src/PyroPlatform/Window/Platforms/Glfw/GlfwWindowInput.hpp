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
#include <PyroPlatform/Forward.hpp>
#include <PyroPlatform/Window/IWindowInput.hpp>
#ifdef PYRO_PLATFORM_WINDOWING_GLFW

extern "C" struct GLFWwindow;

namespace PyroshockStudios {
    inline namespace Platform {
        class GlfwWindowManager;
        class GlfwWindow;
        class GlfwWindowInput : public IWindowInput, DeleteCopy, DeleteMove {
        public:
            GlfwWindowInput(GlfwWindow* window);
            ~GlfwWindowInput();

            bool IsKeyDown(KeyCode key) override;
            bool IsMouseDown(MouseButton button) override;

            WindowEvents& GetEvents() override;

        private:
            void CreateCallbacks();

            static void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
            static void CursorEnterCallback(GLFWwindow* window, int entered);
            static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
            static void MouseScrollCallback(GLFWwindow* window, double x, double y);
            static void MousePositionCallback(GLFWwindow* window, double x, double y);
            static void CharCallback(GLFWwindow* window, unsigned int codePoint);
            static void ResizeCallback(GLFWwindow* window, int width, int height);
            static void FocusCallback(GLFWwindow* window, int focussed);
            static void CloseCallback(GLFWwindow* window);
            static void PositionCallback(GLFWwindow* window, int x, int y);

            GlfwWindow* mWindow = nullptr;
            WindowEvents* mEvents = nullptr;
        };
    }
}
#endif