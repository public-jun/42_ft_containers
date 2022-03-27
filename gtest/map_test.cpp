#include <map.hpp>

#include <gtest/gtest.h>
#include <map>
#include <time.h>
#define SIZE 1000

TEST(Map, Constructor)
{
    // map()
    ft::map<int, int> m;

    // explicit map(const Compare& comp, const Allocator& alloc = Allocator()
    // );

    //  map( InputIt first, InputIt last, const Compare& comp = Compare(), const
    //  Allocator& alloc = Allocator() )
    {
        ft::map<int, int> m;
        for (int i = 0; i < 10; ++i)
            m.insert(ft::make_pair(i, i));
        ft::map<int, int>           m1(m.begin(), m.end());
        ft::map<int, int>::iterator m1it = m1.begin();
        for (ft::map<int, int>::iterator mit = m.begin(); mit != m.end(); ++mit)
        {
            EXPECT_EQ(*m1it, *mit);
            ++m1it;
        }
    }
    {
        ft::map<int, int> m;
        for (int i = 0; i < 10; ++i)
            m.insert(ft::make_pair(i, i));
        const ft::map<int, int>           m1(m.begin(), m.end());
        ft::map<int, int>::const_iterator m1it = m1.begin();
        for (ft::map<int, int>::iterator mit = m.begin(); mit != m.end(); ++mit)
        {
            EXPECT_EQ(*m1it, *mit);
            ++m1it;
        }
    }
    // map( const map& other );

    // operator=(const map& other);
    {
        ft::map<int, int> m;
        for (int i = 0; i < 10; ++i)
            m.insert(ft::make_pair(i, i));
        ft::map<int, int> m1;
        m1 = m;
        for (int i = 0; i < 10; ++i)
            EXPECT_EQ(m[i], m1[i]);
        ft::map<int, int> m2;
        for (int i = 10; i < 20; ++i)
            m2.insert(ft::make_pair(i, i));
        m1 = m2;
        for (int i = 0; i < 10; ++i)
            EXPECT_EQ(m2[i], m1[i]);
    }
}

TEST(Map, ElementAccess)
{
    // std::map<Key,T,Compare,Allocator>::at
    ft::map<int, char> m;
    for (int i = 0; i < 10; ++i)
        m.insert(ft::make_pair(i, 'a' + static_cast<char>(i)));
    for (int i = 0; i < 10; ++i)
        EXPECT_EQ('a' + i, m[i]);
    m[10] = 'x';
    EXPECT_EQ('x', m[10]);
    m[-42] = 'y';
    EXPECT_EQ('y', m[-42]);
    m[0] = 'z';
    EXPECT_EQ('z', m[0]);
}

TEST(Map, ModifiersInsert)
{
    // std::pair<iterator,bool> insert( const value_type& value );
    std::vector<int> v;
    std::srand(time(NULL));
    ft::map<int, int> m;
    for (int i = 0; i < SIZE; ++i)
    {
        ft::pair<ft::map<int, int>::iterator, bool> ret;

        int key = std::rand() % SIZE;
        ret     = m.insert(ft::make_pair(key, key));
        EXPECT_EQ(ret.first->first, key);
        if (ret.second == true)
            v.insert(v.begin(), key);
    }
    std::sort(v.begin(), v.end());
    ft::map<int, int>::iterator it  = m.begin();
    ft::map<int, int>::iterator end = m.end();

    int i = 0;
    while (it != end)
    {
        EXPECT_EQ((*it).second, v.at(i++));
        ++it;
    }
}

TEST(Map, ModifiersClear)
{
    ft::map<int, int> m;
    for (int i = 0; i < 10; ++i)
        m.insert(ft::make_pair(i, i));
    m.clear();
    m.clear();
}

TEST(Map, LookupLowerBound)
{
    // Non const
    ft::map<int, int> m;
    for (int i = 0; i < 50; i += 10)
        m.insert(ft::make_pair(i, i));
    ft::map<int, int>::iterator it;
    it = m.lower_bound(0);
    EXPECT_EQ(0, (*it).first);
    it = m.lower_bound(23);
    EXPECT_EQ(30, (*it).first);
    it = m.lower_bound(53);
    EXPECT_TRUE(m.end() == it);

    // Const
    ft::map<int, int>                 cm = m;
    ft::map<int, int>::const_iterator cit;
    cit = cm.lower_bound(0);
    EXPECT_EQ(0, (*cit).first);
    cit = m.lower_bound(23);
    EXPECT_EQ(30, (*cit).first);
    cit = cm.lower_bound(53);
    EXPECT_TRUE(cm.end() == cit);
}
