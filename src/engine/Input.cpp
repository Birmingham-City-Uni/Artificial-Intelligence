#include "Input.h"
#include <vector>
#include <iostream>

namespace input {
	namespace {
		extern std::vector<bool> g_KeyDown{};
		extern std::vector<bool> g_KeyUp{};
	 }
	
	bool InitialzieInput()
	{
		g_KeyDown.assign(512, false);
		g_KeyUp.assign(512, false);

#ifdef LOGGING
		std::cout << "Input Initialized!\n";
#endif // LOGGING
		return true;
	}
	
	void SetKeyUp(int keycode, bool value)
	{
		g_KeyUp[keycode] = value;
	}

	bool GetKeyUp(int keycode)
	{
		if (keycode > 0 && keycode < 512) {
			return g_KeyUp[keycode];
		}
		return false;
	}

	void SetKeyDown(int keycode, bool value)
	{
		g_KeyDown[keycode] = value;
	}

	bool GetKeyDown(int keycode)
	{
		if (keycode > 0 && keycode < 512) {
			return g_KeyDown[keycode];
		}
		return false;
	}
} // namespace Input