#include "pch.h"
#include "CppUnitTest.h"
#include "Hashmap.h"
#include "ToStringSpecializations.h"
#include "HashFunctorSpecializations.h"
#include "Foo.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;


namespace LibraryDesktopTests
{
	TEST_CLASS(HashMapTests)
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
			Hashmap<Foo, Foo> map{5};
			Assert::IsNotNull(&map);

			Hashmap<std::string, std::string> mapinitializer{

				std::pair("akey", "avalue"),
				std::pair("bkey", "bvalue"),
				std::pair("ckey", "cvalue"),

			};
			Assert::AreEqual(size_t(3), mapinitializer.Size());
			Assert::AreEqual(std::string("avalue"), mapinitializer.At("akey"));
			Assert::AreEqual(std::string("bvalue"), mapinitializer.At("bkey"));
			Assert::AreEqual(std::string("cvalue"), mapinitializer.At("ckey"));


		}

		TEST_METHOD(Size)
		{

			//defaulted
			Hashmap<Foo, Foo> defaultMap{};
			Assert::AreEqual(size_t(0), defaultMap.Size());
			Assert::AreEqual(size_t(5), defaultMap.Buckets());

			//size given
			Hashmap<Foo, Foo> map{ 7 };
			Assert::AreEqual(size_t(0), map.Size());
			Assert::AreEqual(size_t(7), map.Buckets());

		}

		TEST_METHOD(Iterator)
		{
			Hashmap<Foo, Foo> map{ 5 };
			const Foo key{ 3 };
			const Foo value{ 7 };
			const Foo key2{ 4 };
			const Foo value2{ 6 };
			map.Insert(std::pair(key, value));
			map.Insert(std::pair(key2, value2));

			Hashmap<Foo, Foo>::Iterator it;
			Hashmap<Foo, Foo>::Iterator it2;
			Hashmap<Foo, Foo>::Iterator itB = map.begin();

			//test default
			Assert::ExpectException<std::runtime_error>([&it]() {*it; });
			Assert::ExpectException<std::runtime_error>([&it]() {++it; });
			Assert::ExpectException<std::runtime_error>([&it]() {it++; });
			Assert::AreEqual(it, it2);

			//not equal
			Assert::AreNotEqual(it, itB);

			//assignment
			Hashmap<Foo, Foo>::Iterator itC = itB;
			Assert::AreEqual(itB, itC);

			//++
			itB++;
			Assert::AreEqual((*itB).first, key2);
		}

		TEST_METHOD(ConstIterator)
		{
			Hashmap<Foo, Foo> map{ 5 };
			const Foo key{ 3 };
			const Foo value{ 7 };
			const Foo key2{ 4 };
			const Foo value2{ 6 };
			map.Insert(std::pair(key, value));
			map.Insert(std::pair(key2, value2));

			Hashmap<Foo, Foo>::ConstIterator it;
			Hashmap<Foo, Foo>::ConstIterator it2;
			Hashmap<Foo, Foo>::ConstIterator itB = map.begin();

			//test default
			Assert::ExpectException<std::runtime_error>([&it]() {*it; });
			Assert::ExpectException<std::runtime_error>([&it]() {++it; });
			Assert::ExpectException<std::runtime_error>([&it]() {it++; });
			Assert::AreEqual(it, it2);

			//not equal
			Assert::AreNotEqual(it, itB);

			//assignment
			Hashmap<Foo, Foo>::ConstIterator itC = itB;
			Assert::AreEqual(itB, itC);

			//creation of const from normal
			Hashmap<Foo, Foo>::Iterator itBegin = map.begin();
			Hashmap<Foo, Foo>::ConstIterator itConstBegin(itBegin);
			Assert::AreEqual((*itBegin).first, (*itConstBegin).first);

			//++
			itB++;
			Assert::AreEqual((*itB).first, key2);


		}

		TEST_METHOD(Insert)
		{
			Hashmap<Foo, Foo> map{ 5 };
			const Foo key{ 3 };
			const Foo value{ 7 };
			const Foo key2{ 3 };
			const Foo value2{ 7 };
			Hashmap<Foo,Foo>::Iterator it = map.Insert(std::pair(key, value)).first;

			Assert::AreEqual(map.Size(), size_t(1));

			Assert::AreEqual(key, (*it).first);
			Assert::AreEqual(value, (*it).second);


			Hashmap<Foo, Foo>::Iterator it2 = map.Insert((std::pair(key, value))).first;

		}

		TEST_METHOD(Find)
		{
			Hashmap<Foo, Foo> map{ 5 };
			const Foo key{ 3 };
			const Foo value{ 7 };
			Hashmap<Foo, Foo>::Iterator it = map.Insert(std::pair(key, value)).first;

			//test found
			Assert::AreNotEqual(map.Find(key), map.end());

			////test not found
			const Foo key2{ 8 };
			Assert::AreEqual(map.Find(key2), map.end());

			//test not found empty
			const Foo key3{ 4 };
			Assert::AreEqual(map.Find(key3), map.end());

			const Hashmap<Foo, Foo> cMap = map;
			//test const found
			Assert::AreNotEqual(cMap.Find(key), cMap.end());

			////test const not found
			Assert::AreEqual(cMap.Find(key2), cMap.end());

			//test const not found empty
			Assert::AreEqual(cMap.Find(key3), cMap.end());

		}

		TEST_METHOD(Begin)
		{
			Hashmap<Foo, Foo> map{ 5 };
			const Foo key{ 3 };
			const Foo value{ 7 };
			map.Insert(std::pair(key, value));
			const Hashmap<Foo, Foo> cMap = map;


			//normal begin
			Hashmap<Foo, Foo>::Iterator it = map.begin();
			Assert::AreEqual(key, (*it).first);
			Assert::AreEqual(value, (*it).second);

			//const begin
			Hashmap<Foo, Foo>::ConstIterator itC = cMap.begin();
			Assert::AreEqual(key, (*itC).first);
			Assert::AreEqual(value, (*itC).second);

			//const cbegin
			Hashmap<Foo, Foo>::ConstIterator itCC = cMap.cbegin();
			Assert::AreEqual(key, (*itCC).first);
			Assert::AreEqual(value, (*itCC).second);

		}

		TEST_METHOD(End)
		{
			Hashmap<Foo, Foo> map{ 5 };
			const Hashmap<Foo, Foo> cMap = map;

			//normal end 
			Assert::ExpectException<std::runtime_error>([&map]() {*map.end(); });

			//const end
			Assert::ExpectException<std::runtime_error>([&cMap]() {*cMap.end(); });

			//const cend
			Assert::ExpectException<std::runtime_error>([&map]() {*map.cend(); });



		}

		TEST_METHOD(Clear)
		{
			//empty
			Hashmap<Foo, Foo> map{ 5 };
			Assert::AreEqual(size_t(0), map.Size());
			map.Clear();
			Assert::AreEqual(size_t(0), map.Size());

			//filled
			const Foo key{ 3 };
			const Foo value{ 7 };
			Hashmap<Foo, Foo>::Iterator it = map.Insert(std::pair(key, value)).first;
			Assert::AreEqual(size_t(1), map.Size());
			map.Clear();
			Assert::AreEqual(size_t(0), map.Size());


		}

		TEST_METHOD(At)
		{
			Hashmap<Foo, Foo> map{ 5 };
			const Foo key{ 3 };
			const Foo key2{ 8 };
			const Foo key3{ 9 };
			const Foo value{ 7 };
			const Hashmap<Foo, Foo> constMap = map;


			//empty at
			Assert::ExpectException<std::runtime_error>([&map, &key2]() { map.At(key2); });

			//const empty at
			Assert::ExpectException<std::runtime_error>([&constMap, &key2]() { constMap.At(key2); });


			map.Insert(std::pair(key, value));
			const Hashmap<Foo, Foo> cMap = map;


			//not at
			Assert::ExpectException<std::runtime_error>([&map, &key2]() { map.At(key2); });

			//at present
			Assert::AreEqual(value, map.At(key));

			//not at empty
			Assert::ExpectException<std::runtime_error>([&map, &key3]() { map[key3]; });


			//const not at
			Assert::ExpectException<std::runtime_error>([&cMap, &key2]() { cMap.At(key2); });

			//const at present
			Assert::AreEqual(value, cMap.At(key));

		}

		TEST_METHOD(ContainKey)
		{
			Hashmap<Foo, Foo> map{ 5 };
			const Foo key{ 3 };
			const Foo key2{ 8 };
			const Foo value{ 7 };
			map.Insert(std::pair(key, value));


			//key present
			Assert::IsTrue(map.ContainsKey(key));

			//key not present
			Assert::IsFalse(map.ContainsKey(key2));

		}

		TEST_METHOD(Remove)
		{
			Hashmap<Foo, Foo> map{ 5 };
			const Foo key{ 3 };
			const Foo value{ 7 };
			//test empty
			Assert::AreEqual(map.Size(), size_t(0));
			map.Remove(key);
			Assert::AreEqual(map.Size(), size_t(0));


			//test found
			map.Insert(std::pair(key, value));
			Assert::AreEqual(map.Size(), size_t(1));
			map.Remove(key);
			Assert::AreEqual(map.Size(), size_t(0));


		}

		TEST_METHOD(IndexOperator)
		{

			Hashmap<Foo, Foo> map{ 5 };
			const Foo key{ 3 };
			const Foo key2{ 8 };
			const Foo key3{ 9 };
			const Foo value{ 7 };
			map.Insert(std::pair(key, value));

			//not at
			Assert::ExpectException<std::runtime_error>([&map, &key2]() { map[key2]; });

			//not at empty
			Assert::ExpectException<std::runtime_error>([&map, &key3]() { map[key3]; });

			//at present
			Assert::AreEqual(value, map[key]);

		}


		TEST_METHOD(Rehash)
		{
			Hashmap<Foo, Foo> map{ 5 };
			const Foo key{ 3 };
			const Foo value{ 7 };
			map.Insert(std::pair(key, value));

			Assert::AreEqual(size_t(5), map.Buckets());
			map.Rehash(10);
			Assert::AreEqual(size_t(10), map.Buckets());
			Assert::AreNotEqual(map.Find(key), map.end());

		}


	private:
		inline static _CrtMemState _startMemState;
	};
}