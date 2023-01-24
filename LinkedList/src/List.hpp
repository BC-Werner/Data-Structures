#pragma once
#include <initializer_list>
#include <functional>

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
	List(const List<T>& other) 
		: head(nullptr), tail(nullptr), count(0)
	{
		Node* lhsNode = nullptr;
		Node* rhsNode = other.head;

		if (rhsNode)
		{
			lhsNode = new Node{ rhsNode->data, nullptr, nullptr};
			head = lhsNode;
			tail = lhsNode;

			rhsNode = rhsNode->next;
		}

		while (rhsNode && lhsNode)
		{
			lhsNode->next = new Node{ rhsNode->data, lhsNode, nullptr };
			tail = lhsNode;
			lhsNode = lhsNode->next;
			rhsNode = rhsNode->next;
		}

		count = other.count;
	}
	List(List<T>&& other) noexcept
		: head(nullptr), tail(nullptr), count(0)
	{
		other.swap(*this);
	}
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
			node = node->next;
		}

		count = il.size();
		tail = node;
	}
	~List() { clear(); }

	const bool empty() const { return count == 0; }
	const size_t size() const { return count; }

	Iterator begin() { return Iterator(head); }
	Iterator end() { return Iterator(nullptr); }

	T& front() { if (!head) throw std::exception("Front is nullptr. Cannot retrieve data."); return head->data; }
	const T& front() const { if (!head) throw std::exception("Front is nullptr. Cannot retrieve data."); return head->data; }

	T& back() { if (!tail) throw std::exception("Tail is nullptr. Cannot retrieve data."); return tail->data; }
	const T& back() const { if (!tail) throw std::exception("Tail is nullptr. Cannot retrieve data."); return tail->data; }

	void push_front(const T& value) 
	{
		Node* newNode = new Node{value, nullptr, head};
		if (head) head->prev = newNode;
		head = newNode;
		if (!tail) tail = head;
		count++;
	}

	void push_back(const T& value)
	{
		Node* newNode = new Node{value, tail, nullptr};
		if (tail) tail->next = newNode;
		tail = newNode;
		if (!head) head = tail;
		count++;
	}

	Iterator insert(Iterator it, const T& value)
	{
		if (!it.current) return it;
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

	void reverse()
	{
		Node* current = tail;
		Node* temp = nullptr;

		while (current)
		{
			temp = current->next;
			current->next = current->prev;
			current->prev = temp;
			current = current->next;
		}

		Node* newHead = tail;
		tail = current;
		head = newHead;
	}

	void sort()
	{
		sort(head, std::less<T>());
	}

	template <typename Compare>
	void sort(Compare comp)
	{
		sort(head, comp);
	}


	void swap(List& other) noexcept
	{
		std::swap(head, other.head);
		std::swap(tail, other.tail);
		std::swap(count, other.count);
	}
private:
	template <typename Compare>
	void sort(Node*& head_ref, Compare comp)
	{
		Node* ptr = head_ref;
		Node* a = nullptr;
		Node* b = nullptr;

		if (ptr == nullptr || ptr->next == nullptr) return;

		split(ptr, a, b);
		sort(a, comp);
		sort(b, comp);
		head_ref = mergeSortedLists(a, b, comp);
	}

	void split(Node* srcNode, Node*& aRef, Node*& bRef)
	{
		Node* fastPtr = srcNode->next;
		Node* slowPtr = srcNode;

		while (fastPtr != nullptr)
		{
			fastPtr = fastPtr->next;
			if (fastPtr != nullptr)
			{
				slowPtr = slowPtr->next;
				fastPtr = fastPtr->next;
			}
		}

		aRef = srcNode;
		bRef = slowPtr->next;
		slowPtr->next = nullptr;
	}

	template <typename Compare>
	Node* mergeSortedLists(Node* head1, Node* head2, Compare comp)
	{
		Node* result = nullptr;
		if (head1 == nullptr) return head2;
		if (head2 == nullptr) return head1;
		if (comp(head1->data, head2->data))
		{
			head1->next = mergeSortedLists(head1->next, head2, comp);
			head1->next->prev = head1;
			head1->prev = nullptr;
			return head1;
		}
		else
		{
			head2->next = mergeSortedLists(head1, head2->next, comp);
			head2->next->prev = head2;
			head2->prev = nullptr;
			return head2;
		}
	}
};
