//
// Created by User on 15/02/2021.
//

#pragma once
#include <stdint.h>
#include "../keyboard.h"

namespace US_QWERTY_Keyboard {

    namespace SpecialKeys {
        const int LeftShift = 0x2A;
        const int RightShift = 0x36;
        const int Enter = 0x1C;
        const int BackSpace = 0x0E;
        const int Spacebar = 0x39;
        const int CapsLock = 0x3a;
        const int NumLock = 0x45;
        const int Tab = 0x0F;
        const int LeftCtrl = 0x1D;
        const int RightCtrl = 0x36;
        const int FKey_1 = 0x3B;
        const int FKey_2 = 0x3C;
        const int FKey_3 = 0x3D;
        const int FKey_4 = 0x3E;
        const int FKey_5 = 0x3F;
        const int FKey_6 = 0x40;
        const int FKey_7 = 0x41;
        const int FKey_8 = 0x41;
        const int FKey_9 = 0x42;
        const int FKey_10 = 0x44;
        const int FKey_11 = 0x45;
        const int FKey_12 = 0x46;
    };


extern const char ASCIITable[];
extern const char ASCIITableUpper[];

KeyState CreateKeyState(uint8_t scancode, bool uppercase, bool numLock);

char Translate(uint8_t scancode, bool uppercase,bool numLock);

}
