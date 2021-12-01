#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> v(10);
	TMatrix<int> v1(v);
	EXPECT_EQ(v, v1);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> v(10);
	TMatrix<int> v1(v);
	bool temp = ((&v[0][0]) == (&v1[0][0]));
	EXPECT_EQ(false, temp);
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> v(4);

	EXPECT_EQ(4, v.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> v(4);
	v[0][0] = 4;

	EXPECT_EQ(4, v[0][0]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> v(15);
	ASSERT_ANY_THROW(v[-1][1] = 4);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> v(15);
	ASSERT_ANY_THROW(v[15][1] = 4);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> v(15);

	ASSERT_NO_THROW(v = v);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> v(15);
	TMatrix<int> s(15);
	TMatrix<int> g(15);
	for (int i = 0; i < 15; i++)
		for(int j=i; j<15;j++)
			v[i][j] = s[i][j] = i+j;
	g = v;


	EXPECT_EQ(g, s);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> v(15);
	TMatrix<int> s(10);
	s = v;
	EXPECT_EQ(s.GetSize(), v.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> v(15);
	TMatrix<int> s(15);
	TMatrix<int> g(10);
	for (int i = 0; i < 15; i++)
		for (int j = i; j < 15; j++)
			v[i][j] = s[i][j] = i + j;
	g = v;


	EXPECT_EQ(g, s);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> v(15);
	TMatrix<int> s(15);
	for (int i = 0; i < 15; i++)
		for (int j = i; j < 15; j++)
			v[i][j] = s[i][j] = i + j;



	EXPECT_EQ(v, s);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> v(15);


	EXPECT_EQ(v, v);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> v(15);
	TMatrix<int> s(20);
	EXPECT_NE(v, s);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> v(15);
	TMatrix<int> s(15);
	TMatrix<int> g(15);
	for (int i = 0; i < 15; i++)
		for (int j = i; j < 15; j++) {
			v[i][j] = 1;
			s[i][j] = 2;
			g[i][j] = 3;
		}


	EXPECT_EQ(s+v, g);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> v(15);
	TMatrix<int> s(20);

	ASSERT_ANY_THROW(v + s);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> v(15);
	TMatrix<int> s(15);
	TMatrix<int> g(15);
	for (int i = 0; i < 15; i++)
		for (int j = i; j < 15; j++) {
			v[i][j] = 1;
			s[i][j] = 2;
			g[i][j] = 3;
		}

	EXPECT_EQ(v, g-s);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> v(15);
	TMatrix<int> s(20);
	ASSERT_ANY_THROW(v - s);
}

TEST(TMatrix, cin_operator_work_correct)
{
	const int size1 = 3;
	TMatrix<int> v1(size1), v2(size1);

	string temp = "0 1 2 \n 2 3 \n 4 \n";
	stringstream in(temp);

	in >> v1;



	// v2 = 1 2 3 4;
	for (int i = 0; i < size1; i++)
		for(int j = i; j < size1; j++)
			v2[i][j] = i + j;


	EXPECT_EQ(v2, v1);
}



TEST(TMatrix, cout_operator_work_correct)
{
	const int size1 = 3;
	TMatrix<int> v1(size1);
	for (int i = 0; i < size1; i++)
		for (int j = i; j < size1; j++)
			v1[i][j] = i + j;
	stringstream in;
	in << v1;
	string temp = in.str();


	EXPECT_EQ(temp, "0 1 2 \n2 3 \n4 \n");
}