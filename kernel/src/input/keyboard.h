
#pragma once
#include <stdint.h>
#include "keycode.h"

#define PS2_KP_OFFSET 0x80 // PS/2 offset for key presses

enum class KeyboardLayout {
    NONE = 0,
    US_QWERTY = 1
};
static const char *Keyboard_Layouts_STRING[] = {
        "None", "US qwerty",
};

struct KeyState {
    bool LShift; // left Shift
    bool RShift; // Right shift
    bool CapsLocks;
    bool NumLock;
    bool Pressed;
    uint16_t Code;
    char KeyValue;
};


void HandleKeyboard(uint8_t scancode);
void InitialiseKeyboard();
void SetKeyboardLayout(KeyboardLayout layout);

bool RegisterKBHook(void (*callback)(KeyState));
bool UnregisterKBHook();

KeyboardLayout GetCurrentKBLayout();