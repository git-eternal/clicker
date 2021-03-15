#pragma once

#include "../includes.hpp"
#include "../utils/utils.hpp"

#define ms std::chrono::milliseconds

namespace Clicker
{
	const std::string winClass{ "LWJGL" };

	/// <summary>
	/// Mouse side enum (might add right clicker later so this is here for now)
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
	/// Store left key bind
	/// </summary>
	inline int leftBind{ 0 };

	/// <summary>
	/// Cursor location
	/// </summary>
	inline POINT cursorLoc{ 0, 0 };

	/// <summary>
	/// Check if the user is in the minecraft window
	/// </summary>
	inline bool isInMinecraft{ false };

	/// <summary>
	/// If they want to delete file on exit
	/// </summary>
	inline bool deleteFile{ false };

	/// <summary>
	/// Check if big or small endian
	/// </summary>
	/// <returns></returns>
	inline bool isBigEndian()
	{
		union 
		{ 
			uint32_t i; char c[4];
		} 
		bInt = { 0x01020304 };

		return bInt.c[0] == 1;
	}

	/// <summary>
	/// Check whether if the key is down or not
	/// </summary>
	/// <param name="v_key"></param>
	/// <returns></returns>
	inline bool isKeyDown(int vKey)
	{
		short keyState = GetAsyncKeyState(vKey);

		// *should* always be 16
		//
		ULONGLONG shortBits = sizeof(short) * 8; 

		std::bitset<16> keyStateBits(keyState);

		if (isBigEndian())
			keyStateBits.flip();

		bool keyIsDown = keyStateBits.test(0);
		bool pressedPost = keyStateBits.test(shortBits - 1);

		return (keyIsDown || pressedPost);
	}
}