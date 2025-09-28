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

#include <EASTL/functional.h>
#include <EASTL/vector.h>

namespace PyroshockStudios {
    inline namespace Platform {
        enum struct KeyCode : i32 {
            Space = 32,
            Apostrophe = 39,
            Comma = 44,
            Minus = 45,
            Period = 46,
            Slash = 47,

            Key0 = 48,
            Key1 = 49,
            Key2 = 50,
            Key3 = 51,
            Key4 = 52,
            Key5 = 53,
            Key6 = 54,
            Key7 = 55,
            Key8 = 56,
            Key9 = 57,

            Semicolon = 59,
            Equal = 61,

            KeyA = 65,
            KeyB = 66,
            KeyC = 67,
            KeyD = 68,
            KeyE = 69,
            KeyF = 70,
            KeyG = 71,
            KeyH = 72,
            KeyI = 73,
            KeyJ = 74,
            KeyK = 75,
            KeyL = 76,
            KeyM = 77,
            KeyN = 78,
            KeyO = 79,
            KeyP = 80,
            KeyQ = 81,
            KeyR = 82,
            KeyS = 83,
            KeyT = 84,
            KeyU = 85,
            KeyV = 86,
            KeyW = 87,
            KeyX = 88,
            KeyY = 89,
            KeyZ = 90,

            LeftBracket = 91,
            Backslash = 92,
            RightBracket = 93,
            GraveAccent = 96,

            World1 = 161,
            World2 = 162,

            Escape = 256,
            Enter = 257,
            Tab = 258,
            Backspace = 259,
            Insert = 260,
            Delete = 261,
            Right = 262,
            Left = 263,
            Down = 264,
            Up = 265,
            PageUp = 266,
            PageDown = 267,
            Home = 268,
            End = 269,

            CapsLock = 280,
            ScrollLock = 281,
            NumLock = 282,
            PrintScreen = 283,
            Pause = 284,

            F1 = 290,
            F2 = 291,
            F3 = 292,
            F4 = 293,
            F5 = 294,
            F6 = 295,
            F7 = 296,
            F8 = 297,
            F9 = 298,
            F10 = 299,
            F11 = 300,
            F12 = 301,
            F13 = 302,
            F14 = 303,
            F15 = 304,
            F16 = 305,
            F17 = 306,
            F18 = 307,
            F19 = 308,
            F20 = 309,
            F21 = 310,
            F22 = 311,
            F23 = 312,
            F24 = 313,
            F25 = 314,

            Kp0 = 320,
            Kp1 = 321,
            Kp2 = 322,
            Kp3 = 323,
            Kp4 = 324,
            Kp5 = 325,
            Kp6 = 326,
            Kp7 = 327,
            Kp8 = 328,
            Kp9 = 329,
            KpDecimal = 330,
            KpDivide = 331,
            KpMultiply = 332,
            KpSubtract = 333,
            KpAdd = 334,
            KpEnter = 335,
            KpEqual = 336,

            LeftShift = 340,
            LeftControl = 341,
            LeftAlt = 342,
            LeftSuper = 343,
            RightShift = 344,
            RightControl = 345,
            RightAlt = 346,
            RightSuper = 347,
            Menu = 348,

            Last = 348
        };
        enum struct MouseButton : i32 {
            Button1 = 0,
            Button2 = 1,
            Button3 = 2,
            Button4 = 3,
            Button5 = 4,
            Button6 = 5,
            Button7 = 6,
            Button8 = 7,

            Left = Button1,
            Right = Button2,
            Middle = Button3,

            Last = Button8
        };

        struct InputModifiers {
            using Flags = u32;
            enum Bits : Flags {
                Shift = 0x0001,
                Control = 0x0002,
                Alt = 0x0004,
                Super = 0x0008,
                CapsLock = 0x0010,
                NumLock = 0x0020
            };
        };
    } // namespace Platform
} // namespace PyroshockStudios