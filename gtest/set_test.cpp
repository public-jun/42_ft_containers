#include <set.hpp>

#include <gtest/gtest.h>
#include <set>
#include <time.h>

// 内部構造はmapと同じなのでテストは簡易

template <class T>
void compare_set_iterator(T first1, T end1, T first2)
{
    for (; first1 != end1; ++first1, ++first2)
        EXPECT_EQ(*first1, *first2);
}

TEST(Set, Constructor)
{
    // set();
    {
        ft::set<int> s;
        EXPECT_EQ(0, s.size());
        EXPECT_EQ(true, s.empty());
        EXPECT_EQ(s.begin(), s.end());
        EXPECT_EQ(s.rbegin(), s.rend());
    }

    // explicit set(const Compare& comp, const Allocator& alloc = Allocator());
    {
        ft::set<int, std::greater<int> > s((std::greater<int>()),
                                           (std::allocator<int>()));
        EXPECT_EQ(0, s.size());
        EXPECT_EQ(true, s.empty());
    }

    // template< class InputIt >
    // set(InputIt first, InputIt last, const Compare& comp = Compare(),
    //    const Allocator& alloc = Allocator());
    {
        ft::set<int> s1;
        for (int i = 0; i < 10; ++i)
            s1.insert(i);
        ft::set<int> s2(s1.begin(), s1.end(), (std::less<int>()),
                        (std::allocator<int>()));
        compare_set_iterator(s1.begin(), s1.end(), s2.begin());
        EXPECT_EQ(s1.size(), s2.size());
        EXPECT_EQ(s1.get_allocator(), s2.get_allocator());
    }
    // set( const set& other );
    {
        ft::set<int> s1;
        for (int i = 0; i < 10; ++i)
            s1.insert(i);
        ft::set<int> s2(s1);
        compare_set_iterator(s1.begin(), s1.end(), s2.begin());
        EXPECT_EQ(s1.size(), s2.size());
        EXPECT_EQ(s1.get_allocator(), s2.get_allocator());
    }
    // operator=(const set& other);
    {
        ft::set<int> s1;
        for (int i = 0; i < 10; ++i)
            s1.insert(i);
        ft::set<int> s2;
        s2 = s1;
        compare_set_iterator(s1.begin(), s1.end(), s2.begin());
        EXPECT_EQ(s1.size(), s2.size());
        EXPECT_EQ(s1.get_allocator(), s2.get_allocator());
        ft::set<int> s3;
        for (int i = 10; i < 30; ++i)
            s3.insert(i);
        s2 = s3;
        compare_set_iterator(s3.begin(), s3.end(), s2.begin());
        EXPECT_EQ(s3.size(), s2.size());
        EXPECT_EQ(s3.get_allocator(), s2.get_allocator());
    }
}

TEST(Set, Iterator)
{
    ft::set<int> s;
    for (int i = 0; i < 10; ++i)
        s.insert(i);

    // Non const map && Non const iterator
    ft::set<int>::iterator it = s.begin();
    EXPECT_EQ(0, *it);
    ++it;
    EXPECT_EQ(1, *it);
    it = s.end();
    --it;
    EXPECT_EQ(9, *it);

    // Non const map && const iterator
    ft::set<int>::const_iterator cit = s.begin();
    EXPECT_EQ(0, *cit);
    ++cit;
    EXPECT_EQ(1, *cit);
    cit = s.end();
    --cit;
    EXPECT_EQ(9, *cit);

    // const map && const iterator
    const ft::set<int>           cs1(s);
    ft::set<int>::const_iterator cit2 = cs1.begin();
    EXPECT_EQ(0, *cit2);
    const ft::set<int> cs2(cs1);
    cit2 = cs2.begin();
    EXPECT_EQ(0, *cit2);
    ft::set<int>::const_iterator cit3;
    cit3 = cit2;
    EXPECT_EQ(0, *cit3);
    cit3++;
    EXPECT_EQ(1, *cit3);
    cit3 = cs1.end();
    --cit3;
    EXPECT_EQ(9, *cit3);
}

