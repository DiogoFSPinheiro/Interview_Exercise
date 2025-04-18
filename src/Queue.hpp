#pragma once

#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <condition_variable>

/**
 * @brief A thread-safe circular queue implementation with optional timeout-based blocking operations.
 * 
 * Provides basic producer-consumer queue semantics with thread synchronization.
 * Template-based to support any copyable data type.
 * 
 * @tparam T The type of elements stored in the queue.
 */
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
		void DebugState(const std::string& label) const;

	public:
		Queue(int size);
		~Queue();
		void Push(T element);
		T Pop();
		T PopWithTimeout(int milliseconds);
		int Count();
		int Size();

		
};

