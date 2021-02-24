#include "pci.h"
#include "cstr.h"

namespace PCI{

    void EnumerateFunction(uint64_t deviceAddress, uint64_t function){
        uint64_t offset = function << 12;

        uint64_t functionAddress = deviceAddress + offset;
        g_PageTableManager.MapMemory((void*)functionAddress, (void*)functionAddress);

        PCIDeviceHeader* pciDeviceHeader = (PCIDeviceHeader*)functionAddress;
        if (pciDeviceHeader == nullptr) {
            GlobalRenderer->Print("warning: enum function ");
            GlobalRenderer->Print(to_string(function));
            GlobalRenderer->Print(" at ");
            GlobalRenderer->Print(to_hstring(deviceAddress));
            GlobalRenderer->Print(" is null, skipping");
            GlobalRenderer->Next();
            return;

        }
        if (pciDeviceHeader->DeviceID == 0) return;
        if (pciDeviceHeader->DeviceID == 0xFFFF) return;
        GlobalRenderer->Print("     ");
        GlobalRenderer->Print(GetVendorName(pciDeviceHeader->VendorID));
        GlobalRenderer->Print(" / ");
        GlobalRenderer->Print(GetDeviceName(pciDeviceHeader->VendorID, pciDeviceHeader->DeviceID));
        GlobalRenderer->Print(" / ");
        GlobalRenderer->Print(DeviceClasses[pciDeviceHeader->Class]);
        GlobalRenderer->Print(" / ");
        GlobalRenderer->Print(GetSubclassName(pciDeviceHeader->Class, pciDeviceHeader->Subclass));
        GlobalRenderer->Print(" / ");
        GlobalRenderer->Print(GetProgIFName(pciDeviceHeader->Class, pciDeviceHeader->Subclass, pciDeviceHeader->ProgIF));
        GlobalRenderer->Next();


    }

    void EnumerateDevice(uint64_t busAddress, uint64_t device){
        uint64_t offset = device << 15;

        uint64_t deviceAddress = busAddress + offset;
        g_PageTableManager.MapMemory((void*)deviceAddress, (void*)deviceAddress);

        PCIDeviceHeader* pciDeviceHeader = (PCIDeviceHeader*)deviceAddress;
        if (pciDeviceHeader == nullptr) {
            GlobalRenderer->Print("warning: device enum: device ");
            GlobalRenderer->Print(to_string(device));
            GlobalRenderer->Print(" at ");
            GlobalRenderer->Print(to_hstring(busAddress));
            GlobalRenderer->Print(" is null, skipping");
            GlobalRenderer->Next();
            return;

        }
        if (pciDeviceHeader->DeviceID == 0) return;
        if (pciDeviceHeader->DeviceID == 0xFFFF) return;

        for (uint64_t function = 0; function < 8; function++){
            EnumerateFunction(deviceAddress, function);
        }
    }

    void EnumerateBus(uint64_t baseAddress, uint64_t bus){
        GlobalRenderer->Print("test 3");

        uint64_t offset = bus << 20;

        uint64_t busAddress = baseAddress + offset;

        g_PageTableManager.MapMemory((void*)busAddress, (void*)busAddress);
        GlobalRenderer->Print("test 4");
        PCIDeviceHeader* pciDeviceHeader = (PCIDeviceHeader*)busAddress;
        GlobalRenderer->Print("test 5");
        if (pciDeviceHeader == nullptr) {
            GlobalRenderer->Print("warning: Bus ");
            GlobalRenderer->Print(to_string(bus));
            GlobalRenderer->Print(" at ");
            GlobalRenderer->Print(to_hstring(baseAddress));
            GlobalRenderer->Print(" is null, skipping");
            GlobalRenderer->Next();
            return;

        }
        if (pciDeviceHeader->DeviceID == 0) return;
        if (pciDeviceHeader->DeviceID == 0xFFFF) return;
        GlobalRenderer->Print("test 6");
        for (uint64_t device = 0; device < 32; device++){
            EnumerateDevice(busAddress, device);
        }
    }

    void EnumeratePCI(ACPI::MCFGHeader* mcfg){
        uint32_t entries = ((mcfg->Header.Length) - sizeof(ACPI::MCFGHeader)) / sizeof(ACPI::DeviceConfig);
        GlobalRenderer->Print("debug: PCI entries: ");
        GlobalRenderer->Print(to_hstring(entries));
        GlobalRenderer->Next();
        for (int t = 0; t < entries; t++){
            ACPI::DeviceConfig* newDeviceConfig = (ACPI::DeviceConfig*)((uint64_t)mcfg + sizeof(ACPI::MCFGHeader) + (sizeof(ACPI::DeviceConfig) * t));
            GlobalRenderer->Print("debug: device config at ");
            GlobalRenderer->Print(to_hstring((uint32_t)t));
            if (newDeviceConfig == nullptr)
            {
                GlobalRenderer->Print( " is null");

            }
            else {
                GlobalRenderer->Print( " is NOT null");
            }
            GlobalRenderer->Next();
            GlobalRenderer->Print("test ");
            for (uint64_t bus = newDeviceConfig->StartBus; bus < newDeviceConfig->EndBus; bus++){
                GlobalRenderer->Print("test2 ");
                EnumerateBus(newDeviceConfig->BaseAddress, bus);
            }
        }
    }

}