TEST(Set, ReverseIterator)
{
    // reverse_iterator
    ft::set<int> s;
    for (int i = 0; i < 10; ++i)
        s.insert(i);
    ft::set<int>::reverse_iterator rit = s.rbegin();

    int j = 9;
    for (ft::set<int>::reverse_iterator end = s.rend(); rit != end; ++rit, --j)
    {
        EXPECT_EQ(j, *rit);
    }

    // const_reverse_iterator
    const ft::set<int>                   cs(s);
    ft::set<int>::const_reverse_iterator crit = cs.rbegin();
    j                                         = 9;
    for (ft::set<int>::const_reverse_iterator end = cs.rend(); crit != end;
         ++crit, --j)
    {
        EXPECT_EQ(j, *crit);
    }
}

TEST(Set, CapacitySizeAndEmpty)
{
    ft::set<int> s;
    EXPECT_TRUE(s.empty());
    for (int i = 0; i < 10; ++i)
    {
        s.insert(i);
        EXPECT_EQ(i + 1, s.size());
    }
    EXPECT_FALSE(s.empty());
    const ft::set<int> cs(s);
    EXPECT_EQ(s.size(), cs.size());
}

TEST(Set, CapacityMaxSize)
{
    {
        ft::set<int>  ft_s;
        std::set<int> stl_s;
        EXPECT_EQ(stl_s.max_size(), ft_s.max_size());
    }
    {
        ft::set<std::string, std::less<std::string> >  ft_s;
        std::set<std::string, std::less<std::string> > stl_s;
        EXPECT_EQ(stl_s.max_size(), ft_s.max_size());
    }
    {
        ft::set<std::string, std::less<std::string> >  ft_s;
        std::set<std::string, std::less<std::string> > stl_s;
        EXPECT_EQ(stl_s.max_size(), ft_s.max_size());
    }
    {
        ft::set<double, std::less<double> >  ft_s;
        std::set<double, std::less<double> > stl_s;
        EXPECT_EQ(stl_s.max_size(), ft_s.max_size());
    }
}

TEST(Set, ModifiersInsert)
{
    // std::pair<iterator,bool> insert( const value_type& value );
    std::srand(time(NULL));
    {
        std::vector<int>                       v;
        ft::set<int>                           s;
        ft::pair<ft::set<int>::iterator, bool> ret;
        for (int i = 0; i < SIZE; ++i)
        {

            int key = std::rand();
            ret     = s.insert(key);
            EXPECT_EQ(*(ret.first), key);
            if (ret.second == true)
                v.insert(v.begin(), key);
        }
        std::sort(v.begin(), v.end());
        ft::set<int>::iterator it  = s.begin();
        ft::set<int>::iterator end = s.end();

        int i = 0;
        while (it != end)
        {
            EXPECT_EQ((*it), v.at(i++));
            ++it;
        }
    }

    // iterator insert( iterator hint, const value_type& value );
    {
        std::set<int>           stl_s;
        std::set<int>::iterator sit;
        ft::set<int>            s;
        ft::set<int>::iterator  it = s.begin();
        ft::set<int>::iterator  end;
        for (int i = 0; i < SIZE; ++i)
        {
            int key = std::rand() / SIZE;
            it      = s.insert(it, key);
            EXPECT_EQ(*it, key);
            ++it;
            stl_s.insert(key);
        }
        it    = s.begin();
        end   = s.end();
        int i = 0;

        sit = stl_s.begin();
        while (it != end)
        {
            EXPECT_EQ(*it, *sit);
            ++sit;
            ++it;
        }
    }

    // template< class InputIt >
    // void insert(InputIt first, InputIt last)
    {
        ft::set<int> s;
        for (int i = 1; i <= 20; ++i)
            s.insert(i);
        for (int i = 41; i <= 60; ++i)
            s.insert(i);
        ft::set<int> s1;
        for (int i = 21; i <= 40; ++i)
            s1.insert(i);
        s.insert(s1.begin(), s1.end());
        ft::set<int>::iterator it = s.begin();
        for (int i = 1; i <= 60; ++i)
            EXPECT_EQ(i, *(it++));
    }
}

