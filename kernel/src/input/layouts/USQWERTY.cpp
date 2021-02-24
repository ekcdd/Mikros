//
// Created by User on 15/02/2021.
//

#include "USQWERTY.h"
#include "../keycode.h"


namespace US_QWERTY_Keyboard {

    const int LookupTable[128] {
      0,KC_ESCAPE,KC_ONE,KC_TWO,
      KC_THREE,KC_FOUR,KC_FIVE,KC_SIX,
      KC_SEVEN,KC_EIGHT,KC_NINE,KC_ZERO,
      KC_DASH,KC_EQUALS,KC_BACKSPACE,KC_TAB,
      KC_Q,KC_W,KC_E,KC_R,
      KC_T,KC_Y,KC_U,KC_I,
      KC_O,KC_P,KC_LBRACKET,KC_RBRACKET,
      KC_ENTER,KC_LCTRL,KC_A,KC_S,
      KC_D,KC_F,KC_G,KC_H,
      KC_J,KC_K,KC_L,KC_SEMICOLON,
      KC_QUOTE,KC_BACKTICK,KC_LSHIFT,KC_BACKSLASH,
      KC_Z,KC_X,KC_C,KC_V,
      KC_B,KC_N,KC_M,KC_COMMA,
      KC_PERIOD,KC_FOWARDSLASH,KC_RSHIFT,KC_KPMULTIPLY, /* Multiply on the keypad */
      KC_LALT,KC_SPACE,KC_CAPSLOCK,KC_F1,
      KC_F2,KC_F3,KC_F4,KC_F5,
      KC_F6,KC_F7,KC_F8,KC_F9,
      KC_F10,KC_NUMLOCK,KC_SCROLL,KC_KPSEVEN,
      KC_KPEIGHT,KC_KPNINE,KC_KPMINUS,KC_KPFOUR,
      KC_KPFIVE,KC_KPSIX,KC_KPPLUS,KC_KPONE,
      KC_KPTWO,KC_KPTHREE,KC_KPZERO,KC_KPPERIOD,
      0,0,0,KC_F11,
      KC_F12,0,0,0
    };

    const char ASCIITable[] = {

            0, 0, '1', '2',
            '3', '4', '5', '6',
            '7', '8', '9', '0',
            '-', '=', 0, 0,
            'q', 'w', 'e', 'r',
            't', 'y', 'u', 'i',
            'o', 'p', '[', ']',
            0, 0, 'a', 's',
            'd', 'f', 'g', 'h',
            'j', 'k', 'l', ';',
            '\'', '`', 0, '\\',
            'z', 'x', 'c', 'v',
            'b', 'n', 'm', ',',
            '.', '/', 0, '*',
            0, ' ', 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0
    };

    const char ASCIITableUpper[] = {

            0, 0, '!', '@',
            '#', '$', '%', '^',
            '&', '*', '(', ')',
            '_', '+', 0, 0,
            'Q', 'W', 'E', 'R',
            'T', 'Y', 'U', 'I',
            'O', 'P', '{', '}',
            0, 0, 'A', 'S',
            'D', 'F', 'G', 'H',
            'J', 'K', 'L', ':',
            '<', '~', 0, '|',
            'Z', 'X', 'C', 'V',
            'B', 'N', 'M', '<',
            '>', '?', 0, '*',
            0, ' ', 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, '7',
            '8', '9', '-', '4',
            '5', '6', '+', '1',
            '2', '3', '0', '.',
            0, 0, 0, 0,
            0
    };

    char Translate(uint8_t scancode, bool uppercase, bool numLock) {
        if (scancode > 0x80) return 0; // Allow everything that is a keydown, ignore keyup for now.

        if (uppercase) {
            return ASCIITableUpper[scancode];
        }
        if (numLock && scancode > 0x46) {
            return ASCIITableUpper[scancode];
        }
        return ASCIITable[scancode];;
    }

    KeyState CreateKeyState(uint8_t scancode, bool uppercase, bool numLock)
    {
        KeyState state;
        uint8_t  sc = scancode;
        bool pressed = true;
        if (scancode > 0x80)
        {
            sc -= 0x80;
            pressed = false;
        }
        state.Code = LookupTable[sc];
        state.Pressed = pressed;
        state.NumLock = numLock;
        // set the other states else where
        state.KeyValue = Translate(scancode,uppercase,numLock);
        return state;
    }

}