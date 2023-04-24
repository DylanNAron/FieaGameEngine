#include "pch.h"
#include "CppUnitTest.h"
#include "SList.h"
#include "ToStringSpecializations.h"
#include "Foo.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;


namespace LibraryDesktopTests
{
	TEST_CLASS(SListTests)
	{

	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &_startMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(Constructor)
		{

			SList<Foo> list;
			Assert::AreEqual(size_t(0), list.Size());
		
			Assert::ExpectException<std::runtime_error>([&list]() {auto& front = list.Front(); UNREFERENCED_LOCAL(front); });
			Assert::ExpectException<std::runtime_error>([&list]() {auto& back = list.Back(); UNREFERENCED_LOCAL(back); });
		}

		TEST_METHOD(Front)
		{
			//testing non const
			// 
			//testing 0
			SList<Foo> listEmpty;
			Assert::ExpectException<std::runtime_error>([&listEmpty]() {auto& front = listEmpty.Front(); UNREFERENCED_LOCAL(front); });
			//testing multiple
			SList<Foo> list;
			Foo a{ 1 };
			Foo b{ 1 };
			list.PushFront(a);
			list.PushFront(b);
			Assert::AreEqual(b.Data(), list.Front().Data());

			//testing const
			//testin 0
			const SList<Foo> emptyList;
			Assert::ExpectException<std::runtime_error>([&emptyList]() {auto& front =  emptyList.Front(); UNREFERENCED_LOCAL(front); });
			//testing multiple
			const SList<Foo> listConst = list;
			Assert::AreEqual(b.Data(), listConst.Front().Data());
		}

		TEST_METHOD(Back)
		{
			//testing non const
			// 
			//testing 0
			SList<Foo> listEmpty;
			Assert::ExpectException<std::runtime_error>([&listEmpty]() {auto& back = listEmpty.Back(); UNREFERENCED_LOCAL(back);  });
			//testing multiple
			SList<Foo> list;
			Foo a{ 1 };
			Foo b{ 1 };
			list.PushBack(a);
			list.PushBack(b);
			Assert::AreEqual(b.Data(), list.Back().Data());

			//testing const
			//testin 0
			const SList<Foo> emptyList;
			Assert::ExpectException<std::runtime_error>([&emptyList]() {auto& back = emptyList.Back(); UNREFERENCED_LOCAL(back); });
			//testing multiple
			const SList<Foo> listConst = list;
			Assert::AreEqual(b.Data(), listConst.Back().Data());

		}

		TEST_METHOD(PushFront)
		{
			const Foo a(10);
			const Foo b(20);
			const Foo c(20);
			SList<Foo> list;
			Assert::AreEqual(size_t(0), list.Size());
			list.PushFront(a);
			Assert::AreEqual(size_t(1), list.Size());
			Assert::AreEqual(list.Front(), list.Back());
			Assert::AreEqual(a, list.Front());
			Assert::AreNotSame(a, list.Front());
			list.PushFront(b);
			Assert::AreEqual(size_t(2), list.Size());
			Assert::AreNotEqual(list.Front(), list.Back()); 
			Assert::AreEqual(a, list.Back()); 
			Assert::AreEqual(b, list.Front()); 
			list.PushFront(c);
			Assert::AreEqual(size_t(3), list.Size());
			Assert::AreNotEqual(list.Front(), list.Back());
			Assert::AreEqual(a, list.Back());
			Assert::AreEqual(c, list.Front()); 

		}

		TEST_METHOD(PushBack)
		{
			SList<Foo> list;
			Foo testNode{ 1 };
			list.PushBack(testNode);

			Assert::AreEqual(size_t(1), list.Size());

			Assert::AreEqual(testNode.Data(), list.Back().Data());
		}

		TEST_METHOD(PopFront)
		{
			Foo testNode{ 1 };
			Foo testNode2{ 2 };

			//testing size 0
			SList<Foo> list;
			Assert::ExpectException<std::runtime_error>([&list]() {list.PopFront();});

			//testing size of 1
			SList<Foo> list1;
			list1.PushBack(testNode);
			Assert::AreEqual(size_t(1), list1.Size());
			list1.PopFront();
			Assert::AreEqual(size_t(0), list1.Size());

			//testing size larger
			SList<Foo> list2;
			list2.PushBack(testNode);
			list2.PushBack(testNode2);
			list2.PushBack(testNode);
			Assert::AreEqual(size_t(3), list2.Size());
			list2.PopFront();
			list2.PopFront();
			list2.PopFront();
			Assert::AreEqual(size_t(0), list2.Size());


		}


		TEST_METHOD(PopBack)
		{
			Foo testNode{ 1 };
			Foo testNode2{ 2 };
			//testing size 0
			SList<Foo> list;
			Assert::ExpectException<std::runtime_error>([&list]() {list.PopBack(); });

			//testing size of 1
			SList<Foo> list1;
			list1.PushBack(testNode);
			Assert::AreEqual(size_t(1), list1.Size());
			list1.PopBack();
			Assert::AreEqual(size_t(0), list1.Size());

			//testing size larger
			SList<Foo> list2;
			list2.PushBack(testNode);
			list2.PushBack(testNode2);
			list2.PushBack(testNode);
			Assert::AreEqual(size_t(3), list2.Size());
			list2.PopBack();
			list2.PopBack();
			list2.PopBack();
			Assert::AreEqual(size_t(0), list2.Size());

		}

		TEST_METHOD(isEmpty)
		{
			SList<Foo> list;

			Assert::IsTrue(list.isEmpty());

			Foo testNode{ 1 };
			list.PushBack(testNode);

			Assert::IsFalse(list.isEmpty());

		}



		TEST_METHOD(CopySemantics)
		{
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };

			SList<Foo> list;
			list.PushBack(a);
			list.PushBack(b);
			list.PushBack(c);
			Assert::AreEqual(size_t(3), list.Size());
			Assert::AreEqual(a, list.Front());
			Assert::AreEqual(c, list.Back());

			{
				// Testing the copy constructor
				SList<Foo> list2 = list;
				Assert::AreEqual(size_t(3), list2.Size());
				Assert::AreEqual(a, list2.Front());
				Assert::AreEqual(c, list2.Back());
			}

			{
				// Testing copy assignment operator
				SList<Foo> list2;
				Assert::AreEqual(size_t(0), list2.Size());
				list2 = list;
				Assert::AreEqual(size_t(3), list2.Size());
				Assert::AreEqual(a, list2.Front());
				Assert::AreEqual(c, list2.Back());
			}

		}


