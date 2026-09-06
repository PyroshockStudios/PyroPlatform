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
#include "InputEvent.hpp"
#include <EASTL/span.h>
#include <cstdio>

namespace PyroshockStudios {
    inline namespace Platform {
        class PathDropEvent : public InputEvent<InputEventType::PathDrop> {
        public:
            PathDropEvent(IWindow& sender, eastl::span<const char*> paths)
                : InputEvent(sender), kPaths(paths) {}

            InputEventType GetType() const override {
                return InputEventType::Mouse;
            }
            eastl::string GetName() const override {
                return "PathDropEvent";
            }
            eastl::string ToString() const override {
                eastl::string pathBuilder = "";
                for (const char* path : kPaths) {
                    if (!pathBuilder.empty())
                        pathBuilder += ", ";
                    pathBuilder += "\"";
                    pathBuilder += path;
                    pathBuilder += "\"";
                }
                return "Paths dropped: " + pathBuilder;
            }

            const eastl::span<const char*> kPaths;
        };
    } // namespace Platform
} // namespace PyroshockStudios