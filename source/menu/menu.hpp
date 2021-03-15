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

#define set_x ImGui::SetCursorPosX
#define set_y ImGui::SetCursorPosY

#define get_x ImGui::GetCursorPosX
#define get_y ImGui::GetCursorPosY

namespace Menu
{
	void MainScreen();
}