#include <iostream>
#include "Stack.hpp"

template <typename T>
void print(Stack<T>& stack, std::string name)
{
	std::cout << name << "..." << std::endl;
	if (stack.empty())
	{
		std::cout << "Empty" << std::endl;
		return;
	}
	print_impl(stack);
	std::cout << std::endl;
}

template <typename T>
void print_impl(Stack<T>& stack)
{
	if (stack.empty()) return;

	T x = stack.top();
	stack.pop();
	std::cout << x << " ";
	if (!stack.empty()) std::cout << "-> ";
	print_impl(stack);
	stack.push(x);
}

int main()
{
	Stack<int> stack;
	Stack<int> stack2;
	Stack<int> stackIL{ 1, 2, 3, 4, 5 };

	stack.push(55);
	stack.push(25);
	stack.push(3);
	
	stack2.push(1);
	stack2.push(2);

	print(stack, "Stack 1");
	print(stack2, "Stack 2");

	std::cout << "\nSwapping Stack 1 and Stack 2..." << std::endl;
	stack.swap(stack2);

	print(stack, "Stack 1");
	print(stack2, "Stack 2");

	print(stackIL, "\nStack Initializer List");

	std::cout << "\nMoving Stack IL to Stack Move..." << std::endl;
	Stack<int> stackMove(std::move(stackIL));

	print(stackMove, "Stack Move");
	print(stackIL, "Stack Initializer List");

	return 0;
}