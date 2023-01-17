#include <iostream>
#include "Stack.hpp"

int main()
{
	Stack<int> stack;
	Stack<int> stack2;
	stack.push(55);
	stack.push(25);
	stack.push(3);
	
	stack2.push(1);
	stack2.push(2);

	stack.swap(stack2);

	std::cout << "Stack1" << std::endl;
	while (!stack.empty())
	{
		std::cout << stack.top() << std::endl;
		stack.pop();
	}

	std::cout << "Stack2" << std::endl;
	while (!stack2.empty())
	{
		std::cout << stack2.top() << std::endl;
		stack2.pop();
	}

	return 0;
}