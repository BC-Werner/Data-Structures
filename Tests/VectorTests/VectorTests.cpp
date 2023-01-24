#include "CppUnitTest.h"
#include "../../Vector/src/Vector.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VectorTests
{
	TEST_CLASS(VectorTests)
	{
	public:
		
		TEST_METHOD(Default_Constructor)
		{
			Vector<int> vec;

			Assert::IsTrue(vec.empty());
			Assert::IsTrue(vec.size() == 0);
			Assert::IsTrue(vec.capacity() == 1);
		}
		
		TEST_METHOD(InitializerList_Constructor)
		{
			Vector<int> vec{ 1, 2, 3, 4, 5 };

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 5);
			Assert::IsTrue(vec.capacity() == 5);
		}
		
		TEST_METHOD(Copy_Constructor)
		{
			Vector<int> vec{ 1, 2, 3, 4, 5 };
			vec.reserve(15);
			Vector<int> vecCopy(vec);

			Assert::IsFalse(vecCopy.empty());
			Assert::IsTrue(vecCopy.size() == 5);
			Assert::IsTrue(vecCopy.size() == vec.size());
			Assert::IsTrue(vecCopy.capacity() == 15);
			Assert::IsTrue(vecCopy.capacity() == vec.capacity());

			for (int i = 0; i < vec.size(); i++)
				Assert::AreEqual(vec[i], vecCopy[i]);
		}

		TEST_METHOD(Move_Constructor)
		{
			Vector<int> vec{ 1, 2, 3, 4, 5 };
			Vector<int> vecCopy(std::move(vec));

			Assert::IsFalse(vecCopy.empty());
			Assert::IsTrue(vecCopy.size() == 5);
			Assert::IsTrue(vecCopy.capacity() == 5);
		}

		TEST_METHOD(Move_Constructor_With_Capacity)
		{
			Vector<int> vec{ 1, 2, 3, 4, 5 };
			vec.reserve(15);
			Vector<int> vecCopy(std::move(vec));

			Assert::IsFalse(vecCopy.empty());
			Assert::IsTrue(vecCopy.size() == 5);
			Assert::IsTrue(vecCopy.capacity() == 15);
		}

		TEST_METHOD(Reserve_LessThanCapacity_ShouldNotReserveNewCapacity)
		{
			Vector<int> vec{ 1, 2, 3, 4, 5 };
			vec.reserve(2);

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 5);
			Assert::IsTrue(vec.capacity() == 5);
		}

		TEST_METHOD(Reserve_EqualToCapacity_ShouldNotReserveNewCapacity)
		{
			Vector<int> vec{ 1, 2, 3, 4, 5 };
			vec.reserve(5);

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 5);
			Assert::IsTrue(vec.capacity() == 5);
		}

		TEST_METHOD(Reserve_GreaterThanCapacity_ShouldReserveCapacity)
		{
			Vector<int> vec{ 1, 2, 3, 4, 5 };
			vec.reserve(20);

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 5);
			Assert::IsTrue(vec.capacity() == 20);
		}

		TEST_METHOD(Resize_LessThanSize)
		{
			Vector<int> vec{ 1, 2, 3, 4, 5 };
			vec.resize(3);

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 3);
			Assert::IsTrue(vec.capacity() == 5);
		}

		TEST_METHOD(Resize_GreaterThanSize)
		{
			Vector<int> vec{ 1, 2, 3, 4, 5 };
			vec.resize(10);

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 10);
			Assert::IsTrue(vec.capacity() == 10);
		}

		TEST_METHOD(Resize_EqualToSize)
		{
			Vector<int> vec{ 1, 2, 3, 4, 5 };
			vec.resize(5);

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 5);
			Assert::IsTrue(vec.capacity() == 5);
		}

		TEST_METHOD(Resize_EmptyVector)
		{
			Vector<int> vec;
			vec.resize(5);

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 5);
			Assert::IsTrue(vec.capacity() == 5);
		}

		TEST_METHOD(ShrinkToFit_CapacityGreaterThanSize)
		{
			Vector<int> vec{ 1, 2, 3, 4, 5 };
			vec.reserve(20);
			vec.push_back(6);
			vec.shrink_to_fit();

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 6);
			Assert::IsTrue(vec.capacity() == 6);
		}

		TEST_METHOD(ShrinkToFit_CapacityEqualToSize)
		{
			Vector<int> vec{ 1, 2, 3, 4, 5 };
			vec.shrink_to_fit();

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 5);
			Assert::IsTrue(vec.capacity() == 5);
		}

		TEST_METHOD(Clear)
		{
			Vector<int> vec{ 1, 2, 3, 4, 5 };
			vec.clear();

			Assert::IsTrue(vec.empty());
			Assert::IsTrue(vec.size() == 0);
			Assert::IsTrue(vec.capacity() == 5);
		}

		TEST_METHOD(IteratorAt)
		{
			Vector<int> vec{ 1, 2, 3, 4, 5 };

			Vector<int>::Iterator it = vec.iterator_at(2);

			Assert::AreEqual(*it.data(), vec[2]);
			Assert::AreEqual(it.data(), &vec[2]);
		}

		TEST_METHOD(IteratorAt_InvalidAddress_ShouldThrow)
		{
			Assert::ExpectException<std::out_of_range>([]() { 
				Vector<int> vec{ 1, 2, 3, 4, 5 };
				vec.iterator_at(9);
			});
		}

		TEST_METHOD(PushBack_EmptyVector)
		{
			Vector<int> vec;
			vec.push_back(1);

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 1);
			Assert::IsTrue(vec.capacity() == 1);

			Assert::IsTrue(vec[0] == 1);
		}

		TEST_METHOD(PushBack_ShouldResize)
		{
			Vector<int> vec;
			vec.push_back(1);
			vec.push_back(2);
			vec.push_back(3);
			vec.push_back(4);
			vec.push_back(5);

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 5);
			Assert::IsTrue(vec.capacity() == 8);

			for (int i = 0; i < vec.size(); i++)
				Assert::AreEqual(vec[i], i + 1);
		}

		TEST_METHOD(PushBack_ReservedVector)
		{
			Vector<int> vec;
			vec.reserve(5);
			vec.push_back(1);

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 1);
			Assert::IsTrue(vec.capacity() == 5);
		}

		TEST_METHOD(PushBack_ResizedVector)
		{
			Vector<int> vec;
			vec.resize(5);
			vec.push_back(1);

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 6);
			Assert::IsTrue(vec.capacity() == 10);
		}

		TEST_METHOD(PopBack_ShouldResize)
		{
			Vector<int> vec{ 1, 2, 3, 4, 5 };
			vec.pop_back();

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 4);
			Assert::IsTrue(vec.capacity() == 5);
		}

		TEST_METHOD(PopBack_EmptyVector_ShouldNotResize)
		{
			Vector<int> vec;
			vec.pop_back();

			Assert::IsTrue(vec.empty());
			Assert::IsTrue(vec.size() == 0);
			Assert::IsTrue(vec.capacity() == 1);
		}

		TEST_METHOD(Erase)
		{
			Vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
			Vector<int>::Iterator pos = vec.iterator_at(4);

			Assert::IsTrue(vec[4] == 5);

			vec.erase(pos);

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 9);
			Assert::IsTrue(vec.capacity() == 10);
			Assert::IsTrue(vec[4] == 6);
		}

		TEST_METHOD(Erase_EmptyVector)
		{
			Vector<int> vec;
			Vector<int>::Iterator pos = vec.begin();

			vec.erase(pos);

			Assert::IsTrue(vec.empty());
			Assert::IsTrue(vec.size() == 0);
			Assert::IsTrue(vec.capacity() == 1);
		}

		TEST_METHOD(Erase_Range)
		{
			Vector<int> expected{ 0, 1, 2, 3, 7, 8, 9 };
			Vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			Vector<int>::Iterator start = vec.iterator_at(4);
			Vector<int>::Iterator end = vec.iterator_at(7);

			vec.erase(start, end);

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 7);
			Assert::IsTrue(vec.capacity() == 10);

			Assert::AreEqual(expected.size(), vec.size());
			for (int i = 0; i < vec.size(); i++)
				Assert::IsTrue(vec[i] == expected[i]);
		}

		TEST_METHOD(Erase_Range_From_Begin)
		{
			Vector<int> expected{ 3, 4, 5, 6, 7, 8, 9 };
			Vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			Vector<int>::Iterator start = vec.begin();
			Vector<int>::Iterator end = vec.iterator_at(3);

			vec.erase(start, end);

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 7);
			Assert::IsTrue(vec.capacity() == 10);

			Assert::AreEqual(expected.size(), vec.size());
			for (int i = 0; i < vec.size(); i++)
				Assert::IsTrue(vec[i] == expected[i]);
		}

		TEST_METHOD(Erase_Range_To_End)
		{
			Vector<int> expected{ 0, 1, 2, 3, 4, 5, 6 };
			Vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			Vector<int>::Iterator start = vec.iterator_at(7);
			Vector<int>::Iterator end = vec.end();

			vec.erase(start, end);

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 7);
			Assert::IsTrue(vec.capacity() == 10);

			Assert::AreEqual(expected.size(), vec.size());
			for (int i = 0; i < vec.size(); i++)
				Assert::IsTrue(vec[i] == expected[i]);
		}

		TEST_METHOD(Erase_Range_Begin_To_End)
		{
			Vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			Vector<int>::Iterator start = vec.begin();
			Vector<int>::Iterator end = vec.end();

			vec.erase(start, end);

			Assert::IsTrue(vec.empty());
			Assert::IsTrue(vec.size() == 0);
			Assert::IsTrue(vec.capacity() == 10);
		}

		TEST_METHOD(Insert)
		{
			Vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			Vector<int>::Iterator pos = vec.iterator_at(5);

			vec.insert(pos, 100);

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 11);
			Assert::IsTrue(vec.capacity() == 11);

			Assert::IsTrue(vec[5] == 100);
		}

		TEST_METHOD(Insert_AtEnd)
		{
			Vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			Vector<int>::Iterator pos = vec.end();

			vec.insert(pos, 100);

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 11);
			Assert::IsTrue(vec.capacity() == 11);

			Assert::IsTrue(vec[10] == 100);
		}

		TEST_METHOD(Insert_AtBegin)
		{
			Vector<int> vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			Vector<int>::Iterator pos = vec.begin();

			vec.insert(pos, 100);

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 11);
			Assert::IsTrue(vec.capacity() == 11);

			Assert::IsTrue(vec[0] == 100);
		}

		TEST_METHOD(Insert_EmptyVector)
		{
			Vector<int> vec;
			Vector<int>::Iterator pos = vec.begin();

			vec.insert(pos, 100);

			Assert::IsFalse(vec.empty());
			Assert::IsTrue(vec.size() == 1);
			Assert::IsTrue(vec.capacity() == 1);

			Assert::IsTrue(vec[0] == 100);
		}
	};
}
