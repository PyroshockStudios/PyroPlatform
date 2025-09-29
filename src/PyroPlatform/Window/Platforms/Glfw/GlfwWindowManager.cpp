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

#include "GlfwWindowManager.hpp"
#include <PyroCommon/Logger.hpp>
#include <PyroPlatform/Window/Platforms/Glfw/GlfwCursor.hpp>
#include <PyroPlatform/Window/Platforms/Glfw/GlfwWindow.hpp>

#define GLFW_NATIVE_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <libassert/assert.hpp>


namespace PyroshockStudios {
    inline namespace Platform {
        static const ILogStream* gGlfwSink = nullptr;

        bool GlfwWindowManager::Init() {
            mMonitors.clear();
            mMonitorsStorage.clear();
            bool result = glfwInit();
            if (result) {
                // disable legacy OpenGL functionality
                glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
                // force X11 on linux
#ifdef PYRO_PLATFORM_LINUX
                glfwWindowHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
#endif
                glfwSetMonitorCallback([](GLFWmonitor* monitor, int event) {
                    if (event == GLFW_CONNECTED) {
                        GlfwWindowManager::MonitorConnectedCallback(monitor);
                    } else if (event == GLFW_DISCONNECTED) {
                        GlfwWindowManager::MonitorConnectedCallback(monitor);
                    }
                });
                int count = 0;
                GLFWmonitor** glfwMonitors = glfwGetMonitors(&count);
                mMonitorsStorage.clear();
                mMonitors.clear();
                mMonitorsStorage.reserve(count);
                for (int i = 0; i < count; ++i) {
                    mMonitorsStorage.emplace_back(eastl::make_shared<GlfwMonitor>(glfwMonitors[i]));
                    mMonitors.push_back(mMonitorsStorage.back().get());
                }
            } else {
                const char* err;
                glfwGetError(&err);
                Logger::Error(gGlfwSink, "Failed to initialise GLFW! Reason: {}", err);
            }
            bInitialised = result;
            return result;
        }

        bool GlfwWindowManager::Terminate() {
            Logger::Trace(gGlfwSink, "Terminating GLFW");
            glfwTerminate();
            mMonitors.clear();
            mMonitorsStorage.clear();
            bInitialised = false;
            return true;
        }

        void GlfwWindowManager::PollEvents() {
            ASSERT(bInitialised, "Window manager not initialised!");
            glfwPollEvents();
        }
        void GlfwWindowManager::WaitEvents() {
            ASSERT(bInitialised, "Window manager not initialised!");
            glfwWaitEvents();
        }

        bool GlfwWindowManager::HasClipboardText() {
            ASSERT(bInitialised, "Window manager not initialised!");
            return glfwGetClipboardString(nullptr) != nullptr;
        }

        eastl::string GlfwWindowManager::GetClipboardText() {
            ASSERT(bInitialised, "Window manager not initialised!");
            return eastl::string(glfwGetClipboardString(nullptr));
        }

        void GlfwWindowManager::SetClipboardText(eastl::string_view text) {
            ASSERT(bInitialised, "Window manager not initialised!");
            glfwSetClipboardString(nullptr, text.data());
        }

        eastl::span<IMonitor*> GlfwWindowManager::GetMonitors() {
            ASSERT(bInitialised, "Window manager not initialised!");
            return eastl::span<IMonitor*>(mMonitors.data(), mMonitors.size());
        }

        IMonitor* GlfwWindowManager::GetPrimaryMonitor() {
            ASSERT(bInitialised, "Window manager not initialised!");
            GLFWmonitor* primary = glfwGetPrimaryMonitor();
            for (auto* monitor : mMonitors) {
                auto* glfwMonitor = static_cast<GlfwMonitor*>(monitor)->GetGLFWMonitor();
                if (glfwMonitor == primary)
                    return monitor;
            }
            const char* err;
            glfwGetError(&err);
            Logger::Error(gGlfwSink, "No monitor was found! Reason: {}", err);
            return nullptr;
        }

        IWindow* GlfwWindowManager::CreateWindow(const WindowInfo& info) {
            ASSERT(bInitialised, "Window manager not initialised!");
            glfwWindowHint(GLFW_RESIZABLE, info.flags & WindowCreateBits::RESIZABLE ? GLFW_TRUE : GLFW_FALSE);
            glfwWindowHint(GLFW_VISIBLE, info.flags & WindowCreateBits::VISIBLE ? GLFW_TRUE : GLFW_FALSE);
            glfwWindowHint(GLFW_FOCUSED, info.flags & WindowCreateBits::FOCUSED ? GLFW_TRUE : GLFW_FALSE);
            glfwWindowHint(GLFW_FOCUS_ON_SHOW, info.flags & WindowCreateBits::FOCUSED ? GLFW_TRUE : GLFW_FALSE);
            glfwWindowHint(GLFW_DECORATED, info.flags & WindowCreateBits::DECORATED ? GLFW_TRUE : GLFW_FALSE);
            glfwWindowHint(GLFW_FLOATING, info.flags & WindowCreateBits::TOP_MOST ? GLFW_TRUE : GLFW_FALSE);
            glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, info.flags & WindowCreateBits::PASSTHROUGH ? GLFW_TRUE : GLFW_FALSE);
            glfwWindowHint(GLFW_SCALE_TO_MONITOR, info.flags & WindowCreateBits::HIGH_DPI ? GLFW_TRUE : GLFW_FALSE);

            Logger::Trace(gGlfwSink, "Creating window \"{}\" with size {}x{}", info.title, info.width, info.height);
            return new GlfwWindow(info.width, info.height, info.title.c_str(), nullptr, nullptr);
        }

