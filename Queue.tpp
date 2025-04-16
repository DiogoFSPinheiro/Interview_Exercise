#include "Queue.hpp"


template<typename T>
void  Queue<T>::Push(T element)
{
	if (_count > _maxSize - 1)
		_count = 0;

	_buffer[_count] = element;
	_count++;

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
 