#include "menu.hpp"

void Menu::MainScreen()
{
  ImGui::SetNextWindowSize(ImVec2(windowSize.X, windowSize.Y));

	ImGui::SetNextWindowPos(ImVec2(0, 0));

	ImGui::Begin("main_window", nullptr, MENU_FLAGS); 
	{	
		ImGui::Text("left cps");

		ImGui::SliderFloat("###leftCps", &Clicker::leftCps, 0.0f, 20.0f, "%.2f");

		ImGui::Checkbox("enable", &Clicker::leftOn);
	}
	ImGui::End();
}
