#ifndef ARRAY_LIST_UNITTEST_H_
#define ARRAY_LIST_UNITTEST_H_

#include "../structure_data/array_list.h"
#include "gtest/gtest.h"


class ArrayListTest : public::testing::Test
{
protected:
	virtual void SetUp() 
	{
		array0.Add(1);
		array0.Add(2);
		array0.Insert(1, 3);
		array0.Insert(2, 4);

		array1.Add(1.1);
		array1.Add(2.2);
		array1.Insert(1, 3.3);
		array1.Insert(2, 4.4);
		array1.Add(5.5);

		array3 = new ArrayList<std::string>(6);
		array3->Add("A");
		array3->Add("B");
		array3->Insert(1, "C");
		array3->Insert(2, "D");
		array3->Add("E");
		array3->Add("F");
	}

	virtual void TearDown() 
	{
		delete array3;
	}

	template <typename C, typename T>
	::testing::AssertionResult Remove(C array, T item)
	{
		if (array.Remove(item))
			return ::testing::AssertionSuccess() << item << " is include";
		else
			return ::testing::AssertionFailure() << item << " is absent";
	}

	template <typename C, typename T>
	::testing::AssertionResult IndexOf(const char *array_expr, const char *item_expr, C array, T item)
	{
		if (array.IndexOf(item) != -1)
		{
			return ::testing::AssertionSuccess();
		}
		return ::testing::AssertionFailure() << array_expr << " doesn't contain the "
			<< item_expr << " (" << item << ")";
	}

	ArrayList<int> array0;
	ArrayList<double> array1;
	ArrayList<int> array2;
	ArrayList<std::string> *array3;
};

TEST_F(ArrayListTest, ConstructorDefault)
{
	EXPECT_FALSE(array2.Count() > 0);
	EXPECT_EQ(0, array2.Count());
	EXPECT_EQ(0, array2.Capacity());
}

TEST_F(ArrayListTest, DynamicConstructor)
{
	EXPECT_TRUE(array3->Count() != 0);
	EXPECT_EQ(6, array3->Count());
	EXPECT_EQ(6, array3->Capacity());
}

TEST_F(ArrayListTest, OtherConstructor)
{
	EXPECT_EQ(4, array0.Count());
	EXPECT_EQ(4, array0.Capacity());

	EXPECT_EQ(5, array1.Count());
	EXPECT_EQ(8, array1.Capacity());
}

TEST_F(ArrayListTest, Exception)
{
	ASSERT_THROW({ ArrayList<int> array4(-1); }, std::length_error);
	ASSERT_ANY_THROW(array0.Insert(10, 10));
	ASSERT_ANY_THROW(array0.RemoveAt(10));
	ASSERT_NO_THROW(array1.Insert(1, 10));
	ASSERT_NO_THROW(array1.RemoveAt(1));
}


struct TestContains : public std::unary_function<int, bool>
{
	explicit TestContains(ArrayList<int> &test_) : test(test_) {}
	bool operator()(int i) { return test.Contains(i); }
	ArrayList<int> &test;
};

TEST_F(ArrayListTest, Contains)
{
	EXPECT_PRED1([&](double i) {return array1.Contains(i); }, 3.3);
	EXPECT_PRED1([&](std::string i) {return array3->Contains(i); }, std::string("C"));
	EXPECT_PRED1(TestContains(array0), 2);
}

TEST_F(ArrayListTest, RemoveOperation)
{
	EXPECT_TRUE(Remove(array1, 5.5));
	EXPECT_TRUE(Remove(*array3, "F"));
	EXPECT_FALSE(Remove(array1, 5.51));
	EXPECT_FALSE(Remove(*array3, "FF"));
}

TEST_F(ArrayListTest, IndexOfOperation)
{
	EXPECT_PRED_FORMAT2(IndexOf, array1, 3.3);
	EXPECT_PRED_FORMAT2(IndexOf, array0, 2);
	EXPECT_PRED_FORMAT2(IndexOf, *array3, "E");
}

TEST_F(ArrayListTest, FloatingPointTest)
{
	//EXPECT_FLOAT_EQ(expected, actial);
	EXPECT_DOUBLE_EQ(1.1, array1[0]);
	EXPECT_NEAR(1.1, array1[0], 0.001);
	EXPECT_PRED_FORMAT2(::testing::DoubleLE, 1, 2);
}

template <typename T>
void FuncTest()
{
	ArrayList<T> test;
	::testing::StaticAssertTypeEq<int, T>();
	test.Add(100);
}

TEST_F(ArrayListTest, TypeAssertions)
{
	FuncTest<int>();
}

TEST_F(ArrayListTest, PrintTest)
{
	EXPECT_TRUE(array0.Count() == 4) << "Elements: " << ::testing::PrintToString(array0);
}

#endif // ARRAY_LIST_UNITTEST_H_