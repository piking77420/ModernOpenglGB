#pragma once
#include <Core/CoreEngine.h>



class ThreadPoolDynamic
{
public:



	__forceinline std::thread& operator[](uint32_t index)
	{
		return threads.at(index);
	}

	__forceinline void JoinIfJoinable() 
	{
		for (std::thread& t : threads)
		{
			if (t.joinable())
				t.join();
		}
	};

	__forceinline void Resize(uint32_t size)
	{
		threads.resize(size);
	};

	__forceinline void Clear()
	{
		threads.clear();
	};

	constexpr __forceinline uint32_t GetSize()
	{
		return threads.size();
	}

	ThreadPoolDynamic() = delete;

	ThreadPoolDynamic(uint32_t size)
	{
		Resize(size);
	}

	~ThreadPoolDynamic()
	{
		
	}

private:
	std::vector<std::thread> threads;
};

