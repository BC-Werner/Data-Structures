#pragma once

#include <initializer_list>

template <typename T>
class RBTree
{
// Inner Classes
public:
	class Iterator
	{
	// Properties
	public:
	private:

	// Methods
	public:
	private:
	};

private:
	class Node
	{
	public:
		T      key;
		Node*  parent;
		Node*  left;
		Node*  right;
		Color  color;

		Node() = delete;
		Node(T& data) : key(data), parent(nullptr), left(nullptr), right(nullptr), color(Color::black) {}
	};

// Properties
private:
	enum class Color { red, black };
	Node*  m_root;
	size_t m_size;

// Methods
public:
	RBTree()                                   : m_root(nullptr), m_size(0) {}
	RBTree(RBTree const& copy)                 : m_root(nullptr), m_size(0) {}
	RBTree(std::initializer_list<T> const& il) : m_root(nullptr), m_size(0) {}
	RBTree(RBTree&& move)                      : m_root(nullptr), m_size(0) {}

private:
};
