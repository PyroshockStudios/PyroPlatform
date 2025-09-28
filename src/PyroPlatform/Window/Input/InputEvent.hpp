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
#include <PyroCommon/Core.hpp>
#include <PyroPlatform/Core.hpp>
#include <PyroPlatform/Forward.hpp>
#include <PyroPlatform/Window/Input/Types.hpp>

namespace PyroshockStudios {
    inline namespace Platform {
        enum class InputEventType : i32 {
            Unknown = -1,
            Key,
            Mouse,
            CursorScroll,
            CursorPosition,
            CursorEnter,
            CharInput,
            WindowClose,
            WindowFocus,
            WindowPosition,
            WindowResize,
            COUNT
        };

        template <enum InputEventType E = InputEventType::Unknown>
        class InputEvent : DeleteCopy {
        public:
            static constexpr InputEventType Type = E;

            InputEvent(IWindow& sender)
                : mWindow(sender) {}
            virtual ~InputEvent() = default;

            virtual InputEventType GetType() const = 0;
            virtual eastl::string GetName() const = 0;
            virtual eastl::string ToString() const = 0;

            IWindow* Sender() {
                return &mWindow;
            }

            bool WasHandled() const {
                return bHandled;
            }

        protected:
            bool bHandled = false;
            IWindow& mWindow;
        };
    } // namespace Platform
} // namespace PyroshockStudios