// MIT License
//
// Copyright (c) 2025-2026 Pyroshock Studios
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
#include <PyroPlatform/Gamepad/IGamepadManager.hpp>
#include <PyroPlatform/Window/IWindowManager.hpp>

namespace PyroshockStudios {
    inline namespace Platform {
        class GlfwGamepadManager : public IGamepadManager, DeleteCopy, DeleteMove {
        public:
            bool Init() override;
            bool Terminate() override;

            bool SetHardwareMappings(const char* mappings) override;

            void GetConnectedGamepadIdentifiers(GamepadIdentifier* outIdentifiers, u32* inoutNumIdentifiers) override;

            void AddGamepadConnectionListener(PFN_GamepadConnected listener) override;
            bool TryGetGamepadState(GamepadIdentifier identifier, GamepadInputState* outInputState) override;
            bool TryGetGamepadDeviceInfo(GamepadIdentifier identifier, GamepadDeviceInfo* outDeviceInfo) override;

            void InjectLogger(ILogStream* stream) override;

        private:
            static void JoystickStatusCallback(int jid, int event);

        private:
            bool bInitialised = false;
        };

    } // namespace Platform
} // namespace PyroshockStudios
