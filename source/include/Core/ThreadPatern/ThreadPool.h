#pragma once
#include "Core/CoreEngine.h"

template<uint32_t T>
class ThreadPool
{
public:

	std::thread& operator[](uint32_t index)
	{
		return threads[index];
	}

	constexpr __forceinline uint32_t GetSize()
	{
		return T;
	}

	__forceinline void JoinIfJoinable()
	{
		for (size_t i = 0; i < T; i++)
		{
			if (threads[i].joinable())
				threads[i].join();
		}
	}

private:
	std::array<std::thread,T> threads;
};

