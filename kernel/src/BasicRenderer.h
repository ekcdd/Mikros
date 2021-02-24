#pragma once
#include "math.h"
#include "../include/video.h"
#include <stdint.h>

#define DEFAULT_COLOUR  0xffffffff
#define COLOUR_GREEN    0x0000ff00
#define COLOUR_RED      0xffff0000
#define COLOUR_ORANGE   0xffff6600

class BasicRenderer{
public:
    BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font);
    Point CursorPosition;
    Framebuffer* TargetFramebuffer;
    PSF1_FONT* PSF1_Font;
    unsigned int Colour;
    unsigned int ClearColour;
    uint32_t MouseCursorBuffer[16 * 16];
    uint32_t MouseCursorBufferAfter[16 * 16];
    void Print(const char* str);
    void Print(const uint32_t colour,const char *str);
    void PutChar(char chr, unsigned int xOff, unsigned int yOff);
    void PutChar(char chr);
    void PutPix(uint32_t x, uint32_t y, uint32_t colour);
    uint32_t GetPix(uint32_t x, uint32_t y);
    void ClearChar();
    void Clear();
    void Next();

    void DrawOverlayMouseCursor(uint8_t* mouseCursor, Point position, uint32_t colour);
    void ClearMouseCursor(uint8_t* mouseCursor, Point position);
    bool MouseDrawn;
};

extern BasicRenderer* GlobalRenderer;