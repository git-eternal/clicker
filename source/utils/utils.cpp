#include "utils.hpp"

std::string Utils::ToLower(std::string str)
{
	std::transform(
		str.begin(),
		str.end(),
		str.begin(), static_cast<int(*)(int)>(::tolower));

	// Return the lowered string
	//
	return str;
}

std::string Utils::GetKeyName(const int id)
{
	// Credits to biscuit! (github.com/b1scoito)
	//
	static std::unordered_map<int, std::string> key_names = 
	{
		{ 0, "None" },
		{ VK_LBUTTON, "Mouse 1" },
		{ VK_RBUTTON, "Mouse 2" },
		{ VK_MBUTTON, "Mouse 3" },
		{ VK_XBUTTON1, "Mouse 4" },
		{ VK_XBUTTON2, "Mouse 5" },
		{ VK_BACK, "Back" },
		{ VK_TAB, "Tab" },
		{ VK_CLEAR, "Clear" },
		{ VK_RETURN, "Enter" },
		{ VK_SHIFT, "Shift" },
		{ VK_CONTROL, "Ctrl" },
		{ VK_MENU, "Alt" },
		{ VK_PAUSE, "Pause" },
		{ VK_CAPITAL, "Caps Lock" },
		{ VK_ESCAPE, "Escape" },
		{ VK_SPACE, "Space" },
		{ VK_PRIOR, "Page Up" },
		{ VK_NEXT, "Page Down" },
		{ VK_END, "End" },
		{ VK_HOME, "Home" },
		{ VK_LEFT, "Left Key" },
		{ VK_UP, "Up Key" },
		{ VK_RIGHT, "Right Key" },
		{ VK_DOWN, "Down Key" },
		{ VK_SELECT, "Select" },
		{ VK_PRINT, "Print Screen" },
		{ VK_INSERT, "Insert" },
		{ VK_DELETE, "Delete" },
		{ VK_HELP, "Help" },
		{ VK_SLEEP, "Sleep" },
		{ VK_MULTIPLY, "*" },
		{ VK_ADD, "+" },
		{ VK_SUBTRACT, "-" },
		{ VK_DECIMAL, "." },
		{ VK_DIVIDE, "/" },
		{ VK_NUMLOCK, "Num Lock" },
		{ VK_SCROLL, "Scroll" },
		{ VK_LSHIFT, "Left Shift" },
		{ VK_RSHIFT, "Right Shift" },
		{ VK_LCONTROL, "Left Ctrl" },
		{ VK_RCONTROL, "Right Ctrl" },
		{ VK_LMENU, "Left Alt" },
		{ VK_RMENU, "Right Alt" },
	};

	if (id >= 0x30 && id <= 0x5A)
		return std::string(1, (char)id);

	if (id >= 0x60 && id <= 0x69)
		return "Num " + std::to_string(id - 0x60);

	if (id >= 0x70 && id <= 0x87)
		return "F" + std::to_string((id - 0x70) + 1);

	return key_names[id];
}

void Utils::SelfDelete()
{
	TCHAR szModuleName[MAX_PATH];
	TCHAR szCmd[2 * MAX_PATH];

	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	GetModuleFileName(NULL, szModuleName, MAX_PATH);

	StringCbPrintf(
		szCmd, 2 *
		MAX_PATH,
		("cmd.exe /C ping 1.1.1.1 -n 1 -w 3000 > Nul & Del /f /q \"%s\""),
		szModuleName);

	CreateProcess(NULL, szCmd,
		NULL,
		NULL,
		FALSE,
		CREATE_NO_WINDOW,
		NULL, NULL, &si, &pi);

	CloseHandle(pi.hThread); CloseHandle(pi.hProcess);
}

void Utils::CenterWindow()
{
	RECT rectClient, rectWindow;

	GetClientRect(Menu::hwnd, &rectClient);
	GetWindowRect(Menu::hwnd, &rectWindow);

	int posX{}, posY{};

	posX = GetSystemMetrics(SM_CXSCREEN) / 2 - (rectWindow.right - rectWindow.left) / 2,
	posY = GetSystemMetrics(SM_CYSCREEN) / 2 - (rectWindow.bottom - rectWindow.top) / 2,

	MoveWindow(Menu::hwnd, posX, posY, 
		rectClient.right - rectClient.left,
		rectClient.bottom - rectClient.top, TRUE);
}

void Utils::EnableMenuDrag()
{
	if (ImGui::IsMouseClicked(0))
	{
		POINT cursorPosition{};
		RECT  menuPosition{};

		// Get the cursor position
		//
		GetCursorPos(&cursorPosition);
		
		// Get the window size
		//
		GetWindowRect(Menu::hwnd, &menuPosition);

		// Calculate difference between cursor position and window position 
		//
		Menu::movementX = cursorPosition.x - menuPosition.left;
		Menu::movementY = cursorPosition.y - menuPosition.top;
	}

	// If they are within the bounds of the top bar and are dragging mouse
	//
	if ((Menu::movementX >= 0 && Menu::movementY <= 40) && ImGui::IsMouseDragging(0))
	{
		POINT cursor_position; GetCursorPos(&cursor_position);

		SetWindowPos(Menu::hwnd, nullptr,
			cursor_position.x - Menu::movementX,
			cursor_position.y - Menu::movementY,
			0, 0, SWP_NOSIZE
		);
	}
}
