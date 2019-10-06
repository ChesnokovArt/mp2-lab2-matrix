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
	TVector<int> v(4);
	v[2] = 3; v[3] = 1; // (0,0,3,1)
	TVector<int> v1(v);
	EXPECT_EQ(v, v1);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	TVector<int> v(4);
	TVector<int> v1(v); 
	EXPECT_NE(&v[0], &v1[0]);
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
	TVector<int> v(4);
	ASSERT_ANY_THROW(v[-3] = 1);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> v(4);
	ASSERT_ANY_THROW(v[MAX_VECTOR_SIZE + 1] = 1);
}

TEST(TVector, can_assign_vector_to_itself)
{
	TVector<int> v(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4; // (1,2,3,4)
	TVector<int> v1(v);
	v = v;
	EXPECT_EQ(v1, v);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	TVector<int> v(4), v2(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4; // (1,2,3,4)
	v2 = v;
	EXPECT_EQ(v, v2);
}

TEST(TVector, assign_operator_change_vector_size)
{
	TVector<int> v(4), v2(2);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4; // (1,2,3,4)
	v2 = v;
	EXPECT_EQ(4, v2.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	TVector<int> v(4), v2(2);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4; // (1,2,3,4)
	v2 = v;
	EXPECT_EQ(v, v2);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	TVector<int> v(4), v2(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4; // (1,2,3,4)
	v2[0] = 1; v2[1] = 2; v2[2] = 3; v2[3] = 4; // (1,2,3,4)
	EXPECT_EQ(true, v == v2);
	
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int> v(4);
	EXPECT_EQ(true, v == v);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int> v(4), v2(2);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4; // (1,2,3,4)
	v2[0] = 1; v2[1] = 2;                   // (1,2)
	EXPECT_EQ(false, v == v2);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int> v(4), v2(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;     // (1,2,3,4)
	v2[0] = 4; v2[1] = 5; v2[2] = 6; v2[3] = 7; // (1,2,3,4) + 3 = (4,5,6,7)
	EXPECT_EQ(v2, v + 3);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> v(4), v2(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;     // (1,2,3,4)
	v2[0] = 0; v2[1] = 1; v2[2] = 2; v2[3] = 3; // (1,2,3,4) - 1 = (0,1,2,3)
	EXPECT_EQ(v2, v - 1);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int> v(4), v2(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;     // (1,2,3,4)
	v2[0] = 3; v2[1] = 6; v2[2] = 9; v2[3] = 12; // (1,2,3,4) * 3 = (3,6,9,12)
	EXPECT_EQ(v2, v * 3);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int> v(4), v2(4), v3(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;         // (1,2,3,4)
	v2[0] = 3; v2[1] = 6; v2[2] = 9; v2[3] = 12;    // (3,6,9,12)
	v3[0] = 4; v3[1] = 8; v3[2] = 12; v3[3] = 16;   // v + v2 = (4,8,12,16)
	EXPECT_EQ(v3, v + v2);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> v(4), v2(2);
	ASSERT_ANY_THROW(v + v2);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int> v(4), v2(4), v3(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;         // (1,2,3,4)
	v2[0] = 3; v2[1] = 6; v2[2] = 9; v2[3] = 12;    // (3,6,9,12)
	v3[0] = 2; v3[1] = 4; v3[2] = 6; v3[3] = 8;   // v2 - v = (2,4,6,8)
	EXPECT_EQ(v3, v2 - v);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> v(4), v2(2);
	ASSERT_ANY_THROW(v - v2);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int> v(4), v2(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;         // (1,2,3,4)
	v2[0] = 2; v2[1] = 3; v2[2] = 2; v2[3] = 3;     // (2,3,2,3)
	EXPECT_EQ(1 * 2 + 2 * 3 + 3 * 2 + 4 * 3, v2 * v);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> v(4), v2(2);
	ASSERT_ANY_THROW(v * v2);
}

