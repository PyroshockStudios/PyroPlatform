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

#include "GamepadCallbacks.hpp"

#include <PyroCommon/LoggerInterface.hpp>

namespace PyroshockStudios {
    inline namespace Platform {
        struct IGamepadManager : ILoggerAware {
            IGamepadManager() = default;

            virtual bool Init() = 0;
            virtual bool Terminate() = 0;

            virtual bool SetHardwareMappings(const char* mappings) = 0;

            virtual void GetConnectedGamepadIdentifiers(GamepadIdentifier* outIdentifiers, u32* inoutNumIdentifiers) = 0;

            virtual void AddGamepadConnectionListener(PFN_GamepadConnected listener) = 0;
            virtual bool TryGetGamepadState(GamepadIdentifier identifier, GamepadInputState* outInputState) = 0;
            virtual bool TryGetGamepadDeviceInfo(GamepadIdentifier identifier, GamepadDeviceInfo* outDeviceInfo) = 0;
        };
    } // namespace Platform
} // namespace PyroshockStudios