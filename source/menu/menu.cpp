#include "menu.hpp"

void Menu::MainScreen()
{
  ImGui::SetNextWindowSize(ImVec2(windowSize.X, windowSize.Y));

	ImGui::SetNextWindowPos(ImVec2(0, 0));

	ImGui::Begin("main_window", nullptr, MENU_FLAGS); 
	{	
		ImGui::Text("hi");
	}
	ImGui::End();
}
