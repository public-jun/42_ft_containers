#include <vector.hpp>
#include <gtest/gtest.h>

TEST(Vector, Constructor)
{
    // vector();
    ft::vector<int> ft_v;
    std::vector<int> stl_v;
    EXPECT_EQ(ft_v.size(), stl_v.size());
}
