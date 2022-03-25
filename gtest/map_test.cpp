#include <map.hpp>

#include <gtest/gtest.h>
#include <map>
#include <time.h>

#define SIZE 20
TEST(Map, Construct)
{
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
