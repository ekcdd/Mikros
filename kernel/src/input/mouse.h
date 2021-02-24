#pragma once


#include "../IO.h"
#include "../math.h"
#include "../BasicRenderer.h"
#include "../math.h"


extern uint8_t MousePointer[];

void InitPS2Mouse();
void HandlePS2Mouse(uint8_t data);
void ProcessMousePacket();

enum class MouseButton {
    None = 0,
    Left,
    Middle,
    Right,
    Fourth,
    Fifth
};

struct MouseInfo {
    Point Location;
    MouseButton ButtonClicked;
    bool XOverflow;
    bool YOverflow;
};

bool RegisterMouseHook(void (*callback)(MouseInfo));
bool UnregisterMouseHook();