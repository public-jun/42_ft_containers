#include <tree.hpp>
#include <gtest/gtest.h>

TEST(TreeNode, Contruct)
{
    ft::tree_node<int> node;
    EXPECT_EQ(NULL, node.parent);
    EXPECT_EQ(NULL, node.left);
    EXPECT_EQ(NULL, node.right);
    EXPECT_EQ(ft::kBlack, node.color);
}
