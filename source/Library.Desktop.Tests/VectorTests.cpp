#include "pch.h"
#include "CppUnitTest.h"
#include "Vector.h"
#include "ToStringSpecializations.h"
#include "Foo.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;


namespace LibraryDesktopTests
{
	TEST_CLASS(VectorTests)
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

		TEST_METHOD(Construction)
		{
			//Test default construction
			Vector<Foo> vector;
			Assert::AreEqual(size_t(0), vector.Size());
			Assert::AreEqual(size_t(0), vector.Capacity());

			//Test Copy Construction
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };
			vector.PushBack(a);
			vector.PushBack(b);
			vector.PushBack(c);
			Vector<Foo> vectorCopy(vector);
			Assert::AreEqual(vectorCopy.Size(), vector.Size());
			Assert::AreEqual(vectorCopy.Capacity(), vector.Capacity());
			Assert::AreEqual(vectorCopy[0], vector[0]);
			Assert::AreEqual(vectorCopy[1], vector[1]);
			Assert::AreEqual(vectorCopy[2], vector[2]);


		}

		TEST_METHOD(Operators)
		{
			//Test [] operator
			Vector<Foo> vector;
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };
			vector.PushBack(a);
			vector.PushBack(b);
			vector.PushBack(c);
			const Vector<Foo> constVector = vector;

			Assert::ExpectException<std::runtime_error>([&constVector]() {const Foo test = constVector[size_t(15)]; });
			Assert::ExpectException<std::runtime_error>([&vector]() {Foo test = vector[size_t(15)]; });
			Assert::AreEqual(a, vector[0]);
			Assert::AreEqual(b, vector[1]);
			Assert::AreEqual(c, vector[2]);


			//Test assignment operator
			Vector<Foo> vectorAssign;
			vectorAssign = vector;
			Assert::AreEqual(vectorAssign.Size(), vector.Size());
			Assert::AreEqual(vectorAssign.Capacity(), vector.Capacity());
			Assert::AreEqual(vectorAssign[0], vector[0]);
			Assert::AreEqual(vectorAssign[1], vector[1]);
			Assert::AreEqual(vectorAssign[2], vector[2]);

		}

		TEST_METHOD(At)
		{
			//Test ref at
			Vector<Foo> vector;
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };
			vector.PushBack(a);
			vector.PushBack(b);
			vector.PushBack(c);
			Assert::ExpectException<std::runtime_error>([&vector]() {Foo test = vector.At(size_t(-5)); });
			Assert::ExpectException<std::runtime_error>([&vector]() {Foo test = vector.At(size_t(15)); });
			Assert::AreEqual(a, vector.At(size_t(0)));

			//Test const ref at
			const Vector<Foo> vectorConst = vector;
			Assert::ExpectException<std::runtime_error>([&vectorConst]() {const Foo test = vectorConst.At(size_t(-5)); });
			Assert::ExpectException<std::runtime_error>([&vectorConst]() {const Foo test = vectorConst.At(size_t(15)); });
			Assert::AreEqual(a, vectorConst.At(size_t(0)));
		}

		TEST_METHOD(PopBack)
		{
			Vector<Foo> vector;
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };

			//Testing Empty PopBack
			Assert::ExpectException<std::runtime_error>([&vector]() {vector.PopBack(); });

			//Testing Normal PopBack
			vector.PushBack(a);
			vector.PushBack(b);
			vector.PushBack(c);
			size_t originalCapacity = vector.Capacity();
			Assert::AreEqual(size_t(3), vector.Size());
			Assert::AreEqual(originalCapacity, vector.Capacity());
			vector.PopBack();
			Assert::AreEqual(size_t(2), vector.Size());
			Assert::AreEqual(originalCapacity, vector.Capacity());
			vector.PopBack();
			Assert::AreEqual(size_t(1), vector.Size());
			Assert::AreEqual(originalCapacity, vector.Capacity());

		}

		TEST_METHOD(isEmpty)
		{
			Vector<Foo> vector;
			const Foo a{ 1 };
			Assert::IsTrue(vector.IsEmpty());
			vector.PushBack(a);
			Assert::IsFalse(vector.IsEmpty());

		}

		TEST_METHOD(Front)
		{
			//Testing Empty
			Vector<Foo> vector;
			const Foo a{ 1 };
			const Foo b{ 2 };
			Assert::ExpectException<std::runtime_error>([&vector]() {const Foo test = vector.Front(); });


			//Testing normal front
			vector.PushBack(a);
			vector.PushBack(b);
			Assert::AreEqual(a, vector.Front());

			//testing const empty
			const Vector<Foo> vectorConstEmpty;
			Assert::ExpectException<std::runtime_error>([&vectorConstEmpty]() {const Foo test = vectorConstEmpty.Front(); });

			//normal const
			const Vector<Foo> vectorConst = vector;
			Assert::AreEqual(a, vectorConst.Front());

		}

		TEST_METHOD(Back)
		{

			//Testing Empty
			Vector<Foo> vector;
			const Foo a{ 1 };
			const Foo b{ 2 };
			Assert::ExpectException<std::runtime_error>([&vector]() {const Foo test = vector.Back(); });


			//Testing normal Back
			vector.PushBack(a);
			vector.PushBack(b);
			Assert::AreEqual(b, vector.Back());

			//testing const empty
			const Vector<Foo> vectorConstEmpty;
			Assert::ExpectException<std::runtime_error>([&vectorConstEmpty]() {const Foo test = vectorConstEmpty.Back(); });

			//normal const
			const Vector<Foo> vectorConst = vector;
			Assert::AreEqual(b, vectorConst.Back());

		}

		TEST_METHOD(Size)
		{
			//Testing Empty
			Vector<Foo> vector;
			const Foo a{ 1 };
			const Foo b{ 2 };
			Assert::AreEqual(size_t(0), vector.Size());

			//Testing with
			vector.PushBack(a);
			Assert::AreEqual(size_t(1), vector.Size());

		}

		TEST_METHOD(Capacity)
		{
			//Testing Empty
			Vector<Foo> vector;
			const Foo a{ 1 };
			const Foo b{ 2 };
			Assert::AreEqual(size_t(0), vector.Capacity());

			//Testing with
			vector.PushBack(a);
			Assert::AreEqual(size_t(1), vector.Capacity());
		}

		TEST_METHOD(begin)
		{
			Vector<Foo> vector;
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };
			vector.PushBack(a);
			vector.PushBack(b);
			vector.PushBack(c);
			const Vector<Foo> cVector = vector;
			//normal begin
			Assert::AreEqual(vector.Front(), *vector.begin());
			//const begin
			Assert::AreEqual(cVector.Front(), *vector.begin());
			//cbegin
			Assert::AreEqual(vector.Front(), *vector.cbegin());

		}

		TEST_METHOD(end)
		{
			Vector<Foo> vector;
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };
			vector.PushBack(a);
			vector.PushBack(b);
			vector.PushBack(c);
			const Vector<Foo> cVector = vector;
			

			//normal end
			Assert::ExpectException<std::runtime_error>([&vector]() {*vector.end(); });
			//const end
			Assert::ExpectException<std::runtime_error>([&cVector]() {*cVector.end(); });
			//cend
			Assert::ExpectException<std::runtime_error>([&vector]() {*vector.cend(); });

		}

		TEST_METHOD(PushBack)
		{
			Vector<Foo> vector;
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };

			//test one push
			vector.PushBack(a);
			Assert::AreEqual(a, vector[0]);
			Assert::AreEqual(size_t(1), vector.Size());

			//test multiple pushes
			vector.PushBack(b);
			vector.PushBack(c);
			Assert::AreEqual(b, vector[1]);
			Assert::AreEqual(c, vector[2]);
			Assert::AreEqual(size_t(3), vector.Size());

		}

		TEST_METHOD(PushBackFunctor)
		{
			Vector<Foo> vector;
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };
			vector.PushBack(a);
			vector.PushBack(b);
			Assert::AreEqual(size_t(2), vector.Size());

			//test that we want double capacity
			vector.PushBack(c, Vector<Foo>::IncrementFunctor{2});
			Assert::AreEqual(a, vector[0]);
			Assert::AreEqual(size_t(4), vector.Capacity());
		}

		TEST_METHOD(Reserve)
		{
			Vector<Foo> vector;
			Assert::AreEqual(size_t(0), vector.Capacity());

			vector.Reserve(size_t(5));
			Assert::AreEqual(size_t(5), vector.Capacity());

		}

		TEST_METHOD(Find)
		{
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };
			const Foo d{ 4 };
			Vector<Foo> vector;
			vector.PushBack(a);
			vector.PushBack(b);
			vector.PushBack(c);
			const Vector<Foo> cvector = vector;

			//testing not found - should give end
			Assert::AreEqual(vector.end(), vector.Find(d));

			//testing const not found - should give end
			Assert::AreEqual(cvector.end(), cvector.Find(d));

			//testing normal find
			Vector<Foo>::Iterator it = vector.begin();
			++it;
			Vector<Foo>::Iterator itFind = vector.Find(b);
			Assert::AreEqual(it, itFind);

			//testing const find
			Vector<Foo>::ConstIterator itC = cvector.begin();
			++itC;
			Vector<Foo>::ConstIterator itCFind = cvector.Find(b);
			Assert::AreEqual(itC, itCFind);

		}

		TEST_METHOD(ClearShrink)
		{
			Vector<Foo> vector;
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };
			vector.PushBack(a);
			vector.PushBack(b);
			vector.PushBack(c);
			
			//Clear
			Assert::AreEqual(size_t(3), vector.Size());
			Assert::AreEqual(size_t(3), vector.Capacity());
			vector.Clear();
			Assert::AreEqual(size_t(0), vector.Size());
			Assert::AreEqual(size_t(3), vector.Capacity());

			//Shrink empty
			vector.ShrinkToFit();
			Assert::AreEqual(size_t(0), vector.Size());
			Assert::AreEqual(size_t(0), vector.Capacity());

			//shrink normal
			vector.PushBack(a);
			vector.PushBack(b);
			vector.PushBack(c);
			vector.Reserve(size_t(9));
			Assert::AreEqual(size_t(9), vector.Capacity());
			vector.ShrinkToFit();
			Assert::AreEqual(vector.Size(), vector.Capacity());

		}

		TEST_METHOD(Remove)
		{
			Vector<Foo> vector;
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };
			const Foo d{ 7 };
			vector.PushBack(a);
			vector.PushBack(b);
			vector.PushBack(c);
			
			//normal remove
			Assert::AreEqual(size_t(3), vector.Size());
			Assert::IsTrue(vector.Remove(b));
			Assert::AreEqual(size_t(2), vector.Size());

			//remove end
			Assert::AreEqual(size_t(2), vector.Size());
			Assert::IsTrue(vector.Remove(c));
			Assert::AreEqual(size_t(1), vector.Size());


			//remove not found
			Assert::AreEqual(size_t(1), vector.Size());
			Assert::IsFalse(vector.Remove(d));
			Assert::AreEqual(size_t(1), vector.Size());

		}


		TEST_METHOD(Iterator)
		{
			Vector<Foo> vector;
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };
			vector.PushBack(a);
			vector.PushBack(b);
			vector.PushBack(c);

			//testing default instantiated
			Vector<Foo>::Iterator it;
			Vector<Foo>::Iterator it2;
			Assert::ExpectException<std::runtime_error>([&it]() {it++; });
			Assert::ExpectException<std::runtime_error>([&it]() {++it; });
			Assert::ExpectException<std::runtime_error>([&it]() {it--; });
			Assert::ExpectException<std::runtime_error>([&it]() {--it; });
			Assert::IsTrue(it == it2);
			Assert::ExpectException<std::runtime_error>([&it]() {*it; });

			//test !=
			it = vector.begin();
			Assert::IsFalse(it == it2);

			//Testing for loop +
			std::size_t count = 0;
			Assert::AreEqual(size_t(0), count);
			for (Vector<Foo>::Iterator position = vector.begin(); position != vector.end(); ++position)
			{
				++count;
			}
			Assert::AreEqual(vector.Size(), count);

			//Testing for loop -
			count = 0;
			Assert::AreEqual(size_t(0), count);
			for (Vector<Foo>::Iterator position = vector.end(); position != vector.begin(); --position)
			{
				count++;
			}
			Assert::AreEqual(vector.Size(), count);

			//Testing addition
			Vector<Foo>::Iterator iterator = vector.begin();
			iterator += 2;
			Assert::AreEqual(c, *iterator);


		}

		TEST_METHOD(ConstIterator)
		{
			Vector<Foo> vector;
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };
			vector.PushBack(a);
			vector.PushBack(b);
			vector.PushBack(c);

			//testing const default instantiated
			Vector<Foo>::ConstIterator it;
			Vector<Foo>::ConstIterator it2;
			Assert::ExpectException<std::runtime_error>([&it]() {it++; });
			Assert::ExpectException<std::runtime_error>([&it]() {++it; });
			Assert::ExpectException<std::runtime_error>([&it]() {it--; });
			Assert::ExpectException<std::runtime_error>([&it]() {--it; });
			Assert::AreEqual(it, it2);
			Assert::ExpectException<std::runtime_error>([&it]() {*it; });

			//test !=
			it = vector.begin();
			Assert::IsFalse(it == it2);

			//create ConstIterator from given Iterator
			Vector<Foo>::Iterator itNonConst = vector.begin();
			Vector<Foo>::ConstIterator copyIt(itNonConst);
			Assert::AreEqual(*itNonConst, *copyIt);

			//Testing for loop +
			std::size_t count = 0;
			Assert::AreEqual(size_t(0), count);
			for (Vector<Foo>::ConstIterator position = vector.begin(); position != vector.end(); ++position)
			{
				++count;
			}
			Assert::AreEqual(vector.Size(), count);

			//Testing for loop -
			count = 0;
			Assert::AreEqual(size_t(0), count);
			for (Vector<Foo>::ConstIterator position = vector.end(); position != vector.begin(); --position)
			{
				count++;
			}
			Assert::AreEqual(vector.Size(), count);
		}

		TEST_METHOD(MoveSemantics)
		{
			Vector<Foo> vector;
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };
			vector.PushBack(a);
			vector.PushBack(b);
			vector.PushBack(c);

			//move constructor
			Vector<Foo> vectorMoved(std::move(vector));
			Assert::AreEqual(size_t(0), vector.Size());
			Assert::AreEqual(size_t(0), vector.Capacity());
			Assert::AreEqual(size_t(3), vectorMoved.Capacity());
			Assert::AreEqual(size_t(3), vectorMoved.Capacity());

			//move assignment operator
			Vector<Foo> vectorMovedOp; vectorMovedOp = std::move(vectorMoved);
			Assert::AreEqual(size_t(0), vectorMoved.Size());
			Assert::AreEqual(size_t(0), vectorMoved.Capacity());
			Assert::AreEqual(size_t(3), vectorMovedOp.Capacity());
			Assert::AreEqual(size_t(3), vectorMovedOp.Capacity());

		}

	private:
		inline static _CrtMemState _startMemState;
	};
}