#include <map.hpp>

#include <gtest/gtest.h>
#include <map>
#include <time.h>
#define SIZE 5000

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
        ft::map<std::string, int, std::less<std::string> >  ft_m;
        std::map<std::string, int, std::less<std::string> > stl_m;
        EXPECT_EQ(stl_m.max_size(), ft_m.max_size());
    }
    {
        ft::map<std::string, char, std::less<std::string> >  ft_m;
        std::map<std::string, char, std::less<std::string> > stl_m;
        EXPECT_EQ(stl_m.max_size(), ft_m.max_size());
    }
    {
        ft::map<double, float, std::less<double> >  ft_m;
        std::map<double, float, std::less<double> > stl_m;
        EXPECT_EQ(stl_m.max_size(), ft_m.max_size());
    }
}

TEST(Map, ModifiersInsert)
{
    // std::pair<iterator,bool> insert( const value_type& value );
    std::srand(time(NULL));
    {
        std::vector<int>                            v;
        ft::map<int, int>                           m;
        ft::pair<ft::map<int, int>::iterator, bool> ret;
        for (int i = 0; i < SIZE; ++i)
        {

            int key = std::rand();
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

    // iterator insert( iterator hint, const value_type& value );
    {
        std::vector<int>            v;
        std::set<int>               s;
        std::set<int>::iterator     sit;
        ft::map<int, int>           m;
        ft::map<int, int>::iterator it = m.begin();
        ft::map<int, int>::iterator end;
        for (int i = 0; i < SIZE; ++i)
        {
            int key = std::rand() / SIZE;
            it      = m.insert(it, ft::make_pair(key, key));
            EXPECT_EQ((*it).first, key);
            ++it;
            s.insert(key);
        }
        it    = m.begin();
        end   = m.end();
        int i = 0;

        sit = s.begin();
        while (it != end)
        {
            EXPECT_EQ((*it).second, *sit);
            ++sit;
            ++it;
        }
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

TEST(Map, ModifiersMemberSwap)
{
    ft::map<int, char> m1;
    for (int i = 0; i < 10; ++i)
        m1.insert(ft::make_pair(i, 'a' + i));
    ft::map<int, char> m2;
    for (int i = -10; i < -4; ++i)
        m2.insert(ft::make_pair(i, 'z' - i));
    ft::map<int, char>::iterator prev_m1_it = m1.begin();
    ft::map<int, char>::iterator prev_m2_it = m2.begin();
    ft::map<int, char>::iterator tmp_it;
    m1.swap(m2);
    tmp_it = m2.begin();
    for (ft::map<int, char>::iterator end = m2.end(); tmp_it != end;
         ++tmp_it, ++prev_m1_it)
    {
        EXPECT_EQ(prev_m1_it, tmp_it);
        EXPECT_EQ((*prev_m1_it).first, (*tmp_it).first);
        EXPECT_EQ((*prev_m1_it).second, (*tmp_it).second);
    }
    tmp_it = m1.begin();
    for (ft::map<int, char>::iterator end = m1.end(); tmp_it != end;
         ++tmp_it, ++prev_m2_it)
    {
        EXPECT_EQ(prev_m2_it, tmp_it);
        EXPECT_EQ((*prev_m2_it).first, (*tmp_it).first);
        EXPECT_EQ((*prev_m2_it).second, (*tmp_it).second);
    }

    prev_m1_it = m1.begin();
    ft::map<int, char>           empty1;
    ft::map<int, char>::iterator prev_empty_it  = empty1.begin();
    ft::map<int, char>::iterator prev_empty_end = empty1.end();
    empty1.swap(m1);
    tmp_it = empty1.begin();
    for (ft::map<int, char>::iterator end = empty1.end(); tmp_it != end;
         ++tmp_it, ++prev_m1_it)
    {
        EXPECT_EQ(prev_m1_it, tmp_it);
        EXPECT_EQ((*prev_m1_it).first, (*tmp_it).first);
        EXPECT_EQ((*prev_m1_it).second, (*tmp_it).second);
    }
    EXPECT_NE(prev_empty_it, m1.begin());
    EXPECT_NE(prev_empty_end, m1.end());
    for (int i = 0; i < 10; ++i)
        m1.insert(ft::make_pair(i, 'a' + i));
    tmp_it = m1.begin();
    for (int i = 0; i < 10; ++i, ++tmp_it)
    {
        EXPECT_EQ(i, (*tmp_it).first);
        EXPECT_EQ('a' + i, (*tmp_it).second);
    }
}

TEST(Map, LookupCount)
{
    ft::map<int, int> m;
    for (int i = 0; i < 10; ++i)
        m.insert(ft::make_pair(i, i));
    EXPECT_EQ(1, m.count(1));
    EXPECT_EQ(0, m.count(42));
    m.insert(ft::make_pair(42, 42));
    EXPECT_EQ(1, m.count(42));
}

TEST(Map, Lookupfind)
{
    ft::map<int, int> m;
    for (int i = 1; i < 20; i *= 2)
        m.insert(ft::make_pair(i, i));
    ft::map<int, int>::iterator it = m.find(2);
    EXPECT_EQ(2, (*it).first);
    it = m.find(3);
    EXPECT_EQ(m.end(), it);

    const ft::map<int, int>           cm(m);
    ft::map<int, int>::const_iterator cit = cm.find(2);
    EXPECT_EQ(2, (*cit).first);
    cit = cm.find(3);
    EXPECT_EQ(cm.end(), cit);
}

TEST(Map, LookupEqualRange)
{
    // Non Const
    // std::pair<iterator,iterator> equal_range( const Key& key );
    ft::map<int, int> m;
    for (int i = 0; i < 100; i += 10)
        m.insert(ft::make_pair(i, i));
    ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> ret;
    ret = m.equal_range(-10);
    EXPECT_EQ(0, (*ret.first).first);
    EXPECT_EQ(0, (*ret.second).first);
    ret = m.equal_range(0);
    EXPECT_EQ(0, (*ret.first).first);
    EXPECT_EQ(10, (*ret.second).first);
    ret = m.equal_range(42);
    EXPECT_EQ(50, (*ret.first).first);
    EXPECT_EQ(50, (*ret.second).first);
    ret = m.equal_range(50);
    EXPECT_EQ(50, (*ret.first).first);
    EXPECT_EQ(60, (*ret.second).first);
    ret = m.equal_range(90);
    EXPECT_EQ(90, (*ret.first).first);
    EXPECT_EQ(m.end(), ret.second);
    ret = m.equal_range(100);
    EXPECT_EQ(m.end(), ret.first);
    EXPECT_EQ(m.end(), ret.second);

    // Const
    // ft::pair<const_iterator, const_iterator> equal_range(const Key& key)
    // const;
    const ft::map<int, int> cm(m);

    ft::pair<ft::map<int, int>::const_iterator,
             ft::map<int, int>::const_iterator>
        cret;
    cret = cm.equal_range(-10);
    EXPECT_EQ(0, (*cret.first).first);
    EXPECT_EQ(0, (*cret.second).first);
    cret = cm.equal_range(0);
    EXPECT_EQ(0, (*cret.first).first);
    EXPECT_EQ(10, (*cret.second).first);
    cret = cm.equal_range(42);
    EXPECT_EQ(50, (*cret.first).first);
    EXPECT_EQ(50, (*cret.second).first);
    cret = cm.equal_range(50);
    EXPECT_EQ(50, (*cret.first).first);
    EXPECT_EQ(60, (*cret.second).first);
    cret = cm.equal_range(90);
    EXPECT_EQ(90, (*cret.first).first);
    EXPECT_EQ(cm.end(), cret.second);
    cret = cm.equal_range(100);
    EXPECT_EQ(cm.end(), cret.first);
    EXPECT_EQ(cm.end(), cret.second);
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

TEST(Map, LookupUpperBound)
{
    // Non const
    // iterator upper_bound( const Key& key );
    ft::map<int, int> m;
    for (int i = 0; i < 50; i += 10)
        m.insert(ft::make_pair(i, i));
    ft::map<int, int>::iterator it;
    it = m.upper_bound(-100);
    EXPECT_EQ(m.begin(), it);
    EXPECT_EQ(0, (*it).first);
    it = m.upper_bound(10);
    EXPECT_EQ(20, (*it).first);
    it = m.upper_bound(100);
    EXPECT_EQ(m.end(), it);

    // Const
    // const_iterator upper_bound( const Key& key ) const;
    const ft::map<int, int>           cm(m);
    ft::map<int, int>::const_iterator cit;
    cit = cm.upper_bound(-100);
    EXPECT_EQ(cm.begin(), cit);
    EXPECT_EQ(0, (*cit).first);
    cit = cm.upper_bound(10);
    EXPECT_EQ(20, (*cit).first);
    cit = cm.upper_bound(100);
    EXPECT_EQ(cm.end(), cit);
}

TEST(Map, ObserversKeyComp)
{
    {
        ft::map<int, char>              m;
        ft::map<int, char>::key_compare comp;
        comp = m.key_comp();
        EXPECT_TRUE(comp(1, 2));
        EXPECT_FALSE(comp(2, 2));
        EXPECT_FALSE(comp(3, 2));
    }

    {
        ft::map<int, char, std::greater<int> >              m;
        ft::map<int, char, std::greater<int> >::key_compare comp;
        comp = m.key_comp();
        EXPECT_FALSE(comp(1, 2));
        EXPECT_FALSE(comp(2, 2));
        EXPECT_TRUE(comp(3, 2));
    }

    {
        ft::map<std::string, char, std::less<std::string> >              m;
        ft::map<std::string, char, std::less<std::string> >::key_compare comp;
        comp = m.key_comp();
        EXPECT_TRUE(comp("abc", "xyz"));
        EXPECT_FALSE(comp("abc", "abc"));
        EXPECT_FALSE(comp("xyz", "abc"));
    }

    {
        ft::map<std::string, char, std::greater<std::string> > m;
        ft::map<std::string, char, std::greater<std::string> >::key_compare
            comp;
        comp = m.key_comp();
        EXPECT_FALSE(comp("abc", "xyz"));
        EXPECT_FALSE(comp("abc", "abc"));
        EXPECT_TRUE(comp("xyz", "abc"));
    }
}

TEST(Map, ObserversValueComp)
{
    {
        ft::map<int, char>                m;
        ft::map<int, char>::value_compare comp = m.value_comp();
        EXPECT_TRUE(comp(ft::make_pair(1, 'a'), ft::make_pair(2, 'a')));
        EXPECT_FALSE(comp(ft::make_pair(2, 'a'), ft::make_pair(2, 'a')));
        EXPECT_FALSE(comp(ft::make_pair(3, 'a'), ft::make_pair(1, 'a')));
    }

    {
        ft::map<int, char, std::greater<int> >                m;
        ft::map<int, char, std::greater<int> >::value_compare comp =
            m.value_comp();
        EXPECT_FALSE(comp(ft::make_pair(1, 'a'), ft::make_pair(2, 'a')));
        EXPECT_FALSE(comp(ft::make_pair(2, 'a'), ft::make_pair(2, 'a')));
        EXPECT_TRUE(comp(ft::make_pair(3, 'a'), ft::make_pair(1, 'a')));
    }

    {
        ft::map<std::string, char, std::less<std::string> > m;
        ft::map<std::string, char, std::less<std::string> >::value_compare
            comp = m.value_comp();
        EXPECT_TRUE(comp(ft::make_pair("abc", 'a'), ft::make_pair("xyz", 'a')));
        EXPECT_FALSE(
            comp(ft::make_pair("abc", 'a'), ft::make_pair("abc", 'a')));
        EXPECT_FALSE(
            comp(ft::make_pair("xyz", 'a'), ft::make_pair("abc", 'a')));
    }

    {
        ft::map<std::string, char, std::greater<std::string> > m;
        ft::map<std::string, char, std::greater<std::string> >::value_compare
            comp = m.value_comp();
        EXPECT_FALSE(
            comp(ft::make_pair("abc", 'a'), ft::make_pair("xyz", 'a')));
        EXPECT_FALSE(
            comp(ft::make_pair("abc", 'a'), ft::make_pair("abc", 'a')));
        EXPECT_TRUE(comp(ft::make_pair("xyz", 'a'), ft::make_pair("abc", 'a')));
    }
}

TEST(Map, NonMemberFunctionsLexicographical)
{
    {
        ft::map<int, char> m1;
        ft::map<int, char> m2;
        m1[0] = 'a';
        m2[0] = 'a';
        EXPECT_TRUE(m1 == m2);
        EXPECT_FALSE(m1 != m2);
        EXPECT_FALSE(m1 < m2);
        EXPECT_TRUE(m1 <= m2);
        EXPECT_FALSE(m1 > m2);
        EXPECT_TRUE(m1 >= m2);

        m2[1] = 'b';
        // a & ab
        EXPECT_FALSE(m1 == m2);
        EXPECT_TRUE(m1 != m2);
        EXPECT_TRUE(m1 < m2);
        EXPECT_TRUE(m1 <= m2);
        EXPECT_FALSE(m1 > m2);
        EXPECT_FALSE(m1 >= m2);

        m1[1] = 'c';
        // ac & ab
        EXPECT_FALSE(m1 == m2);
        EXPECT_TRUE(m1 != m2);
        EXPECT_FALSE(m1 < m2);
        EXPECT_FALSE(m1 <= m2);
        EXPECT_TRUE(m1 > m2);
        EXPECT_TRUE(m1 >= m2);
    }
    // key を比較する。同じ場合は valueで比較する。
    {
        ft::map<std::string, char, std::less<std::string> > m1;
        ft::map<std::string, char, std::less<std::string> > m2;
        m1["aaa"] = 'a';
        m2["aaa"] = 'a';
        EXPECT_TRUE(m1 == m2);
        EXPECT_FALSE(m1 != m2);
        EXPECT_FALSE(m1 < m2);
        EXPECT_TRUE(m1 <= m2);
        EXPECT_FALSE(m1 > m2);
        EXPECT_TRUE(m1 >= m2);
        m2["aaa"] = 'b';
        EXPECT_FALSE(m1 == m2);
        EXPECT_TRUE(m1 != m2);
        EXPECT_TRUE(m1 < m2);
        EXPECT_TRUE(m1 <= m2);
        EXPECT_FALSE(m1 > m2);
        EXPECT_FALSE(m1 >= m2);
        m1["bbb"] = 'b';
        // ab & b
        EXPECT_EQ(2, m1.size());
        EXPECT_FALSE(m1 == m2);
        EXPECT_TRUE(m1 != m2);
        EXPECT_TRUE(m1 < m2);
        EXPECT_TRUE(m1 <= m2);
        EXPECT_FALSE(m1 > m2);
        EXPECT_FALSE(m1 >= m2);
    }
}

TEST(Map, NonMemberFunctionsSwap)
{
    ft::map<int, char> m1;
    for (int i = 0; i < 10; ++i)
        m1.insert(ft::make_pair(i, 'a' + i));
    ft::map<int, char> m2;
    for (int i = -10; i < -4; ++i)
        m2.insert(ft::make_pair(i, 'z' - i));
    ft::map<int, char>::iterator prev_m1_it = m1.begin();
    ft::map<int, char>::iterator prev_m2_it = m2.begin();
    ft::map<int, char>::iterator tmp_it;
    ft::swap(m1, m2);
    tmp_it = m2.begin();
    for (ft::map<int, char>::iterator end = m2.end(); tmp_it != end;
         ++tmp_it, ++prev_m1_it)
    {
        EXPECT_EQ(prev_m1_it, tmp_it);
        EXPECT_EQ((*prev_m1_it).first, (*tmp_it).first);
        EXPECT_EQ((*prev_m1_it).second, (*tmp_it).second);
    }
    tmp_it = m1.begin();
    for (ft::map<int, char>::iterator end = m1.end(); tmp_it != end;
         ++tmp_it, ++prev_m2_it)
    {
        EXPECT_EQ(prev_m2_it, tmp_it);
        EXPECT_EQ((*prev_m2_it).first, (*tmp_it).first);
        EXPECT_EQ((*prev_m2_it).second, (*tmp_it).second);
    }

    prev_m1_it = m1.begin();
    ft::map<int, char>           empty1;
    ft::map<int, char>::iterator prev_empty_it  = empty1.begin();
    ft::map<int, char>::iterator prev_empty_end = empty1.end();
    ft::swap(empty1, m1);
    tmp_it = empty1.begin();
    for (ft::map<int, char>::iterator end = empty1.end(); tmp_it != end;
         ++tmp_it, ++prev_m1_it)
    {
        EXPECT_EQ(prev_m1_it, tmp_it);
        EXPECT_EQ((*prev_m1_it).first, (*tmp_it).first);
        EXPECT_EQ((*prev_m1_it).second, (*tmp_it).second);
    }
    EXPECT_NE(prev_empty_it, m1.begin());
    EXPECT_NE(prev_empty_end, m1.end());
    for (int i = 0; i < 10; ++i)
        m1.insert(ft::make_pair(i, 'a' + i));
    tmp_it = m1.begin();
    for (int i = 0; i < 10; ++i, ++tmp_it)
    {
        EXPECT_EQ(i, (*tmp_it).first);
        EXPECT_EQ('a' + i, (*tmp_it).second);
    }
}
