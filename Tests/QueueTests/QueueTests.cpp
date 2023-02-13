#include "CppUnitTest.h"
#include "../../Queue/src/Queue.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace QueueTests
{
	TEST_CLASS(QueueTests)
	{
	public:
		
		TEST_METHOD(Queue_Constructor)
		{
			Queue<int> actual;

			Assert::IsTrue(actual.empty());

		}
		
		TEST_METHOD(Queue_Copy_Constructor)
		{
			Queue<int> queue;
			queue.push(1);
			queue.push(2);
			queue.push(3);

			Queue<int> copy(queue);

			Assert::IsFalse(queue.empty());
			Assert::IsTrue(queue.size() == copy.size());

			while (!queue.empty())
			{
				Assert::AreEqual(queue.top(), copy.top());
				queue.pop();
				copy.pop();
			}
		}

		TEST_METHOD(Queue_Constructor_InitializerList)
		{
			Queue<int> actual{ 1, 2, 3, 4, 5 };

			Assert::IsFalse(actual.empty());
		}

		TEST_METHOD(Queue_Move_Constructor)
		{
			Queue<int> moved{ 1, 2, 3, 4, 5 };
			Queue<int> actual = std::move(moved);

			Assert::IsFalse(actual.empty());
		}

		TEST_METHOD(Queue_Top)
		{
			int expected = 5;
			Queue<int> actual{ 5, 4, 3, 2, 1 };

			Assert::IsFalse(actual.empty());
			Assert::AreEqual(expected, actual.top());
		}

		TEST_METHOD(Queue_Top_PushedNewValue_ShouldNotChangeTop)
		{
			int expected = 5;
			Queue<int> actual{ 5, 4, 3, 2, 1 };

			actual.push(0);
			actual.push(9);

			Assert::IsFalse(actual.empty());
			Assert::AreEqual(expected, actual.top());
		}

		TEST_METHOD(Queue_Top_PoppedValueShouldChangeTop)
		{
			int expected = 4;
			Queue<int> actual{ 5, 4, 3, 2, 1 };

			actual.pop();

			Assert::IsFalse(actual.empty());
			Assert::AreEqual(expected, actual.top());
		}

		TEST_METHOD(Queue_Push)
		{
			size_t expected = 5;
			Queue<int> actual{ 1, 2, 3, 4, 5 };
			Assert::IsFalse(actual.empty());

			Assert::AreEqual(expected, actual.size());

			actual.push(6);
			expected++;

			Assert::AreEqual(expected, actual.size());
		}

		TEST_METHOD(Queue_Pop)
		{
			size_t expected = 5;
			Queue<int> actual{ 1, 2, 3, 4, 5 };
			Assert::IsFalse(actual.empty());

			Assert::AreEqual(expected, actual.size());

			actual.pop();
			expected--;

			Assert::AreEqual(expected, actual.size());
		}

		TEST_METHOD(Queue_Pop_AllValuesShouldBeEmpty)
		{
			Queue<int> actual{ 1, 2, 3, 4, 5 };
			Assert::IsFalse(actual.empty());

			actual.pop();
			actual.pop();
			actual.pop();
			actual.pop();
			actual.pop();

			Assert::IsTrue(actual.empty());
		}

		TEST_METHOD(Queue_Clear)
		{
			size_t expected = 5;
			Queue<int> actual{ 1, 2, 3, 4, 5 };
			Assert::IsFalse(actual.empty());

			Assert::AreEqual(expected, actual.size());

			actual.clear();
			expected = 0;

			Assert::AreEqual(expected, actual.size());
			Assert::IsTrue(actual.empty());
		}
	};
}