TEST(Set, ModifiersErase)
{
    std::srand(time(NULL));
    // void erase( iterator pos );
    {
        std::vector<int> v;
        ft::set<int>     s;

        ft::pair<ft::set<int>::iterator, bool> ret;
        for (int i = 0; i < SIZE; ++i)
        {
            int key = std::rand() % SIZE;
            ret     = s.insert(key);
            EXPECT_EQ(*(ret.first), key);
            if (ret.second == true)
                v.insert(v.begin(), key);
        }
        std::vector<int>::iterator it = v.begin();
        for (std::vector<int>::iterator end = v.end(); it != end; ++it)
        {
            s.erase(s.find(*it));
        }
        EXPECT_EQ(s.size(), 0);
        EXPECT_TRUE(s.empty());
    }

    // void erase( iterator first, iterator last );
    {
        std::vector<int> v;
        ft::set<int>     s;

        ft::pair<ft::set<int>::iterator, bool> ret;
        for (int i = 0; i < SIZE; ++i)
        {
            int key = std::rand() % SIZE;
            ret     = s.insert(key);
            EXPECT_EQ(*(ret.first), key);
            if (ret.second == true)
                v.insert(v.begin(), key);
        }
        std::sort(v.begin(), v.end());

        std::vector<int>::iterator vf, vl, vtmp;
        // 削除する範囲の値を得る
        while (true)
        {
            vf = find(v.begin(), v.end(), std::rand() % SIZE);
            vl = find(vf, v.end(), std::rand() % SIZE);
            if (vf != v.end() && vl != v.end())
                break;
        }
        ft::set<int>::iterator first, last, stmp;
        first = s.find(*vf);
        last  = s.find(*vl);

        s.erase(first, last);

        vtmp = v.begin();
        stmp = s.begin();

        std::size_t size             = 0;
        bool        is_removed_range = false;
        for (; vtmp != v.end(); ++vtmp)
        {
            if (vtmp == vf)
                is_removed_range = true;
            if (vtmp == vl)
                is_removed_range = false;
            if (is_removed_range == false)
            {
                EXPECT_EQ(*vtmp, *stmp);
                ++size;
                ++stmp;
            }
            // [first, last) が消去されているか確認
            if (is_removed_range == true)
                EXPECT_EQ(s.end(), s.find(*vtmp));
        }
        EXPECT_EQ(size, s.size());
        EXPECT_FALSE(s.empty());
    }

    // size_type erase( const key_type& key );
    {
        std::vector<int> v;
        ft::set<int>     s;
        int              key;

        ft::pair<ft::set<int>::iterator, bool> ret;
        for (int i = 0; i < SIZE; ++i)
        {
            key = std::rand() % SIZE;
            ret = s.insert(key);
            EXPECT_EQ(*ret.first, key);
            if (ret.second == true)
                v.insert(v.begin(), key);
        }
        std::sort(v.begin(), v.end());

        for (int i = 0; i < SIZE; ++i)
        {
            key = std::rand() % SIZE;

            std::vector<int>::iterator it = find(v.begin(), v.end(), key);
            if (it != v.end())
            {
                EXPECT_EQ(1, s.erase(key));
                v.erase(it);
            }
            else
                EXPECT_EQ(0, s.erase(key));
            EXPECT_EQ(v.size(), s.size());
        }
    }
}

TEST(Set, ModifiersClear)
{
    ft::set<int> s;
    for (int i = 0; i < 10; ++i)
        s.insert(i);
    s.clear();
    s.clear();
    EXPECT_EQ(0, s.size());
    EXPECT_TRUE(s.empty());
}

