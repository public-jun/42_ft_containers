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
        EXPECT_EQ(m.size(), m1.size());
        EXPECT_EQ(m.get_allocator(), m1.get_allocator());
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
        EXPECT_EQ(m.size(), m1.size());
        EXPECT_EQ(m.get_allocator(), m1.get_allocator());
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
        EXPECT_EQ(m.size(), m1.size());
        ft::map<int, int> m2;
        for (int i = 10; i < 20; ++i)
            m2.insert(ft::make_pair(i, i));
        m1 = m2;
        for (int i = 0; i < 10; ++i)
            EXPECT_EQ(m2[i], m1[i]);
        EXPECT_EQ(m.get_allocator(), m1.get_allocator());
        EXPECT_EQ(m1.get_allocator(), m2.get_allocator());
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

TEST(Map, Iterator)
{
    ft::map<int, int> m;
    for (int i = 0; i < 10; ++i)
        m.insert(ft::make_pair(i, i));

    // Non const map && Non const iterator
    ft::map<int, int>::iterator it = m.begin();
    EXPECT_EQ(0, it->first);
    EXPECT_EQ(0, it->second);
    ++it;
    EXPECT_EQ(1, it->first);
    EXPECT_EQ(1, it->second);
    it = m.end();
    --it;
    EXPECT_EQ(9, it->first);
    EXPECT_EQ(9, it->second);

    // Non const map && const iterator
    ft::map<int, int>::const_iterator cit = m.begin();
    EXPECT_EQ(0, cit->first);
    EXPECT_EQ(0, cit->second);
    ++cit;
    EXPECT_EQ(1, cit->first);
    EXPECT_EQ(1, cit->second);
    cit = m.end();
    --cit;
    EXPECT_EQ(9, cit->first);
    EXPECT_EQ(9, cit->second);

    // const map && const iterator
    const ft::map<int, int>           cm1(m);
    ft::map<int, int>::const_iterator cit2 = cm1.begin();
    EXPECT_EQ(0, cit2->first);
    EXPECT_EQ(0, cit2->second);
    const ft::map<int, int> cm2(cm1);
    cit2 = cm2.begin();
    EXPECT_EQ(0, cit2->first);
    EXPECT_EQ(0, cit2->second);
    ft::map<int, int>::const_iterator cit3;
    cit3 = cit2;
    EXPECT_EQ(0, cit3->first);
    EXPECT_EQ(0, cit3->second);
    cit3++;
    EXPECT_EQ(1, cit3->first);
    EXPECT_EQ(1, cit3->second);
    cit3 = cm1.end();
    --cit3;
    EXPECT_EQ(9, cit3->first);
    EXPECT_EQ(9, cit3->second);
}

TEST(Map, ReverseIterator)
{
    // reverse_iterator
    ft::map<int, int> m;
    for (int i = 0; i < 10; ++i)
        m.insert(ft::make_pair(i, i));
    ft::map<int, int>::reverse_iterator rit = m.rbegin();

    int j = 9;
    for (ft::map<int, int>::reverse_iterator end = m.rend(); rit != end;
         ++rit, --j)
    {
        EXPECT_EQ(j, rit->first);
        EXPECT_EQ(j, rit->second);
    }

    // const_reverse_iterator
    const ft::map<int, int>                   cm(m);
    ft::map<int, int>::const_reverse_iterator crit = cm.rbegin();
    j                                              = 9;
    for (ft::map<int, int>::const_reverse_iterator end = cm.rend(); crit != end;
         ++crit, --j)
    {
        EXPECT_EQ(j, crit->first);
        EXPECT_EQ(j, crit->second);
    }
}

TEST(Map, CapacitySizeAndEmpty)
{
    ft::map<int, int> m;
    EXPECT_TRUE(m.empty());
    for (int i = 0; i < 10; ++i)
    {
        m.insert(ft::make_pair(i, i));
        EXPECT_EQ(i + 1, m.size());
    }
    EXPECT_FALSE(m.empty());
    const ft::map<int, int> cm(m);
    EXPECT_EQ(m.size(), cm.size());
}

TEST(Map, CapacityMaxSize)
{
    {
        ft::map<int, int>  ft_m;
        std::map<int, int> stl_m;
        EXPECT_EQ(stl_m.max_size(), ft_m.max_size());
    }
    {
        ft::map<std::string, int>  ft_m;
        std::map<std::string, int> stl_m;
        EXPECT_EQ(stl_m.max_size(), ft_m.max_size());
    }
    {
        ft::map<std::string, char>  ft_m;
        std::map<std::string, char> stl_m;
        EXPECT_EQ(stl_m.max_size(), ft_m.max_size());
    }
    {
        ft::map<double, float>  ft_m;
        std::map<double, float> stl_m;
        EXPECT_EQ(stl_m.max_size(), ft_m.max_size());
    }
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
