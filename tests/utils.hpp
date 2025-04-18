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

inline void pushingMain(Queue<int> &q)
{
	q.Push(1);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	q.Push(2);
	q.Push(3);
	q.Push(4);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	q.Push(5);
}

inline void popingMain(Queue<int> &q)
{
	EXPECT_EQ(q.Pop(), 1);
	EXPECT_EQ(q.Pop(), 3);
	EXPECT_EQ(q.Pop(), 4);
	EXPECT_EQ(q.Pop(), 5);
}

inline void pushing(Queue<int> &q)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // Wait for 100ms
	q.Push(2);
}

inline void poping(Queue<int> &q)
{
	int x = q.Pop();
}
