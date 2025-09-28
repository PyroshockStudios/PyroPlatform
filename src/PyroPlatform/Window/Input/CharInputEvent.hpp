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

namespace PyroshockStudios {
    inline namespace Platform {
        class CharInputEvent : public InputEvent<InputEventType::CharInput> {
        public:
            CharInputEvent(IWindow& sender, u32 unicode)
                : InputEvent(sender), kUnicode(unicode) {}

            InputEventType GetType() const override {
                return InputEventType::CharInput;
            }
            eastl::string GetName() const override {
                return "CharInputEvent";
            }
            eastl::string ToString() const override {
                eastl::string result = {};

                if (kUnicode <= 0x7F) {
                    result += static_cast<char>(kUnicode);
                } else if (kUnicode <= 0x7FF) {
                    result += static_cast<char>(0xC0 | ((kUnicode >> 6) & 0x1F));
                    result += static_cast<char>(0x80 | (kUnicode & 0x3F));
                } else if (kUnicode <= 0xFFFF) {
                    result += static_cast<char>(0xE0 | ((kUnicode >> 12) & 0x0F));
                    result += static_cast<char>(0x80 | ((kUnicode >> 6) & 0x3F));
                    result += static_cast<char>(0x80 | (kUnicode & 0x3F));
                } else if (kUnicode <= 0x10FFFF) {
                    result += static_cast<char>(0xF0 | ((kUnicode >> 18) & 0x07));
                    result += static_cast<char>(0x80 | ((kUnicode >> 12) & 0x3F));
                    result += static_cast<char>(0x80 | ((kUnicode >> 6) & 0x3F));
                    result += static_cast<char>(0x80 | (kUnicode & 0x3F));
                } else {
                    // Invalid code point
                    result += '?'; // or replacement character: 0xEF 0xBF 0xBD
                }

                return "Char Typed: " + result;
            }

            const u32 kUnicode;
        };
    } // namespace Platform
} // namespace PyroshockStudios