        void GlfwWindowManager::DestroyWindow(IWindow*& window) {
            ASSERT(bInitialised, "Window manager not initialised!");
            ASSERT(dynamic_cast<GlfwWindow*>(window) != nullptr, "Type must be of GlfwWindow!");
            Logger::Trace(gGlfwSink, "Destroying window \"{}\"", window->GetTitle());
            GlfwWindow* wnd = static_cast<GlfwWindow*>(window);
            delete wnd;
            window = nullptr;
        }

        ICursor* GlfwWindowManager::CreateCursor(CursorType type) {
            ASSERT(bInitialised, "Window manager not initialised!");
            GLFWcursor* cur = nullptr;
            switch (type) {
            case (CursorType::Arrow):
                cur = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
                break;
            case (CursorType::Crosshair):
                cur = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
                break;
            case (CursorType::Hand):
                cur = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
                break;
            case (CursorType::HResize):
                cur = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
                break;
            case (CursorType::IBeam):
                cur = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
                break;
            case (CursorType::NESWResize):
                cur = glfwCreateStandardCursor(GLFW_RESIZE_NESW_CURSOR);
                break;
            case (CursorType::NotAllowed):
                cur = glfwCreateStandardCursor(GLFW_NOT_ALLOWED_CURSOR);
                break;
            case (CursorType::NWSEResize):
                cur = glfwCreateStandardCursor(GLFW_RESIZE_NWSE_CURSOR);
                break;
            case (CursorType::Resize):
                cur = glfwCreateStandardCursor(GLFW_RESIZE_ALL_CURSOR);
                break;
            case (CursorType::VResize):
                cur = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
                break;
            }
            if (!cur) {
                const char* err;
                glfwGetError(&err);
                Logger::Error(gGlfwSink, "Failed to create cursor! Reason: {}", err);
                return nullptr;
            }
            return new GlfwCursor(cur);
        }

        void GlfwWindowManager::DestroyCursor(ICursor*& cursor) {
            ASSERT(bInitialised, "Window manager not initialised!");
            delete static_cast<GlfwCursor*>(cursor);
            cursor = nullptr;
        }

        KeyCode GlfwWindowManager::TranslateKey(i32 key, i32 scancode, KeySource source) {
            ASSERT(bInitialised, "Window manager not initialised!");
            if (source == KeySource::Physical) {
                return static_cast<KeyCode>(key);
            }

            // Use the same logic as ImGui_ImplWindowing_TranslateUntranslatedKey
            GLFWerrorfun prev_callback = glfwSetErrorCallback(nullptr);
            const char* key_name = glfwGetKeyName(key, scancode);
            glfwSetErrorCallback(prev_callback);

            if (key_name && key_name[0] != 0) {
                char c = key_name[0];

                // Numbers
                if (c >= '0' && c <= '9')
                    return static_cast<KeyCode>(static_cast<int>(KeyCode::Key0) + (c - '0'));
                // Letters
                if (c >= 'A' && c <= 'Z')
                    return static_cast<KeyCode>(static_cast<int>(KeyCode::KeyA) + (c - 'A'));
                if (c >= 'a' && c <= 'z')
                    return static_cast<KeyCode>(static_cast<int>(KeyCode::KeyA) + (c - 'a'));

                // Symbols mapping
                switch (c) {
                case '`':
                    return KeyCode::GraveAccent;
                case '-':
                    return KeyCode::Minus;
                case '=':
                    return KeyCode::Equal;
                case '[':
                    return KeyCode::LeftBracket;
                case ']':
                    return KeyCode::RightBracket;
                case '\\':
                    return KeyCode::Backslash;
                case ';':
                    return KeyCode::Semicolon;
                case '\'':
                    return KeyCode::Apostrophe;
                case ',':
                    return KeyCode::Comma;
                case '.':
                    return KeyCode::Period;
                case '/':
                    return KeyCode::Slash;
                }
            }
            // fallback
            return static_cast<KeyCode>(key);
        }

        void GlfwWindowManager::InjectLogger(const ILogStream* stream) {
            gGlfwSink = stream;
        }

        void GlfwWindowManager::MonitorConnectedCallback(GLFWmonitor* monitor) {
            const char* name = glfwGetMonitorName(monitor);
            Logger::Error(gGlfwSink, "Monitor \"{}\" connected", name ? name : "NAME_ERROR");
            auto* self = reinterpret_cast<GlfwWindowManager*>(glfwGetMonitorUserPointer(monitor));
            self->mMonitorsStorage.emplace_back(eastl::make_shared<GlfwMonitor>(monitor));
            self->mMonitors.push_back(self->mMonitorsStorage.back().get());
        }

        void GlfwWindowManager::MonitorDisconnectedCallback(GLFWmonitor* monitor) {
            const char* name = glfwGetMonitorName(monitor);
            Logger::Error(gGlfwSink, "Monitor \"{}\" disconnected", name ? name : "NAME_ERROR");
            auto* self = reinterpret_cast<GlfwWindowManager*>(glfwGetMonitorUserPointer(monitor));
            auto it = eastl::find_if(self->mMonitorsStorage.begin(), self->mMonitorsStorage.end(),
                [monitor](const eastl::shared_ptr<GlfwMonitor>& m) { return m->GetGLFWMonitor() == monitor; });

            if (it != self->mMonitorsStorage.end()) {
                // Remove pointer from mMonitors
                self->mMonitors.erase(eastl::remove(self->mMonitors.begin(), self->mMonitors.end(), static_cast<IMonitor*>(it->get())));
                // Remove storage
                self->mMonitorsStorage.erase(it);
            }
        }

    } // namespace Platform
} // namespace PyroshockStudios
