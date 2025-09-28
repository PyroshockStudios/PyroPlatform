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

#include "GlfwWindowInput.hpp"
#define GLFW_NATIVE_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#include <PyroPlatform/Window/Platforms/Glfw/GlfwWindow.hpp>
#include <PyroPlatform/Window/WindowEvents.hpp>

#include <GLFW/glfw3.h>

namespace PyroshockStudios {
    inline namespace Platform {
        GlfwWindowInput::GlfwWindowInput(GlfwWindow* window) : mWindow(window) {
            CreateCallbacks();
            mEvents = new WindowEvents;
        }
        GlfwWindowInput::~GlfwWindowInput() {
            delete mEvents;
        }
        bool GlfwWindowInput::IsKeyDown(KeyCode key) {
            return glfwGetKey(mWindow->GetGLFWWindow(), static_cast<int>(key)) == GLFW_PRESS;
        }

        bool GlfwWindowInput::IsMouseDown(MouseButton button) {
            return glfwGetMouseButton(mWindow->GetGLFWWindow(), static_cast<int>(button)) == GLFW_PRESS;
        }
        WindowEvents& GlfwWindowInput::GetEvents() {
            return *mEvents;
        }
        void GlfwWindowInput::CreateCallbacks() {
            glfwSetKeyCallback(mWindow->GetGLFWWindow(), GlfwWindowInput::KeyCallback);
            glfwSetCursorEnterCallback(mWindow->GetGLFWWindow(), GlfwWindowInput::CursorEnterCallback);
            glfwSetMouseButtonCallback(mWindow->GetGLFWWindow(), GlfwWindowInput::MouseButtonCallback);
            glfwSetScrollCallback(mWindow->GetGLFWWindow(), GlfwWindowInput::MouseScrollCallback);
            glfwSetCursorPosCallback(mWindow->GetGLFWWindow(), GlfwWindowInput::MousePositionCallback);
            glfwSetCharCallback(mWindow->GetGLFWWindow(), GlfwWindowInput::CharCallback);
            glfwSetWindowSizeCallback(mWindow->GetGLFWWindow(), GlfwWindowInput::ResizeCallback);
            glfwSetWindowFocusCallback(mWindow->GetGLFWWindow(), GlfwWindowInput::FocusCallback);
            glfwSetWindowCloseCallback(mWindow->GetGLFWWindow(), GlfwWindowInput::CloseCallback);
            glfwSetWindowPosCallback(mWindow->GetGLFWWindow(), GlfwWindowInput::PositionCallback);
        }

        void GlfwWindowInput::KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
            GlfwWindow* pThis = reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
            KeyEvent event = KeyEvent(*pThis, static_cast<KeyCode>(key), scanCode, static_cast<InputModifiers::Flags>(mods),
                action == GLFW_PRESS || action == GLFW_REPEAT, action == GLFW_REPEAT);
            WindowEvents& events = pThis->GetInputHandler()->GetEvents();
            events.GetEventDispatcher<KeyEvent>().Dispatch(event);
        }
        void GlfwWindowInput::CursorEnterCallback(GLFWwindow* window, int entered) {
            GlfwWindow* pThis = reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
            CursorEnterEvent event = CursorEnterEvent(*pThis, entered != 0);
            WindowEvents& events = pThis->GetInputHandler()->GetEvents();
            events.GetEventDispatcher<CursorEnterEvent>().Dispatch(event);
        }
        void GlfwWindowInput::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
            GlfwWindow* pThis = reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
            MouseEvent event = MouseEvent(*pThis, static_cast<MouseButton>(button),
                static_cast<InputModifiers::Flags>(mods), action == GLFW_PRESS);
            WindowEvents& events = pThis->GetInputHandler()->GetEvents();
            events.GetEventDispatcher<MouseEvent>().Dispatch(event);
        }
        void GlfwWindowInput::MouseScrollCallback(GLFWwindow* window, double x, double y) {
            GlfwWindow* pThis = reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
            CursorScrollEvent event = CursorScrollEvent(*pThis, static_cast<float>(x),
                static_cast<float>(y));
            WindowEvents& events = pThis->GetInputHandler()->GetEvents();
            events.GetEventDispatcher<CursorScrollEvent>().Dispatch(event);
        }
        void GlfwWindowInput::MousePositionCallback(GLFWwindow* window, double x, double y) {
            GlfwWindow* pThis = reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
            CursorPositionEvent event = CursorPositionEvent(*pThis, static_cast<float>(x),
                static_cast<float>(y));
            WindowEvents& events = pThis->GetInputHandler()->GetEvents();
            events.GetEventDispatcher<CursorPositionEvent>().Dispatch(event);
        }
        void GlfwWindowInput::CharCallback(GLFWwindow* window, unsigned int codePoint) {
            GlfwWindow* pThis = reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
            CharInputEvent event = CharInputEvent(*pThis, codePoint);
            WindowEvents& events = pThis->GetInputHandler()->GetEvents();
            events.GetEventDispatcher<CharInputEvent>().Dispatch(event);
        }
        void GlfwWindowInput::ResizeCallback(GLFWwindow* window, int width, int height) {
            GlfwWindow* pThis = reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
            WindowResizeEvent event = WindowResizeEvent(*pThis, width, height);
            WindowEvents& events = pThis->GetInputHandler()->GetEvents();
            events.GetEventDispatcher<WindowResizeEvent>().Dispatch(event);
        }

        void GlfwWindowInput::FocusCallback(GLFWwindow* window, int focussed) {
            GlfwWindow* pThis = reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
            WindowFocusEvent event = WindowFocusEvent(*pThis, focussed != 0);
            WindowEvents& events = pThis->GetInputHandler()->GetEvents();
            events.GetEventDispatcher<WindowFocusEvent>().Dispatch(event);
        }
        void GlfwWindowInput::CloseCallback(GLFWwindow* window) {
            GlfwWindow* pThis = reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
            WindowCloseEvent event = WindowCloseEvent(*pThis);
            WindowEvents& events = pThis->GetInputHandler()->GetEvents();
            events.GetEventDispatcher<WindowCloseEvent>().Dispatch(event);
        }
        void GlfwWindowInput::PositionCallback(GLFWwindow* window, int x, int y) {
            GlfwWindow* pThis = reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
            WindowPositionEvent event = WindowPositionEvent(*pThis, static_cast<f64>(x), static_cast<f64>(y));
            WindowEvents& events = pThis->GetInputHandler()->GetEvents();
            events.GetEventDispatcher<WindowPositionEvent>().Dispatch(event);
        }
    }
}
