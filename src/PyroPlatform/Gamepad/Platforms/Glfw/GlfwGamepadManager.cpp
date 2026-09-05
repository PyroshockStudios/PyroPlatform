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

#include "GlfwGamepadManager.hpp"

#include <EASTL/list.h>
#include <GLFW/glfw3.h>

#include <PyroCommon/Logger.hpp>

namespace PyroshockStudios {
    inline namespace Platform {
        ILogStream* gGamepadSink = nullptr;

        eastl::list<PFN_GamepadConnected> gGamepadConnectionCallbacks;

        bool GlfwGamepadManager::Init() {
            return glfwSetJoystickCallback(JoystickStatusCallback);
        }

        bool GlfwGamepadManager::Terminate() {
            gGamepadSink = nullptr;
            glfwSetJoystickCallback(nullptr);
            gGamepadConnectionCallbacks.clear();
            return true;
        }

        bool GlfwGamepadManager::SetHardwareMappings(const char* mappings) {
            return glfwUpdateGamepadMappings(mappings);
        }

        void GlfwGamepadManager::GetConnectedGamepadIdentifiers(GamepadIdentifier* outIdentifiers, u32* inoutNumIdentifiers) {
            if (!inoutNumIdentifiers) {
                return;
            }
            u32 connections = 0;
            for (int jid = GLFW_JOYSTICK_1; jid <= GLFW_JOYSTICK_LAST; jid++) {
                if (glfwJoystickPresent(jid) == GLFW_FALSE) {
                    continue;
                }
                if (outIdentifiers && connections < *inoutNumIdentifiers) {
                    outIdentifiers[connections++] = jid;
                }
            }
            *inoutNumIdentifiers = connections;
        }

        void GlfwGamepadManager::AddGamepadConnectionListener(PFN_GamepadConnected listener) {
            gGamepadConnectionCallbacks.push_back(listener);
        }

        bool GlfwGamepadManager::TryGetGamepadState(GamepadIdentifier identifier, GamepadInputState* outInputState) {
            GLFWgamepadstate gpState;
            if (!glfwGetGamepadState(identifier, &gpState)) {
                return false;
            }
            if (outInputState) {
                for (int i = 0; i < 6; ++i) {
                    outInputState->axes[i] = gpState.axes[i];
                }
                for (int i = 0; i < 15; ++i) {
                    outInputState->buttons[i] = gpState.buttons[i];
                }
            }
            return true;
        }

        bool GlfwGamepadManager::TryGetGamepadDeviceInfo(GamepadIdentifier identifier, GamepadDeviceInfo* outDeviceInfo) {
            if (!glfwJoystickPresent(identifier)) {
                return false;
            }
            if (outDeviceInfo) {
                const char* guidStr = glfwGetJoystickGUID(identifier);
                const char* name = glfwGetJoystickName(identifier);
                outDeviceInfo->hardwareDeviceGUID = GUID::FromString(guidStr ? guidStr : "");
                outDeviceInfo->hardwareDeviceName = name;
            }
            return true;
        }

        void GlfwGamepadManager::InjectLogger(ILogStream* stream) {
            gGamepadSink = stream;
        }

        void GlfwGamepadManager::JoystickStatusCallback(int jid, int event) {
            Logger::Debug(gGamepadSink, "GLFW: Joystick {} was {}", jid, event == GLFW_CONNECTED ? "connected" : "disconnected");

            GamepadIdentifier identifier = jid;
            GamepadConnectionState state = event == GLFW_CONNECTED ? GamepadConnectionState::Connected : GamepadConnectionState::Disconnected;

            for (PFN_GamepadConnected callback : gGamepadConnectionCallbacks) {
                callback(identifier, state);
            }
        }
    } // namespace Platform
} // namespace PyroshockStudios
