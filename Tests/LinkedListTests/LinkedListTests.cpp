//#include "pch.h"
#include "CppUnitTest.h"
#include "../../LinkedList/src/List.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LinkedListTests
{
	TEST_CLASS(LinkedListTests)
	{
	public:
		TEST_METHOD(constructor_ShouldBeEmpty)
		{
			List<int> newList;
			int actual = (int)newList.size();

			Assert::AreEqual(0, actual);
		}

		TEST_METHOD(constructor_initializerlist_shouldHaveSizeFour)
		{
			List<int> newList{ 2, 2, 2, 2 };
			int actual = (int)newList.size();

			Assert::AreEqual(4, actual);
		}
		
		TEST_METHOD(pushfront_onEmptyList_ShouldContainOneElement)
		{
			List<int> expected{ 1 };
			List<int> actual;
			actual.push_front(1);

			Assert::AreEqual(1, (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();
			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}

		TEST_METHOD(pushback_onEmptyList_ShouldContainOneElement)
		{
			List<int> expected{ 1 };
			List<int> actual;
			actual.push_back(1);

			Assert::AreEqual(1, (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();
			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}

		TEST_METHOD(pushback_onListSizeFour_ShouldHaveCorrectValue)
		{
			List<int> expected{ 2, 2, 2, 2, 1 };
			List<int> actual{ 2, 2, 2, 2 };
			actual.push_back(1);

			Assert::AreEqual((int)actual.size(), (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();
			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}

		TEST_METHOD(pushfront_onListSizeFour_ShouldHaveCorrectValue)
		{
			List<int> expected{ 1, 2, 2, 2, 2 };
			List<int> actual{ 2, 2, 2, 2 };
			actual.push_front(1);

			Assert::AreEqual((int)actual.size(), (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();
			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}
		
		TEST_METHOD(popfront_onEmptyList_ShouldContainOneElement)
		{
			List<int> expected;
			List<int> actual{ 2 };
			actual.pop_front();

			Assert::AreEqual(0, (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();
			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}

		TEST_METHOD(popback_onEmptyList_ShouldContainOneElement)
		{
			List<int> expected;
			List<int> actual{ 2 };;
			actual.pop_back();

			Assert::AreEqual(0, (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();
			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}

		TEST_METHOD(popback_onListSizeFour_ShouldHaveCorrectValue)
		{
			List<int> expected{ 2, 2, 2, 2};
			List<int> actual{ 2, 2, 2, 2, 1 };
			actual.pop_back();

			Assert::AreEqual((int)actual.size(), (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();
			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}

		TEST_METHOD(popfront_onListSizeFour_ShouldHaveCorrectValue)
		{
			List<int> expected{ 2, 2, 2, 2 };
			List<int> actual{ 1, 2, 2, 2, 2 };
			actual.pop_front();

			Assert::AreEqual((int)actual.size(), (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();
			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}

		TEST_METHOD(insert_ShouldHaveCorrectValue)
		{
			List<int> expected{ 1, 1, 3, 1, 1, 1 };
			List<int> actual{ 1, 1, 1, 1, 1 };
			List<int>::Iterator it = actual.begin();
			it++;
			it++;
			actual.insert(it, 3);

			Assert::AreEqual((int)actual.size(), (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();
			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}

		TEST_METHOD(insert_onEmptyList_ShouldBeEmpty)
		{
			List<int> expected;
			List<int> actual;
			List<int>::Iterator it = actual.begin();
			actual.insert(it, 3);

			Assert::AreEqual((int)actual.size(), (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();
			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}

		TEST_METHOD(insert_atFront)
		{
			List<int> expected{ 3, 1, 1, 1, 1, 1 };
			List<int> actual{ 1, 1, 1, 1, 1 };
			List<int>::Iterator it = actual.begin();
			actual.insert(it, 3);

			Assert::AreEqual((int)actual.size(), (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();
			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}

		TEST_METHOD(insert_atBack)
		{
			List<int> expected{ 1, 1, 1, 1, 1, 3 };
			List<int> actual{ 1, 1, 1, 1, 1 };
			List<int>::Iterator it = actual.end();
			actual.insert(it, 3);

			Assert::AreEqual((int)actual.size(), (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();
			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}

		TEST_METHOD(erase_atFront)
		{
			List<int> expected{ 1, 1, 1, 1, 1 };
			List<int> actual{ 3, 1, 1, 1, 1, 1 };
			List<int>::Iterator it = actual.begin();
			actual.erase(it);

			Assert::AreEqual((int)actual.size(), (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();
			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}

		TEST_METHOD(erase_atBack)
		{
			List<int> expected{ 1, 1, 1, 1, 1 };
			List<int> actual{ 1, 1, 1, 1, 1, 3 };
			List<int>::Iterator it = actual.end();
			actual.erase(it);

			Assert::AreEqual((int)actual.size(), (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();
			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}

		TEST_METHOD(erase_threeElements)
		{
			List<int> expected{ 1, 1, 1, 1, 1 };
			List<int> actual{ 1, 1, 3, 3, 3, 1, 1, 1 };
			List<int>::Iterator start = actual.begin();

			while (*start != 3)
				start++;

			List<int>::Iterator end = start;

			while (*end != 1)
				end++;

			actual.erase(start, end);

			Assert::AreEqual((int)actual.size(), (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();

			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}

		TEST_METHOD(erase_lastThreeElements)
		{
			List<int> expected{ 1, 1, 1, 1, 1 };
			List<int> actual{ 1, 1, 1, 1, 1, 3, 3, 3 };
			List<int>::Iterator start = actual.begin();
			List<int>::Iterator end = actual.end();

			while (*start != 3)
				start++;

			actual.erase(start, end);

			Assert::AreEqual((int)actual.size(), (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();

			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}

		TEST_METHOD(erase_firstThreeElements)
		{
			List<int> expected{ 1, 1, 1, 1, 1 };
			List<int> actual{3, 3, 3, 1, 1, 1, 1, 1 };
			List<int>::Iterator start = actual.begin();
			List<int>::Iterator end = actual.begin();

			while (*end != 1)
				end++;

			actual.erase(start, end);

			Assert::AreEqual((int)actual.size(), (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();

			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}

		TEST_METHOD(clear_ShouldBeEmpty)
		{
			List<int> expected;
			List<int> actual{3, 3, 3, 1, 1, 1, 1, 1 };
			actual.clear();

			Assert::AreEqual((int)actual.size(), (int)actual.size());
			Assert::IsTrue(actual.empty());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();

			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}

		TEST_METHOD(reverse)
		{
			List<int> expected{ 3, 21, 4, 3, 22, 5, 23 };
			List<int> actual{ 23, 5, 22, 3, 4, 21, 3 };
			actual.reverse();

			Assert::AreEqual((int)actual.size(), (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();

			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}

		TEST_METHOD(sort_ascending)
		{
			List<int> expected{ 3, 3, 4, 5, 21, 22, 23 };
			List<int> actual{ 23, 5, 22, 3, 4, 21, 3 };
			actual.sort();

			Assert::AreEqual((int)actual.size(), (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();

			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}

		TEST_METHOD(sort_descending)
		{
			List<int> expected{ 23, 22, 21, 5, 4, 3, 3 };
			List<int> actual{ 23, 5, 22, 3, 4, 21, 3 };
			actual.sort(std::greater<int>());

			Assert::AreEqual((int)actual.size(), (int)actual.size());

			List<int>::Iterator exp = expected.begin();
			List<int>::Iterator act = actual.begin();

			while (exp != expected.end() && act != actual.end())
			{
				Assert::IsTrue(*exp == *act);
				exp++;
				act++;
			}
		}
	};
}
