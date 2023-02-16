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
		BNode* parent = it.p->pParent;

		// Node is the root
		if (toDel == m_root)
		{
			// Root Has a left child
			// - Go left once and then right all the way down
			if (toDel->pLeft)
			{
				BNode* tmp = toDel->pLeft;
				while (tmp->pRight)
				{
					tmp = tmp->pRight;
				}

				// Swap tmp and toDel
				if (tmp != toDel->pLeft) tmp->pLeft = toDel->pLeft;
				tmp->pRight = toDel->pRight;
				tmp->pParent->pRight = nullptr;
				tmp->pParent = toDel->pParent;

				delete toDel;
				m_root = tmp;

				return;
			}

			// Root Has a right child
			// - Go right once and then left all the way down
			if (toDel->pRight)
			{
				BNode* tmp = toDel->pRight;
				while (tmp->pLeft)
				{
					tmp = tmp->pLeft;
				}

				// Swap tmp and toDel
				tmp->pLeft = toDel->pLeft;
				if (tmp != toDel->pRight) tmp->pRight = toDel->pRight;
				tmp->pParent->pLeft = nullptr;
				tmp->pParent = toDel->pParent;

				delete toDel;
				m_root = tmp;

				return;
			}

			// Root Has no children
			delete toDel;
			m_root = nullptr;
			return;
		}

		// Node has both children
		if (toDel->pLeft && toDel->pRight)
		{
			BNode* tmp = toDel->pLeft;
			while (tmp->pRight)
			{
				tmp = tmp->pRight;
			}

			// Swap tmp and toDel
			tmp->pParent->pRight = tmp->pLeft;
			tmp->pParent = toDel->pParent;
			if (toDel->pParent->pLeft == toDel) toDel->pParent->pLeft = tmp;
			if (toDel->pParent->pRight == toDel) toDel->pParent->pRight = tmp;
			tmp->pLeft = toDel->pLeft;
			tmp->pRight = toDel->pRight;
		}

		// TODO:
		// Node has left only child
		// Node has right only child

		// Node has no children
		if (!toDel->pLeft && !toDel->pRight)
		{
			if (toDel->pParent->pLeft == toDel) toDel->pParent->pLeft = nullptr;
			if (toDel->pParent->pRight == toDel) toDel->pParent->pRight = nullptr;

			delete toDel;
		}
	}

	void        clear()          {}
	Iterator    find(T const& t) { return Iterator(find_impl(m_root, t)); }
	Iterator    begin()          { return Iterator(findMin()); }
	Iterator    end()            { return Iterator(nullptr); }

	void print() { print_impl(m_root); std::cout << std::endl; }

private:
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
