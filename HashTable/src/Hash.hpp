#pragma once

template <typename K>
class Hash
{
public:
	size_t operator () (const K& key) { return static_cast<size_t>(key); }
};

template <>
class Hash<std::string>
{
	size_t operator () (const std::string& key)
	{
		size_t x = 0;
		for (char c : key)
			x += c;
		return x;
	}
};
