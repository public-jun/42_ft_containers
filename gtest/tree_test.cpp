#include <pair.hpp>
#include <tree.hpp>

#include <gtest/gtest.h>
#include <iostream>

TEST(Tree, TreeNodeContruct)
{
    ft::tree_node<int> node;
    EXPECT_EQ(NULL, node.parent);
    EXPECT_EQ(NULL, node.left);
    EXPECT_EQ(NULL, node.right);
    EXPECT_EQ(ft::kBlack, node.color);
}

TEST(Tree, TreeNodeCheckType)
{
    // node_value_type
    EXPECT_EQ(
        typeid(ft::pair<std::string, int>),
        typeid(ft::tree_node<ft::pair<std::string, int> >::node_value_type));
    EXPECT_EQ(typeid(int), typeid(ft::tree_node<int>::node_value_type));

    // key_type
    EXPECT_EQ(typeid(std::string),
              typeid(ft::tree_node<ft::pair<std::string, int> >::key_type));
    EXPECT_EQ(typeid(int), typeid(ft::tree_node<int>::key_type));

    // node_type
    EXPECT_EQ(typeid(ft::tree_node<ft::pair<std::string, int> >),
              typeid(ft::tree_node<ft::pair<std::string, int> >::node_type));
    EXPECT_EQ(typeid(ft::tree_node<int>),
              typeid(ft::tree_node<int>::node_type));

    // node_pointer
    EXPECT_EQ(typeid(ft::tree_node<ft::pair<std::string, int> >*),
              typeid(ft::tree_node<ft::pair<std::string, int> >::node_pointer));
    EXPECT_EQ(typeid(ft::tree_node<int>*),
              typeid(ft::tree_node<int>::node_pointer));
}

// TEST(Tree)
