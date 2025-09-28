#ifdef PYRO_PLATFORM_WINDOWING
#include <gtest/gtest.h>

#include <PyroPlatform/Window/Input/CharInputEvent.hpp>
#include <PyroPlatform/Window/Input/CursorPositionEvent.hpp>
#include <PyroPlatform/Window/Input/CursorScrollEvent.hpp>
#include <PyroPlatform/Window/Input/InputEvent.hpp>
#include <PyroPlatform/Window/Input/InputEventDispatcher.hpp>
#include <PyroPlatform/Window/Input/KeyEvent.hpp>
#include <PyroPlatform/Window/Input/MouseEvent.hpp>
#include <PyroPlatform/Window/Input/WindowResizeEvent.hpp>

#include "Stubs/WindowStub.hpp"

using namespace PyroshockStudios;
using namespace PyroshockStudios::Platform;

WindowStub gWindowStub = {};

// -------- WindowResizeEvent --------
TEST(WindowResizeEventTest, StoresValuesCorrectly) {
    WindowResizeEvent event(gWindowStub, 1024, 768);
    EXPECT_EQ(event.kWidth, 1024);
    EXPECT_EQ(event.kHeight, 768);
}

TEST(WindowResizeEventTest, ToString) {
    WindowResizeEvent event(gWindowStub, 800, 600);
    EXPECT_STREQ(event.ToString().c_str(), "Window Resize: (800, 600)");
}

// -------- CharInputEvent --------
TEST(CharInputEventTest, StoresCharacter) {
    CharInputEvent event(gWindowStub, U'A');
    EXPECT_EQ(event.kUnicode, U'A');
}

// -------- CharInputEvent --------
TEST(CharInputEventTest, StoresCharacterUTF16) {
    CharInputEvent event(gWindowStub, 0x5BB6); // kanji for "house"
    EXPECT_EQ(event.kUnicode, 0x5BB6);
}


// -------- MouseEvent --------
TEST(MouseEventTest, CursorPress) {
    MouseEvent event(gWindowStub, MouseButton::Button4, {}, false);
    EXPECT_EQ(event.kButton, MouseButton::Button4);
}


// -------- CursorPositionEvent --------
TEST(CursorPositionEventTest, StoresPosition) {
    CursorPositionEvent event(gWindowStub, 300.5, 400.25);
    EXPECT_DOUBLE_EQ(event.kX, 300.5);
    EXPECT_DOUBLE_EQ(event.kY, 400.25);
}

// -------- CursorScrollEvent --------
TEST(CursorScrollEventTest, StoresScrollOffsets) {
    CursorScrollEvent event(gWindowStub, 0.0, -1.5);
    EXPECT_DOUBLE_EQ(event.kX, 0.0);
    EXPECT_DOUBLE_EQ(event.kY, -1.5);
}

// -------- KeyEvent --------
TEST(KeyEventTest, StoresKeyInfo) {
    KeyEvent event(gWindowStub, KeyCode::KeyD, 52, InputModifiers::Control | InputModifiers::Alt, true, true);
    EXPECT_EQ(event.kKey, KeyCode::KeyD);
    EXPECT_EQ(event.kModifiers, InputModifiers::Control | InputModifiers::Alt);
    EXPECT_EQ(event.kbDown, true);
    EXPECT_EQ(event.kScanCode, 52);
    EXPECT_EQ(event.kbRepeating, true);
}

// -------- InputEventDispatcher --------
TEST(InputEventDispatcherTest, CanAddAndDispatch) {
    InputEventDispatcher<KeyEvent> dispatcher{};

    bool called = false;
    dispatcher.Bind({ [&](const KeyEvent& evt) {
        called = true;
        EXPECT_EQ(evt.kKey, KeyCode::KeyD);
    } });

    KeyEvent keyEvent(gWindowStub, KeyCode::KeyD, 0, {}, true, false);
    dispatcher.Dispatch(keyEvent);
    EXPECT_TRUE(called);
}


// -------- InputEventDispatcher --------
TEST(InputEventDispatcherTest, CanRemoveAndDispatch) {
    InputEventDispatcher<KeyEvent> dispatcher{};

    bool called = false;
    InputEventHandler<KeyEvent> handler = { [&](const KeyEvent& evt) {
        called = true;
    } };

    InputEventHandler<KeyEvent> two = handler;

    dispatcher.Bind(handler);
    dispatcher.Unbind(handler);

    KeyEvent keyEvent(gWindowStub, KeyCode::KeyD, 0, {}, true, false);
    dispatcher.Dispatch(keyEvent);
    EXPECT_FALSE(called);
}



// -------- InputEventDispatcher --------
TEST(InputEventDispatcherTest, MultipleBinds) {
    InputEventDispatcher<KeyEvent> dispatcher{};

    bool called1 = false;
    InputEventHandler<KeyEvent> handler1 = { [&](const KeyEvent& evt) {
        called1 = true;
    } };
    bool called2 = false;
    InputEventHandler<KeyEvent> handler2 = { [&](const KeyEvent& evt) {
        called2 = true;
    } };


    dispatcher.Bind(handler1);
    dispatcher.Bind(handler2);

    KeyEvent keyEvent(gWindowStub, KeyCode::KeyD, 0, {}, true, false);
    dispatcher.Dispatch(keyEvent);
    EXPECT_TRUE(called1);
    EXPECT_TRUE(called2);
}

// -------- InputEventDispatcher --------
TEST(InputEventDispatcherTest, MultipleBindThenUnbind) {
    InputEventDispatcher<KeyEvent> dispatcher{};

    bool called1 = false;
    InputEventHandler<KeyEvent> handler1 = { [&](const KeyEvent& evt) {
        called1 = true;
    } };
    bool called2 = false;
    InputEventHandler<KeyEvent> handler2 = { [&](const KeyEvent& evt) {
        called2 = true;
    } };
    bool called3 = false;
    InputEventHandler<KeyEvent> handler3 = { [&](const KeyEvent& evt) {
        called3 = true;
    } };


    dispatcher.Bind(handler1);
    dispatcher.Bind(handler2);
    dispatcher.Bind(handler3);

    dispatcher.Unbind(handler2);

    KeyEvent keyEvent(gWindowStub, KeyCode::KeyD, 0, {}, true, false);
    dispatcher.Dispatch(keyEvent);
    EXPECT_TRUE(called1);
    EXPECT_FALSE(called2);
    EXPECT_TRUE(called3);
}

#endif