#include "pch.h"
#include "CppUnitTest.h"
#include "../../LinkedList/src/List.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LinkedListTests
{
	TEST_CLASS(LinkedListTests)
	{
	public:
		
		TEST_METHOD(pushfront_onEmptyList_ShouldContainOneElement)
		{
			List<int> expected{ 1 };
			List<int> actual;
			actual.push_front(1);

			Assert::AreEqual(1, (int)actual.Size());

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
