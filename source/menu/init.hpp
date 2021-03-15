#pragma once

#include "../includes.hpp"

#include "menu.hpp"

namespace Menu
{
	// Data
	//
	inline ID3D11Device* g_pd3dDevice{ nullptr };
	inline ID3D11DeviceContext* g_pd3dDeviceContext{ nullptr };
	inline IDXGISwapChain* g_pSwapChain{ nullptr };
	inline ID3D11RenderTargetView* g_mainRenderTargetView{ nullptr };

	// Forward declarations of helper functions
	//
	bool CreateDeviceD3D(HWND hWnd);
	void CleanupDeviceD3D();
	void CreateRenderTarget();
	void CleanupRenderTarget();
	LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// Create application window
  // 
	inline WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, Menu::WndProc,
		0L, 0L, GetModuleHandle(NULL),
		NULL, NULL, NULL, NULL, _T(" "), NULL
	};

	inline HWND hwnd{ nullptr };  
	
	inline ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	inline COORD windowSize{ 218, 157 };

	int Initialize();
	void LoadStyles();
	void BeginLoop();
	void Cleanup();
}