#include "Queue.tpp"
#include <iostream>

int main()
{
	Queue<int> teste(6);

	teste.Push(0);
	teste.Push(1);
	teste.Push(2);
	teste.Push(3);
	teste.Push(4);
	teste.Push(5);


	teste.show();
	std::cout << std::endl;
	teste.Push(22);
	teste.Push(55);

	teste.show();



	return 0;
}