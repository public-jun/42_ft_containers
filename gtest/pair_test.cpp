#include <pair.hpp>

#include <gtest/gtest.h>
#include <map>

TEST(Pair, DefaultConstructor)
{
    ft::pair<int, float> p;
    EXPECT_EQ(0, p.first);
    EXPECT_EQ(0, p.second);

    ft::pair<std::string, char> p1;
    EXPECT_EQ("", p1.first);
    EXPECT_EQ('\0', p1.second);
}

TEST(Pair, ConatructorAndInitialize)
{
    ft::pair<int, double> p(42, 0.42);
    EXPECT_EQ(42, p.first);
    EXPECT_EQ(0.42, p.second);

    ft::pair<int, std::string> p1(42, "hoge");
    EXPECT_EQ(42, p1.first);
    EXPECT_EQ("hoge", p1.second);

    ft::pair<char, int> p3('a', 100);
    EXPECT_EQ('a', p3.first);
    EXPECT_EQ(100, p3.second);
}

TEST(Pair, CopyConstructor)
{
    ft::pair<int, double> p1(42, 0.42);
    ft::pair<int, double> p2(p1);

    EXPECT_EQ(42, p2.first);
    EXPECT_EQ(0.42, p2.second);

    ft::pair<char, std::string> p3('a', "hoge");
    ft::pair<char, std::string> p4(p3);
    EXPECT_EQ('a', p4.first);
    EXPECT_EQ("hoge", p4.second);
}

TEST(Pair, AssginOperator)
{
    ft::pair<int, double> p1(42, 0.42);
    ft::pair<int, double> p2;
    p2 = p1;

    EXPECT_EQ(42, p2.first);
    EXPECT_EQ(0.42, p2.second);

    ft::pair<char, std::string> p3('a', "hoge");
    ft::pair<char, std::string> p4;
    p4 = p3;

    EXPECT_EQ('a', p4.first);
    EXPECT_EQ("hoge", p4.second);

    ft::pair<int, char> p5(100, 'a');
    p5 = p5;

    EXPECT_EQ(100, p5.first);
    EXPECT_EQ('a', p5.second);
}

TEST(Pair, OperatorEqual)
{
    ft::pair<int, double> p1(42, 0.42);
    ft::pair<int, double> p2(p1);

    EXPECT_TRUE(p1 == p2);

    ft::pair<int, char> p3(42, 'a');
    ft::pair<int, char> p4(42, 'b');

    EXPECT_FALSE(p3 == p4);

    ft::pair<std::string, float> p5("hoge", 0.42f);
    ft::pair<std::string, float> p6("hoge", 0.42f);

    EXPECT_TRUE(p5 == p6);
}

TEST(Pair, OperatorNotEqual)
{
    ft::pair<int, double> p1(42, 0.42);
    ft::pair<int, double> p2(24, 0.24);

    EXPECT_TRUE(p1 != p2);

    ft::pair<int, char> p3(42, 'a');
    ft::pair<int, char> p4(42, 'b');

    EXPECT_TRUE(p3 != p4);

    ft::pair<std::string, float> p5("hoge", 0.42f);
    ft::pair<std::string, float> p6("hoge", 0.42f);

    EXPECT_FALSE(p5 != p6);
}

TEST(Pair,  OperatorLessThan)
{
    // Compare second when lsh.first < rsh.first
    ft::pair<int, double> p1(10, 0.1);
    ft::pair<int, double> p2(100, 0.2);
    EXPECT_TRUE(p1 < p2);
    p2.second = 0.05;
    EXPECT_TRUE(p1 < p2);
    p2.second = 0.1;
    EXPECT_TRUE(p1 < p2);

    // Compare second when lsh.first > rsh.first
    ft::pair<int, double> p3(100, 0.1);
    ft::pair<int, double> p4(10, 0.2);
    EXPECT_FALSE(p3 < p4);
    p2.second = 0.05;
    EXPECT_FALSE(p3 < p4);
    p2.second = 0.1;
    EXPECT_FALSE(p3 < p4);

    // Compare second when lsh.first == rsh.first
    ft::pair<int, double> p5(100, 0.1);
    ft::pair<int, double> p6(100, 0.2);
    EXPECT_TRUE(p5 < p6);
    p6.second = 0.05;
    EXPECT_FALSE(p5 < p6);
    p6.second = 0.1;
    EXPECT_FALSE(p5 < p6);

    // Compare string
    ft::pair<std::string, int> p7("aaa", 10);
    ft::pair<std::string, int> p8("bbb", 20);
    EXPECT_TRUE(p7 < p8);
    p8.first = "bb";
    EXPECT_TRUE(p7 < p8);
    p8.first = "aa";
    EXPECT_FALSE(p7 < p8);
    p8.first = "aab";
    EXPECT_TRUE(p7 < p8);
    p8.first = "aaab";
    EXPECT_TRUE(p7 < p8);
}

