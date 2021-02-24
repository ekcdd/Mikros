
#include "kernelUtil.h"

Point MousePosition;
Point OldMousePosition;

void KeyboardUpdate(KeyState state);
void MouseUpdate(MouseInfo info);

extern "C" void _start(BootInfo* bootInfo){


    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;

    RegisterKBHook(KeyboardUpdate);
    RegisterMouseHook(MouseUpdate);
    GlobalRenderer->Print(COLOUR_GREEN, "info: Kernel Initialized Successfully");
    GlobalRenderer->Next();

 //   int* test = (int*)0x80000000000;
 //   *test = 2;

    while(true) {
       ProcessMousePacket();
       asm("hlt");
    }
}

void KeyboardUpdate(KeyState state)
{
    if (state.Code == KC_SPACE && state.Pressed) {
        GlobalRenderer->PutChar(' ');
        return;
    }
    if (state.Code == KC_BACKSPACE && state.Pressed) {
        GlobalRenderer->ClearChar();
        return;
    }
    if (state.Code == KC_ENTER && state.Pressed)
    {
        GlobalRenderer->Next();
        return;
    }
    if (state.KeyValue != '\0') {
        GlobalRenderer->PutChar(state.KeyValue);
    }
}
void MouseUpdate(MouseInfo info) {

    OldMousePosition = MousePosition;
    MousePosition = info.Location;
    if (MousePosition.X < 0) MousePosition.X = 0;
    if (MousePosition.X > GlobalRenderer->TargetFramebuffer->Width-1) MousePosition.X = GlobalRenderer->TargetFramebuffer->Width-1;

    if (MousePosition.Y < 0) MousePosition.Y = 0;
    if (MousePosition.Y > GlobalRenderer->TargetFramebuffer->Height-1) MousePosition.Y = GlobalRenderer->TargetFramebuffer->Height-1;

    // OldMousePosition = MousePosition;
    //MousePosition = info.Location;

    GlobalRenderer->ClearMouseCursor(MousePointer, OldMousePosition);
    GlobalRenderer->DrawOverlayMouseCursor(MousePointer, MousePosition, 0xffffffff);

    switch (info.ButtonClicked) {
        case MouseButton::None:
        case MouseButton::Left:
        case MouseButton::Right:
            break;
    }

}