#pragma once

class FuncHook {
public:
	virtual bool Initialize() = 0;
};

// include hooks here
#include "Hooks/KeymapHook.h"
#include "Hooks/SplashHook.h"

void InitHooks() {
	// initialize hooks here
	static FuncHook* hooks[] = {
		// include hooks here
        &KeymapHook::Get(),
        &SplashHook::Get()
	};

    for (std::size_t i = 0; i < std::size(hooks); ++i)
    {
        if (not hooks[i]->Initialize())
        {
            //error handling
            std::cout << "Failed to initialize hook " << i << std::endl;
        }
    }
}