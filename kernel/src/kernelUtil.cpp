#include "kernelUtil.h"
#include "gdt/gdt.h"
#include "interrupts/IDT.h"
#include "interrupts/interrupts.h"
#include "IO.h"

KernelInfo kernelInfo;

void PrepareMemory(BootInfo* bootInfo){
    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

    GlobalAllocator = PageFrameAllocator();
    GlobalAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1;

    GlobalAllocator.LockPages(&_KernelStart, kernelPages);

    PageTable* PML4 = (PageTable*)GlobalAllocator.RequestPage();
    memset(PML4, 0, 0x1000);

    g_PageTableManager = PageTableManager(PML4);

    for (uint64_t t = 0; t < GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize); t+= 0x1000){
        g_PageTableManager.MapMemory((void*)t, (void*)t);
    }

    uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize + 0x1000;
    GlobalAllocator.LockPages((void*)fbBase, fbSize/ 0x1000 + 1);
    for (uint64_t t = fbBase; t < fbBase + fbSize; t += 4096){
        g_PageTableManager.MapMemory((void*)t, (void*)t);
    }

    asm ("mov %0, %%cr3" : : "r" (PML4));

    kernelInfo.pageTableManager = &g_PageTableManager;
}

IDTR idtr;
void SetIDTGate(void* handler, uint8_t entryOffset, uint8_t type_attr, uint8_t selector){

    IDTDescEntry* interrupt = (IDTDescEntry*)(idtr.Offset + entryOffset * sizeof(IDTDescEntry));
    interrupt->SetOffset((uint64_t)handler);
    interrupt->type_attr = type_attr;
    interrupt->selector = selector;
}

void PrepareInterrupts(){
    idtr.Limit = 0x0FFF;
    idtr.Offset = (uint64_t)GlobalAllocator.RequestPage();

    SetIDTGate((void*)PageFault_Handler, 0xE, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)DoubleFault_Handler, 0x8, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)GPFault_Handler, 0xD, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)KeyboardInt_Handler, 0x21, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)MouseInt_Handler, 0x2C, IDT_TA_InterruptGate, 0x08);

    asm ("lidt %0" : : "m" (idtr));

    RemapPIC();
}

void PrepareACPI(BootInfo* bootInfo){
   // GlobalRenderer->Print(DEFAULT_COLOUR,"Initialising ACPI...");
    ACPI::SDTHeader* xsdt = (ACPI::SDTHeader*)(bootInfo->rsdp->XSDTAddress);

    ACPI::MCFGHeader* mcfg = (ACPI::MCFGHeader*)ACPI::FindTable(xsdt, (char*)"MCFG");

    if (mcfg == nullptr)
    {
        GlobalRenderer->Print(COLOUR_ORANGE,"Warn");
        GlobalRenderer->Next();
        GlobalRenderer->Print(COLOUR_ORANGE,"No MCFG detected, PCI devices may not get detected");
        GlobalRenderer->Next();
        return;

    }

    GlobalRenderer->Print(COLOUR_GREEN,"OK");
    GlobalRenderer->Next();
    GlobalRenderer->Print(DEFAULT_COLOUR,"PCI Devices:");
    GlobalRenderer->Next();
    PCI::EnumeratePCI(mcfg);
}

BasicRenderer r = BasicRenderer(NULL, NULL);
KernelInfo InitializeKernel(BootInfo* bootInfo){

    r = BasicRenderer(bootInfo->framebuffer, bootInfo->psf1_Font);
    GlobalRenderer = &r;
    PrepareMemory(bootInfo);
    memset(bootInfo->framebuffer->BaseAddress, 0, bootInfo->framebuffer->BufferSize);

    GlobalRenderer->Print(DEFAULT_COLOUR,"Mikros Operating System");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Version 0.1");
    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(DEFAULT_COLOUR,"Loading GDT... ");

    GDTDescriptor gdtDescriptor;
    gdtDescriptor.Size = sizeof(GDT) - 1;
    gdtDescriptor.Offset = (uint64_t)&DefaultGDT;
    LoadGDT(&gdtDescriptor);
    GlobalRenderer->Print(COLOUR_GREEN,"OK");
    GlobalRenderer->Next();

    GlobalRenderer->Print(DEFAULT_COLOUR,"Setting up interrupts... ");

    PrepareInterrupts();

    GlobalRenderer->Print(COLOUR_GREEN,"OK");
    GlobalRenderer->Next();

    GlobalRenderer->Print(DEFAULT_COLOUR,"Setting up PS/2 devices... ");
    InitPS2Mouse();
    InitialiseKeyboard();
    SetKeyboardLayout(KeyboardLayout::US_QWERTY);
    GlobalRenderer->Print(COLOUR_GREEN,"OK");
    GlobalRenderer->Next();

    GlobalRenderer->Print(DEFAULT_COLOUR,"Setting up ACPI... ");
    PrepareACPI(bootInfo);

    GlobalRenderer->Print(DEFAULT_COLOUR,"Preparing PIC controller... ");
    outb(PIC1_DATA, 0b11111001);
    outb(PIC2_DATA, 0b11101111);
    asm ("sti");
    GlobalRenderer->Print(COLOUR_GREEN,"OK");
    GlobalRenderer->Next();

    return kernelInfo;
}
