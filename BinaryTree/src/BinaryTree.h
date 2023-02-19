#pragma once

#include <initializer_list>
#include "../../Vector/src/Vector.hpp"

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
		Vector<BNode*> predecessors;

		void findPredecessors(const BNode* p) 
		{
			if (!tree_root) return;

			predecessors.clear();

			BNode* tmp = tree_root;
			while (tmp->pLeft)
				tmp = tmp->pLeft;

			predecessors.push_back(tmp);

			while (tmp && tmp != p)
			{
				if (tmp->pRight && !contains(tmp->pRight))
				{
					tmp = tmp->pRight;
					while (tmp->pLeft)
						tmp = tmp->pLeft;
					predecessors.push_back(tmp);
				}
				else
				{
					tmp = tmp->pParent;
					if (!contains(tmp))
						predecessors.push_back(tmp);
				}
			}
		}

		const bool contains(BNode* p) { for (auto node : predecessors) if (node == p) return true; return false; }

	public:
		//Iterator() {}
		Iterator(BNode* ptr, BNode* root) : p(ptr), tree_root(root)             { findPredecessors(p); }
		Iterator(Iterator const& rhs)     : p(rhs.p), tree_root(rhs.tree_root)  { findPredecessors(p); }

		void             operator=(Iterator const& rhs) { p = rhs.p; tree_root = rhs.tree_root; findPredecessors(p); }
		bool             operator==(const Iterator& it) const { return it.p = p; }
		bool             operator!=(const Iterator& it) const { return it.p != p; }
		Iterator&        operator++()
		{
			predecessors.push_back(p);
			// Find Successor
			// if node has a right go right then as far left as possible
			// if node has no right go to its parent until its parent is not in the list of predecessors
			if (p->pRight)
			{
				p = p->pRight;
				while (p->pLeft)
					p = p->pLeft;
			}
			else
			{
				if (p->pParent) p = p->pParent;
				while (p && contains(p))
					p = p->pParent;
			}

			return *this;
		}
		Iterator&        operator--() 
		{ 
			if (predecessors.size() < 1) 
			{ 
				p = nullptr; 
				return *this; 
			} 

			p = predecessors.back(); 
			predecessors.pop_back();
			return* this;
	    }
		const Iterator&  operator++(int)          { Iterator tmp = *this; ++(*this); return tmp; }
		const Iterator&  operator--(int)          { Iterator tmp = *this; --(*this); return tmp; }
		T                operator*()              { return p->data; }

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
		if (root->data == target || !root)
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
