#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
	TVector<int> v(10);
	TVector<int> v1(v);
	EXPECT_EQ(v,v1);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	TVector<int> v(10);
	TVector<int> v1(v);
	bool temp = ((&v[0]) == (&v1[0]));
	EXPECT_EQ(false, temp);
}

TEST(TVector, can_get_size)
{
  TVector<int> v(4);

  EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
  TVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	TVector<int> v(15,5);
	ASSERT_ANY_THROW(v[-1]=4);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> v(10);
	ASSERT_ANY_THROW(v[10] = 4);
}

TEST(TVector, can_assign_vector_to_itself)
{
	TVector<int> v(15);

	ASSERT_NO_THROW(v=v);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	TVector<int> v(15);
	TVector<int> s(15);
	TVector<int> g(15);
	for (int i = 0; i < 15; i++) {
		v[i] = s[i] = i;
	}
	g = v;


	EXPECT_EQ(g, s);
}

TEST(TVector, assign_operator_change_vector_size)
{
	TVector<int> v(15);
	TVector<int> s(10);
	s = v;
	EXPECT_EQ(s.GetSize(),v.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	TVector<int> v(15);
	TVector<int> s(15);
	TVector<int> g(10);
	for (int i = 0; i < 15; i++) {
		v[i] = s[i] = i;
	}
	g = v;

	EXPECT_EQ(g, s);
}

TEST(TVector, compare_equal_vectors_return_true)
{

	TVector<int> v(15);
	TVector<int> s(15);
	for (int i = 0; i < 15; i++) {
		v[i] = s[i] = i;
	}

	EXPECT_EQ(v, s);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int> v(15);

	for (int i = 0; i < 15; i++) {
		v[i]  = i;
	}

	EXPECT_EQ(v, v);

}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int> v(15);
	TVector<int> s(20);
	EXPECT_NE(v,s);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int> v(15);
	TVector<int> s(15);
	for (int i = 0; i < 15; i++) {
		v[i] = 1;
		s[i] = 3;
	}

	v = v + 2;

	EXPECT_EQ(v, s);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> v(15);
	TVector<int> s(15);
	for (int i = 0; i < 15; i++) {
		v[i] = 1;
		s[i] = 3;
	}

	s = s - 2;

	EXPECT_EQ(v, s);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int> v(15);
	TVector<int> s(15);
	for (int i = 0; i < 15; i++) {
		v[i] = 1;
		s[i] = 4;
	}

	v = v * 4;

	EXPECT_EQ(v, s);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int> v(15);
	TVector<int> s(15);
	TVector<int> g(15);
	for (int i = 0; i < 15; i++) {
		v[i] = 1;
		s[i] = 3;
		g[i] = 4;
	}

	EXPECT_EQ(v+s, g);

}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> v(15);
	TVector<int> s(20);



	ASSERT_ANY_THROW(v + s);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int> v(15);
	TVector<int> s(15);
	TVector<int> g(15);
	for (int i = 0; i < 15; i++) {
		v[i] = 1;
		s[i] = 3;
		g[i] = 4;
	}

	EXPECT_EQ(g - s, v);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> v(15);
	TVector<int> s(20);



	ASSERT_ANY_THROW(v - s);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int> v(15);
	TVector<int> s(15);
	TVector<int> g(15);
	for (int i = 0; i < 15; i++) {
		v[i] = 1;
		s[i] = 3;
	}

	EXPECT_EQ(45, v*s);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> v(15);
	TVector<int> s(20);



	ASSERT_ANY_THROW(v * s);
}


TEST(TVector, cin_operator_work_correct)
{
	const int size1 = 4;
	TVector<int> v1(size1), v2(size1);

	string temp = "1 2 3 4 ";
	stringstream in(temp);

	in >> v1;



	// v2 = 1 2 3 4;
	for (int i = 0; i < size1; i++)
		v2[i] = i + 1;


	EXPECT_EQ(v2, v1);
}



TEST(TVector, cout_operator_work_correct)
{
	const int size1 = 4;
	TVector<int> v1(size1);
	for (int i = 0; i < size1; i++)
		v1[i] = i + 1;
	stringstream in;
	in << v1;
	string temp = in.str();


	EXPECT_EQ(temp, "1 2 3 4 ");
}
