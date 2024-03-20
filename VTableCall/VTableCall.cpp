#include <iostream>

template <typename Ret, typename... Args>
Ret CallFunc(void* func, Args... args)
{
	return ((Ret(*)(Args...))func)(args...);
}

int main()
{
	// CallFunc works like so
	// CallFunc<ReturnType, ArgTypes...>(void* functionPointer, ArgValues...);

	// an example is shown below
	// CallFunc<int, int, int>(functionPointer, 1, 2); // calls a function that takes two ints and returns an int
}