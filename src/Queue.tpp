/**
 * @file Queue.tpp
 * @author DiogoFSPinheiro
 * @brief Contains the template function definitions for the Queue class.
 * @version 1.01
 * @date 2025-04-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "Queue.hpp"

/**
 * @brief Returns the current number of elements in the queue.
 * @return The number of elements currently stored.
 */
template <typename T>
int Queue<T>::Count()
{
	return _count;
}

/**
 * @brief Removes and returns an element from the queue, blocking up to a specified timeout.
 * 
 * Blocks the calling thread until an item becomes available or the timeout elapses.
 * 
 * @param milliseconds Maximum time to wait for an element, in milliseconds.
 * @return The item removed from the queue.
 * @throws std::runtime_error If the timeout expires without receiving an element.
 */
template<typename T>
T Queue<T>::PopWithTimeout(int milliseconds)
{
	std::unique_lock<std::mutex> lock(mtx);

	if (!cv.wait_for(lock, std::chrono::milliseconds(milliseconds), [this] { return _count > 0; }))
	{
		throw std::runtime_error("No element received in time.");
	}

	T value = _buffer[_head];
	advance(_head);
	--_count;

	return value;
}

/**
 * @brief Removes and returns an element from the queue, blocking until one is available.
 * 
 * @return The item removed from the queue.
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
 * @brief Inserts an element into the queue.
 * 
 * If the queue is full, the oldest element is overwritten. Notifies one waiting thread, if any.
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
 * @brief Constructs a queue with the specified capacity.
 * 
 * @param size The maximum number of elements the queue can hold.
 */
template<typename T>
Queue<T>::Queue(int size) : _maxSize(size), _head(0), _tail(0), _count(0)
{
	_buffer = new T[size];
}

/**
 * @brief Destructor. Releases allocated resources.
 */
template<typename T>
Queue<T>::~Queue()
{
	delete[] _buffer;
}

/**
 * @brief Returns the maximum capacity of the queue.
 * 
 * @return The maximum number of elements the queue can hold.
 */
template<typename T>
int Queue<T>::Size()
{
	return _maxSize;
}

/**
 * @brief Advances the specified index in a circular fashion.
 * 
 * @param index The index to update.
 */
template<typename T>
void Queue<T>::advance(int &index)
{
	index = (index + 1) % _maxSize;
}

/**
 * @brief Prints the internal state of the queue for debugging purposes.
 * 
 * Displays buffer contents, head/tail indices, and the element count.
 * 
 * @param label A label to prefix the debug output.
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
