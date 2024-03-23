#pragma once

#include "Vector2.h"

#define GENERATE_ACCESSOR(type, name, offset) \
    type name##() { \
        return *reinterpret_cast<type*>(reinterpret_cast<char*>(this) + offset); \
    } \
    void name##(type new_##name) { \
        *reinterpret_cast<type*>(reinterpret_cast<char*>(this) + offset) = new_##name; \
    }

class UIControl
{
public:
	GENERATE_ACCESSOR(Vector2<float>, Offset, 0x38);
	//GENERATE_ACCESSOR(char[16], ControlName, 0x18); actualyl I'll do this method manually later
	GENERATE_ACCESSOR(Vector2<float>, Size, 0x40);
	GENERATE_ACCESSOR(float, Opacity, 0x58);
	GENERATE_ACCESSOR(Vector2<float>, Position, 0x78);
	GENERATE_ACCESSOR(UIControl*, ChildrenRef, 0x90);
	GENERATE_ACCESSOR(UIControl*, Parent, 0x98);
};