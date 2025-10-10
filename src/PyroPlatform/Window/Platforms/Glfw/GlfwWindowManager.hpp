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
#include <EASTL/vector.h>

#include "GlfwMonitor.hpp"
#include <EASTL/shared_ptr.h>
#include <PyroCommon/Core.hpp>
#include <PyroPlatform/Forward.hpp>
#include <PyroPlatform/Window/IWindowManager.hpp>

namespace PyroshockStudios {
    inline namespace Platform {
        class GlfwWindowManager : public IWindowManager, DeleteCopy, DeleteMove {
        public:
            bool Init() override;
            bool Terminate() override;

            void PollEvents() override;
            void WaitEvents() override;

            bool HasClipboardText() override;
            eastl::string GetClipboardText() override;
            void SetClipboardText(eastl::string_view text) override;
            eastl::span<IMonitor*> GetMonitors() override;
            IMonitor* GetPrimaryMonitor() override;
            IWindow* CreateWindow(const WindowInfo& info) override;
            void DestroyWindow(IWindow*& window) override;
            ICursor* CreateCursor(CursorType type) override;
            void DestroyCursor(ICursor*& cursor) override;
            KeyCode TranslateKey(i32 key, i32 scancode, KeySource source) override;

            void InjectLogger(ILogStream* stream) override;
        private:
            static void MonitorConnectedCallback(GLFWmonitor* monitor);
            static void MonitorDisconnectedCallback(GLFWmonitor* monitor);

            eastl::vector<eastl::shared_ptr<GlfwMonitor>> mMonitorsStorage;
            eastl::vector<IMonitor*> mMonitors;
            bool bInitialised = false;
        };
    } // namespace Platform
} // namespace PyroshockStudios
