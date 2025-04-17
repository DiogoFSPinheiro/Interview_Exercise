#pragma once


#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <condition_variable>



template<typename T>
class Queue
{
	private:
		T* _buffer;                // Dynamically allocated buffer
		int _maxSize;              // Max elements in queue
		int _head;                 // Index for popping
		int _tail;                 // Index for pushing
		int _count;                // Current element count

		
		mutable std::mutex mtx;               // Mutex for thread safety
		std::condition_variable cv;           // Condition variable for blocking pop
		void advance(int &index);             // Helper for circular index

	public:
		Queue(int size);
		~Queue();
		void Push(T element);
		T Pop();
		T PopWithTimeout(int milliseconds);
		int Count();
		int Size();

		void DebugState(const std::string& label) const;
};

