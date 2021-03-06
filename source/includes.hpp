#pragma once

// Exclude rarely-used stuff from Windows headers
//
#define WIN32_LEAN_AND_MEAN

// Use std::min and std::max instead of min() and max()
//
#define NOMINMAX 

#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_win32.h"
#include "../imgui/backends/imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>
#include <thread>
#include <chrono>
#include <random>
#include <ctime>
#include <functional>
#include <iostream>
#include <algorithm>
#include <mutex>
#include <strsafe.h>
#include <bitset>

using namespace std::chrono_literals;

#include "menu/init.hpp"
#include "menu/fonts/fonts.hpp"