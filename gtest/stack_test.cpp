#include <stack.hpp>

#include <stack>
#include <gtest/gtest.h>

namespace {

TEST(Stack, ConstructAndBasicOperation)
{
    ft::stack<int> int_stack;

    int_stack.push(1);
    int_stack.push(2);

    EXPECT_EQ(int_stack.size(), 2ul);
    EXPECT_EQ(int_stack.top(), 2);
    int_stack.pop();
    EXPECT_EQ(int_stack.size(), 1ul);
    EXPECT_EQ(int_stack.top(), 1);
    int_stack.pop();
    EXPECT_EQ(int_stack.size(), 0ul);
    EXPECT_TRUE(int_stack.empty());
}

TEST(Stack, CopyConstruct)
{
    ft::stack<int> int_stack1;

    int_stack1.push(1);
    int_stack1.push(2);

    ft::stack<int> int_stack2 = int_stack1;
    EXPECT_EQ(int_stack1, int_stack2);
    int_stack2.push(1);
    int_stack2.push(2);
    EXPECT_NE(int_stack1, int_stack2);
}

} // namespace
