#include "hooks.hpp"

LRESULT Hooks::KeyboardCallback(int code, WPARAM msg_id, LPARAM l_param)
{
	KBDLLHOOKSTRUCT* hook_struct{ reinterpret_cast<KBDLLHOOKSTRUCT*>(l_param) };

	if (code == HC_ACTION && msg_id == WM_KEYDOWN)
	{
		if (Clicker::isInMinecraft)
		{
			if (!hook_struct->flags)
			{
				if (hook_struct->vkCode == Clicker::leftBind)
				{
					Clicker::leftOn = !Clicker::leftOn;
				}

				//if (hook_struct->vkCode == right_key_bind)
				//{
				//	if (right_custom_key_binds)
				//		right_on = !right_on;
				//}
			}
		}
	}

	return CallNextHookEx(keyboard, code, msg_id, l_param);
}

auto Hooks::InitDeviceCallbacks() -> void
{
	// Our keyboard callback
	keyboard = SetWindowsHookEx(
		WH_KEYBOARD_LL,
		KeyboardCallback,
		nullptr, NULL);

	MSG message_struct{ nullptr };

	while (!GetMessage(&message_struct, nullptr, 0, 0))
	{
		TranslateMessage(&message_struct);
		DispatchMessage(&message_struct);
	}

	UnhookWindowsHookEx(keyboard);
}