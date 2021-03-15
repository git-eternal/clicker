#pragma once

#include "../includes.hpp"

#include "init.hpp"

#include "../clicker/clicker.hpp"

#define MENU_FLAGS ImGuiWindowFlags_NoScrollWithMouse \
	| ImGuiWindowFlags_NoResize												  \
	| ImGuiWindowFlags_NoMove														\
	| ImGuiWindowFlags_NoSavedSettings								  \
	| ImGuiWindowFlags_NoScrollbar											\
	| ImGuiWindowFlags_NoTitleBar												\
	| ImGuiWindowFlags_NoCollapse 

#define SetX ImGui::SetCursorPosX
#define SetY ImGui::SetCursorPosY

#define GetX ImGui::GetCursorPosX
#define GetY ImGui::GetCursorPosY

namespace Menu
{
	void MainScreen();

	void Hotkey(int& key, int width, int height);
}