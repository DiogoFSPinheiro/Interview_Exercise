#include "Queue.tpp"
#include <iostream>

int main()
{
	Queue<int> teste(3);

	teste.DebugState("before");
	teste.Push(22);
	teste.DebugState("after");
	teste.DebugState("before");
	teste.Push(55);
	teste.DebugState("after");
	teste.DebugState("before");
	teste.Push(77);
	teste.DebugState("after");
	teste.DebugState("before");
	teste.Push(99);
	teste.DebugState("after");

	std::cout << std::endl << "Size is: " <<teste.Count() << std::endl;

	int x = teste.Pop();
	std::cout << x << std::endl;
	teste.DebugState("after");
	x = teste.Pop();
	std::cout << x << std::endl;
	teste.DebugState("after");
	x = teste.Pop();
	std::cout << x << std::endl;
	teste.DebugState("after");

	try
	{
		x = teste.PopWithTimeout(1000); // 1 second timeout
		std::cout << "Popped: " << x << std::endl;
	}

	catch (const std::runtime_error& e)
	{
		std::cout << "Pop timed out: " << e.what() << std::endl;
	}

	std::cout << std::endl << "Size is: " <<teste.Count() << std::endl;
	teste.Push(22);
	teste.DebugState("after");

	std::cout << std::endl << "Size is: " <<teste.Count() << std::endl;


	



	return 0;
}