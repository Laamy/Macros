#pragma once

#include "Vector2.h"

#pragma region macro code stuff

// fake fields
#define PROXY_VARIABLE(type, name, offset) \
        ProxyVariable<type> name## = ProxyVariable<type>(reinterpret_cast<type*>((uintptr_t)this->VTable + offset))

#define CREATE_PROXY(type, name, args) \
        type##* name## = new type##(args)

template<typename T>
class ProxyVariable {
private:
    T* target;

public:
    ProxyVariable(T* target) : target(target) {} // init/constructor

    ProxyVariable& operator=(const T& value) {
        *target = value;

        return *this; // allow chain assignments
    }

    operator T() const& {
        return *target;
    }
};

class ClassVTable {
public:
    uintptr_t** _v; // actual class vtable pointer
};

// some scaffolding mmeory thing for shared methods
class ClassProxy
{
public:
    ClassVTable* VTable;

public:
    ClassProxy(void* target) : VTable(reinterpret_cast<ClassVTable*>(target)) {}

    // some methods for vtable scaffolding variable
    uintptr_t* GetFunc(int index) {
        return VTable->_v[index];
    }

    void LogInfo() {
        std::cout << "Addr: " << std::hex << VTable << std::endl;
    }
};

#pragma endregion

class UIControl : public ClassProxy
{
public:
    using ClassProxy::ClassProxy; // inherit proxy class arguments

    PROXY_VARIABLE(Vector2<float>, Offset, 0x38);
    PROXY_VARIABLE(Vector2<float>, Size, 0x40);
    PROXY_VARIABLE(float, Opacity, 0x58);
    PROXY_VARIABLE(Vector2<float>, Position, 0x78);
};