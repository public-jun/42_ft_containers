#include <map.hpp>

#include <gtest/gtest.h>
#include <map>
#include <time.h>

#define SIZE 1000
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
    // const ft::map<int, int>           cm(m);
    // ft::map<int, int>::const_iterator cit;
    // cit = cm.lower_bound(0);
    // EXPECT_EQ(0, (*cit).first);
    // cit = m.lower_bound(23);
    // EXPECT_EQ(30, (*cit).first);
    // cit = cm.lower_bound(53);
    // EXPECT_TRUE(cm.end() == cit);
}
