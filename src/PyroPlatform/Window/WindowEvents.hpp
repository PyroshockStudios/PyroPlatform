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
#include <EASTL/array.h>
#include <EASTL/variant.h>

#include <PyroCommon/Types.hpp>
#include <PyroPlatform/Window/Input/CharInputEvent.hpp>
#include <PyroPlatform/Window/Input/CursorEnterEvent.hpp>
#include <PyroPlatform/Window/Input/CursorPositionEvent.hpp>
#include <PyroPlatform/Window/Input/CursorScrollEvent.hpp>
#include <PyroPlatform/Window/Input/InputEventDispatcher.hpp>
#include <PyroPlatform/Window/Input/KeyEvent.hpp>
#include <PyroPlatform/Window/Input/MouseEvent.hpp>
#include <PyroPlatform/Window/Input/Types.hpp>
#include <PyroPlatform/Window/Input/WindowCloseEvent.hpp>
#include <PyroPlatform/Window/Input/WindowFocusEvent.hpp>
#include <PyroPlatform/Window/Input/WindowPositionEvent.hpp>
#include <PyroPlatform/Window/Input/WindowResizeEvent.hpp>

namespace PyroshockStudios {
    inline namespace Platform {
        struct IWindowInput;
        class WindowEvents {
        public:
            using InputEventMap = eastl::array<
                eastl::variant<
                    InputEventDispatcher<KeyEvent>,
                    InputEventDispatcher<MouseEvent>,
                    InputEventDispatcher<CursorScrollEvent>,
                    InputEventDispatcher<CursorPositionEvent>,
                    InputEventDispatcher<CursorEnterEvent>,
                    InputEventDispatcher<CharInputEvent>,
                    InputEventDispatcher<WindowCloseEvent>,
                    InputEventDispatcher<WindowFocusEvent>,
                    InputEventDispatcher<WindowPositionEvent>,
                    InputEventDispatcher<WindowResizeEvent>>,
                static_cast<usize>(InputEventType::COUNT)>;

            WindowEvents() = default;
            ~WindowEvents() = default;

            template <typename Event>
            bool BindEvent(const InputEventHandler<Event>& handler) {
                return GetEventDispatcher<Event>().Bind(handler);
            }
            template <typename Event>
            PYRO_NODISCARD InputEventHandler<Event> BindEvent(DispatchableEvent<Event>&& fn) {
                InputEventHandler<Event> handler = InputEventHandler<Event>(eastl::move(fn));
                GetEventDispatcher<Event>().Bind(handler);
                return handler;
            }

            template <typename Event>
            bool UnbindEvent(const InputEventHandler<Event>& handler) {
                return GetEventDispatcher<Event>().Unbind(handler);
            }

            template <typename Event>
            PYRO_NODISCARD InputEventDispatcher<Event>& GetEventDispatcher() {
                return eastl::get<InputEventDispatcher<Event>>(events[static_cast<usize>(Event::Type)]);
            }

        protected:
            friend struct IWindowInput;

        private:
            InputEventMap events = {
                InputEventDispatcher<KeyEvent>(),
                InputEventDispatcher<MouseEvent>(),
                InputEventDispatcher<CursorScrollEvent>(),
                InputEventDispatcher<CursorPositionEvent>(),
                InputEventDispatcher<CursorEnterEvent>(),
                InputEventDispatcher<CharInputEvent>(),
                InputEventDispatcher<WindowCloseEvent>(),
                InputEventDispatcher<WindowFocusEvent>(),
                InputEventDispatcher<WindowPositionEvent>(),
                InputEventDispatcher<WindowResizeEvent>()
            };
        };
    } // namespace Platform
} // namespace PyroshockStudios