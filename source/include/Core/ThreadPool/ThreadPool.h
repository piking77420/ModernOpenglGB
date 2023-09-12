#pragma once
#include<Core/CoreEngine.h>

enum class ThreadType
{
	OPENGL,PHYSICS,COLLISION
};



class ThreadPool
{
public:


	ThreadPool()
	{
		for (std::thread& t : m_poolThreads)
		{
			//t.detach();
		}
	}

	[[nodiscard]]
	inline std::thread& GetThread(ThreadType type)
	{
		return m_poolThreads[static_cast<int>(type)];
	}

	[[nodiscard]]
	inline const std::thread& GetThread(ThreadType type) const 
	{
		return m_poolThreads[static_cast<int>(type)];
	}
	  

private:
	std::array<std::thread, 3> m_poolThreads;
};