		TEST_METHOD(TestClear)
		{
			SList<Foo> list;
			Foo testNode{1};
			list.PushFront(testNode); 

			list.Clear();
			Assert::AreEqual(size_t(0), list.Size());
			list.Clear();
			Assert::AreEqual(size_t(0), list.Size());
		}

		TEST_METHOD(IteratorBegin)
		{
			SList<Foo> list;
			Foo testNode{ 1 };
			list.PushFront(testNode);

			const SList<Foo> cList = list;

			//normal begin
			Assert::AreEqual(list.Front(), *list.begin());
			//const begin
			Assert::AreEqual(cList.Front(), *list.begin());
			//cbegin
			Assert::AreEqual(list.Front(), *list.cbegin());

		}
		
		TEST_METHOD(IteratorEnd)
		{
			SList<Foo> list;
			Foo testNode{ 1 };
			list.PushBack(testNode);
			
			const SList<Foo> cList = list;

			//normal end
			Assert::ExpectException<std::runtime_error>([&list]() {*list.end(); });
			//const end
			Assert::ExpectException<std::runtime_error>([&cList]() {*cList.end(); });
			//cend
			Assert::ExpectException<std::runtime_error>([&list]() {*list.cend(); });

		}

		TEST_METHOD(IteratorInsertAfter)
		{
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };
			const Foo d{ 777 };
			const Foo e{ 77 };
			SList<Foo> list;
			list.PushBack(a);
			list.PushBack(b);
			list.PushBack(c);
			SList<Foo>::Iterator it2;

			//test wrong container
			Assert::ExpectException<std::runtime_error>([&list, &d, &it2]() {list.InsertAfter(d, it2); });

			//test if end
			list.InsertAfter(d, list.end());
			Assert::AreEqual(list.Back().Data(), d.Data());
			Assert::AreNotEqual(list.end(), list.Find(d));

			//test normal insert
			SList<Foo>::Iterator it = list.begin();
			++it;
			list.InsertAfter(e, it);
			Assert::AreNotEqual(list.end(), list.Find(e));

