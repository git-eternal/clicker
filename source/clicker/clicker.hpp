#pragma once

#include "../includes.hpp"
#include "../utils/utils.hpp"

#define ms std::chrono::milliseconds

namespace Clicker
{
	const std::string winClass{ "LWJGL" };

	/// <summary>
	/// Mouse side enum
  /// </summary>
	enum class MouseClick : int
	{
		Left, Right
	};

	/// <summary>
	/// Mouse button up
	/// </summary>
	/// <param name="click_type"></param>
	/// <returns>void</returns>
	auto MouseUp(const MouseClick& clickType) -> void;

	/// <summary>
	/// Mouse button down
	/// </summary>
	/// <param name="click_type"></param>
	/// <returns>void</returns>
	auto MouseDn(const MouseClick& clickType) -> void;

	/// <summary>
	/// Apply randomization to the algorithm
	/// </summary>
	/// <param name="click_type"></param>
	/// <returns>void</returns>
	static float Randomization(const MouseClick& clickType);

	[[noreturn]] void Thread();

	/// <summary>
	/// Store left CPS
	/// </summary>
	inline float leftCps{ 5 };

	/// <summary>
	/// Store left clicker state 
	/// </summary>
	inline bool leftOn{ false };

	/// <summary>
	/// Cursor location
	/// </summary>
	inline POINT cursorLoc{ 0, 0 };
}