TEST(Set, ModifiersMemberSwap)
{
    ft::set<char> s1;
    for (int i = 0; i < 10; ++i)
        s1.insert('a' + i);
    ft::set<char> s2;
    for (int i = -10; i < -4; ++i)
        s2.insert('z' - i);
    ft::set<char>::iterator prev_s1_it = s1.begin();
    ft::set<char>::iterator prev_s2_it = s2.begin();
    ft::set<char>::iterator tmp_it;
    s1.swap(s2);
    tmp_it = s2.begin();
    for (ft::set<char>::iterator end = s2.end(); tmp_it != end;
         ++tmp_it, ++prev_s1_it)
    {
        EXPECT_EQ(prev_s1_it, tmp_it);
        EXPECT_EQ(*prev_s1_it, *tmp_it);
    }
    tmp_it = s1.begin();
    for (ft::set<char>::iterator end = s1.end(); tmp_it != end;
         ++tmp_it, ++prev_s2_it)
    {
        EXPECT_EQ(prev_s2_it, tmp_it);
        EXPECT_EQ(*prev_s2_it, *tmp_it);
    }

    prev_s1_it = s1.begin();
    ft::set<char>           empty1;
    ft::set<char>::iterator prev_empty_it  = empty1.begin();
    ft::set<char>::iterator prev_empty_end = empty1.end();
    empty1.swap(s1);
    tmp_it = empty1.begin();
    for (ft::set<char>::iterator end = empty1.end(); tmp_it != end;
         ++tmp_it, ++prev_s1_it)
    {
        EXPECT_EQ(prev_s1_it, tmp_it);
        EXPECT_EQ(*prev_s1_it, *tmp_it);
    }
    EXPECT_NE(prev_empty_it, s1.begin());
    EXPECT_NE(prev_empty_end, s1.end());
    for (int i = 0; i < 10; ++i)
        s1.insert('a' + i);
    tmp_it = s1.begin();
    for (int i = 0; i < 10; ++i, ++tmp_it)
    {
        EXPECT_EQ('a' + i, *tmp_it);
    }
}

TEST(Set, LookupCount)
{
    ft::set<int> s;
    for (int i = 0; i < 10; ++i)
        s.insert(i);
    EXPECT_EQ(1, s.count(1));
    EXPECT_EQ(0, s.count(42));
    s.insert(42);
    EXPECT_EQ(1, s.count(42));
}

TEST(Set, Lookupfind)
{
    ft::set<int> s;
    for (int i = 1; i < 20; i *= 2)
        s.insert(i);
    ft::set<int>::iterator it = s.find(2);
    EXPECT_EQ(2, *it);
    it = s.find(3);
    EXPECT_EQ(s.end(), it);

    const ft::set<int>           cs(s);
    ft::set<int>::const_iterator cit = cs.find(2);
    EXPECT_EQ(2, *cit);
    cit = cs.find(3);
    EXPECT_EQ(cs.end(), cit);
}

TEST(Set, LookupEqualRange)
{
    // Non Const
    // std::pair<iterator,iterator> equal_range( const Key& key );
    ft::set<int> s;
    for (int i = 0; i < 100; i += 10)
        s.insert(i);
    ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> ret;
    ret = s.equal_range(-10);
    EXPECT_EQ(0, *ret.first);
    EXPECT_EQ(0, *ret.second);
    ret = s.equal_range(0);
    EXPECT_EQ(0, *ret.first);
    EXPECT_EQ(10, *ret.second);
    ret = s.equal_range(42);
    EXPECT_EQ(50, *ret.first);
    EXPECT_EQ(50, *ret.second);
    ret = s.equal_range(50);
    EXPECT_EQ(50, *ret.first);
    EXPECT_EQ(60, *ret.second);
    ret = s.equal_range(90);
    EXPECT_EQ(90, *ret.first);
    EXPECT_EQ(s.end(), ret.second);
    ret = s.equal_range(100);
    EXPECT_EQ(s.end(), ret.first);
    EXPECT_EQ(s.end(), ret.second);

    // Const
    // ft::pair<const_iterator, const_iterator> equal_range(const Key& key)
    // const;
    const ft::set<int> cs(s);

    ft::pair<ft::set<int>::const_iterator, ft::set<int>::const_iterator> cret;
    cret = cs.equal_range(-10);
    EXPECT_EQ(0, *cret.first);
    EXPECT_EQ(0, *cret.second);
    cret = cs.equal_range(0);
    EXPECT_EQ(0, *cret.first);
    EXPECT_EQ(10, *cret.second);
    cret = cs.equal_range(42);
    EXPECT_EQ(50, *cret.first);
    EXPECT_EQ(50, *cret.second);
    cret = cs.equal_range(50);
    EXPECT_EQ(50, *cret.first);
    EXPECT_EQ(60, *cret.second);
    cret = cs.equal_range(90);
    EXPECT_EQ(90, *cret.first);
    EXPECT_EQ(cs.end(), cret.second);
    cret = cs.equal_range(100);
    EXPECT_EQ(cs.end(), cret.first);
    EXPECT_EQ(cs.end(), cret.second);
}

