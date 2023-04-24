#include "pch.h"
#include "CppUnitTest.h"
#include "ToStringSpecializations.h"
#include "Foo.h"
#include "Datum.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;


namespace LibraryDesktopTests
{
	TEST_CLASS(DatumTests)
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
			{
				Datum d;
				Assert::AreEqual(size_t(0), d.Size());
				Assert::AreEqual(size_t(0), d.Capacity());
				Assert::IsTrue(Datum::DatumTypes::Unknown == d.Type());
			}

			{
				Datum d(2, Datum::DatumTypes::Float);
				Assert::AreEqual(size_t(2), d.Size());
				Assert::IsTrue(Datum::DatumTypes::Float == d.Type());
			}

		}

		TEST_METHOD(CopyConstructor)
		{
			//Internal

			{

				Datum d{ 1, 2, 3 };
				Datum c(d);
				Assert::AreEqual(size_t(3), c.Size());
				Assert::IsTrue(Datum::DatumTypes::Integer == c.Type());

			}

			{
				Datum d{ 1.f, 2.f, 3.f };
				Datum c(d);
				Assert::AreEqual(size_t(3), c.Size());
				Assert::IsTrue(Datum::DatumTypes::Float == c.Type());
			}

			{
				Datum d{ glm::vec4(1), glm::vec4(2), glm::vec4(3) };
				Datum c(d);
				Assert::AreEqual(size_t(3), c.Size());
				Assert::IsTrue(Datum::DatumTypes::Vector == c.Type());

			}

			{
				Datum d{ glm::mat4(1), glm::mat4(2), glm::mat4(3) };
				Datum c(d);
				Assert::AreEqual(size_t(3), c.Size());
				Assert::IsTrue(Datum::DatumTypes::Matrix == c.Type());

			}

			{
				Datum d{ std::string("apple"), std::string("banana"), std::string("mango") };
				Datum c(d);
				Assert::AreEqual(size_t(3), c.Size());
				Assert::IsTrue(Datum::DatumTypes::String == c.Type());
			}

			{
				Foo foo1{ 1 };
				Foo foo2{ 2 };
				Foo foo3{ 3 };
				RTTI* a = &foo1;
				RTTI* b = &foo2;
				RTTI* c = &foo3;
				Datum d{ a, b, c };

				Datum copy(d);

				Assert::AreEqual(size_t(3), copy.Size());
				Assert::IsTrue(Datum::DatumTypes::Pointer == copy.Type());

			}

			//External
			{

				Datum d;
				std::string str{ "Helllo" };
				d.SetStorageString(&str, std::size(str));

				Datum c(d);
				Assert::AreEqual(size_t(6), c.Size());
				Assert::AreEqual(size_t(6), c.Capacity());
				Assert::IsTrue(Datum::DatumTypes::String == c.Type());
				Assert::IsTrue( c.IsExternal());

			}


		}

		TEST_METHOD(CopyAssignment)
		{
			//Internal

			{

				Datum d{ 1, 2, 3 };
				Datum c;
				c = d;
				Assert::AreEqual(size_t(3), c.Size());
				Assert::IsTrue(Datum::DatumTypes::Integer == c.Type());

			}

			{
				Datum d{ 1.f, 2.f, 3.f };
				Datum c;
				c = d;
				Assert::AreEqual(size_t(3), c.Size());
				Assert::IsTrue(Datum::DatumTypes::Float == c.Type());
			}

			{
				Datum d{ glm::vec4(1), glm::vec4(2), glm::vec4(3) };
				Datum c;
				c = d;
				Assert::AreEqual(size_t(3), c.Size());
				Assert::IsTrue(Datum::DatumTypes::Vector == c.Type());

			}

			{
				Datum d{ glm::mat4(1), glm::mat4(2), glm::mat4(3) };
				Datum c;
				c = d;
				Assert::AreEqual(size_t(3), c.Size());
				Assert::IsTrue(Datum::DatumTypes::Matrix == c.Type());

			}

			{
				Datum d{ std::string("apple"), std::string("banana"), std::string("mango") };
				Datum c;
				c = d;
				Assert::AreEqual(size_t(3), c.Size());
				Assert::IsTrue(Datum::DatumTypes::String == c.Type());
			}

			{
				Foo foo1{ 1 };
				Foo foo2{ 2 };
				Foo foo3{ 3 };
				RTTI* a = &foo1;
				RTTI* b = &foo2;
				RTTI* c = &foo3;
				Datum d{ a, b, c };

				Datum copy;
				copy = d;

				Assert::AreEqual(size_t(3), copy.Size());
				Assert::IsTrue(Datum::DatumTypes::Pointer == copy.Type());

			}

			//External
			{

				Datum d;
				std::string str{ "Helllo" };
				d.SetStorageString(&str, std::size(str));

				Datum c;
				c = d;
				Assert::AreEqual(size_t(6), c.Size());
				Assert::AreEqual(size_t(6), c.Capacity());
				Assert::IsTrue(Datum::DatumTypes::String == c.Type());
				Assert::IsTrue(c.IsExternal());

			}


		}

		TEST_METHOD(AssignmentOperatorOverloads)
		{

			{

				Datum d;
				d = 1;
				Assert::AreEqual(size_t(1), d.Size());
				Assert::IsTrue(Datum::DatumTypes::Integer == d.Type());

			}

			{
				Datum d;
				d = 1.f;
				Assert::AreEqual(size_t(1), d.Size());
				Assert::IsTrue(Datum::DatumTypes::Float == d.Type());
			}

			{
				Datum d;
				d = glm::vec4(1);
				Assert::AreEqual(size_t(1), d.Size());
				Assert::IsTrue(Datum::DatumTypes::Vector == d.Type());

			}

			{
				Datum d;
				d = glm::mat4(1);
				Assert::AreEqual(size_t(1), d.Size());
				Assert::IsTrue(Datum::DatumTypes::Matrix == d.Type());

			}

			{
				Datum d;
				d = std::string("mango");
				Assert::AreEqual(size_t(1), d.Size());
				Assert::IsTrue(Datum::DatumTypes::String == d.Type());
			}

			{
				Foo foo1{ 1 };
				RTTI* a = &foo1;
				Datum d;
				d = a;

				Assert::AreEqual(size_t(1), d.Size());
				Assert::IsTrue(Datum::DatumTypes::Pointer == d.Type());

			}


		}


		TEST_METHOD(ComparisonOperator)
		{

			{
				//default
				Datum a;
				Datum b;
				Assert::IsTrue(a == b);

			}


			{
				//datum int and int
				Datum d{ 1, 2, 3 };
				Datum c = d;
				Datum diff{ 1, 5, 7};
				Assert::IsTrue(c == d);
				Assert::IsTrue(c != diff);

				Datum i{ 5 };
				Assert::IsTrue(i == 5);
				Assert::IsTrue(i != 7);

				Assert::IsFalse(i == 7.f);

			}

			{
				//datum float and float
				Datum d{ 1.f, 2.f, 3.f };
				Datum c = d;
				Datum diff{ 1.f, 4.f, 7.f};
				Assert::IsTrue(c == d);
				Assert::IsTrue(c != diff);

				Datum i{ 5.f };
				Assert::IsTrue(i == 5.f);
				Assert::IsTrue(i != 7.f);

				Assert::IsFalse(i == 7);

			}

			{
				//datum vec and vec
				Datum d{ glm::vec4(1), glm::vec4(2), glm::vec4(3) };
				Datum c = d;
				Datum diff{ glm::vec4(3), glm::vec4(5), glm::vec4(3) };

				Assert::IsTrue(c == d);
				Assert::IsTrue(c != diff);

				Datum i{ glm::vec4(1) };
				Assert::IsTrue(i == glm::vec4(1));
				Assert::IsTrue(i != glm::vec4(17));

				Assert::IsFalse(i == glm::mat4(7));

			}

			{
				//datum mat and mat
				Datum d{ glm::mat4(1), glm::mat4(2), glm::mat4(3) };
				Datum c=d;
				Datum diff{ glm::mat4(3), glm::mat4(7), glm::mat4(3) };
				
				Assert::IsTrue(c == d);
				Assert::IsTrue(c != diff);

				Datum i{ glm::mat4(1) };
				Assert::IsTrue(i == glm::mat4(1));
				Assert::IsTrue(i != glm::mat4(19));


				Assert::IsFalse(i == glm::vec4(19));
			}

			{
				//datum string and string
				Datum d{ std::string("apple"), std::string("banana"), std::string("mango") };
				Datum c=d;
				Datum diff{ std::string("ale"), std::string("airplane"), std::string("mango") };
				

				Assert::IsTrue(c == d);
				Assert::IsTrue(c != diff);

				Datum i{ std::string("apple") };
				Assert::IsTrue(i == std::string("apple"));
				Assert::IsTrue(i != std::string("aircraft"));


				Foo foo1{ 1 };
				RTTI* a = &foo1;
				Assert::IsFalse(i == a);
			}

			{
				//datum pointer and pouinter
				Foo foo1{ 1 };
				Foo foo2{ 2 };
				Foo foo3{ 3 };
				RTTI* a = &foo1;
				RTTI* b = &foo2;
				RTTI* c = &foo3;

				Datum dat1{ a, b, c };
				Datum dat2 = dat1;
				Datum diff;

				Assert::IsTrue(dat1 == dat2);
				Assert::IsTrue(dat2 != diff);

				Datum i{ a };
				Assert::IsTrue(i == a);
				Assert::IsTrue(i != b);

				Assert::IsFalse(i == std::string("fake"));
			}


		}


		TEST_METHOD(MoveSemantics)
		{

			Datum d{ 1, 2, 3 };
			//move constructor
			Datum dMove(std::move(d));
			Assert::AreEqual(size_t(0), d.Size());
			Assert::AreEqual(size_t(0), d.Capacity());
			Assert::AreEqual(size_t(3), dMove.Capacity());
			Assert::AreEqual(size_t(3), dMove.Capacity());

			//move assignment operator
			Datum dMovedOp; dMovedOp = std::move(dMove);
			Assert::AreEqual(size_t(0), dMove.Size());
			Assert::AreEqual(size_t(0), dMove.Capacity());
			Assert::AreEqual(size_t(3), dMovedOp.Capacity());
			Assert::AreEqual(size_t(3), dMovedOp.Capacity());
		}

		TEST_METHOD(Reserve)
		{
			Datum d;
			Assert::AreEqual(size_t(0), d.Capacity());
			Assert::ExpectException<std::runtime_error>([&d]() {d.Reserve(5); });
			d.SetType(Datum::DatumTypes::Integer);
			d.Reserve(5);
			Assert::AreEqual(size_t(5), d.Capacity());


		}

		TEST_METHOD(Resize)
		{
			{

				Datum d;
				Assert::AreEqual(size_t(0), d.Capacity());
				Assert::AreEqual(size_t(0), d.Size());
				Assert::ExpectException<std::runtime_error>([&d]() {d.Resize(5); });
				d.SetType(Datum::DatumTypes::Integer);
				d.Resize(5);
				Assert::AreEqual(size_t(5), d.Capacity());
				Assert::AreEqual(size_t(5), d.Size());

			}

			{

				Datum d{ std::string("Apple"), std::string("Cherry"), std::string("Pear") };
				d.Resize(1);
				Assert::AreEqual(size_t(1), d.Capacity());
				Assert::AreEqual(size_t(1), d.Size());

			}

			{
				Datum d;
				int32_t a = 10;
				d.SetStorageInteger(&a, size_t(1));
				Assert::ExpectException<std::runtime_error>([&d]() {d.Resize(5); });
				
			}

			{
				Datum d{ 1, 2, 4 };
				d.Resize(0);
				Assert::ExpectException<std::out_of_range>([&d]() {int32_t a = d.GetInteger(); a; });
			}
			

		}

		TEST_METHOD(SetStorageString)
		{
			Datum d;
			std::string str{ "Helllo" };
			std::string str2{ "HELLOWORLD" };
			Assert::AreEqual(size_t(0), d.Capacity());
			Assert::AreEqual(size_t(0), d.Size());

			d.SetStorageString(&str, std::size(str));
			Assert::AreEqual(std::size(str), d.Capacity());
			Assert::AreEqual(std::size(str), d.Size());

			Assert::AreEqual(d.GetString(), str);
			str = str2;
			Assert::IsTrue(str2.compare(d.GetString()) == 0);

		}

		TEST_METHOD(SetStorageInteger)
		{

			Datum d;
			int32_t a = 10;
			Assert::AreEqual(size_t(0), d.Capacity());
			Assert::AreEqual(size_t(0), d.Size());

			d.SetStorageInteger(&a, size_t(1));
			Assert::AreEqual(size_t(1), d.Capacity());
			Assert::AreEqual(size_t(1), d.Size());

			Assert::AreEqual(d.GetInteger(), a);

		}

		TEST_METHOD(SetStorageFloat)
		{

			Datum d;
			float a = 10;
			Assert::AreEqual(size_t(0), d.Capacity());
			Assert::AreEqual(size_t(0), d.Size());

			d.SetStorageFloat(&a, size_t(1));
			Assert::AreEqual(size_t(1), d.Capacity());
			Assert::AreEqual(size_t(1), d.Size());

			Assert::AreEqual(d.GetFloat(), a);

		}

		TEST_METHOD(SetStorageVector)
		{

			Datum d;
			glm::vec4 a {10};
			Assert::AreEqual(size_t(0), d.Capacity());
			Assert::AreEqual(size_t(0), d.Size());

			d.SetStorageVector(&a, size_t(1));
			Assert::AreEqual(size_t(1), d.Capacity());
			Assert::AreEqual(size_t(1), d.Size());

			Assert::IsTrue(d.GetVector() == a);

		}

		TEST_METHOD(SetStorageMatrix)
		{

			Datum d;
			glm::mat4 a{ 10 };
			Assert::AreEqual(size_t(0), d.Capacity());
			Assert::AreEqual(size_t(0), d.Size());

			d.SetStorageMatrix(&a, size_t(1));
			Assert::AreEqual(size_t(1), d.Capacity());
			Assert::AreEqual(size_t(1), d.Size());

			Assert::IsTrue(d.GetMatrix() == a);

		}

		TEST_METHOD(SetStoragePointer)
		{

			Datum d;
			Foo foo{ 7 };
			RTTI* a = &foo;
			Assert::AreEqual(size_t(0), d.Capacity());
			Assert::AreEqual(size_t(0), d.Size());

			d.SetStoragePointer(&a, size_t(1));
			Assert::AreEqual(size_t(1), d.Capacity());
			Assert::AreEqual(size_t(1), d.Size());

			Assert::IsTrue(d.GetPointer() == a);

		}

		TEST_METHOD(PushBackString)
		{
			Datum d;
			std::string str{ "Helllo" };
			Assert::AreEqual(size_t(0), d.Capacity());
			Assert::AreEqual(size_t(0), d.Size());
			d.SetType(Datum::DatumTypes::String);
			d.PushBack(str);
			Assert::AreEqual(size_t(1), d.Capacity());
			Assert::AreEqual(size_t(1), d.Size());

		}

		TEST_METHOD(PushBackInteger)
		{
			Datum d;
			int32_t a{ 7 };
			Assert::AreEqual(size_t(0), d.Capacity());
			Assert::AreEqual(size_t(0), d.Size());
			d.PushBack(a);
			Assert::AreEqual(size_t(1), d.Capacity());
			Assert::AreEqual(size_t(1), d.Size());
			Assert::IsTrue(Datum::DatumTypes::Integer == d.Type());

		}

		TEST_METHOD(PushBackFloat)
		{
			Datum d;
			float a{ 7 };
			Assert::AreEqual(size_t(0), d.Capacity());
			Assert::AreEqual(size_t(0), d.Size());
			d.PushBack(a);
			Assert::AreEqual(size_t(1), d.Capacity());
			Assert::AreEqual(size_t(1), d.Size());
			Assert::IsTrue(Datum::DatumTypes::Float == d.Type());

		}

		TEST_METHOD(PushBackVector)
		{
			Datum d;
			glm::vec4 a{ 7 };
			Assert::AreEqual(size_t(0), d.Capacity());
			Assert::AreEqual(size_t(0), d.Size());
			d.PushBack(a);
			Assert::AreEqual(size_t(1), d.Capacity());
			Assert::AreEqual(size_t(1), d.Size());
			Assert::IsTrue(Datum::DatumTypes::Vector == d.Type());

		}

		TEST_METHOD(PushBackMatrix)
		{
			Datum d;
			float a{ 7 };
			Assert::AreEqual(size_t(0), d.Capacity());
			Assert::AreEqual(size_t(0), d.Size());
			d.PushBack(a);
			Assert::AreEqual(size_t(1), d.Capacity());
			Assert::AreEqual(size_t(1), d.Size());
			Assert::IsTrue(Datum::DatumTypes::Float == d.Type());

		}

		TEST_METHOD(PushBackPointer)
		{
			Datum d;
			Foo foo{ 7 };
			RTTI* a = &foo;
			Assert::AreEqual(size_t(0), d.Capacity());
			Assert::AreEqual(size_t(0), d.Size());
			d.PushBack(a);
			Assert::AreEqual(size_t(1), d.Capacity());
			Assert::AreEqual(size_t(1), d.Size());
			Assert::IsTrue(Datum::DatumTypes::Pointer == d.Type());

		}

		TEST_METHOD(GetString)
		{
			{

				Datum d;
				std::string str{ "Helllo" };
				d.SetType(Datum::DatumTypes::String);

				Assert::ExpectException<std::out_of_range>([&d]() {std::string a = d.GetString(); });

				d.PushBack(str);
				Assert::AreEqual(str, d.GetString());

			}

			//const version
			{
				Datum a;
				std::string str{ "Helllo" };
				a.SetType(Datum::DatumTypes::String);
				const Datum d = a;


				Assert::ExpectException<std::out_of_range>([&d]() {std::string a = d.GetString(); });

				a.PushBack(str);
				const Datum d2 = a;
				Assert::AreEqual(str, d2.GetString());
			}
		}


		TEST_METHOD(GetInteger)
		{
			{


				Datum d{ 10 };
				Assert::IsTrue(Datum::DatumTypes::Integer == d.Type());
				Assert::AreEqual(size_t(1), d.Capacity());
				Assert::AreEqual(size_t(1), d.Size());
				Assert::AreEqual(10, d.GetInteger());

				Assert::ExpectException<std::out_of_range>([&d]() {std::int32_t a = d.GetInteger(3); a; });

			}
			
			//const version
			{
				const Datum d{ 10 };
				Assert::IsTrue(Datum::DatumTypes::Integer == d.Type());
				Assert::AreEqual(size_t(1), d.Capacity());
				Assert::AreEqual(size_t(1), d.Size());
				Assert::AreEqual(10, d.GetInteger());

				Assert::ExpectException<std::out_of_range>([&d]() {std::int32_t a = d.GetInteger(3); a; });

			}


		}

		TEST_METHOD(GetFloat)
		{
			{
				Datum d{ 10.f };
				Assert::IsTrue(Datum::DatumTypes::Float == d.Type());
				Assert::AreEqual(size_t(1), d.Capacity());
				Assert::AreEqual(size_t(1), d.Size());
				Assert::AreEqual(10.f, d.GetFloat());

				Assert::ExpectException<std::out_of_range>([&d]() {float a = d.GetFloat(3); a; });
			}

			//const version
			{
				const Datum d{ 10.f };
				Assert::IsTrue(Datum::DatumTypes::Float == d.Type());
				Assert::AreEqual(size_t(1), d.Capacity());
				Assert::AreEqual(size_t(1), d.Size());
				Assert::AreEqual(10.f, d.GetFloat());

				Assert::ExpectException<std::out_of_range>([&d]() {float a = d.GetFloat(3); a; });
			}
		

		}

		TEST_METHOD(GetVector)
		{
			{
				Datum d{ glm::vec4(1) };
				Assert::IsTrue(Datum::DatumTypes::Vector == d.Type());
				Assert::AreEqual(size_t(1), d.Capacity());
				Assert::AreEqual(size_t(1), d.Size());

				Assert::IsTrue(glm::vec4(1) == d.GetVector());

				Assert::ExpectException<std::out_of_range>([&d]() {glm::vec4 v = d.GetVector(3); v; });


			}
			
			//const version
			{
				const Datum d{ glm::vec4(1) };
				Assert::IsTrue(Datum::DatumTypes::Vector == d.Type());
				Assert::AreEqual(size_t(1), d.Capacity());
				Assert::AreEqual(size_t(1), d.Size());

				Assert::IsTrue(glm::vec4(1) == d.GetVector());

				Assert::ExpectException<std::out_of_range>([&d]() {glm::vec4 v = d.GetVector(3); v; });


			}
	
		}

		TEST_METHOD(GetMatrix)
		{
			{

				Datum d{ glm::mat4(1) };
				Assert::IsTrue(Datum::DatumTypes::Matrix == d.Type());
				Assert::AreEqual(size_t(1), d.Capacity());
				Assert::AreEqual(size_t(1), d.Size());

				Assert::IsTrue(glm::mat4(1) == d.GetMatrix());

				Assert::ExpectException<std::out_of_range>([&d]() {glm::mat4 m = d.GetMatrix(3); m; });

			}
		
			//const version
			{

				const Datum d{ glm::mat4(1) };
				Assert::IsTrue(Datum::DatumTypes::Matrix == d.Type());
				Assert::AreEqual(size_t(1), d.Capacity());
				Assert::AreEqual(size_t(1), d.Size());

				Assert::IsTrue(glm::mat4(1) == d.GetMatrix());

				Assert::ExpectException<std::out_of_range>([&d]() {glm::mat4 m = d.GetMatrix(3); m; });

			}
		}

		TEST_METHOD(GetPointer)
		{
			{

				Foo a{ 10 };
				RTTI* pointer = &a;

				Datum d{ pointer };
				Assert::IsTrue(Datum::DatumTypes::Pointer == d.Type());
				Assert::AreEqual(size_t(1), d.Capacity());
				Assert::AreEqual(size_t(1), d.Size());

				Assert::IsTrue(pointer == d.GetPointer());

				Assert::ExpectException<std::out_of_range>([&d]() {RTTI* p = d.GetPointer(3); p; });

			}
			
			//const version
			{

				Foo a{ 10 };
				RTTI* pointer = &a;

				const Datum d{ pointer };
				Assert::IsTrue(Datum::DatumTypes::Pointer == d.Type());
				Assert::AreEqual(size_t(1), d.Capacity());
				Assert::AreEqual(size_t(1), d.Size());

				Assert::IsTrue(pointer == d.GetPointer());

				Assert::ExpectException<std::out_of_range>([&d]() {RTTI* p = d.GetPointer(3); p; });

			}
		

		}


		TEST_METHOD(SetString)
		{
			Datum d;
			std::string str{ "Helllo" };
			std::string str2{ "GBYEE!" };
			d.SetType(Datum::DatumTypes::String);


			Assert::ExpectException<std::out_of_range>([&d, &str2]() {d.SetString(str2); });


			d.PushBack(str);
			Assert::AreEqual(str, d.GetString());
			d.SetString(str2);
			Assert::AreEqual(str2, d.GetString());

		}

		TEST_METHOD(SetInteger)
		{
			int32_t a{ 1 };
			int32_t b{ 5 };
			Datum d { a };

			Assert::ExpectException<std::out_of_range>([&d, &a]() {d.SetInteger(a, 5); });

			Assert::AreEqual(a, d.GetInteger());
			d.SetInteger(b);
			Assert::AreEqual(b, d.GetInteger());

		}

		TEST_METHOD(SetFloat)
		{
			float a{ 1 };
			float b{ 5 };
			Datum d{ a };

			Assert::ExpectException<std::out_of_range>([&d, &a]() {d.SetFloat(a, 5); });

			Assert::AreEqual(a, d.GetFloat());
			d.SetFloat(b);
			Assert::AreEqual(b, d.GetFloat());

		}

		TEST_METHOD(SetVector)
		{
			glm::vec4 a{ 1 };
			glm::vec4 b{ 5 };
			Datum d{ a };

			Assert::ExpectException<std::out_of_range>([&d, &a]() {d.SetVector(a, 5); });

			Assert::IsTrue(a == d.GetVector());
			d.SetVector(b);
			Assert::IsTrue(b == d.GetVector());

		}

		TEST_METHOD(SetMatrix)
		{
			glm::mat4 a{ 1 };
			glm::mat4 b{ 5 };
			Datum d{ a };

			Assert::ExpectException<std::out_of_range>([&d, &a]() {d.SetMatrix(a, 5); });

			Assert::IsTrue(a == d.GetMatrix());
			d.SetMatrix(b);
			Assert::IsTrue(b == d.GetMatrix());

		}

		TEST_METHOD(SetPointer)
		{
			Foo foo1{ 1 };
			Foo foo2{ 2 };
			RTTI* a{ &foo1 };
			RTTI* b{ &foo2 };
			Datum d{ a };

			Assert::ExpectException<std::out_of_range>([&d, &a]() {d.SetPointer(a, 5); });

			Assert::IsTrue(a ==  d.GetPointer());
			d.SetPointer(b);
			Assert::IsTrue(b == d.GetPointer());

		}

		TEST_METHOD(PopBack)
		{
			{
				Datum d;
				Assert::ExpectException<std::runtime_error>([&d]() {d.PopBack(); });
			}

			{
				Datum d{ 1, 2, 3 };
				Assert::AreEqual(size_t(3), d.Size());
				d.PopBack();
				Assert::AreEqual(size_t(2), d.Size());

			}

			{
				Datum d{ std::string("HI"), std::string("HELLLO") };
				Assert::AreEqual(size_t(2), d.Size());
				d.PopBack();
				Assert::AreEqual(size_t(1), d.Size());

			}

		}

		TEST_METHOD(FrontBackInteger)
		{
			{
				Datum d;
				d.SetType(Datum::DatumTypes::Integer);
				Assert::ExpectException<std::runtime_error>([&d]() {int32_t a = d.FrontInteger(); a; });
				Assert::ExpectException<std::runtime_error>([&d]() {int32_t a = d.BackInteger(); a;  });
			}

			{
				Datum d{ 1, 2 };
				Assert::AreEqual(1, d.FrontInteger());
				Assert::AreEqual(2, d.BackInteger());

			}


			//const
			{
				Datum a;
				a.SetType(Datum::DatumTypes::Integer);
				const Datum d = a;
				Assert::ExpectException<std::runtime_error>([&d]() {int32_t a = d.FrontInteger(); a; });
				Assert::ExpectException<std::runtime_error>([&d]() {int32_t a = d.BackInteger(); a; });
			}

			{
				const Datum d{ 1, 2 };
				Assert::AreEqual(1, d.FrontInteger());
				Assert::AreEqual(2, d.BackInteger());

			}

		}


		TEST_METHOD(FrontBackFloat)
		{
			{
				Datum d;
				d.SetType(Datum::DatumTypes::Float);
				Assert::ExpectException<std::runtime_error>([&d]() {float a = d.FrontFloat(); a; });
				Assert::ExpectException<std::runtime_error>([&d]() {float a = d.BackFloat(); a;  });
			}

			{
				Datum d{ 1.f, 2.f };
				Assert::AreEqual(1.f, d.FrontFloat());
				Assert::AreEqual(2.f, d.BackFloat());

			}


			//const
			{
				Datum a;
				a.SetType(Datum::DatumTypes::Float);
				const Datum d = a;
				Assert::ExpectException<std::runtime_error>([&d]() {float a = d.FrontFloat(); a; });
				Assert::ExpectException<std::runtime_error>([&d]() {float a = d.BackFloat(); a;  });
			}

			{
				const Datum d{ 1.f, 2.f };
				Assert::AreEqual(1.f, d.FrontFloat());
				Assert::AreEqual(2.f, d.BackFloat());

			}

		}

		TEST_METHOD(FrontBackVector)
		{
			{
				Datum d;
				d.SetType(Datum::DatumTypes::Vector);
				Assert::ExpectException<std::runtime_error>([&d]() {glm::vec4 a = d.FrontVector(); a; });
				Assert::ExpectException<std::runtime_error>([&d]() {glm::vec4 a = d.BackVector(); a;  });
			}

			{
				Datum d{ glm::vec4(1), glm::vec4(2)};
				Assert::IsTrue(glm::vec4(1) == d.FrontVector());
				Assert::IsTrue(glm::vec4(2) == d.BackVector());

			}

			//const
			{
				Datum a;
				a.SetType(Datum::DatumTypes::Vector);
				const Datum d = a;
				Assert::ExpectException<std::runtime_error>([&d]() {glm::vec4 a = d.FrontVector(); a; });
				Assert::ExpectException<std::runtime_error>([&d]() {glm::vec4 a = d.BackVector(); a;  });
			}

			{
				const Datum d{ glm::vec4(1), glm::vec4(2) };
				Assert::IsTrue(glm::vec4(1) == d.FrontVector());
				Assert::IsTrue(glm::vec4(2) == d.BackVector());

			}

		}

		TEST_METHOD(FrontBackMatrix)
		{
			{
				Datum d;
				d.SetType(Datum::DatumTypes::Matrix);
				Assert::ExpectException<std::runtime_error>([&d]() {glm::mat4 a = d.FrontMatrix(); a; });
				Assert::ExpectException<std::runtime_error>([&d]() {glm::mat4 a = d.BackMatrix(); a; });
			}

			{
				Datum d{ glm::mat4(1), glm::mat4(2) };
				Assert::IsTrue(glm::mat4(1) == d.FrontMatrix());
				Assert::IsTrue(glm::mat4(2) == d.BackMatrix());

			}

			//const
			{
				Datum a;
				a.SetType(Datum::DatumTypes::Matrix);
				const Datum d = a;
				Assert::ExpectException<std::runtime_error>([&d]() {glm::mat4 a = d.FrontMatrix(); a; });
				Assert::ExpectException<std::runtime_error>([&d]() {glm::mat4 a = d.BackMatrix(); a; });
			}

			{
				const Datum d{ glm::mat4(1), glm::mat4(2) };
				Assert::IsTrue(glm::mat4(1) == d.FrontMatrix());
				Assert::IsTrue(glm::mat4(2) == d.BackMatrix());

			}

		}

		TEST_METHOD(FrontBackString)
		{
			{
				Datum d;
				d.SetType(Datum::DatumTypes::String);
				Assert::ExpectException<std::runtime_error>([&d]() {std::string a = d.FrontString(); a; });
				Assert::ExpectException<std::runtime_error>([&d]() {std::string a = d.BackString(); a; });
			}

			{
				Datum d{ std::string("front"), std::string("back")};
				Assert::AreEqual(std::string("front"), d.FrontString());
				Assert::AreEqual(std::string("back"), d.BackString());

			}

			//const
			{
				Datum a;
				a.SetType(Datum::DatumTypes::String);
				const Datum d = a;
				Assert::ExpectException<std::runtime_error>([&d]() {std::string a = d.FrontString(); a; });
				Assert::ExpectException<std::runtime_error>([&d]() {std::string a = d.BackString(); a; });
			}

			{
				const Datum d{ std::string("front"), std::string("back") };
				Assert::AreEqual(std::string("front"), d.FrontString());
				Assert::AreEqual(std::string("back"), d.BackString());

			}

		}

		TEST_METHOD(FrontBackPointer)
		{
			{
				Datum d;
				d.SetType(Datum::DatumTypes::Pointer);
				Assert::ExpectException<std::runtime_error>([&d]() {RTTI* a = d.FrontPointer(); a; });
				Assert::ExpectException<std::runtime_error>([&d]() {RTTI* a = d.BackPointer(); a; });
			}

			{
				Foo foo1{ 1 };
				Foo foo2{ 2 };
				RTTI* a = &foo1;
				RTTI* b = &foo2;
				Datum d{ a, b};
				Assert::IsTrue(a == d.FrontPointer());
				Assert::IsTrue(b == d.BackPointer());

			}

			//const
			{
				Datum a;
				a.SetType(Datum::DatumTypes::Pointer);
				const Datum d = a;
				Assert::ExpectException<std::runtime_error>([&d]() {RTTI* a = d.FrontPointer(); a; });
				Assert::ExpectException<std::runtime_error>([&d]() {RTTI* a = d.BackPointer(); a; });
			}

			{
				Foo foo1{ 1 };
				Foo foo2{ 2 };
				RTTI* a = &foo1;
				RTTI* b = &foo2;
				const Datum d{ a, b };
				Assert::IsTrue(a == d.FrontPointer());
				Assert::IsTrue(b == d.BackPointer());

			}

		}

		TEST_METHOD(FindInteger)
		{

			Datum d{ 1, 2, 3 };
			Assert::AreEqual(size_t(1), d.Find(2));
			Assert::AreEqual(size_t(SIZE_MAX), d.Find(72));

		}

		TEST_METHOD(FindFloat)
		{

			Datum d{ 1.f, 2.f, 3.f };
			Assert::AreEqual(size_t(1), d.Find(2.f));
			Assert::AreEqual(size_t(SIZE_MAX), d.Find(72.f));

		}

		TEST_METHOD(FindVector)
		{

			Datum d{ glm::vec4(1), glm::vec4(2), glm::vec4(3) };
			Assert::AreEqual(size_t(1), d.Find(glm::vec4(2)));
			Assert::AreEqual(size_t(SIZE_MAX), d.Find(glm::vec4(25)));

		}

		TEST_METHOD(FindMatrix)
		{

			Datum d{ glm::mat4(1), glm::mat4(2), glm::mat4(3) };
			Assert::AreEqual(size_t(1), d.Find(glm::mat4(2)));
			Assert::AreEqual(size_t(SIZE_MAX), d.Find(glm::mat4(25)));

		}

		TEST_METHOD(FindString)
		{

			Datum d{ std::string("apple"), std::string("banana"), std::string("mango")};
			Assert::AreEqual(size_t(1), d.Find(std::string("banana")));
			Assert::AreEqual(size_t(SIZE_MAX), d.Find(std::string("DragonFruit")));

		}

		TEST_METHOD(FindPointer)
		{
			Foo foo1{ 1 };
			Foo foo2{ 2 };
			Foo foo3{ 3 };
			Foo fooNo{ 85 };
			RTTI* a = &foo1;
			RTTI* b = &foo2;
			RTTI* c = &foo3;
			RTTI* no = &fooNo;
			Datum d{ a, b, c };
			Assert::AreEqual(size_t(1), d.Find(b));
			Assert::AreEqual(size_t(SIZE_MAX), d.Find(no));

		}

		TEST_METHOD(RemoveAt)
		{
			{
				Datum d{ 1.f, 2.f, 3.f };
				Assert::AreEqual(size_t(3), d.Size());
				Assert::IsTrue(d.RemoveAt(d.Find(2.f)));
				Assert::IsFalse(d.RemoveAt(d.Find(7.f)));
				
				Assert::AreEqual(size_t(2), d.Size());
				Assert::AreEqual(size_t(SIZE_MAX), d.Find(2.f));

			}

			{

				Datum d{ 1, 2, 3 };
				Assert::AreEqual(size_t(3), d.Size());
				Assert::IsTrue(d.RemoveAt(d.Find(2)));
				Assert::IsFalse(d.RemoveAt(d.Find(7)));

				Assert::AreEqual(size_t(2), d.Size());
				Assert::AreEqual(size_t(SIZE_MAX), d.Find(2));
			}

			{

				Datum d{ glm::mat4(1), glm::mat4(2), glm::mat4(3) };

				Assert::AreEqual(size_t(3), d.Size());
				Assert::IsTrue(d.RemoveAt(d.Find(glm::mat4(2))));
				Assert::IsFalse(d.RemoveAt(d.Find(glm::mat4(9))));

				Assert::AreEqual(size_t(2), d.Size());
				Assert::AreEqual(size_t(SIZE_MAX), d.Find(glm::mat4(2)));
			}

			{

				Datum d{ std::string("apple"), std::string("banana"), std::string("mango") };

				Assert::AreEqual(size_t(3), d.Size());
				Assert::IsTrue(d.RemoveAt(d.Find(std::string("banana"))));
				Assert::IsFalse(d.RemoveAt(d.Find(std::string("Iguana"))));

				Assert::AreEqual(size_t(2), d.Size());
				Assert::AreEqual(size_t(SIZE_MAX), d.Find(std::string("banana")));
			}

			{

				Datum d{ glm::vec4(1), glm::vec4(2), glm::vec4(3) };

				Assert::AreEqual(size_t(3), d.Size());
				Assert::IsTrue(d.RemoveAt(d.Find(glm::vec4(2))));
				Assert::IsFalse(d.RemoveAt(d.Find(glm::vec4(9))));

				Assert::AreEqual(size_t(2), d.Size());
				Assert::AreEqual(size_t(SIZE_MAX), d.Find(glm::vec4(2)));
			}

			{

				Foo foo1{ 1 };
				Foo foo2{ 2 };
				Foo foo3{ 3 };
				Foo fooNo{ 85 };
				RTTI* a = &foo1;
				RTTI* b = &foo2;
				RTTI* c = &foo3;
				RTTI* no = &fooNo;
				Datum d{ a, b, c };

				Assert::AreEqual(size_t(3), d.Size());
				Assert::IsTrue(d.RemoveAt(d.Find(b)));
				Assert::IsFalse(d.RemoveAt(d.Find(no)));

				Assert::AreEqual(size_t(2), d.Size());
				Assert::AreEqual(size_t(SIZE_MAX), d.Find(b));

			}
		}

		TEST_METHOD(Remove)
		{
			{
				Datum d{ 1, 2, 3 };
				Assert::AreEqual(size_t(3), d.Size());
				Assert::IsTrue(d.Remove(2));
				Assert::IsFalse(d.Remove(7));

				Assert::AreEqual(size_t(2), d.Size());
				Assert::AreEqual(size_t(SIZE_MAX), d.Find(2));
			}

			{
				Datum d{ 1.f, 2.f, 3.f };
				Assert::AreEqual(size_t(3), d.Size());
				Assert::IsTrue(d.Remove(2.f));
				Assert::IsFalse(d.Remove(7.f));

				Assert::AreEqual(size_t(2), d.Size());
				Assert::AreEqual(size_t(SIZE_MAX), d.Find(2.f));

			}

			{

				Datum d{ glm::mat4(1), glm::mat4(2), glm::mat4(3) };

				Assert::AreEqual(size_t(3), d.Size());
				Assert::IsTrue(d.Remove(glm::mat4(2)));
				Assert::IsFalse(d.Remove(glm::mat4(9)));

				Assert::AreEqual(size_t(2), d.Size());
				Assert::AreEqual(size_t(SIZE_MAX), d.Find(glm::mat4(2)));
			}

			{

				Datum d{ std::string("apple"), std::string("banana"), std::string("mango") };

				Assert::AreEqual(size_t(3), d.Size());
				Assert::IsTrue(d.Remove(std::string("banana")));
				Assert::IsFalse(d.Remove(std::string("Iguana")));

				Assert::AreEqual(size_t(2), d.Size());
				Assert::AreEqual(size_t(SIZE_MAX), d.Find(std::string("banana")));
			}

			{

				Datum d{ glm::vec4(1), glm::vec4(2), glm::vec4(3) };

				Assert::AreEqual(size_t(3), d.Size());
				Assert::IsTrue(d.Remove(glm::vec4(2)));
				Assert::IsFalse(d.Remove(glm::vec4(9)));

				Assert::AreEqual(size_t(2), d.Size());
				Assert::AreEqual(size_t(SIZE_MAX), d.Find(glm::vec4(2)));
			}

			{

				Foo foo1{ 1 };
				Foo foo2{ 2 };
				Foo foo3{ 3 };
				Foo fooNo{ 85 };
				RTTI* a = &foo1;
				RTTI* b = &foo2;
				RTTI* c = &foo3;
				RTTI* no = &fooNo;
				Datum d{ a, b, c };

				Assert::AreEqual(size_t(3), d.Size());
				Assert::IsTrue(d.Remove(b));
				Assert::IsFalse(d.Remove(no));

				Assert::AreEqual(size_t(2), d.Size());
				Assert::AreEqual(size_t(SIZE_MAX), d.Find(b));

			}


		}

		TEST_METHOD(ToString)
		{
			{

				Datum a{ 1 };
				Assert::ExpectException<std::out_of_range>([&a]() {a.ToString(5); });

			}
			{
				int i{ 1 };
				int i2{ 2 };
				Datum a{ 1 };
				Assert::AreEqual(a.ToString(), std::to_string(i));
				Assert::AreNotEqual(a.ToString(), std::to_string(i2));

			}

			{
				float i{ 1.f };
				float i2{ 2.f };
				Datum a{ 1.f };
				Assert::AreEqual(a.ToString(), std::to_string(i));
				Assert::AreNotEqual(a.ToString(), std::to_string(i2));

			}

			{
				glm::vec4 i{ 1 };
				glm::vec4 i2{ 3 };
				Datum a{ glm::vec4{ 1 } };
				Assert::AreEqual(a.ToString(), glm::to_string(i));
				Assert::AreNotEqual(a.ToString(), glm::to_string(i2));

			}
			
			{
				glm::mat4 i{ 1 };
				glm::mat4 i2{ 2 };
				Datum a{ glm::mat4{ 1 } };
				Assert::AreEqual(a.ToString(), glm::to_string(i));
				Assert::AreNotEqual(a.ToString(), glm::to_string(i2));

			}

			{
				std::string i{ "hello" };
				std::string i2{ "helloagain" };
				Datum a{ std::string{"hello"} };
				Assert::AreEqual(a.ToString(), i);
				Assert::AreNotEqual(a.ToString(), i2);

			}

			{
				Foo foo1{ 1 };
				Foo foo2{ 1 };
				Foo foo3{ 5 };
				RTTI* i = &foo1;
				RTTI* i2 = &foo3;
				Datum a{ &foo2 };
				Assert::AreEqual(a.ToString(), i->ToString());
				Assert::AreNotEqual(a.ToString(), i2->ToString());

			}

		}

		TEST_METHOD(SetFromString)
		{
			{
				Datum a{ 1 };
				a.SetFromStringInteger(std::string("27"));
				Assert::AreNotEqual(size_t(SIZE_MAX), a.Find(27));
				Assert::AreEqual(size_t(SIZE_MAX), a.Find(1));

			}

			{
				Datum a{ 1.f };
				a.SetFromStringFloat(std::string("27"));
				Assert::AreNotEqual(size_t(SIZE_MAX), a.Find(27.f));
				Assert::AreEqual(size_t(SIZE_MAX), a.Find(1.f));

			}

			{
				Datum a{ glm::vec4{ 1 } };
				a.SetFromStringVector(std::string("vec4(1.0, 2.0, 3.0, 4.0)"));
				Assert::AreNotEqual(size_t(SIZE_MAX), a.Find(glm::vec4{ 1, 2, 3, 4 }));
				Assert::AreEqual(size_t(SIZE_MAX), a.Find(glm::vec4{ 1 }));

			}

			{
				Datum a{ glm::mat4{ 1 } };
				a.SetFromStringMatrix(std::string("mat4((1.0, 2.0, 3.0, 4.0), (5.0, 6.0, 7.0, 8.0), (9.0, 10.0, 11.0, 12.0), (13.0, 14.0, 15.0, 16.0))"));
				Assert::AreNotEqual(size_t(SIZE_MAX), a.Find(glm::mat4{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));
				Assert::AreEqual(size_t(SIZE_MAX), a.Find(glm::mat4{ 1 }));


			}


		}




	private:
		inline static _CrtMemState _startMemState;
	};
}