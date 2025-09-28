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
#include "InputEvent.hpp"

#include <PyroCommon/Types.hpp>

#include <EASTL/functional.h>
#include <EASTL/vector.h>
#include <PyroCommon/GUID.hpp>
#include <cassert>

namespace PyroshockStudios {
    inline namespace Platform {
        template <typename Event>
        using DispatchableEvent = eastl::function<void(Event&)>;

        template <typename Event>
        class InputEventHandler {
        public:
            InputEventHandler() = default;

            InputEventHandler(const DispatchableEvent<Event>& fn) noexcept : mFn(fn), kHandle(GUID()) {}

            InputEventHandler(const InputEventHandler& other) : mFn(other.mFn), kHandle(other.kHandle) {}
            InputEventHandler& operator=(const InputEventHandler& other) noexcept {
                if (*this == other)
                    return *this;
                mFn = other.mFn;
                const_cast<GUID&>(kHandle) = other.kHandle;
                return *this;
            }
            InputEventHandler(InputEventHandler&& other) noexcept : mFn(eastl::move(other.mFn)), kHandle(other.kHandle) {
                other.mFn = {};
                const_cast<GUID&>(other.kHandle) = GUID::Invalid();
            }
            InputEventHandler& operator=(InputEventHandler&& other) noexcept {
                if (*this == other)
                    return *this;
                mFn = eastl::move(other.mFn);
                other.mFn = {};
                const_cast<GUID&>(kHandle) = other.kHandle;
                const_cast<GUID&>(other.kHandle) = GUID::Invalid();
                return *this;
            }

            bool operator==(const InputEventHandler& other) const noexcept {
                return this->kHandle == other.kHandle;
            }

            void operator()(Event& e) {
                mFn(e);
            }

            const GUID kHandle = GUID::Invalid();

        private:
            DispatchableEvent<Event> mFn;
        };

        template <typename Event>
        class InputEventDispatcher {
        public:
            InputEventDispatcher() = default;

            void Dispatch(Event& e) {
                for (InputEventHandler<Event>& fn : functions) {
                    assert(fn.kHandle.Valid());
                    fn(e);
                }
            }
            bool Bind(const InputEventHandler<Event>& handler) {
                assert(handler.kHandle.Valid());
                if (eastl::find(functions.begin(), functions.end(), handler) != functions.end()) {
                    return false;
                }
                functions.emplace_back(handler);
                return true;
            }
            bool Unbind(const InputEventHandler<Event>& handler) {
                assert(handler.kHandle.Valid());
                for (i32 i = 0; i < functions.size(); ++i) {
                    if (functions[i] == handler) {
                        functions.erase(functions.begin() + i);
                        return true;
                    }
                }
                return false;
            }

        private:
            eastl::vector<InputEventHandler<Event>> functions;
        };
    } // namespace Platform
} // namespace PyroshockStudios