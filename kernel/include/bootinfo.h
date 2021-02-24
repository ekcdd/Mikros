//
// Created by User on 20/02/2021.
//

#pragma once

#ifdef __cplusplus

struct BootInfo {
    Framebuffer* framebuffer;
    PSF1_FONT* psf1_Font;
    EFI_MEMORY_DESCRIPTOR* mMap;
    uint64_t mMapSize;
    uint64_t mMapDescSize;
    ACPI::RSDP2* rsdp;
};
#else
typedef struct {
    Framebuffer* framebuffer;
    PSF1_FONT* psf1_Font;
    EFI_MEMORY_DESCRIPTOR* mMap;
    UINTN mMapSize;
    UINTN mMapDescSize;
    void* rsdp;
} BootInfo;

#endif