#pragma once
#include "Core/CoreEngine.h"

template<uint32_t P, uint32_t C, class T >
class TheardCP
{
public:


	__forceinline void EndProduction()
	{
		m_endProduction = true;
	}

	void WaitForEveryProducersExpect(std::thread::id id)
	{
		for (size_t i = 0; i < producers.size(); i++)
		{
			if(id != producers[i].get_id() && producers[i].joinable())
			{
				producers[i].join();
			}
		}
	}

	__forceinline bool GetProductionState()
	{
		return m_endProduction;
	}

	__forceinline bool EndProcess()
	{
		return resources.empty() && m_endProduction;
	}
	__forceinline void Reset()
	{
		for (size_t i = 0; i < resources.size(); i++)
		{
			resources.pop();
		}
		m_endProduction = false;
	}

	__forceinline void ProducersPushRessoures(T value)
	{
		std::lock_guard<std::mutex> lock(resourcesMutex);
		resources.push(value);
		consumersCv.notify_one();
	}
	__forceinline T ConsumersGetValue()
	{
		T value = resources.front();
		resources.pop();
		return value;
	}


	std::thread& GetConsumer(uint32_t index)
	{
		return consumers[index];
	}

	std::thread& GetProducer(uint32_t index)
	{
		return producers[index];
	}

	constexpr uint32_t  GetConsumerSize(uint32_t index)
	{
		return consumers.size();
	}

	constexpr uint32_t  GetProducerSize()
	{
		return producers.size();
	}

	__forceinline void JoinIfJoinableConsumers()
	{
		for (std::thread& t : consumers)
		{
			if (t.joinable())
			{
				t.join();
			}
		}
		
	}

	__forceinline void JoinIfJoinableProducers()
	{
		
		for (std::thread& t : producers)
		{
			if (t.joinable())
			{
				t.join();
			}
		}
	}


	std::thread* GetAsleepProducer()
	{
		std::thread* result = nullptr;

		for (size_t i = 0; i < producers.size(); i++)
		{
			if (!producers[i].joinable())
			{
				result = &producers[i];
				break; 
			}
		}

		return result;
	}




	std::mutex resourcesMutex;
	std::queue<T> resources;
	std::array<std::thread, P> producers;
	std::array<std::thread, C> consumers;

	std::condition_variable consumersCv;


private:

	std::mutex m_cvMutex;
	bool m_endProduction = false;
	
};