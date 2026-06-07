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
            return name ? name : "";
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

        Size GlfwMonitor::GetWorkArea() const {
            int x, y;
            glfwGetMonitorWorkarea(mMonitor, nullptr, nullptr, &x, &y);
            return Size(static_cast<u32>(x), static_cast<u32>(y));
        }

        Sizef GlfwMonitor::GetContentScale() const {
            float xScale = 1.0f, yScale = 1.0f;
            glfwGetMonitorContentScale(mMonitor, &xScale, &yScale);
            return Sizef(xScale, yScale);
        }

        static MonitorVideoMode FromGlfwVidMode(const GLFWvidmode& mode) {
            return {
                .dimensions = { static_cast<u32>(mode.width), static_cast<u32>(mode.height) },
                .colorBits = { static_cast<u32>(mode.redBits), static_cast<u32>(mode.greenBits),
                    static_cast<u32>(mode.blueBits) },
                .refreshRate = static_cast<u32>(mode.refreshRate),
            };
        }

        MonitorVideoMode GlfwMonitor::GetCurrentVideoMode() const {
            const GLFWvidmode* mode = glfwGetVideoMode(mMonitor);
            return mode ? FromGlfwVidMode(*mode) : MonitorVideoMode{};
        }
        eastl::span<const MonitorVideoMode> GlfwMonitor::GetVideoModes() const {
            int count = 0;
            const GLFWvidmode* modes = glfwGetVideoModes(mMonitor, &count);
            mCacheVidModes.clear();
            if (modes) {
                for (int i = 0; i < count; ++i) {
                    mCacheVidModes.push_back(FromGlfwVidMode(modes[i]));
                }
            }
            return mCacheVidModes;
        }
    } // namespace Platform
} // namespace PyroshockStudios
