#include "Queue.hpp"

template <typename T>
void Queue<T>::Push(T element)
{
	std::unique_lock<std::mutex> lock(mtx);     // 1️⃣ Lock for thread safety

	if (_count == _maxSize) {                   // 2️⃣ If full...
		advance(_head);                         //    Drop oldest → move head forward
		--_count;                               //    One item "forgotten"
	}

	_buffer[_tail] = element;                   // 3️⃣ Write at tail
	advance(_tail);                             // 4️⃣ Move tail forward (circularly)
	++_count;                                   // 5️⃣ One more item now

	cv.notify_one();                            // 6️⃣ Wake up one waiting Pop()
}

template<typename T>
void Queue<T>::show()
{
	int c = 0;
	while (c < _maxSize)
	{
		std::cout << _buffer[c] << std::endl;
		c++;
	}
		
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