#include <gtest/gtest.h>
//#include "../src/Queue.tpp"
#include "utils.hpp"

TEST(QueueTest, Subject_main)
{
	Queue<int> q(2);
	std::thread producer(pushingMain, std::ref(q));
    std::thread consumer(popingMain, std::ref(q));

	producer.join();
	consumer.join();


}

TEST(QueueTest, Pop_Waits_for_Push)
{
	Queue<int> q(10);
	std::thread producer(pushing, std::ref(q));
    std::thread consumer(poping, std::ref(q));

	producer.join();
	consumer.join();

	EXPECT_EQ(q.Count(), 0);
	q.Push(22);

	EXPECT_EQ(q.Count(), 1);
	EXPECT_EQ(q.Pop(), 22);

}

TEST(QueueTest, OverwritesWhenFull)
{
	Queue<int> q(2);
	q.Push(1);
	q.Push(2);
	q.Push(3);
	EXPECT_EQ(q.Count(), 2);
	EXPECT_EQ(q.Pop(), 2);
	EXPECT_EQ(q.Pop(), 3);
}

TEST(QueueTest, PopWithTimeoutThrowsOnTimeout)
{
	Queue<int> q(1);
	EXPECT_THROW(q.PopWithTimeout(100), std::runtime_error);
}



TEST(QueueTest, MultithreadedPushPop)
{
	Queue<int> q(10);
	std::thread producer(producerFunction<int>, std::ref(q));
	std::thread consumer(consumerFunction<int>, std::ref(q));

	producer.join();
	consumer.join();
}


TEST(QueueTest, MultithreadedPushPop_long)
{
	Queue<long> q(10);
	std::thread producer(producerFunction<long>, std::ref(q));
	std::thread consumer(consumerFunction<long>, std::ref(q));

	producer.join();
	consumer.join();
}

TEST(QueueTest, MultithreadedPushPop_unsigned_int)
{
	Queue<unsigned int> q(10);
	std::thread producer(producerFunction<unsigned int>, std::ref(q));
	std::thread consumer(consumerFunction<unsigned int>, std::ref(q));

	producer.join();
	consumer.join();
}






