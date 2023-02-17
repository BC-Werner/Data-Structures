#pragma once

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
	public:
		Iterator() {}
		Iterator(BNode* ptr) : p(ptr) {}
		Iterator(Iterator const& rhs) : p(rhs.p) {}

		//Iterator         operator=(Iterator& rhs) {}
		bool             operator==(Iterator& it) { return it.p = p; }
		bool             operator!=(Iterator& it) { return it.p != p; }
		Iterator&        operator++()             {}
		Iterator&        operator--()             {}
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
	BinaryTree() : m_size(0), m_root(nullptr) {}
	BinaryTree(BinaryTree const& rhs) : m_size(0), m_root(nullptr) {}
	~BinaryTree() { clear(); }

	BinaryTree&  operator=(BinaryTree rhs)  {}
	size_t      size()  const               { return m_size; }
	bool        empty() const               { return m_size == 0; }

	void insert(T const& t) 
	{
		if (!m_root)
		{
			m_root = new BNode(t);
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
	}

	void erase(Iterator const& it)
	{
		// Node is nullptr
		if (!it.p) return;

		BNode* toDel = it.p;
		BNode* toDelParent = it.p->pParent;

		// Node is the root

		// Node has no children
		if (!toDel->pLeft && !toDel->pRight)
		{
			if (toDelParent->pLeft == toDel) toDelParent->pLeft = nullptr;
			if (toDelParent->pRight == toDel) toDelParent->pRight = nullptr;

			delete toDel;

			return;
		}

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
				BNode* successorParent = successor->pParent;

				if (successor->pParent != toDel)
				{
					successor->pParent = toDelParent;
					if (toDelParent->pLeft == toDel) toDelParent->pLeft = successor;
					if (toDelParent->pRight == toDel) toDelParent->pRight = successor;

					successorParent->pLeft = successor->pRight;
					if (successor->pRight) successor->pRight->pParent = successorParent;

					successor->pRight = toDel->pRight;
					toDel->pRight->pParent = successor;
					successor->pLeft = toDel->pLeft;
					toDel->pLeft->pParent = successor;
				}
				else
				{
					// Set successor parent to toDel parent
					// set successor left to toDel left (if successor is not toDel left)
					// set successor right to toDel right (if successor is not toDel right)
					successor->pParent = toDel->pParent;
					if (toDelParent->pLeft == toDel) toDelParent->pLeft = successor;
					if (toDelParent->pRight == toDel) toDelParent->pRight = successor;

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

			return;
		}

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

			return;
		}

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

			return;
		}
	}

	void        clear()          {}
	Iterator    find(T const& t) { return Iterator(find_impl(m_root, t)); }
	Iterator    begin()          { return Iterator(findMin()); }
	Iterator    end()            { return Iterator(nullptr); }

	void print() { print_impl(m_root); std::cout << std::endl; }

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
			BNode* successor = sub_root->pLeft;
			while (successor && successor->pRight) successor = successor->pRight;
			return successor;
		}

		return nullptr;
	}

	void print_impl(BNode* root)
	{
		if (!root) return;
		print_impl(root->pLeft);
		std::cout << root->data << " ";
		print_impl(root->pRight);
	}

	BNode* find_impl(BNode* root, T const& target)
	{
		if (root->data == target || !root)
			return root;

		if (root->data > target) return find_impl(root->pLeft, target);
		if (root->data < target) return find_impl(root->pRight, target);
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
};
