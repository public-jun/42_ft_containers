#if STL // -DTEST=1
#else   // -DTEST=0
#include <stack.hpp>
#include <vector.hpp>
#endif

#if __cplusplus >= 201103L
#include <gtest/gtest.h>
#else
#include "../ft_test.hpp"
#endif

#include <stack>

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

TEST(Stack, InitializeWithContainer)
{
    ft::vector<int> int_vec;
    for (int i = 0; i < 10; ++i)
        int_vec.push_back(i);

    ft::stack<int, ft::vector<int> > int_stack(int_vec);
    for (int i = 9; i >= 0; --i)
    {
        EXPECT_EQ(int_stack.top(), int_vec[i]);
        int_stack.pop();
    }
}

TEST(Stack, CopyConstruct)
{
    ft::stack<int> int_stack1;

    int_stack1.push(1);
    int_stack1.push(2);

    ft::stack<int> int_stack2 = int_stack1;
    EXPECT_EQ(int_stack1, int_stack2);
    EXPECT_EQ(int_stack1.size(), int_stack2.size());
    int_stack2.push(1);
    int_stack2.push(2);
    EXPECT_NE(int_stack1, int_stack2);
}

TEST(Stack, AssignmentOperator)
{
    ft::stack<int> int_stack1;

    int_stack1.push(1);
    int_stack1.push(2);

    ft::stack<int> int_stack2;
    int_stack2 = int_stack1;
    EXPECT_EQ(int_stack1, int_stack2);
    int_stack1.push(1);
    int_stack1.push(2);
    EXPECT_NE(int_stack1, int_stack2);
    int_stack1.pop();
    int_stack1.pop();
    EXPECT_EQ(int_stack1, int_stack2);
}

TEST(Stack, Top)
{
    ft::stack<int> int_stack;

    int_stack.push(1);
    int_stack.push(2);

    EXPECT_EQ(2, int_stack.top());
    EXPECT_EQ(2, int_stack.top());
    int_stack.push(3);
    EXPECT_EQ(3, int_stack.top());
}

TEST(Stack, Empty)
{
    ft::stack<int> int_stack;

    EXPECT_TRUE(int_stack.empty());
    int_stack.push(1);
    EXPECT_FALSE(int_stack.empty());
}

TEST(Stack, Size)
{
    ft::stack<int> int_stack;

    std::size_t i = 0;
    for (; i < 20; ++i)
    {
        EXPECT_EQ(i, int_stack.size());
        int_stack.push(i);
    }
    EXPECT_EQ(i, int_stack.size());
}

TEST(Stack, Push)
{
    ft::stack<int> int_stack;

    int_stack.push(1);
    EXPECT_EQ(1, int_stack.top());
    int_stack.push(2);
    EXPECT_EQ(2, int_stack.top());
}

TEST(Stack, Pop)
{
    ft::stack<int> int_stack;

    for (int i = 0; i < 10; ++i)
        int_stack.push(i);
    for (int i = 9; i >= 0; --i)
    {
        EXPECT_EQ(i, int_stack.top());
        int_stack.pop();
    }
    EXPECT_TRUE(int_stack.empty());
}

TEST(Stack, OperatorEqual)
{
    ft::stack<int> int_stack1;
    ft::stack<int> int_stack2;

    EXPECT_TRUE(int_stack1 == int_stack2);
    int_stack1.push(1);
    EXPECT_FALSE(int_stack1 == int_stack2);
    int_stack2.push(1);
    EXPECT_TRUE(int_stack1 == int_stack2);
}

TEST(Stack, OperatorNotEqual)
{
    ft::stack<int> int_stack1;
    ft::stack<int> int_stack2;

    EXPECT_FALSE(int_stack1 != int_stack2);
    int_stack1.push(1);
    EXPECT_TRUE(int_stack1 != int_stack2);
    int_stack2.push(1);
    EXPECT_FALSE(int_stack1 != int_stack2);
}

TEST(Stack, OperatorLessThan)
{
    ft::stack<int> int_stack1;
    ft::stack<int> int_stack2;

    EXPECT_FALSE(int_stack1 < int_stack2);
    int_stack2.push(1);
    EXPECT_TRUE(int_stack1 < int_stack2);
    int_stack1.push(1);
    int_stack1.push(2);
    EXPECT_FALSE(int_stack1 < int_stack2);
}

TEST(Stack, OperatorLessThanOrEqual)
{
    ft::stack<int> int_stack1;
    ft::stack<int> int_stack2;

    EXPECT_TRUE(int_stack1 <= int_stack2);
    int_stack1.push(1);
    EXPECT_FALSE(int_stack1 < int_stack2);
    int_stack2.push(1);
    EXPECT_TRUE(int_stack1 <= int_stack2);
    int_stack2.push(2);
    EXPECT_TRUE(int_stack1 <= int_stack2);
}

TEST(Stack, OperatorGreaterThan)
{
    ft::stack<int> int_stack1;
    ft::stack<int> int_stack2;

    EXPECT_FALSE(int_stack1 > int_stack2);
    int_stack2.push(1);
    EXPECT_FALSE(int_stack1 > int_stack2);
    int_stack1.push(1);
    EXPECT_FALSE(int_stack1 > int_stack2);
    int_stack1.push(2);
    EXPECT_TRUE(int_stack1 > int_stack2);
}

TEST(Stack, OperatorGreaterThanOrEqual)
{
    ft::stack<int> int_stack1;
    ft::stack<int> int_stack2;

    EXPECT_TRUE(int_stack1 >= int_stack2);
    int_stack2.push(1);
    EXPECT_FALSE(int_stack1 >= int_stack2);
    int_stack1.push(1);
    EXPECT_TRUE(int_stack1 >= int_stack2);
    int_stack1.push(2);
    EXPECT_TRUE(int_stack1 >= int_stack2);
}

} // namespace
