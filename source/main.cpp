#include "includes.hpp"

int WINAPI main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  Menu::Initialize();
  Menu::LoadStyles();
  Menu::BeginLoop();
}