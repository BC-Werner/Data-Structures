#include "CppUnitTest.h"
#include "../../BinaryTree/src/BinaryTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BinaryTreeTests
{
	TEST_CLASS(BinaryTreeTests)
	{
	public:
		
		TEST_METHOD(Constructor_ShouldBeEmpty)
		{
			BinaryTree<int> bst;

			Assert::IsTrue(bst.empty());
		}
		
		TEST_METHOD(InitializerListConstructor)
		{
			BinaryTree<int> bst{ 3, 1, 4, 5, 2 };
			size_t expected = 5;

			Assert::IsFalse(bst.empty());
			Assert::AreEqual(expected, bst.size());

			BinaryTree<int>::Iterator iter = bst.begin();
			for (int i = 1; i <= bst.size(); i++)
			{
				Assert::AreEqual(i, *iter);
				iter++;
			}
		}
		
		TEST_METHOD(CopyConstructor)
		{
			BinaryTree<int> original{ 4, 2, 5, 1, 3 };
			BinaryTree<int> copy(original);

			Assert::IsFalse(copy.empty());
			Assert::AreEqual(original.size(), copy.size());

			BinaryTree<int>::Iterator oIter = original.begin();
			BinaryTree<int>::Iterator cIter = copy.begin();

			while (oIter != original.end() && cIter != copy.end())
			{
				Assert::AreEqual(*oIter, *cIter);

				oIter++;
				cIter++;
			}
		}
		
		TEST_METHOD(MoveConstructor)
		{
			BinaryTree<int> original{ 4, 2, 5, 1, 3 };
			size_t expected_size = original.size();
			BinaryTree<int> move(std::move(original));

			Assert::IsFalse(move.empty());
			Assert::AreEqual(expected_size, move.size());

			BinaryTree<int>::Iterator iter = move.begin();
			for (int i = 1; i <= move.size(); i++)
			{
				Assert::AreEqual(i, *iter);
				iter++;
			}
		}

		TEST_METHOD(insert_onEmptyTree_ShouldHaveOneNode)
		{
			BinaryTree<int> bst;
			bst.insert(5);
			size_t expected_size = 1;

			Assert::IsFalse(bst.empty());
			Assert::AreEqual(expected_size, bst.size());
		}

		TEST_METHOD(find_shouldReturnCorrectIterator)
		{
			BinaryTree<int> bst{ 44, 22, 64, 245, 67 , 65, 43, 21, 99 };
			size_t expected_size = 9;
			int expected_value = 245;
			BinaryTree<int>::Iterator found = bst.find(245);

			Assert::IsFalse(bst.empty());
			Assert::AreEqual(expected_size, bst.size());
			Assert::IsTrue(found != bst.end());
			Assert::AreEqual(expected_value, *found);
		}

		TEST_METHOD(find_shouldReturnIteratorToEnd)
		{
			BinaryTree<int> bst{ 44, 22, 64, 245, 67 , 65, 43, 21, 99 };
			size_t expected_size = 9;
			BinaryTree<int>::Iterator found = bst.find(1);

			Assert::IsFalse(bst.empty());
			Assert::AreEqual(expected_size, bst.size());
			Assert::IsTrue(found == bst.end());
		}

		TEST_METHOD(iteration_shouldBeSorted)
		{
			BinaryTree<int> bst{ 44, 22, 64, 245, 67 , 65, 43, 21, 99 };
			size_t expected_size = 9;

			Assert::IsFalse(bst.empty());
			Assert::AreEqual(expected_size, bst.size());

			BinaryTree<int>::Iterator current = bst.begin();
			BinaryTree<int>::Iterator trailing = current++;

			while (current != bst.end() && trailing != bst.end())
			{
				Assert::IsTrue(*current > *trailing);
				current++;
				trailing++;
			}
		}
	};
}
