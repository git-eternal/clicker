#include "clicker.hpp"

auto Clicker::MouseUp(const MouseClick& clickType) -> void
{
	Sleep(Randomization(clickType) * 2);

	switch (clickType)
	{
		// If we want to left click up
		//
		case MouseClick::Left:
		{
			SendMessage(
				FindWindow(winClass.c_str(), nullptr),
				WM_LBUTTONUP,
				MK_LBUTTON,
				MAKELPARAM(cursorLoc.x, cursorLoc.y)
			);
		}
		break;

		// If we want to right click up
	  //
		case MouseClick::Right:
		{
			SendMessage(
				FindWindow(winClass.c_str(), nullptr),
				WM_RBUTTONUP,
				MK_RBUTTON,
				MAKELPARAM(cursorLoc.x, cursorLoc.y)
			);
		}
		break;
	}
}

auto Clicker::MouseDn(const MouseClick& clickType) -> void
{
	Sleep(Randomization(clickType) * 2);

	switch (clickType)
	{
		// If we want to left click down
		//
		case MouseClick::Left:
		{
			SendMessage(
				FindWindow(winClass.c_str(), nullptr),
				WM_LBUTTONDOWN,
				MK_LBUTTON,
				MAKELPARAM(cursorLoc.x, cursorLoc.y)
			);
		}
		break;

		// If we want to right click down
		//
		case MouseClick::Right:
		{
			SendMessage(
				FindWindow(winClass.c_str(), nullptr),
				WM_RBUTTONDOWN,
				MK_RBUTTON,
				MAKELPARAM(cursorLoc.x, cursorLoc.y)
			);
		}
		break;
	}
}

float Clicker::Randomization(const MouseClick& click_type)
{
	// Very simplistic randomization, but should bypass decent server anti-cheats.
	// This is the only thing I will not spoonfeed. 
	// Make a good randomization yourself!
	//
	return static_cast<float>(Random::GenerateNum(450, 550) / leftCps);
}

[[noreturn]] void Clicker::Thread()
{
	while (true)
	{               
		bool isInMinecraft = GetForegroundWindow() == FindWindowA(winClass.c_str(), nullptr);

		std::this_thread::sleep_for(1ms);

		// Get current cursor position
		//
		GetCursorPos(&Clicker::cursorLoc);

		if (Clicker::leftOn)
		{
			// If they are in minecraft
			//
			if (isInMinecraft)
			{
				// If they press mouse down
				//	
				if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
					Clicker::MouseDn(MouseClick::Left);
			}
		}
	}
}