TEST(Pair, OperatorLessThanOrEqual)
{
    // Compare second when lsh.first < rsh.first
    ft::pair<int, double> p1(10, 0.1);
    ft::pair<int, double> p2(100, 0.2);
    EXPECT_TRUE(p1 <= p2);
    p2.second = 0.05;
    EXPECT_TRUE(p1 <= p2);
    p2.second = 0.1;
    EXPECT_TRUE(p1 <= p2);

    // Compare second when lsh.first > rsh.first
    ft::pair<int, double> p3(100, 0.1);
    ft::pair<int, double> p4(10, 0.2);
    EXPECT_FALSE(p3 <= p4);
    p2.second = 0.05;
    EXPECT_FALSE(p3 <= p4);
    p2.second = 0.1;
    EXPECT_FALSE(p3 <= p4);

    // Compare second when lsh.first == rsh.first
    ft::pair<int, double> p5(100, 0.1);
    ft::pair<int, double> p6(100, 0.2);
    EXPECT_TRUE(p5 <= p6);
    p6.second = 0.05;
    EXPECT_FALSE(p5 <= p6);
    p6.second = 0.1;
    EXPECT_TRUE(p5 <= p6);

    // Compare string
    ft::pair<std::string, int> p7("aaa", 10);
    ft::pair<std::string, int> p8("bbb", 20);
    EXPECT_TRUE(p7 <= p8);
    p8.first = "bb";
    EXPECT_TRUE(p7 <= p8);
    p8.first = "aa";
    EXPECT_FALSE(p7 <= p8);
    p8.first = "aab";
    EXPECT_TRUE(p7 <= p8);
    p8.first = "aaab";
    EXPECT_TRUE(p7 <= p8);
}

TEST(Pair, OperatorMoreThan)
{
    // Compare second when lsh.first < rsh.first
    ft::pair<int, double> p1(10, 0.1);
    ft::pair<int, double> p2(100, 0.2);
    EXPECT_FALSE(p1 > p2);
    p2.second = 0.05;
    EXPECT_FALSE(p1 > p2);
    p2.second = 0.1;
    EXPECT_FALSE(p1 > p2);

    // Compare second when lsh.first > rsh.first
    ft::pair<int, double> p3(100, 0.1);
    ft::pair<int, double> p4(10, 0.2);
    EXPECT_TRUE(p3 > p4);
    p2.second = 0.05;
    EXPECT_TRUE(p3 > p4);
    p2.second = 0.1;
    EXPECT_TRUE(p3 > p4);

    // Compare second when lsh.first == rsh.first
    ft::pair<int, double> p5(100, 0.1);
    ft::pair<int, double> p6(100, 0.2);
    EXPECT_FALSE(p5 > p6);
    p6.second = 0.05;
    EXPECT_TRUE(p5 > p6);
    p6.second = 0.1;
    EXPECT_FALSE(p5 > p6);

    // Compare string
    ft::pair<std::string, int> p7("aaa", 10);
    ft::pair<std::string, int> p8("bbb", 20);
    EXPECT_FALSE(p7 > p8);
    p8.first = "bb";
    EXPECT_FALSE(p7 > p8);
    p8.first = "aa";
    EXPECT_TRUE(p7 > p8);
    p8.first = "aab";
    EXPECT_FALSE(p7 > p8);
    p8.first = "aaab";
    EXPECT_FALSE(p7 > p8);
}

TEST(Pair, OperatorMoreThanOrEqual)
{
    // Compare second when lsh.first < rsh.first
    ft::pair<int, double> p1(10, 0.1);
    ft::pair<int, double> p2(100, 0.2);
    EXPECT_FALSE(p1 >= p2);
    p2.second = 0.05;
    EXPECT_FALSE(p1 >= p2);
    p2.second = 0.1;
    EXPECT_FALSE(p1 >= p2);

    // Compare second when lsh.first >= rsh.first
    ft::pair<int, double> p3(100, 0.1);
    ft::pair<int, double> p4(10, 0.2);
    EXPECT_TRUE(p3 >= p4);
    p2.second = 0.05;
    EXPECT_TRUE(p3 >= p4);
    p2.second = 0.1;
    EXPECT_TRUE(p3 >= p4);

    // Compare second when lsh.first == rsh.first
    ft::pair<int, double> p5(100, 0.1);
    ft::pair<int, double> p6(100, 0.2);
    EXPECT_FALSE(p5 >= p6);
    p6.second = 0.05;
    EXPECT_TRUE(p5 >= p6);
    p6.second = 0.1;
    EXPECT_TRUE(p5 >= p6);

    // Compare string
    ft::pair<std::string, int> p7("aaa", 10);
    ft::pair<std::string, int> p8("bbb", 20);
    EXPECT_FALSE(p7 >= p8);
    p8.first = "bb";
    EXPECT_FALSE(p7 >= p8);
    p8.first = "aa";
    EXPECT_TRUE(p7 >= p8);
    p8.first = "aab";
    EXPECT_FALSE(p7 >= p8);
    p8.first = "aaab";
}

TEST(Pair, MakePair)
{
    ft::pair<int, double> p1;
    p1 = ft::make_pair(42, 0.42);
    EXPECT_EQ(42, p1.first);
    EXPECT_EQ(0.42, p1.second);

    ft::pair<std::string, float> p2;
    p2 = ft::make_pair("hoge", 0.42f);
    EXPECT_EQ("hoge", p2.first);
    EXPECT_EQ(0.42f, p2.second);
}
