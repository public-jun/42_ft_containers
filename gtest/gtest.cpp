#include "../includes/containers/vector.hpp"
#include <gtest/gtest.h>

TEST(Vector, Constructor)
{
    // vector();
    ft::vector<int> v;
    EXPECT_EQ(v.size(), 0);
}
