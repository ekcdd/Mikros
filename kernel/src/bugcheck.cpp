//
// Created by User on 15/02/2021.
//

#include "bugcheck.h"

#include "BasicRenderer.h"

void BugCheck(const char* Message){
    GlobalRenderer->ClearColour = 0x00ff0000;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0;

    GlobalRenderer->Print("Kernel Panic");

    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(Message);

    while(true)
    {
        asm("hlt");
    }
}