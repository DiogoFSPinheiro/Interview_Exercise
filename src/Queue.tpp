#include "Queue.hpp"

template <typename T>
int Queue<T>::Count()
{
	return _count;
}

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


template<typename T>
Queue<T>::Queue(int size) : _maxSize(size), _head(0), _tail(0), _count(0)
{
	_buffer = new T[size];
}

template<typename T>
Queue<T>::~Queue()
{
	delete[] _buffer;
}

template<typename T>
int Queue<T>::Size()
{
	return _maxSize;
}

template<typename T>
void Queue<T>::advance(int &index)
{
	index = (index + 1) % _maxSize;
}

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