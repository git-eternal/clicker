#include "menu.hpp"

void Menu::Hotkey(int& key, int width, int height)
{
	static auto b_get = false;

	static std::string sz_text = ("click to bind");

	if (ImGui::Button(sz_text.c_str(), ImVec2(static_cast<float>(width), static_cast<float>(height))))
		b_get = true;

	if (b_get)
	{
		for (auto i = 1; i < 256; i++)
		{
			if (GetAsyncKeyState(i) & 0x8000)
			{
				if (i != 12)
				{
					key = i == VK_ESCAPE ? 0 : i;
					b_get = false;
				}
			}
		}
		sz_text = ("press a key");
	}

	else if (!b_get && key == 0)
		sz_text = ("click to bind");

	else if (!b_get && key != 0)
		sz_text = ("bound to ") + Utils::ToLower(Utils::GetKeyName(key));
}

void Menu::TopBar()
{
	ImGui::Text("test clicker"); ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(30, 30, 39, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(30, 30, 39, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(30, 30, 39, 0));

	SetX(GetX() + 93);

	ImGui::PushFont(exitIcon);

	if (ImGui::Button("a", ImVec2(30, 23)))
		std::exit(EXIT_SUCCESS);

	ImGui::PopFont();

	ImGui::PopStyleColor(3);

	ImGui::Separator();
}

void Menu::MainScreen()
{
  ImGui::SetNextWindowSize(ImVec2(windowSize.X, windowSize.Y));

	ImGui::SetNextWindowPos(ImVec2(0, 0));

	ImGui::Begin("main_window", nullptr, MENU_FLAGS); 
	{	
		TopBar();

		ImGui::Text("left cps");

		ImGui::PushItemWidth(203);

		ImGui::SliderFloat("###leftCps", &Clicker::leftCps, 0.0f, 20.0f, "%.1f");

		Hotkey(Clicker::leftBind, 99, 25); ImGui::SameLine();
		
		SetX(GetX() - 4);

		if (ImGui::Button(Clicker::leftOn ? "toggle off" : "toggle on", ImVec2(100, 25)))
			Clicker::leftOn = !Clicker::leftOn;

		ImGui::Checkbox("delete file", &Clicker::deleteFile);
	}
	ImGui::End();
}