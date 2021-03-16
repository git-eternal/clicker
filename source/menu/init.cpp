#include "init.hpp"

bool Menu::CreateDeviceD3D(HWND hWnd)
{
  // Setup swap chain
  //
  DXGI_SWAP_CHAIN_DESC sd;
  ZeroMemory(&sd, sizeof(sd));
  sd.BufferCount = 2;
  sd.BufferDesc.Width = 0;
  sd.BufferDesc.Height = 0;
  sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  sd.BufferDesc.RefreshRate.Numerator = 60;
  sd.BufferDesc.RefreshRate.Denominator = 1;
  sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.OutputWindow = hWnd;
  sd.SampleDesc.Count = 1;
  sd.SampleDesc.Quality = 0;
  sd.Windowed = TRUE;
  sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

  UINT createDeviceFlags = 0;
  //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
  D3D_FEATURE_LEVEL featureLevel;
  const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

  if (D3D11CreateDeviceAndSwapChain(
    NULL,  D3D_DRIVER_TYPE_HARDWARE, NULL, 
    createDeviceFlags, featureLevelArray, 2, 
    D3D11_SDK_VERSION, &sd, &g_pSwapChain, 
    &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
    return false;

  CreateRenderTarget();
  return true;
}

void Menu::CleanupDeviceD3D()
{
  CleanupRenderTarget();

  if (g_pSwapChain)
  {
    g_pSwapChain->Release(); 
    g_pSwapChain = nullptr;
  }

  if (g_pd3dDeviceContext)
  {
    g_pd3dDeviceContext->Release();
    g_pd3dDeviceContext = nullptr;
  }

  if (g_pd3dDevice)
  {
    g_pd3dDevice->Release(); 
    g_pd3dDevice = nullptr;
  }
}

void Menu::CreateRenderTarget()
{
  ID3D11Texture2D* pBackBuffer;

  g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

  g_pd3dDevice->CreateRenderTargetView(
    pBackBuffer, NULL, &g_mainRenderTargetView);

  pBackBuffer->Release();
}

void Menu::CleanupRenderTarget()
{
  if (g_mainRenderTargetView) 
  {
    g_mainRenderTargetView->Release(); 
    g_mainRenderTargetView = nullptr;
  }
}

// Forward declare message handler from imgui_impl_win32.cpp
//
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
//
LRESULT WINAPI Menu::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
    return true;

  switch (msg)
  {
    case WM_SIZE:
    {
      if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
      {
        CleanupRenderTarget();

        g_pSwapChain->ResizeBuffers(0,
          (UINT)LOWORD(lParam),
          (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);

        CreateRenderTarget();
      }
      return 0;
    }

    case WM_SYSCOMMAND:
    {
      // Disable ALT application menu
      //
      if ((wParam & 0xfff0) == SC_KEYMENU)
        return 0;

      break;
    }

    case WM_DESTROY:
    {
      ::PostQuitMessage(0);
      return 0;
    }
  }

  return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

int Menu::Initialize()
{
  // ImGui_ImplWin32_EnableDpiAwareness();

  ::RegisterClassEx(&wc);

  hwnd = ::CreateWindow(
    wc.lpszClassName, _T(" "),
    WS_POPUP, 100, 100, windowSize.X, windowSize.Y,
    NULL, NULL, wc.hInstance, NULL
  );

  // Initialize Direct3D
  //
  if (!Menu::CreateDeviceD3D(hwnd))
  {
    Menu::CleanupDeviceD3D();
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);
    return 1;
  }

  // Show the window
  //
  ::ShowWindow(hwnd, SW_SHOW);
  ::UpdateWindow(hwnd);
}

void Menu::LoadStyles()
{
  // Setup ImGui context
  //
  IMGUI_CHECKVERSION();

  ImGui::CreateContext();

  ImGuiIO& io = ImGui::GetIO(); (void)io;

  // No imgui ini file
  //
  io.IniFilename = nullptr;

  // Setup Dear ImGui style
  //
  ImGui::StyleColorsDark();

  // Add firaBold font (default)
  //
  Menu::firaBold = io.Fonts->AddFontFromMemoryCompressedTTF
  (
    Fonts::firaBold, 20, 20.0f, NULL, io.Fonts->GetGlyphRangesDefault()
  );

  // Add exitIcon font
  //
  Menu::exitIcon = io.Fonts->AddFontFromMemoryCompressedTTF
  (
    Fonts::exitIcon, 16, 16.0f, NULL, io.Fonts->GetGlyphRangesDefault()
  );
}

void Menu::BeginLoop()
{
  // Setup Platform/Renderer backends
  //
  ImGui_ImplWin32_Init(Menu::hwnd);
  ImGui_ImplDX11_Init(Menu::g_pd3dDevice, Menu::g_pd3dDeviceContext);

  Utils::CenterWindow();

  // Main loop
  //
  MSG msg{};
  ZeroMemory(&msg, sizeof(msg));

  while (msg.message != WM_QUIT)
  {
    if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
    {
      ::TranslateMessage(&msg);
      ::DispatchMessage(&msg);
      continue;
    }

    // Start the ImGui frame
    //
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();

    // So we can drag our WS_POPUP window around
    //
    Utils::EnableMenuDrag(); 

    // Render main menu
    //
    Menu::MainScreen();

    // Rendering
    //
    ImGui::Render();

    const float clear_color_with_alpha[4] =
    {
      Menu::clear_color.x * Menu::clear_color.w,
      Menu::clear_color.y * Menu::clear_color.w,
      Menu::clear_color.z * Menu::clear_color.w,
      Menu::clear_color.w
    };

    Menu::g_pd3dDeviceContext->OMSetRenderTargets(1, &Menu::g_mainRenderTargetView, NULL);

    Menu::g_pd3dDeviceContext->ClearRenderTargetView(
      Menu::g_mainRenderTargetView, clear_color_with_alpha);

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    Menu::g_pSwapChain->Present(1, 0); // Present with vsync
    //g_pSwapChain->Present(0, 0); // Present without vsync (lots of CPU usage)
  }

  Menu::Cleanup();
}

void Menu::Cleanup()
{
  // Cleanup
  //
  ImGui_ImplDX11_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();

  Menu::CleanupDeviceD3D();
  ::DestroyWindow(Menu::hwnd);
  ::UnregisterClass(Menu::wc.lpszClassName, Menu::wc.hInstance);
}