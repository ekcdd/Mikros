//
// Created by User on 14/02/2021.
//

#pragma once
#include <stddef.h>
#include <stdint.h>

class BitMapper {
public:
    size_t Size;
    uint8_t* Buffer;
    bool operator[](uint64_t index);
    bool Set(uint64_t index, bool value);
};
