/**
 * @file Queue.tpp
 * @author DiogoFSPinheiro
 * @brief This file has all the Template Functions
 * @version 1.01
 * @date 2025-04-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "Queue.hpp"

/**
* @brief Gets the current number of elements in the queue.
* 
* @return The current count of elements.
*/
template <typename T>
int Queue<T>::Count()
{
	return _count;
}

/**
* @brief Removes and returns an element from the queue with a timeout.
* 
* Blocks the calling thread until an item is available or the specified timeout is reached.
* 
* @param milliseconds The timeout in milliseconds to wait for an element.
* @return The item popped from the queue.
* 
* @throws std::runtime_error If no element is received within the given timeout.
*/
template<typename T>
T Queue<T>::PopWithTimeout(int milliseconds)
{
	std::unique_lock<std::mutex> lock(mtx);

	if (_count == 0)
	{
		if (!cv.wait_for(lock, std::chrono::milliseconds(milliseconds), [this] { return _count > 0; }))
		{
			throw std::runtime_error("No element received in time.");
		}
	}

	T value = _buffer[_head];
	advance(_head);
	--_count;

	return value;
}

/**
* @brief Removes and returns an element from the queue.
* 
* Blocks the calling thread until an item becomes available.
* 
* @return The item popped from the queue.
*/
template<typename T>
T Queue<T>::Pop()
{
	std::unique_lock<std::mutex> lock(mtx);

	cv.wait(lock, [this]() { return _count > 0; });

	T value = _buffer[_head];
	advance(_head);
	--_count;

	return value;
}

/**
* @brief Adds an element to the queue.
* 
* If the queue is full, it discards the oldest element before inserting the new one.
* Notifies one waiting thread (if any).
* 
* @param element The element to insert.
*/
template <typename T>
void Queue<T>::Push(T element)
{
	std::unique_lock<std::mutex> lock(mtx);

	if (_count == _maxSize)
	{
		advance(_head);
		--_count;
	}

	_buffer[_tail] = element;
	advance(_tail);
	++_count;

	cv.notify_one();
}

/**
* @brief Constructs a queue with a fixed capacity.
* 
* @param size The maximum number of elements the queue can hold.
*/
template<typename T>
Queue<T>::Queue(int size) : _maxSize(size), _head(0), _tail(0), _count(0)
{
	_buffer = new T[size];
}

/**
* @brief Destructor for the queue.
* 
* Frees the dynamically allocated buffer.
*/
template<typename T>
Queue<T>::~Queue()
{
	delete[] _buffer;
}

/**
* @brief Gets the maximum capacity of the queue.
* 
* @return The maximum number of elements the queue can hold.
*/
template<typename T>
int Queue<T>::Size()
{
	return _maxSize;
}

/**
* @brief Advances an index in circular fashion within the bounds of the queue size.
* 
* @param index Reference to the index to be incremented.
*/
template<typename T>
void Queue<T>::advance(int &index)
{
	index = (index + 1) % _maxSize;
}

/**
* @brief Prints internal state of the queue for debugging purposes.
* 
* Shows buffer content, head, tail, and count values with a custom label.
* 
* @param label A label to identify the debug print.
*/
template<typename T>
void Queue<T>::DebugState(const std::string& label) const
{
	std::lock_guard<std::mutex> lock(mtx);
	std::cout << "[" << label << "]\n";
	std::cout << "Buffer: ";

	for (int i = 0; i < _maxSize; ++i)
		std::cout << _buffer[i] << " ";

	std::cout << "\n_head = " << _buffer[_head] << ", _tail = " << _buffer[_tail] << ", _count = " << _count << "\n\n";
}