TEST(Set, LookupLowerBound)
{
    // Non const
    ft::set<int> s;
    for (int i = 0; i < 50; i += 10)
        s.insert(i);
    ft::set<int>::iterator it;
    it = s.lower_bound(0);
    EXPECT_EQ(0, *it);
    it = s.lower_bound(23);
    EXPECT_EQ(30, *it);
    it = s.lower_bound(53);
    EXPECT_TRUE(s.end() == it);

    // Const
    ft::set<int>                 cs = s;
    ft::set<int>::const_iterator cit;
    cit = cs.lower_bound(0);
    EXPECT_EQ(0, *cit);
    cit = s.lower_bound(23);
    EXPECT_EQ(30, *cit);
    cit = cs.lower_bound(53);
    EXPECT_TRUE(cs.end() == cit);
}

TEST(Set, LookupUpperBound)
{
    // Non const
    // iterator upper_bound( const Key& key );
    ft::set<int> s;
    for (int i = 0; i < 50; i += 10)
        s.insert(i);
    ft::set<int>::iterator it;
    it = s.upper_bound(-100);
    EXPECT_EQ(s.begin(), it);
    EXPECT_EQ(0, *it);
    it = s.upper_bound(10);
    EXPECT_EQ(20, *it);
    it = s.upper_bound(100);
    EXPECT_EQ(s.end(), it);

    // Const
    // const_iterator upper_bound( const Key& key ) const;
    const ft::set<int>           cs(s);
    ft::set<int>::const_iterator cit;
    cit = cs.upper_bound(-100);
    EXPECT_EQ(cs.begin(), cit);
    EXPECT_EQ(0, *cit);
    cit = cs.upper_bound(10);
    EXPECT_EQ(20, *cit);
    cit = cs.upper_bound(100);
    EXPECT_EQ(cs.end(), cit);
}

TEST(Set, ObserversKeyComp)
{
    {
        ft::set<int>              s;
        ft::set<int>::key_compare comp;
        comp = s.key_comp();
        EXPECT_TRUE(comp(1, 2));
        EXPECT_FALSE(comp(2, 2));
        EXPECT_FALSE(comp(3, 2));
    }

    {
        ft::set<int, std::greater<int> >              s;
        ft::set<int, std::greater<int> >::key_compare comp;
        comp = s.key_comp();
        EXPECT_FALSE(comp(1, 2));
        EXPECT_FALSE(comp(2, 2));
        EXPECT_TRUE(comp(3, 2));
    }

    {
        ft::set<std::string, std::less<std::string> >              s;
        ft::set<std::string, std::less<std::string> >::key_compare comp;
        comp = s.key_comp();
        EXPECT_TRUE(comp("abc", "xyz"));
        EXPECT_FALSE(comp("abc", "abc"));
        EXPECT_FALSE(comp("xyz", "abc"));
    }

    {
        ft::set<std::string, std::greater<std::string> >              s;
        ft::set<std::string, std::greater<std::string> >::key_compare comp;
        comp = s.key_comp();
        EXPECT_FALSE(comp("abc", "xyz"));
        EXPECT_FALSE(comp("abc", "abc"));
        EXPECT_TRUE(comp("xyz", "abc"));
    }
}

