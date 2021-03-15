#pragma once

#include "../includes.hpp"

#define FIFO    THREAD_PRIORITY_TIME_CRITICAL
#define DEFAULT THREAD_PRIORITY_HIGHEST

namespace Thread
{
	class Create
	{
	private:
		using Handle = std::thread::native_handle_type; 

		// Store our thread
		std::thread mThread{ nullptr }; 

	public:
		Create(std::function<void()> func, const bool& fifo = true) : mThread{ std::thread(func) }
		{
			if (fifo)
				// Set to time critical for fifo capability
				//
				SetThreadPriority(GetHandle(), FIFO); 
			else
				// Default thread priority (set to high)
				//
				SetThreadPriority(GetHandle(), DEFAULT); 
		}

		~Create()
		{
			if (mThread.joinable()) mThread.join();
		}

		Handle GetHandle() 
		{ 
			return mThread.native_handle();
		}
	};
}

namespace Utils
{
	std::string ToLower(std::string str);
	std::string GetKeyName(const int id);
  void SelfDelete();
	void CenterWindow();
}

namespace Random
{
	/// <summary>
	/// Initialize our mersenne twister with a random seed based on the clock (once at system startup)
	/// </summary>
	inline std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	__forceinline int GenerateNum(int min, int max)
	{
		// Create the distributiion
		//
		std::uniform_int_distribution die{ min, max };

		// Generate a random number from our global generator
		//
		return die(Random::mersenne);
	}
}