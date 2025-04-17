#pragma once

#include "../src/Queue.tpp"

template<typename T>
void producerFunction(Queue<T> &q)
{
	for (T i = 0; i < 5; ++i)
	{
		q.Push(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

template<typename T>
void consumerFunction(Queue<T> &q)
{
	for (T i = 0; i < 5; ++i)
	{
		T val = q.PopWithTimeout(100);
		EXPECT_EQ(val, i);
	}
}