TEST(Set, ObserversValueComp)
{
    {
        ft::set<int>                s;
        ft::set<int>::value_compare comp;
        comp = s.key_comp();
        EXPECT_TRUE(comp(1, 2));
        EXPECT_FALSE(comp(2, 2));
        EXPECT_FALSE(comp(3, 2));
    }

    {
        ft::set<int, std::greater<int> >                s;
        ft::set<int, std::greater<int> >::value_compare comp;
        comp = s.key_comp();
        EXPECT_FALSE(comp(1, 2));
        EXPECT_FALSE(comp(2, 2));
        EXPECT_TRUE(comp(3, 2));
    }

    {
        ft::set<std::string, std::less<std::string> >                s;
        ft::set<std::string, std::less<std::string> >::value_compare comp;
        comp = s.key_comp();
        EXPECT_TRUE(comp("abc", "xyz"));
        EXPECT_FALSE(comp("abc", "abc"));
        EXPECT_FALSE(comp("xyz", "abc"));
    }

    {
        ft::set<std::string, std::greater<std::string> >                s;
        ft::set<std::string, std::greater<std::string> >::value_compare comp;
        comp = s.key_comp();
        EXPECT_FALSE(comp("abc", "xyz"));
        EXPECT_FALSE(comp("abc", "abc"));
        EXPECT_TRUE(comp("xyz", "abc"));
    }
}

TEST(Set, NonMemberFunctionsLexicographical)
{
    ft::set<int> s1;
    ft::set<int> s2;
    s1.insert(10);
    s2.insert(10);
    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 != s2);
    EXPECT_FALSE(s1 < s2);
    EXPECT_TRUE(s1 <= s2);
    EXPECT_FALSE(s1 > s2);
    EXPECT_TRUE(s1 >= s2);
    s2.insert(20);
    EXPECT_FALSE(s1 == s2);
    EXPECT_TRUE(s1 != s2);
    EXPECT_TRUE(s1 < s2);
    EXPECT_TRUE(s1 <= s2);
    EXPECT_FALSE(s1 > s2);
    EXPECT_FALSE(s1 >= s2);
    s1.insert(30);
    EXPECT_FALSE(s1 == s2);
    EXPECT_TRUE(s1 != s2);
    EXPECT_FALSE(s1 < s2);
    EXPECT_FALSE(s1 <= s2);
    EXPECT_TRUE(s1 > s2);
    EXPECT_TRUE(s1 >= s2);
}

TEST(Set, NonMemberFunctionsSwap)
{
    ft::set<char> s1;
    for (int i = 0; i < 10; ++i)
        s1.insert('a' + i);
    ft::set<char> s2;
    for (int i = -10; i < -4; ++i)
        s2.insert('z' - i);
    ft::set<char>::iterator prev_s1_it = s1.begin();
    ft::set<char>::iterator prev_s2_it = s2.begin();
    ft::set<char>::iterator tmp_it;
    ft::swap(s1, s2);
    tmp_it = s2.begin();
    for (ft::set<char>::iterator end = s2.end(); tmp_it != end;
         ++tmp_it, ++prev_s1_it)
    {
        EXPECT_EQ(prev_s1_it, tmp_it);
        EXPECT_EQ(*prev_s1_it, *tmp_it);
    }
    tmp_it = s1.begin();
    for (ft::set<char>::iterator end = s1.end(); tmp_it != end;
         ++tmp_it, ++prev_s2_it)
    {
        EXPECT_EQ(prev_s2_it, tmp_it);
        EXPECT_EQ(*prev_s2_it, *tmp_it);
    }

    prev_s1_it = s1.begin();
    ft::set<char>           empty1;
    ft::set<char>::iterator prev_empty_it  = empty1.begin();
    ft::set<char>::iterator prev_empty_end = empty1.end();
    ft::swap(empty1, s1);
    tmp_it = empty1.begin();
    for (ft::set<char>::iterator end = empty1.end(); tmp_it != end;
         ++tmp_it, ++prev_s1_it)
    {
        EXPECT_EQ(prev_s1_it, tmp_it);
        EXPECT_EQ(*prev_s1_it, *tmp_it);
    }
    EXPECT_NE(prev_empty_it, s1.begin());
    EXPECT_NE(prev_empty_end, s1.end());
    for (int i = 0; i < 10; ++i)
        s1.insert('a' + i);
    tmp_it = s1.begin();
    for (int i = 0; i < 10; ++i, ++tmp_it)
    {
        EXPECT_EQ('a' + i, *tmp_it);
    }
}