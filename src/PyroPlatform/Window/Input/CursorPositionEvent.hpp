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
#include <cstdio>

namespace PyroshockStudios {
    inline namespace Platform {
        class CursorPositionEvent : public InputEvent<InputEventType::CursorPosition> {
        public:
            CursorPositionEvent(IWindow& sender, f64 x, f64 y)
                : InputEvent(sender), kX(x), kY(y) {}

            InputEventType GetType() const override {
                return InputEventType::CursorPosition;
            }
            eastl::string GetName() const override {
                return "CursorPositionEvent";
            }
            eastl::string ToString() const override {
                char buff[64] = {};
                snprintf(buff, 64, "(%.2lf, %.2lf)", kX, kY);
                return "Cursor Position : " + eastl::string(buff);
            }

            const f64 kX;
            const f64 kY;
        };
    } // namespace Platform
} // namespace PyroshockStudios