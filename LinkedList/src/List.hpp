#pragma once
#include <initializer_list>

template <typename T>
class List {
private:
	struct Node {
		T data;
		Node* prev;
		Node* next;
	};

	Node* head;
	Node* tail;
	size_t count;

public:
	class Iterator {
	private:
		Node* current;
	public:
		Iterator(Node* node) : current(node) {}
		Iterator operator++() { if (current) current = current->next; return *this; }
		Iterator operator--() { if (current) current = current->prev; return *this; }
		Iterator operator++(int) { Iterator copy(*this); if (current) current = current->next; return copy; }
		Iterator operator--(int) { Iterator copy(*this); if (current) current = current->prev; return copy; }
		T& operator*() { return current->data; }
		bool operator==(const Iterator& other) { return current == other.current; }
		bool operator!=(const Iterator& other) const { return current != other.current; }

		friend class List;
	};

	List() : head(nullptr), tail(nullptr), count(0) {}
	List(const std::initializer_list<T>& il)
		: head(nullptr), tail(nullptr), count(0)
	{
		if (il.size() == 0) return;

		auto it = il.begin();
		head = new Node{ *it, nullptr, head };
		it++;

		Node* node = head;
		while (it != il.end())
		{
			node->next = new Node{*(it)++, node, nullptr};
			//node->next->prev = node;
			node = node->next;
			//++it;
		}

		count = il.size();
		tail = node;
	}
	~List() { clear(); }

	void push_front(T value) 
	{
		Node* newNode = new Node{value, nullptr, head};
		if (head) head->prev = newNode;
		head = newNode;
		if (!tail) tail = head;
		count++;
	}

	void push_back(T value)
	{
		Node* newNode = new Node{value, nullptr, head};
		if (tail) tail->next = newNode;
		tail = newNode;
		if (!head) head = tail;
		count++;
	}

	Iterator insert(Iterator it, T value)
	{
		if (it.current == head) { push_front(value); return Iterator(head); }

		Node* newNode = new Node{ value, it.current->prev, it.current };
		if (it.current->prev) it.current->prev->next = newNode;
		it.current->prev = newNode;
		count++;

		return Iterator(newNode);
	}

	void pop_front()
	{
		erase(Iterator(head));
	}

	void pop_back()
	{
		erase(Iterator(tail));
	}

	Iterator erase(Iterator it)
	{
		if (!it.current) return it;

		Iterator next = it;
		next++;
		if (it.current->prev) { it.current->prev->next = it.current->next; }
		if (it.current->next) { it.current->next->prev = it.current->prev; }
		if (it.current == head) { head = it.current->next; }
		if (it.current == tail) { tail = it.current->prev; }
		delete it.current;
		count--;
		return next;
	}

	Iterator erase(Iterator start, Iterator end)
	{
		Iterator it = start;
		while(it != end)
		{
			Iterator next = it;
			next++;
			it = erase(it);
			it = next;
		}
		return end;
	}

	void clear()
	{
		erase(begin(), end());
	}

	//void reverse();
	//void sort();

	const bool empty() const { return count == 0; }
	const size_t Size() const { return count; }

	Iterator begin() { return Iterator(head); }
	Iterator end() { return Iterator(nullptr); }
};
