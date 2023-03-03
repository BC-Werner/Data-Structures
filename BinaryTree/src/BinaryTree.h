#pragma once

#include <initializer_list>

template <typename T>
class BinaryTree
{
// Inner Classes
private:
	class BNode
	{
	public:
		BNode() : data(T()), pLeft(nullptr), pRight(nullptr), pParent(nullptr) {}
		BNode(T t) : data(t), pLeft(nullptr), pRight(nullptr), pParent(nullptr) {}

		T data;
		BNode* pLeft;
		BNode* pRight;
		BNode* pParent;
	};

public:
	class Iterator
	{
	private:
		BNode* p;
		BNode* tree_root;

		BNode* inorder_Predecessor() 
		{
			// Empty Root Node
			if (p == tree_root)
			{
				BNode* curr = p;
				if (curr->pLeft) curr = curr->pLeft;
				while (curr->pRight)
					curr = curr->pRight;
				return curr;
			}

			// Leaf node or right only
			if (!p->pLeft)
			{
				BNode* curr = p->pParent;
				BNode* lastVisited = p;
				while (lastVisited == curr->pLeft)
				{
					if (!curr->pParent) return nullptr;
					lastVisited = curr;
					curr = curr->pParent;
				}
				return curr;
			}

			// Not Leaf Node
			if (p->pLeft)
			{
				BNode* curr = p->pLeft;
				while (curr->pRight)
					curr = curr->pRight;
				return curr;
			}
			return nullptr;
		}
		BNode* inorder_Successor() 
		{
			// Empty Root Node
			if (p == tree_root)
			{
				BNode* curr = p;
				if (curr->pRight) curr = curr->pRight;
				while (curr->pLeft)
					curr = curr->pLeft;
				return curr;
			}

			// Leaf Node or only Left child
			if (!p->pRight)
			{
				BNode* curr = p->pParent;
				BNode* lastVisited = p;
				while (lastVisited == curr->pRight)
				{
					if (!curr->pParent) return nullptr;
					lastVisited = curr;
					curr = curr->pParent;
				}
				return curr;
			}
			 
			// Not Leaf Node
			if (p->pRight)
			{
				BNode* curr = p->pRight;
				while (curr->pLeft)
					curr = curr->pLeft;
				return curr;
			}
			return nullptr;
		}

	public:
		Iterator(BNode* ptr, BNode* root) : p(ptr), tree_root(root)             {}
		Iterator(Iterator const& rhs)     : p(rhs.p), tree_root(rhs.tree_root)  {}

		void             operator=(Iterator const& rhs)       { p = rhs.p; tree_root = rhs.tree_root; }
		bool             operator==(const Iterator& it) const { return it.p == p; }
		bool             operator!=(const Iterator& it) const { return it.p != p; }
		Iterator&        operator++()                         { p = inorder_Successor(); return *this; }
		Iterator&        operator--()                         { p = inorder_Predecessor(); return *this; }
		const Iterator&  operator++(int)                      { Iterator tmp = *this; ++(*this); return tmp; }
		const Iterator&  operator--(int)                      { Iterator tmp = *this; --(*this); return tmp; }
		T                operator*()                          { return p->data; }

		friend class BinaryTree;
	};

// Properties
private:
	size_t m_size;
	BNode* m_root;

// Methods
public:
	BinaryTree()                                    : m_size(0), m_root(nullptr) {}
	BinaryTree(BinaryTree const& copy)              : m_size(0), m_root(nullptr) { copyTree(copy.m_root); }
	BinaryTree(const std::initializer_list<T>& il)  : m_size(0), m_root(nullptr) { for (auto x : il) insert(x); };
	BinaryTree(BinaryTree&& move) noexcept          : m_size(0), m_root(nullptr) { move.swap(*this); }
	~BinaryTree() { clear(); }

	Iterator    begin()                     { return Iterator(findMin(), m_root); }
	Iterator    end()                       { return Iterator(nullptr, m_root); }
	Iterator    find(T const& t)            { return Iterator(find_impl(m_root, t), m_root); }
	size_t      size()  const               { return m_size; }
	bool        empty() const               { return m_size == 0; }
	void        clear()                     { clear_impl(m_root); }
	void        operator=(BinaryTree rhs)   { m_size = rhs.m_size; m_root = rhs.m_root; }

	void insert(T const& t) 
	{
		if (!m_root)
		{
			m_root = new BNode(t);
			m_size++;
			return;
		}

		BNode* tmp = m_root;
		BNode* parent = nullptr;

		while (tmp != nullptr)
		{
			parent = tmp;

			if (t < tmp->data)
				tmp = tmp->pLeft;
			else
				tmp = tmp->pRight;
		}

		if (t < parent->data)
		{
			parent->pLeft = new BNode(t);
			parent->pLeft->pParent = parent;
		}
		else
		{
			parent->pRight = new BNode(t);
			parent->pRight->pParent = parent;
		}

		m_size++;
	}

