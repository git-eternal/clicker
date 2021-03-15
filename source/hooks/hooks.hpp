#pragma once

#include "../includes.hpp"

namespace Hooks
{
	/// <summary>
	/// Mouse hhook definition
	/// </summary>
	inline HHOOK mouse{ nullptr };

	/// <summary>
	/// Keyboard hhook definition
	/// </summary>
	inline HHOOK keyboard{ nullptr };

	///// <summary>
	///// Mouse hook callback
	///// </summary>
	///// <param name="n_code"></param>
	///// <param name="w_param"></param>
	///// <param name="l_param"></param>
	///// <returns></returns>
	//LRESULT CALLBACK MouseCallback(int n_code, WPARAM w_param, LPARAM l_param);

	/// <summary>
	/// Keyboard hook callback
	/// </summary>
	/// <param name="code"></param>
	/// <param name="msg_id"></param>
	/// <param name="l_param"></param>
	/// <returns></returns>
	LRESULT CALLBACK KeyboardCallback(int code, WPARAM msg_id, LPARAM l_param);

	/// <summary>
	/// Init devices callback
	/// </summary>
	[[noreturn]] auto InitDeviceCallbacks() -> void;
}