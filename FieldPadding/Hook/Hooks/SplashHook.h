#pragma once

void* __o__DrawSplash;

#include "../../SDK/UIControl.h"

//SplashTextRenderer::render(
// SplashTextRenderer *this, 
// MinecraftUIRenderContext *, 
// IClientInstance *, 
// UIControl *, 
// int, 
// RectangleArea *)
__int64 SplashTextRenderDetour(
    __int64 _this,
    __int64 ctx,
    __int64 ci,
    UIControl* control,
    __int64 a5,
    __int64 rect
)
{
    // some debug values to test it
    //control->Position = { 10, 10 };
    //control->Opacity = 0.5f;

    //return 3.141; // idk lol

    control->Opacity(3.141);
    std::cout << control->Opacity() << std::endl;

    return CallFunc<__int64, __int64, __int64, __int64, UIControl*, __int64, __int64>(
        __o__DrawSplash,
        _this,
        ctx,
        ci,
        control,
        a5,
        rect
    );
}

#include <thread>

class SplashHook : public FuncHook
{
public:
    bool Initialize() override
    {
        uintptr_t splashAddr = findOffset("48 8B C4 55 53 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? ? ? 70 A8 ? ? 78 98 44 ? ? 40 88 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B E1", "SplashRender");

        return HookFunction(
            (void*)splashAddr,
            &SplashTextRenderDetour,
            &__o__DrawSplash
        );
    }

    static SplashHook& Get()
    {
        static SplashHook instance;
        return instance;
    }
};