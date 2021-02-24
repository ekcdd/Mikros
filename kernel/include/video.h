//
//  Mikros
//

#pragma once
#include <stddef.h>

// PSF v1 structures and definitions

#define PSF1_MAGIC0 0x36
#define PSF1_MAGIC1 0x04



#ifdef __cplusplus
struct Framebuffer{
	void* BaseAddress;
	size_t BufferSize;
	unsigned int Width;
	unsigned int Height;
	unsigned int PixelsPerScanLine;
};
struct PSF1_HEADER {
    unsigned char magic[2];
    unsigned char mode;
    unsigned char charsize;
};

struct PSF1_FONT {
    PSF1_HEADER *psf1_Header;
    void *glyphBuffer;
};



#else

typedef struct {
    void* BaseAddress;
    size_t BufferSize;
    unsigned int Width;
    unsigned int Height;
    unsigned int PixelsPerScanLine;
} Framebuffer;

typedef struct {
    unsigned char magic[2];
    unsigned char mode;
    unsigned char charsize;
} PSF1_HEADER;

typedef struct {
    PSF1_HEADER* psf1_Header;
    void* glyphBuffer;
} PSF1_FONT;

#endif

