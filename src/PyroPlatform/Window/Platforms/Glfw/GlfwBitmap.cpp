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

#include "GlfwBitmap.hpp"
#define GLFW_NATIVE_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cstring>

namespace PyroshockStudios {
    inline namespace Platform {
        GlfwBitmap::GlfwBitmap(int width, int height, const unsigned char* pixels)
            : mBitmap(new GLFWimage{ .width = width, .height = height }) {
            if (mBitmap) {
                usize bytes = static_cast<usize>(width) * height * 4;
                mBitmap->pixels = new unsigned char[bytes];
                if (mBitmap->pixels) {
                    memcpy(mBitmap->pixels, pixels, bytes);
                }
            }
        }
        GlfwBitmap::~GlfwBitmap() {
            if (mBitmap) {
                delete[] mBitmap->pixels;
                delete mBitmap;
            }
        }
        u32 GlfwBitmap::GetWidth() const {
            if (mBitmap)
                return mBitmap->width;
            return 0;
        }
        u32 GlfwBitmap::GetHeight() const {
            if (mBitmap)
                return mBitmap->height;
            return 0;
        }
    } // namespace Platform
} // namespace PyroshockStudios
