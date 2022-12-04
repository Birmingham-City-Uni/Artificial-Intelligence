#pragma once

namespace input {

	bool InitialzieInput();
	void SetKeyUp(int keycode, bool value);
	bool GetKeyUp(int keycode);
	void SetKeyDown(int keyCode, bool value);
	bool GetKeyDown(int keyCode);
} // namespace Input