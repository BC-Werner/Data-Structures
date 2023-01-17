#pragma once

template<typename T>
class Vector
{
public:
	Vector()
	{
		allocate(1);
	}

private:
	void allocate(size_t newCap)
	{
		T* newBlock = new T[newCap];

		if (newCap > m_size)
			m_size = newCap;

		for (size_t i = 0; i < m_size; i++)
			newBlock[i] = m_data[i];

		delete[] m_data;
		m_data = newBlock;
		m_capacity = newCap;
	}

	T* m_data = nullptr;
	size_t m_size;
	size_t m_capacity;
};
