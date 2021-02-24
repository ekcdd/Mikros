//
// Created by User on 16/02/2021.
//

#pragma once
#include <stdint.h>

// Note: this was an enum but the compiler didn't like converting an large enum into an int
//       So, I just made them all defines.

#define KC_UNKNOWN      0 // If set the key pressed (or released) is not supported

#define KC_ESCAPE       1
#define KC_F1           2
#define KC_F2           3
#define KC_F3           4
#define KC_F4           5
#define KC_F5           6
#define KC_F6           7
#define KC_F7           8
#define KC_F8           9
#define KC_F9           10
#define KC_F10          11
#define KC_F11          12
#define KC_F12          13
#define KC_PRINTSCR     14
#define KC_SCROLL       15 // Scroll lock
#define KC_PAUSE        16
#define KC_TILDE        17
// number keys
#define KC_ONE          18
#define KC_TWO          19
#define KC_THREE        20
#define KC_FOUR         21
#define KC_FIVE         22
#define KC_SIX          23
#define KC_SEVEN        24
#define KC_EIGHT        25
#define KC_NINE         26
#define KC_ZERO         27
#define KC_DASH         29
#define KC_EQUALS       30
#define KC_BACKSPACE    31
#define KC_TAB          32
#define KC_Q            33
#define KC_W            34
#define KC_E            35
#define KC_R            36
#define KC_T            37
#define KC_Y            38
#define KC_U            39
#define KC_I            40
#define KC_O            41
#define KC_P            42
#define KC_LBRACKET     43 // Left Bracket [
#define KC_RBRACKET     44 // Right bracket ]
#define KC_BACKSLASH    45
#define KC_CAPSLOCK     46
#define KC_A            47
#define KC_S            48
#define KC_D            49
#define KC_F            50
#define KC_G            51
#define KC_H            52
#define KC_J            53
#define KC_K            54
#define KC_L            55
#define KC_SEMICOLON    56
#define KC_QUOTE        57
#define KC_ENTER        58
#define KC_LSHIFT       59
#define KC_Z            60
#define KC_X            61
#define KC_C            62
#define KC_V            63
#define KC_B            64
#define KC_N            65
#define KC_M            66
#define KC_COMMA        67
#define KC_PERIOD       68
#define KC_FOWARDSLASH  69
#define KC_RSHIFT       70
#define KC_LCTRL        71
#define KC_WIN          72
#define KC_LALT         73
#define KC_SPACE        74
#define KC_RALT         75
#define KC_FUNCTION     76
#define KC_CONTEXT      77
#define KC_RCTRL        78
// arrow keys
#define KC_UP           79
#define KC_DOWN         80
#define KC_LEFT         81
#define KC_RIGHT        82
#define KC_INSERT       83
#define KC_HOME         84
#define KC_PAGEUP       85
#define KC_DEL          86
#define KC_END          87
#define KC_PAGEDOWN     88
#define KC_NUMLOCK      89
// keypad values
#define KC_LPDIVIDE     90
#define KC_KPMULTIPLY   91
#define KC_KPMINUS      92
#define KC_KPSEVEN      93
#define KC_KPEIGHT      94
#define KC_KPNINE       95
#define KC_KPFOUR       96
#define KC_KPFIVE       97
#define KC_KPSIX        98
#define KC_KPONE        99
#define KC_KPTWO        100
#define KC_KPTHREE      101
#define KC_KPENTER      102
#define KC_KPZERO       103
#define KC_KPPERIOD     104
#define KC_KPPLUS       105

#define KC_BACKTICK     106
