#ifdef PYRO_PLATFORM_WINDOWING
#pragma once

#include <PyroCommon/Types.hpp>
#include <PyroPlatform/Forward.hpp>
#include <PyroPlatform/Window/IWindow.hpp>

using namespace PyroshockStudios;
using namespace PyroshockStudios::Platform;
using namespace PyroshockStudios::Types;

class WindowStub : public IWindow {
public:
    // Stubbed state variables
    Size size{ 1280, 720 };
    Point position{ 100, 200 };
    Point cursorPos{ 0, 0 };
    f32 opacity = 1.0f;
    WindowState windowState = WindowState::Normal;
    eastl::string title = "Stub Window";
    Size framebufferSize{ 1280, 720 };
    f32 dpiScale = 1.0f;
    FSize contentScale{ 1.0f, 1.0f };
    CursorMode cursorMode = CursorMode::Normal;
    bool stickyKeys = false;
    bool stickyMouse = false;
    bool rawMouse = false;
    bool visible = true;
    bool shouldCloseFlag = false;
    bool focused = true;
    bool hovered = false;
    bool passthrough = false;
    bool topMost = false;
    IWindowInput* inputHandler = nullptr;
    NativeHandle nativeWindow = 1234;
    NativeHandle nativeInstance = 5678;

    // IWindow overrides
    Size GetSize() const override { return size; }
    Point GetPosition() const override { return position; }
    Point GetCursorPosition() const override { return cursorPos; }
    f32 GetOpacity() const override { return opacity; }

    void SetSize(Size s) override { size = s; }
    void SetPosition(Point p) override { position = p; }
    void SetCursorPosition(Point p) override { cursorPos = p; }
    void SetCursorVisible(bool) override {}
    void SetCursorLockedToWindow(bool) override {}
    void SetOpacity(f32 o) override { opacity = o; }

    void SetCursor(ICursor*) override {}
    void SetFullscreen(IMonitor*) override {}
    void SetWindowState(WindowState state) override { windowState = state; }
    WindowState GetWindowState() const override { return windowState; }

    eastl::string GetTitle() const override { return title; }
    void SetTitle(eastl::string_view t) override { title = t; }

    Size GetFramebufferSize() const override { return framebufferSize; }
    f32 GetDPIScale() const override { return dpiScale; }
    FSize GetContentScale() const override { return contentScale; }

    CursorMode GetCursorMode() const override { return cursorMode; }
    bool IsStickyKeysEnabled() const override { return stickyKeys; }
    bool IsStickyMouseButtonsEnabled() const override { return stickyMouse; }
    bool IsRawMouseMotionEnabled() const override { return rawMouse; }
    void SetCursorMode(CursorMode mode) override { cursorMode = mode; }
    void SetStickyKeysEnabled(bool enabled) override { stickyKeys = enabled; }
    void SetStickyMouseButtonsEnabled(bool enabled) override { stickyMouse = enabled; }
    void SetRawMouseMotionEnabled(bool enabled) override { rawMouse = enabled; }

    void Show() override { visible = true; }
    void Hide() override { visible = false; }

    void Close() override { shouldCloseFlag = true; }
    void CancelClose() override { shouldCloseFlag = false; }
    void Focus() override { focused = true; }
    void SetPassthrough(bool b) override { passthrough = b; }
    void SetTopMost(bool b) override { topMost = b; }
    void RequestAttention() override {}

    bool IsVisible() const override { return visible; }
    bool ShouldClose() const override { return shouldCloseFlag; }
    bool IsFocused() const override { return focused; }
    bool IsHovered() const override { return hovered; }

    IWindowInput* GetInputHandler() override { return inputHandler; }

    NativeHandle GetNativeWindow() const override { return nativeWindow; }
    NativeHandle GetNativeInstance() const override { return nativeInstance; }
};
#endif