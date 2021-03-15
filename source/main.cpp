#include "includes.hpp"

int WINAPI main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  // Initialize clicker thread
  //
  Thread::Create clicker{ Clicker::Thread };

  Menu::Initialize();
  Menu::LoadStyles();
  Menu::BeginLoop();
}