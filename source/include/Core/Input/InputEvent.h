#pragma once
#include<Core/CoreEngine.h>

enum InputEventType
{
    KEYPRESS
	,KEYHOLD
	,KEYRELEASE
    , AXIS

};

enum KeyCode
{
    KEY_None = 0,
    KEY_Tab = 512,
    KEY_LeftArrow,
    KEY_RightArrow,
    KEY_UpArrow,
    KEY_DownArrow,
    KEY_PageUp,
    KEY_PageDown,
    KEY_Home,
    KEY_End,
    KEY_Insert,
    KEY_Delete,
    KEY_Backspace,
    KEY_Space,
    KEY_Enter,
    KEY_Escape,
    KEY_LeftCtrl, KEY_LeftShift, KEY_LeftAlt, KEY_LeftSuper,
    KEY_RightCtrl, KEY_RightShift, KEY_RightAlt, KEY_RightSuper,
    KEY_Menu,
    KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
    KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J,
    KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T,
    KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,
    KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6,
    KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12,
    KEY_Apostrophe,        // '
    KEY_Comma,             // ,
    KEY_Minus,             // -
    KEY_Period,            // .
    KEY_Slash,             // /
    KEY_Semicolon,         // ;
    KEY_Equal,             // =
    KEY_LeftBracket,       // [
    KEY_Backslash,         /* / */
    KEY_RightBracket,      // ]
    KEY_GraveAccent,       // `
    KEY_CapsLock,
    KEY_ScrollLock,
    KEY_NumLock,
    KEY_PrintScreen,
    KEY_Pause,
    KEY_Keypad0, KEY_Keypad1, KEY_Keypad2, KEY_Keypad3, KEY_Keypad4,
    KEY_Keypad5, KEY_Keypad6, KEY_Keypad7, KEY_Keypad8, KEY_Keypad9,
    KEY_KeypadDecimal,
    KEY_KeypadDivide,
    KEY_KeypadMultiply,
    KEY_KeypadSubtract,
    KEY_KeypadAdd,
    KEY_KeypadEnter,
    KEY_KeypadEqual,
    MOUSE_Left, MOUSE_Right, MOUSE_Middle, MOUSE_X1, MOUSE_X2, MOUSE_WheelX, MOUSE_WheelY,
    KEY_COUNT
};

static inline const char* EventTypeToString(InputEventType type)
{
 
    switch (type)
    {
    case KEYPRESS:
        return "KEYPRESS";
        break;
    case KEYHOLD:
        return "KEYHOLD";
        break;
    case KEYRELEASE:
        return "KEYRELEASE";
        break;
    case AXIS:
        return "AXIS";
        break;
    default:
        break;
    }
}



class InputEvent
{
public:

	InputEventType EventType = {};
    KeyCode keycode = KEY_None;
    

    constexpr const std::string ToString() 
    {
        int value = keycode - (KEY_Tab - 1);
        return KeyCodeStrings[value];
    }

    constexpr  InputEvent(KeyCode keycode, InputEventType eventType)
    {
        EventType = eventType;
        this->keycode = keycode;
    }

    constexpr  InputEvent()
    {

    }



private:
   constexpr static inline const char* KeyCodeStrings[] = {
    "KEY_None",
    "KEY_Tab",
    "KEY_LeftArrow",
    "KEY_RightArrow",
    "KEY_UpArrow",
    "KEY_DownArrow",
    "KEY_PageUp",
    "KEY_PageDown",
    "KEY_Home",
    "KEY_End",
    "KEY_Insert",
    "KEY_Delete",
    "KEY_Backspace",
    "KEY_Space",
    "KEY_Enter",
    "KEY_Escape",
    "KEY_LeftCtrl", "KEY_LeftShift", "KEY_LeftAlt", "KEY_LeftSuper",
    "KEY_RightCtrl", "KEY_RightShift", "KEY_RightAlt", "KEY_RightSuper",
    "KEY_Menu",
    "KEY_0", "KEY_1", "KEY_2", "KEY_3", "KEY_4", "KEY_5", "KEY_6", "KEY_7", "KEY_8", "KEY_9",
    "KEY_A", "KEY_B", "KEY_C", "KEY_D", "KEY_E", "KEY_F", "KEY_G", "KEY_H", "KEY_I", "KEY_J",
    "KEY_K", "KEY_L", "KEY_M", "KEY_N", "KEY_O", "KEY_P", "KEY_Q", "KEY_R", "KEY_S", "KEY_T",
    "KEY_U", "KEY_V", "KEY_W", "KEY_X", "KEY_Y", "KEY_Z",
    "KEY_F1", "KEY_F2", "KEY_F3", "KEY_F4", "KEY_F5", "KEY_F6",
    "KEY_F7", "KEY_F8", "KEY_F9", "KEY_F10", "KEY_F11", "KEY_F12",
    "KEY_Apostrophe",        // '
    "KEY_Comma",             // ,
    "KEY_Minus",             // -
    "KEY_Period",            // .
    "KEY_Slash",             // /
    "KEY_Semicolon",         // ;
    "KEY_Equal",             // =
    "KEY_LeftBracket",       // [
    "KEY_Backslash",         // /
    "KEY_RightBracket",      // ]
    "KEY_GraveAccent",       // `
    "KEY_CapsLock",
    "KEY_ScrollLock",
    "KEY_NumLock",
    "KEY_PrintScreen",
    "KEY_Pause",
    "KEY_Keypad0", "KEY_Keypad1", "KEY_Keypad2", "KEY_Keypad3", "KEY_Keypad4",
    "KEY_Keypad5", "KEY_Keypad6", "KEY_Keypad7", "KEY_Keypad8", "KEY_Keypad9",
    "KEY_KeypadDecimal",
    "KEY_KeypadDivide",
    "KEY_KeypadMultiply",
    "KEY_KeypadSubtract",
    "KEY_KeypadAdd",
    "KEY_KeypadEnter",
    "KEY_KeypadEqual",
    "MOUSE_Left", "MOUSE_Right", "MOUSE_Middle", "MOUSE_X1", "MOUSE_X2", "MOUSE_WheelX", "MOUSE_WheelY",
    "KEY_COUNT"
    };
};
