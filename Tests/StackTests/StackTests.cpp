#include "CppUnitTest.h"
#include "../../Stack/src/Stack.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StackTests
{
	TEST_CLASS(StackTests)
	{
	public:
		
		TEST_METHOD(Default_Constructor)
		{
			Stack<int> stack;

			Assert::IsTrue(stack.empty());
		}
		
		TEST_METHOD(Copy_Constructor)
		{
			Stack<int> stack;
			stack.push(1);
			stack.push(2);
			stack.push(3);

			Stack<int> copy(stack);

			Assert::IsFalse(stack.empty());
			Assert::IsTrue(stack.size() == copy.size());

			while (!stack.empty())
			{
				Assert::AreEqual(stack.top(), copy.top());
				stack.pop();
				copy.pop();
			}
		}
		
		TEST_METHOD(InitializerList_Constructor)
		{
			Stack<int> stack{ 1, 2, 3, 4, 5 };

			Assert::IsFalse(stack.empty());
		}
		
		TEST_METHOD(Top_ShouldReturnFirstOnTheStack)
		{
			Stack<int> stack{ 1, 2, 3, 4, 5 };

			Assert::IsFalse(stack.empty());
			Assert::IsTrue(stack.top() == 1);
		}
		
		TEST_METHOD(Pop_EmptyStack)
		{
			Stack<int> stack;
			stack.pop();

			Assert::IsTrue(stack.empty());
			Assert::IsTrue(stack.size() == 0);
		}
		
		TEST_METHOD(Pop_ShouldRemoveFirstOnStack)
		{
			Stack<int> expected{ 2, 3, 4, 5 };
			Stack<int> actual{ 1, 2, 3, 4, 5 };

			Assert::IsFalse(actual.empty());
			Assert::IsTrue(actual.top() == 1);
			actual.pop();
			Assert::IsTrue(actual.top() == 2);
			Assert::IsTrue(actual.size() == 4);

			Assert::IsTrue(actual.size() == expected.size());

			while (!actual.empty())
			{
				Assert::IsTrue(expected.top() == actual.top());
				expected.pop();
				actual.pop();
			}
		}
		
		TEST_METHOD(Pop_EntireStack_ShouldBeEmpty)
		{
			Stack<int> actual{ 1, 2, 3, 4, 5 };

			Assert::IsFalse(actual.empty());

			while (!actual.empty())
				actual.pop();

			Assert::IsTrue(actual.empty());
		}

		TEST_METHOD(Push_EmptyStack_ShouldHaveOneElement)
		{
			Stack<int> stack;
			stack.push(1);

			Assert::IsFalse(stack.empty());
			Assert::IsTrue(stack.size() == 1);
			Assert::IsTrue(stack.top() == 1);
		}

		TEST_METHOD(Push_EmptyStack_ShouldHaveTwoElements)
		{
			Stack<int> stack;
			stack.push(1);
			stack.push(2);

			Assert::IsFalse(stack.empty());
			Assert::IsTrue(stack.size() == 2);
			Assert::IsTrue(stack.top() == 2);
			stack.pop();
			Assert::IsTrue(stack.top() == 1);
		}
	};
}