			list.PopFront();
			list.PopFront();
			Assert::AreEqual(list.Front().Data(), e.Data());

		}

		TEST_METHOD(IteratorFind)
		{
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };
			const Foo d{ 4 };
			SList<Foo> list;
			list.PushBack(a);
			list.PushBack(b);
			list.PushBack(c);
			const SList<Foo> cList = list;
			
			//testing not found - should give end
			Assert::AreEqual(list.end(), list.Find(d));
			
			//testing const not found - should give end
			Assert::AreEqual(cList.end(), cList.Find(d));

			//testing normal find
			SList<Foo>::Iterator it = list.begin();
			++it;
			SList<Foo>::Iterator itFind = list.Find(b);
			Assert::AreEqual(it, itFind);

			//testing const find
			SList<Foo>::ConstIterator itC = cList.begin();
			++itC;
			SList<Foo>::ConstIterator itCFind = cList.Find(b);
			Assert::AreEqual(itC, itCFind);

		}

		TEST_METHOD(IteratorRemove)
		{
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };
			const Foo d{ 4 };
			const Foo e{ 7 };

			SList<Foo> list;
			list.PushBack(a);
			list.PushBack(b);
			list.PushBack(c);
			list.PushBack(d);

			//testing null remove
			Assert::IsFalse(list.Remove(e));

			//testing normal remove
			Assert::AreEqual(size_t(4), list.Size());
			Assert::IsTrue(list.Remove(c));
			Assert::AreEqual(size_t(3), list.Size());
			Assert::AreEqual(list.end(), list.Find(c));


			//testing tail remove
			Assert::AreEqual(size_t(3), list.Size());
			Assert::IsTrue(list.Remove(d));
			Assert::AreEqual(size_t(2), list.Size());
			Assert::AreEqual(list.end(), list.Find(d));

			//testing head remove
			Assert::AreEqual(size_t(2), list.Size());
			Assert::IsTrue(list.Remove(a));
			Assert::AreEqual(size_t(1), list.Size());
			Assert::AreEqual(list.end(), list.Find(a));

		}


		TEST_METHOD(IteratorOperators)
		{
			//testing const iterators
			SList<Foo>::ConstIterator itc;
			SList<Foo>::ConstIterator itc2;
			Assert::ExpectException<std::runtime_error>([&itc]() {itc++; });
			Assert::ExpectException<std::runtime_error>([&itc]() {++itc; });
			//default instantied iterators should be equal bc null
			Assert::IsTrue(itc == itc2);
			Assert::IsFalse(itc != itc2);


			//testing default iterators
			SList<Foo>::Iterator it;
			SList<Foo>::Iterator it2;

			Assert::ExpectException<std::runtime_error>([&it]() {it++; });
			Assert::ExpectException<std::runtime_error>([&it]() {++it; });
			//default instantied iterators should be equal bc null
			Assert::IsTrue(it == it2);

			//Testing ForLoop
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };
			SList<Foo> list;
			list.PushBack(a);
			list.PushBack(b);
			list.PushBack(c);
			std::size_t count = 0;
			Assert::AreEqual(size_t(0), count);
			for (SList<Foo>::Iterator position = list.begin(); position != list.end(); ++position)
			{
				++count;
			}
			Assert::AreEqual(list.Size(), count);


			//testing ForLoop Const
			count = 0;
			const SList<Foo> listC = list;
			Assert::AreEqual(size_t(0), count);
			for (Foo foo : listC)
			{
				++count;
			}
			Assert::AreEqual(list.Size(), count);

			//testing constructing constiterator from a normal iterator
			SList<Foo>::ConstIterator itCconvert = (SList<Foo>::ConstIterator)list.begin();
			Assert::AreEqual(*itCconvert, *listC.begin());

			//testing iterators from different lists
			SList<Foo> listA;
			SList<Foo> listB;
			Assert::AreNotEqual(listA.begin(), listB.begin());
			Assert::IsFalse(listA.begin() == listB.begin());

			//testing const iterators from different lists
			const SList<Foo> listAC;
			const SList<Foo> listBC;
			Assert::AreNotEqual(listAC.begin(), listBC.begin());
			Assert::IsFalse(listAC.begin() == listBC.begin());

		}

	private:
		inline static _CrtMemState _startMemState;
	};
}
