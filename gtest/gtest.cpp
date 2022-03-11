#include <vector.hpp>

#include <gtest/gtest.h>


/* Include all tests files */

#include "stack_test.cpp"

TEST(Vector, Constructor)
{
    // vector();
    ft::vector<int> ft_v;
    std::vector<int> stl_v;
    EXPECT_EQ(ft_v.size(), stl_v.size());
}
