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

#include "GlfwMonitor.hpp"
#define GLFW_NATIVE_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace PyroshockStudios {
    inline namespace Platform {
        GlfwMonitor::GlfwMonitor(GLFWmonitor* monitor)
            : mMonitor(monitor) {
        }
        GlfwMonitor::~GlfwMonitor() {
        }

        eastl::string GlfwMonitor::GetName() const {
            const char* name = glfwGetMonitorName(mMonitor);
            return name ? eastl::string(name) : eastl::string("Unknown");
        }

        Point GlfwMonitor::GetPosition() const {
            int x, y;
            glfwGetMonitorPos(mMonitor, &x, &y);
            return Point(x, y);
        }

        Size GlfwMonitor::GetPhysicalSize() const {
            int widthMM, heightMM;
            glfwGetMonitorPhysicalSize(mMonitor, &widthMM, &heightMM);
            return Size(widthMM, heightMM);
        }

        Size GlfwMonitor::GetResolution() const {
            const GLFWvidmode* mode = glfwGetVideoMode(mMonitor);
            if (!mode)
                return {};
            return { static_cast<u32>(mode->width), static_cast<u32>(mode->height) };
        }

        Size GlfwMonitor::GetWorkArea() const {
            int x, y;
            glfwGetMonitorWorkarea(mMonitor, nullptr, nullptr, &x, &y);
            return Size(static_cast<u32>(x), static_cast<u32>(y));
        }

        FSize GlfwMonitor::GetContentScale() const {
            float xScale = 1.0f, yScale = 1.0f;
            glfwGetMonitorContentScale(mMonitor, &xScale, &yScale);
            return FSize(xScale, yScale);
        }

        u32 GlfwMonitor::GetRefreshRate() const {
            const GLFWvidmode* mode = glfwGetVideoMode(mMonitor);
            return mode ? static_cast<u32>(mode->refreshRate) : 0;
        }
    } // namespace Platform
} // namespace PyroshockStudios
