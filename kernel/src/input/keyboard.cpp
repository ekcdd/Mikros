#include "keyboard.h"
#include "layouts/layouts.h"
#include "../IO.h"
#include "../BasicRenderer.h"

void PushKeyboardState(KeyState state);


void HandleUSQWERTY(uint8_t scancode);

void (*keyboard_hook)(KeyState);

bool isLeftShiftPressed;
bool isRightShiftPressed;
bool isCapsLockPressed;
bool isNumLockEnabled;

bool keyboard_initialised;

bool specialKey_wait = false; // on PS/2 keyboard 0xe0 (or 0xe1?) means you have to wait for the next scancode to come through.
int keyWaitCount  = 0; // number of bytes read so far
int keyWaitTotal = 0; // Number of keys to wait for before setting specialKey_wait to false
uint8_t  keyBuf[4];

KeyboardLayout currentLayout = KeyboardLayout::NONE;

KeyboardLayout GetCurrentKBLayout()
{
    return currentLayout;
}
void InitialiseKeyboard()
{
    if (keyboard_initialised)
    {
        GlobalRenderer->Print(COLOUR_RED, "error: cannot re-initialise keyboard driver");
        GlobalRenderer->Next();
        return;
    }
    keyboard_initialised = true;
    isNumLockEnabled = false;
    isCapsLockPressed = false;
    isLeftShiftPressed = false;
    isRightShiftPressed = false;
    //todo: set the LEDs to off, maybe do a flicker to acknowledge the keyboard has been initialised.
}

void SetKeyboardLayout(KeyboardLayout layout)
{
    if (!keyboard_initialised)
    {
        GlobalRenderer->Print(COLOUR_RED,"error: cannot set keyboard layout on uninitialised keyboard driver");
        GlobalRenderer->Next();
        return;
    }
    currentLayout = layout;
}

void HandleKeyboard(uint8_t scancode){

    if (!keyboard_initialised)
    {
        GlobalRenderer->Print(COLOUR_RED,"error: keyboard driver not initialised");
        GlobalRenderer->Next();
        return;
    }

    switch (currentLayout)
    {
        case KeyboardLayout::US_QWERTY:
            HandleUSQWERTY(scancode);
            break;
        default:
            GlobalRenderer->Print(COLOUR_ORANGE,"warning: no keyboard layout selected, input cannot be processed");
            GlobalRenderer->Next();
    }
}

void HandleUSQWERTY(uint8_t scancode)
{
    if (scancode == 0xe0)
    {
        specialKey_wait = true;
        keyWaitCount = 1;
        keyWaitTotal = 0;
        return;
    }
    if (scancode == 0xe1) {
        specialKey_wait = true;
        keyWaitCount = 2;
        keyWaitTotal = 0;
        return;
    }
    if (specialKey_wait)
    {

    }
    switch (scancode) {
        case US_QWERTY_Keyboard::SpecialKeys::LeftShift:
            isLeftShiftPressed = true;
            break;
        case US_QWERTY_Keyboard::SpecialKeys::LeftShift + PS2_KP_OFFSET:
            isLeftShiftPressed = false;
            break;
        case US_QWERTY_Keyboard::SpecialKeys::RightShift:
            isRightShiftPressed = true;
            break;
        case US_QWERTY_Keyboard::SpecialKeys::RightShift + PS2_KP_OFFSET:
            isRightShiftPressed = false;
            break;
        case US_QWERTY_Keyboard::SpecialKeys::CapsLock:
            isCapsLockPressed = !isCapsLockPressed;
            break;
        case US_QWERTY_Keyboard::SpecialKeys::NumLock:
            isNumLockEnabled = !isNumLockEnabled;
            break;
    }
    KeyState state = US_QWERTY_Keyboard::CreateKeyState(scancode, isLeftShiftPressed | isRightShiftPressed | isCapsLockPressed,isNumLockEnabled);
    state.CapsLocks = isCapsLockPressed;
    state.NumLock = isNumLockEnabled;
    state.LShift = isLeftShiftPressed;
    state.RShift = isRightShiftPressed;
    PushKeyboardState(state);
}

void PushKeyboardState(KeyState state) {
    if (keyboard_hook != nullptr)
    {
        keyboard_hook(state);
    }
}
bool RegisterKBHook(void (*callback)(KeyState)) {
    if (keyboard_hook != nullptr)
    {
        GlobalRenderer->Print(COLOUR_ORANGE,"warning: Keyboard::RegisterKBHook(): hook has already been set");
        GlobalRenderer->Next();
        return false;
    }
    keyboard_hook = callback;
    return true;
}
bool UnregisterKBHook() {
    if (keyboard_hook == nullptr)
    {
        GlobalRenderer->Print(COLOUR_ORANGE,"warning: Keyboard::UnregisterKBHook(): hook has not been set");
        GlobalRenderer->Next();
        return false;
    }
    keyboard_hook = nullptr;
    return true;
}