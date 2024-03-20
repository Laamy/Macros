#include <iostream>

// testing macros for padding classes
#define SCAFFOLD_VAR(type, varName, offset) \
    type Get##varName() const { \
        return *(type*)((uintptr_t)this + offset); \
    } \
    void Set##varName(const type& value) { \
        *(type*)((uintptr_t)this + offset) = value; \
    }

class TempClass {
public: // test variables
    int a;
    float b;
    char c;
    std::string d;
};

class ScaffoldClass {
public: // this is what we normally do it works but its pretty messy and hard to update in large projects
    int a;
    float b;
    char c;
    std::string d; 
};

class ScaffoldClassMain {
public:
    SCAFFOLD_VAR(char, C, 0x8);
};

int main()
{
    TempClass temp{ 1, 2, 'c', "Hello world!"};

    ScaffoldClass* scaffold = reinterpret_cast<ScaffoldClass*>(&temp);

    std::cout << "a: " << scaffold->a << std::endl;
    std::cout << "b: " << scaffold->b << std::endl;
    std::cout << "c: " << scaffold->c << std::endl;
    std::cout << "d: " << scaffold->d << std::endl;

    ScaffoldClassMain* scaffoldMain = reinterpret_cast<ScaffoldClassMain*>(&temp);

    std::cout << "c: " << scaffoldMain->GetC() << std::endl;
    scaffoldMain->SetC('a');
    std::cout << "c: " << scaffold->c << std::endl;
}