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

class TreeIteratorTest : public ::testing::Test
{
protected:
    typedef typename ft::rb_tree<int, std::less<int>, std::allocator<int> >
                                        base;
    typedef typename base::node_pointer node_pointer;
    typedef typename base::iterator     iterator;

    virtual void SetUp()
    {
        root    = tree.create_node(0);
        l_child = tree.create_node(-1);
        r_child = tree.create_node(1);

        tree.begin_     = l_child;
        tree.end_->left = root;
        root->parent    = tree.end_;
        root->left      = l_child;
        root->right     = r_child;
        l_child->parent = root;
        r_child->parent = root;
    }

    virtual void TearDown()
    {
        tree.clear(root);
        tree.delete_node(tree.nil_);
        tree.delete_node(tree.end_);
    }

    base         tree;
    node_pointer root;
    node_pointer l_child;
    node_pointer r_child;
};

TEST_F(TreeIteratorTest, PreIncrement)
{
    EXPECT_EQ(-1, tree.begin_->value);
    EXPECT_EQ(0, tree.begin_->parent->value);
    EXPECT_EQ(1, tree.begin_->parent->right->value);

    iterator it = iterator(tree.begin_, tree.nil_);
    EXPECT_EQ(-1, *(it));
}
