#pragma once
#include "../../LinkedList/src/List.hpp"
#include <initializer_list>

template <typename T, class Container = List<T>>
class Stack
{
public:
	Stack() : count(0) {}
	Stack(const std::initializer_list<T>& il) : count(il.size()), container(il) {}
	Stack(Stack<T, Container>&& other) noexcept : count(0), container() 
	{
		other.swap(*this);
	}
	~Stack() { clear(); }

	const bool empty() const { return count == 0; }
	const size_t Size() const { return count; }

	T& top() { return container.front(); }
	void push(T data) { container.push_front(data); count++; }
	void pop() { container.pop_front(); count--; }

	void swap(Stack<T, Container>& other) noexcept
	{
		std::swap(count, other.count);
		container.swap(other.container);
	}

	void clear() { container.clear(); count = 0; }

private:
	size_t count;
	Container container;
};
