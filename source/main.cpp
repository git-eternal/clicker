#include "includes.hpp"
#include "hooks/hooks.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  std::atexit([]() -> void 
  {
    if (Clicker::deleteFile)
    {
      Utils::SelfDelete();
    }
  });

  // Initialize callbacks 
  //
  Thread::Create hooks{ Hooks::InitDeviceCallbacks };

  // Initialize clicker thread
  //
  Thread::Create clicker{ Clicker::Thread };

  Menu::Initialize();
  Menu::LoadStyles();
  Menu::BeginLoop();
}