	void erase(Iterator const& it)
	{
		// Return iterator to predecessor?
		Iterator tmp = it;
		tmp--;
		// Case 1
		// Node is nullptr
		if (!it.p) return;

		// Case 2
		// Node is the root
		if (it.p == m_root)
		{
			delete it.p;
			m_root = nullptr;
			return;
		}

		BNode* toDel = it.p;
		BNode* toDelParent = it.p->pParent;

		// Case 3
		// Node has no children
		if (!toDel->pLeft && !toDel->pRight)
		{
			if (toDelParent->pLeft == toDel) toDelParent->pLeft = nullptr;
			if (toDelParent->pRight == toDel) toDelParent->pRight = nullptr;

			delete toDel;
			m_size--;

			return;
		}

		// Case 4
		// Node has both children
		if (toDel->pLeft && toDel->pRight)
		{
			// Find successor
			// set successors parent to point to successors right (we were searching left until left was null. so the successor node could have a right)
			// set successors right parent to point to successors parent
			// set successors parent to toDel parent
			// set toDel parent to point to successor
			// set successor right to point to toDel right
			// set successor left to point to toDel left

			BNode* successor = inorder_successor(toDel);
			if (successor)
			{
				// Keep a reference to the successors original parent 
				BNode* successorParent = successor->pParent;

				// Set successor parent to point to toDel parent
				// Set toDel parent to point to successor
				successor->pParent = toDelParent;
				if (toDelParent->pLeft == toDel) toDelParent->pLeft = successor;
				if (toDelParent->pRight == toDel) toDelParent->pRight = successor;

				// The successor is not a child of toDel
				if (successorParent != toDel)
				{
					// The successors original parent should point to the successors right child
					successorParent->pLeft = successor->pRight;
					if (successor->pRight) successor->pRight->pParent = successorParent;

					// Swap successors children with toDel children
					successor->pRight = toDel->pRight;
					toDel->pRight->pParent = successor;
					successor->pLeft = toDel->pLeft;
					toDel->pLeft->pParent = successor;
				}
				// The successor is a child of toDel
				else
				{
					if (toDel->pRight == successor)
					{
						successor->pLeft = toDel->pLeft;
						toDel->pLeft->pParent = successor;
					}
					if (toDel->pLeft == successor)
					{
						successor->pRight = toDel->pRight;
						toDel->pRight->pParent = successor;
					}
				}
			}

			delete toDel;
			m_size--;

			return;
		}

		// Case 5
		// Node has left only child
		if (toDel->pLeft)
		{
			// Find successor
			// set successors parent to point to successors left (we were searching right until right was null. so the successor node could have a left)
			// set successors left parent to point to successors parent
			// set successors parent to toDel parent
			// set toDel parent to point to successor
			// set successor left to point to toDel left

			BNode* successor = inorder_successor(toDel);
			if (successor)
			{
				successor->pParent->pRight = successor->pLeft;
				if (successor->pLeft) successor->pLeft->pParent = successor->pParent;
				successor->pParent = toDel->pParent;
				if (toDelParent->pLeft == toDel) toDelParent->pLeft = successor;
				if (toDelParent->pRight == toDel) toDelParent->pRight = successor;
				if (successor != toDel->pLeft) successor->pLeft = toDel->pLeft;
			}

			delete toDel;
			m_size--;

			return;
		}

		// Case 6
		// Node has right only child
		if (toDel->pRight)
		{
			// Find successor
			// set successors parent to point to successors right (we were searching left until left was null. so the successor node could have a right)
			// set successors right parent to point to successors parent
			// set successors parent to toDel parent
			// set toDel parent to point to successor
			// set successor right to point to toDel right

			BNode* successor = inorder_successor(toDel);
			if (successor)
			{
				successor->pParent->pLeft = successor->pRight;
				if (successor->pRight) successor->pRight->pParent = successor->pParent;
				successor->pParent = toDel->pParent;
				if (toDelParent->pLeft == toDel) toDelParent->pLeft = successor;
				if (toDelParent->pRight == toDel) toDelParent->pRight = successor;
				if (successor != toDel->pRight) successor->pRight = toDel->pRight;
			}

			delete toDel;
			m_size--;

			return;
		}
	}

private:
	BNode* inorder_successor(BNode* sub_root)
	{
		BNode* successor = nullptr;

		if (sub_root->pRight)
		{
			successor = sub_root->pRight;
			while (successor && successor->pLeft) successor = successor->pLeft;
			return successor;
		}
		if (sub_root->pLeft)
		{
			successor = sub_root->pLeft;
			while (successor && successor->pRight) successor = successor->pRight;
			return successor;
		}

		return nullptr;
	}

	BNode* find_impl(BNode* root, T const& target)
	{
		if (!root || root->data == target)
			return root;

		if (root->data > target) return find_impl(root->pLeft, target);
		if (root->data < target) return find_impl(root->pRight, target);
	}

	void clear_impl(BNode* root)
	{
		if (!root) return;

		clear_impl(root->pLeft);
		clear_impl(root->pRight);
	}

	BNode* findMin() const 
	{ 
		if (!m_root) return nullptr;

		BNode* tmp = m_root;  
		while (tmp->pLeft)
		{
			tmp = tmp->pLeft;
		}

		return tmp;
	}

	BNode* findMax() const 
	{ 
		if (!m_root) return nullptr;

		BNode* tmp = m_root;  
		while (tmp->pRight)
		{
			tmp = tmp->pRight;
		}

		return tmp;
	}

	void copyTree(BNode* root)
	{
		if (!root) return;

		insert(root->data);
		copyTree(root->pLeft);
		copyTree(root->pRight);
	}

	void swap(BinaryTree& other)
	{
		std::swap(m_size, other.m_size);
		std::swap(m_root, other.m_root);
	}
};
