#if STL // -DTEST=1
#else   // -DTEST=0
#include <vector.hpp>
#endif

#if __cplusplus >= 201103L
#include <gtest/gtest.h>
#else
#include "../ft_test.hpp"
#endif

#include <sstream>
#include <time.h>
#include <vector>

namespace {

template <class T>
void judge_equal_vector_value(T v1, T v2)
{
    typename T::iterator it1 = v1.begin();
    typename T::iterator it2 = v2.begin();
    for (typename T::iterator end = v1.end(); it1 != end; ++it1, ++it2)
        EXPECT_EQ(*it1, *it2);
}

ft::vector<int> gen_random_vector(std::size_t size)
{
    ft::vector<int> v(size);
    for (std::size_t i = 0; i < size; ++i)
    {
        int value = std::rand() % SIZE;
        v[i]      = value;
    }
    return v;
}

} // namespace

TEST(Vector, Constructor)
{
    std::srand(time(NULL));
    // vector();
    {
        ft::vector<int> v;
        EXPECT_EQ(0, v.size());
        EXPECT_TRUE(v.empty());
        EXPECT_EQ(0, v.capacity());
    }
    // explicit vector( const Allocator& alloc );
    {
        ft::vector<int> v1((std::allocator<int>()));
        EXPECT_EQ(0, v1.size());
        EXPECT_EQ(true, v1.empty());
        EXPECT_EQ((std::allocator<int>()), v1.get_allocator());

        ft::vector<char> v2((std::allocator<char>()));
        EXPECT_EQ(0, v2.size());
        EXPECT_EQ(true, v2.empty());
        EXPECT_EQ((std::allocator<char>()), v2.get_allocator());
    }

    // explicit vector( size_type count,
    //           const T& value = T(),
    //           const Allocator& alloc = Allocator());
    {
        ft::vector<int> v1(10, 42, (std::allocator<int>()));
        for (int i = 0; i < 10; ++i)
            EXPECT_EQ(42, v1[i]);
        ft::vector<std::string> v2(10, "42Tokyo",
                                   (std::allocator<std::string>()));
        for (int i = 0; i < 10; ++i)
            EXPECT_EQ("42Tokyo", v2[i]);
    }

    // template< class InputIt >
    // vector(InputIt first, InputIt last, const Allocator& alloc =
    // Allocator());
    {
        ft::vector<int> v1 = gen_random_vector(10);
        ft::vector<int> v2(v1.begin(), v1.end());
        judge_equal_vector_value(v1, v2);
        EXPECT_EQ(v1.size(), v2.size());
        EXPECT_EQ(v1.capacity(), v2.capacity());
        EXPECT_EQ(v1.get_allocator(), v2.get_allocator());
    }

    // vector( const vector& other );
    {
        ft::vector<int> v1 = gen_random_vector(10);
        ft::vector<int> v2(v1);
        EXPECT_EQ(v1.size(), v2.size());
        EXPECT_EQ(v1.capacity(), v2.capacity());
        EXPECT_EQ(v1.get_allocator(), v2.get_allocator());
    }

    // vector& operator=( const vector& other );
    {
        ft::vector<int> v1 = gen_random_vector(10);
        ft::vector<int> v2;
        v2 = v1;
        EXPECT_EQ(v1.size(), v2.size());
        EXPECT_EQ(v1.capacity(), v2.capacity());
        EXPECT_EQ(v1.get_allocator(), v2.get_allocator());
    }
}

TEST(Vector, Assgin)
{
    // void assign( size_type count, const T& value );
    {
        // capacity >= size >= assign size
        ft::vector<int> v = gen_random_vector(10);
        ft::vector<int> cp_v(v);
        judge_equal_vector_value(v, cp_v);
        EXPECT_EQ(10, v.size());
        v.assign(5, 42);
        ft::vector<int>::iterator it  = v.begin();
        ft::vector<int>::iterator end = v.end();
        for (; it != end; ++it)
            EXPECT_EQ(*it, 42);
        EXPECT_EQ(5, v.size());
        EXPECT_EQ(10, v.capacity());
    }
    {
        // capacity >= assign size > size
        ft::vector<int> v;
        v.reserve(100);
        for (int i = 0; i < 10; ++i)
            v.insert(v.begin(), i);
        EXPECT_EQ(100, v.capacity());
        EXPECT_EQ(10, v.size());
        v.assign(20, 42);
        ft::vector<int>::iterator it  = v.begin();
        ft::vector<int>::iterator end = v.end();
        for (; it != end; ++it)
            EXPECT_EQ(*it, 42);
        EXPECT_EQ(100, v.capacity());
        EXPECT_EQ(20, v.size());
    }
    {
        // capacity < assign size
        ft::vector<int> v = gen_random_vector(10);
        EXPECT_EQ(10, v.capacity());
        EXPECT_EQ(10, v.size());
        v.assign(20, 42);
        ft::vector<int>::iterator it  = v.begin();
        ft::vector<int>::iterator end = v.end();
        for (; it != end; ++it)
            EXPECT_EQ(*it, 42);
        EXPECT_EQ(20, v.capacity());
        EXPECT_EQ(20, v.size());
    }

    // template< class InputIt >
    // void assign(InputIt first, InputIt last);
    {
        // capacity >= size >= assign size
        ft::vector<int> v(10);
        v.reserve(100);
        EXPECT_EQ(100, v.capacity());
        EXPECT_EQ(10, v.size());
        ft::vector<int> a(5);
        for (int i = 0; i < 5; ++i)
            a[i] = i;
        v.assign(a.begin(), a.end());
        EXPECT_EQ(100, v.capacity());
        EXPECT_EQ(5, v.size());
        judge_equal_vector_value(v, a);
    }
    {
        // capacity >= assign size > size
        ft::vector<int> v(10);
        v.reserve(100);
        EXPECT_EQ(100, v.capacity());
        EXPECT_EQ(10, v.size());
        ft::vector<int> a(20);
        for (int i = 0; i < 20; ++i)
            a[i] = i;
        v.assign(a.begin(), a.end());
        EXPECT_EQ(100, v.capacity());
        EXPECT_EQ(20, v.size());
        judge_equal_vector_value(v, a);
    }
    {
        // assign size > capacity
        ft::vector<int> v = gen_random_vector(10);
        EXPECT_EQ(10, v.capacity());
        EXPECT_EQ(10, v.size());
        ft::vector<int> a(20);
        for (int i = 0; i < 20; ++i)
            a[i] = i;
        v.assign(a.begin(), a.end());
        EXPECT_EQ(20, v.capacity());
        EXPECT_EQ(20, v.size());
        judge_equal_vector_value(v, a);
    }
}

TEST(Vector, GetAllocator)
{
    // allocator_type get_allocator() const;
    {
        ft::vector<int> v;
        int*            p;
        p = v.get_allocator().allocate(5);
        int i;
        for (i = 0; i < 5; ++i)
            v.get_allocator().construct(&p[i], i);
        for (i = 0; i < 5; ++i)
            EXPECT_EQ(i, p[i]);
        for (i = 0; i < 5; ++i)
            v.get_allocator().destroy(&p[i]);
        v.get_allocator().deallocate(p, 5);
    }
    {
        ft::vector<char> v;
        char*            p;
        p = v.get_allocator().allocate(5);
        int i;
        for (i = 0; i < 5; ++i)
            v.get_allocator().construct(&p[i], 'a' + i);
        for (i = 0; i < 5; ++i)
            EXPECT_EQ('a' + i, p[i]);
        for (i = 0; i < 5; ++i)
            v.get_allocator().destroy(&p[i]);
    }
}

TEST(Vector, At)
{
    // reference at( size_type pos );
    {
        ft::vector<int> v(10);
        for (int i = 0; i < 10; ++i)
            v.at(i) = i;
        for (int i = 0; i < 10; ++i)
            EXPECT_EQ(i, v.at(i));
        v.at(5) = 42;
        EXPECT_EQ(v.at(5), 42);
        EXPECT_THROW(v.at(11), std::out_of_range);
    }

    // const_reference at( size_type pos ) const;
    {
        ft::vector<int> v(10);
        for (int i = 0; i < 10; ++i)
            v.at(i) = i;
        const ft::vector<int> cv(v);
        for (int i = 0; i < 10; ++i)
            EXPECT_EQ(i, cv.at(i));
        EXPECT_THROW(cv.at(11), std::out_of_range);
    }
}

TEST(Vector, OperatorAccess)
{
    // reference operator[]( size_type pos );
    {
        ft::vector<int> v(10);
        for (int i = 0; i < 10; ++i)
            v[i] = i;
        for (int i = 0; i < 10; ++i)
            EXPECT_EQ(i, v[i]);
    }

    // const_reference operator[]( size_type pos ) const;
    {
        ft::vector<int> v(10);
        for (int i = 0; i < 10; ++i)
            v[i] = i;
        const ft::vector<int> cv(v);
        for (int i = 0; i < 10; ++i)
            EXPECT_EQ(i, cv[i]);
    }
}

TEST(Vector, Front)
{
    //  reference front();
    {
        ft::vector<int> v(10);
        for (int i = 0; i < 10; ++i)
            v.at(i) = i;
        ft::vector<int>::reference ref = v.front();
        EXPECT_EQ(0, ref);
        ref = 42;
        EXPECT_EQ(42, v.at(0));
    }

    // const_reference front() const;
    {
        ft::vector<int> v(10);
        for (int i = 0; i < 10; ++i)
            v.at(i) = i;
        const ft::vector<int>            cv(v);
        ft::vector<int>::const_reference cref = cv.front();
        EXPECT_EQ(0, cref);
    }

    {
        ft::vector<int> v(10);
        for (int i = 0; i < 10; ++i)
            v.at(i) = i;
        ft::vector<int>::const_reference c_ref = v.front();
        ft::vector<int>::reference       ref   = v.front();
        EXPECT_EQ(ref, c_ref);
        ref = 42;
        EXPECT_EQ(ref, c_ref);
    }
}

TEST(Vector, Back)
{
    // reference back();
    {
        ft::vector<int> v(10);
        for (int i = 0; i < 10; ++i)
            v.at(i) = i;
        ft::vector<int>::reference ref = v.back();
        EXPECT_EQ(9, ref);
        ref = 42;
        EXPECT_EQ(42, v.at(9));
    }

    // const_reference back() const;
    {
        ft::vector<int> v(10);
        for (int i = 0; i < 10; ++i)
            v.at(i) = i;
        const ft::vector<int>            cv(v);
        ft::vector<int>::const_reference cref = cv.back();
        EXPECT_EQ(9, cref);
    }

    {
        ft::vector<int> v(10);
        for (int i = 0; i < 10; ++i)
            v.at(i) = i;
        ft::vector<int>::const_reference c_ref = v.back();
        ft::vector<int>::reference       ref   = v.back();
        EXPECT_EQ(ref, c_ref);
        ref = 42;
        EXPECT_EQ(ref, c_ref);
    }
}

TEST(Vector, Iterator) {}

TEST(Vector, ReverseIterator) {}

TEST(Vector, Empty)
{
    // bool empty() const;
    {
        ft::vector<int> v;
        EXPECT_TRUE(v.empty());
        v.push_back(1);
        EXPECT_FALSE(v.empty());
    }
}

TEST(Vector, Size)
{
    // size_type size() const;
    {
        ft::vector<int> v;
        EXPECT_EQ(0, v.size());
        for (int i = 0; i < 10; ++i)
            v.push_back(i);
        EXPECT_EQ(10, v.size());
        for (int i = 10; i < 30; ++i)
            v.push_back(i);
        EXPECT_EQ(30, v.size());
    }
}

TEST(Vector, MaxSize)
{
    // size_type max_size() const;
    {
        std::vector<int> stl_v;
        ft::vector<int>  ft_v;
        EXPECT_EQ(stl_v.max_size(), ft_v.max_size());
    }
    {
        std::vector<char> stl_v;
        ft::vector<char>  ft_v;
        EXPECT_EQ(stl_v.max_size(), ft_v.max_size());
    }
    {
        std::vector<std::string> stl_v;
        ft::vector<std::string>  ft_v;
        EXPECT_EQ(stl_v.max_size(), ft_v.max_size());
    }
    {
        std::vector<double> stl_v;
        ft::vector<double>  ft_v;
        EXPECT_EQ(stl_v.max_size(), ft_v.max_size());
    }
}

TEST(Vector, Reserve)
{
    // void reserve( size_type new_cap );
    {
        std::vector<int> v;
        EXPECT_EQ(0, v.capacity());
        v.reserve(40);
        EXPECT_EQ(0, v.size());
        EXPECT_EQ(40, v.capacity());
        for (int i = 0; i < 20; ++i)
            v.push_back(i);
        for (int i = 0; i < 20; ++i)
            EXPECT_EQ(i, v[i]);
        EXPECT_EQ(20, v.size());
        v.reserve(10);
        EXPECT_EQ(20, v.size());
        EXPECT_EQ(40, v.capacity());
        for (int i = 0; i < 20; ++i)
            EXPECT_EQ(i, v[i]);
    }
}

TEST(Vector, Capacity)
{
    // size_type capacity() const;
    {
        ft::vector<int> v;
        EXPECT_EQ(0, v.capacity());
        EXPECT_EQ(0, v.size());
        v.reserve(10);
        EXPECT_EQ(0, v.size());
        EXPECT_EQ(10, v.capacity());
        v.push_back(1);
        EXPECT_EQ(1, v.size());
        EXPECT_EQ(10, v.capacity());
    }
}

TEST(Vector, Clear)
{
    // void clear();
    ft::vector<int> v;
    v.push_back(1);
    EXPECT_EQ(1, v.size());
    EXPECT_EQ(1, v.capacity());
    v.clear();
    EXPECT_EQ(0, v.size());
    EXPECT_EQ(1, v.capacity());
    v.reserve(100);
    for (int i = 0; i < 10; ++i)
        v.push_back(i);
    EXPECT_EQ(10, v.size());
    EXPECT_EQ(100, v.capacity());
    v.clear();
    EXPECT_EQ(0, v.size());
    EXPECT_EQ(100, v.capacity());
}

TEST(Vector, Insert)
{
    // iterator insert( iterator pos, const T& value );
    {
        // insert first iterator
        ft::vector<int> v(3, 10);
        for (int i = 0; i < 3; ++i)
            EXPECT_EQ(10, v[i]);
        EXPECT_EQ(3, v.size());
        ft::vector<int>::iterator it;
        it = v.insert(v.begin(), 20);
        EXPECT_EQ(4, v.size());
        EXPECT_EQ(20, v[0]);
        for (int i = 1; i < 4; ++i)
            EXPECT_EQ(10, v[i]);
    }
    {
        // insert last iterator
        ft::vector<int> v(3, 10);
        for (int i = 0; i < 3; ++i)
            EXPECT_EQ(10, v[i]);
        EXPECT_EQ(3, v.size());
        ft::vector<int>::iterator it;
        it = v.insert(v.end(), 20);
        EXPECT_EQ(4, v.size());
        for (int i = 0; i < 3; ++i)
            EXPECT_EQ(10, v[i]);
        EXPECT_EQ(20, v[3]);
    }
    {
        // insert mid iterator
        ft::vector<int>           v(10, 10);
        ft::vector<int>::iterator it;
        it = v.insert(v.begin() + 5, 20);
        for (int i = 0; i < 5; ++i)
            EXPECT_EQ(10, v[i]);
        EXPECT_EQ(20, v[5]);
        for (int i = 6; i < 11; ++i)
            EXPECT_EQ(10, v[i]);
    }

    // void insert( iterator pos, size_type count, const T& value );
    {
        std::vector<int> stl_v(100);
        for (int i = 0; i < 100; ++i)
            stl_v[i] = i;
        ft::vector<int> ft_v(100);
        for (int i = 0; i < 100; ++i)
            ft_v[i] = i;
        std::vector<int>::iterator stl_it;
        ft::vector<int>::iterator  ft_it;
        stl_it = stl_v.begin();
        ft_it  = ft_v.begin();

        stl_v.insert(stl_it, 10, 10);
        ft_v.insert(ft_it, 10, 10);
        stl_it = stl_v.begin();
        ft_it  = ft_v.begin();
        for (int i = 0; i < 110; ++i)
            EXPECT_EQ(*(stl_it++), *(ft_it++));

        stl_it = stl_v.end();
        ft_it  = ft_v.end();
        stl_v.insert(stl_it, 10, 20);
        ft_v.insert(ft_it, 10, 20);
        stl_it = stl_v.begin();
        ft_it  = ft_v.begin();
        for (int i = 0; i < 120; ++i)
            EXPECT_EQ(*(stl_it++), *(ft_it++));

        stl_it = stl_v.begin();
        ft_it  = ft_v.begin();
        stl_v.insert(stl_it + 50, 10, 30);
        ft_v.insert(ft_it + 50, 10, 30);
        stl_it = stl_v.begin();
        ft_it  = ft_v.begin();
        for (int i = 0; i < 130; ++i)
            EXPECT_EQ(*(stl_it++), *(ft_it++));
    }

    // template< class InputIt >
    // void insert( iterator pos, InputIt first, InputIt last);
    {
        ft::vector<int>  v1(10, 10);
        ft::vector<int>  v2(20, 20);
        std::vector<int> stl_v;
        stl_v.insert(stl_v.begin(), v1.begin(), v1.end());
        stl_v.insert(stl_v.begin(), v2.begin(), v2.end());

        ft::vector<int>::iterator it;
        it = v1.begin();
        std::vector<int>::iterator stl_it;
        stl_it = stl_v.begin();

        v1.insert(it, v2.begin(), v2.end());
        it = v1.begin();
        for (std::vector<int>::iterator end = stl_v.end(); stl_it != end;
             ++stl_it, ++it)
        {
            EXPECT_EQ(*stl_it, *it);
        }
        EXPECT_EQ(stl_v.size(), v1.size());
    }
    {
        // input iterator ver
        std::stringstream ss1;
        ss1 << 1 << endl << 2 << endl << 3;
        std::istream_iterator<int> is_it1(ss1);
        std::istream_iterator<int> is_last1;
        std::stringstream          ss2;
        ss2 << 1 << endl << 2 << endl << 3;
        std::istream_iterator<int> is_it2(ss2);
        std::istream_iterator<int> is_last2;

        ft::vector<int>            v(3, 10);
        std::vector<int>           stl_v(3, 10);
        ft::vector<int>::iterator  it;
        std::vector<int>::iterator stl_it;
        it     = v.begin();
        stl_it = stl_v.begin();
        v.insert(it, is_it1, is_last1);
        stl_v.insert(stl_it, is_it2, is_last2);
        EXPECT_EQ(stl_v.size(), v.size());

        it     = v.begin();
        stl_it = stl_v.begin();
        for (std::vector<int>::iterator end = stl_v.end(); stl_it != end;
             ++stl_it, ++it)
        {
            EXPECT_EQ(*stl_it, *it);
        }
    }
    {
        ft::vector<std::string> v(1, "aaa");
        std::string             arr[4];
        arr[0] = "xxx";
        arr[1] = "yyy";
        arr[2] = "zzz";
        arr[3] = "end";
        v.insert(v.begin(), arr, arr + 3);
        for (int i = 0; i < 3; ++i)
            EXPECT_EQ(v[i], arr[i]);
        EXPECT_EQ(v[3], "aaa");
    }
    {
        std::size_t       size = 10;
        ft::vector<int>   v(10);
        std::stringstream ss;
        for (std::size_t i = 0; i < size; ++i)
            ss << i << " ";
        std::istream_iterator<int> iit(ss);
        std::istream_iterator<int> eos;
        v.insert(v.end(), iit, eos);
        for (int i = 0; i < 10; ++i)
            EXPECT_EQ(0, v[i]);
        for (int i = 0; i < 10; ++i)
            EXPECT_EQ(i, v[i + 10]);
    }
}

TEST(Vector, Erase)
{
    // iterator erase( iterator pos );
    {
        ft::vector<int> fv(10);
        for (int i = 0; i < 10; ++i)
            fv[i] = i;
        std::vector<int>           sv(fv.begin(), fv.end());
        ft::vector<int>::iterator  fit;
        std::vector<int>::iterator sit;

        for (int i = 0; i < 10; ++i)
        {
            int offset = std::rand() % (10 - i);

            fit = fv.begin() + offset;
            sit = sv.begin() + offset;
            fit = fv.erase(fit);
            sit = sv.erase(sit);
            fit = fv.begin();
            sit = sv.begin();
            for (std::vector<int>::iterator end = sv.end(); sit != end;
                 ++sit, ++fit)
                EXPECT_EQ(*fit, *sit);
            EXPECT_EQ(fv.size(), sv.size());
        }
    }

    // iterator erase( iterator first, iterator last );
    {
        for (int cnt = 0; cnt < 10; ++cnt)
        {
            ft::vector<int> v(50);
            for (int i = 0; i < 50; ++i)
                v[i] = i;
            ft::vector<int>::iterator it, first, last;
            while (true)
            {
                first = v.begin() + std::rand() % 50;
                last  = v.begin() + std::rand() % 50;
                if (first <= last)
                    break;
            }
            std::vector<int>           f_half(v.begin(), first);
            std::vector<int>           l_half(last, v.end());
            std::vector<int>::iterator sit;
            v.erase(first, last);
            EXPECT_EQ(v.size(), f_half.size() + l_half.size());

            sit = f_half.begin();
            it  = v.begin();
            for (std::vector<int>::iterator end = f_half.end(); sit != end;
                 ++sit, ++it)
                EXPECT_EQ(*sit, *it);
            sit = l_half.begin();
            for (std::vector<int>::iterator end = l_half.end(); sit != end;
                 ++sit, ++it)
                EXPECT_EQ(*sit, *it);
        }
    }
}

TEST(Vector, PushBack)
{
    // void push_back( const T& value );
    {
        for (int cnt = 0; cnt < 10; ++cnt)
        {
            ft::vector<int>  v;
            std::vector<int> sv;
            for (int i = 0; i < 1000; ++i)
            {
                int value = std::rand() % 1000;
                v.push_back(value);
                sv.push_back(value);
            }
            for (int i = 0; i < 1000; ++i)
                EXPECT_EQ(v[i], sv[i]);
            EXPECT_EQ(v.size(), sv.size());
            EXPECT_EQ(v.capacity(), sv.capacity());
        }
    }
}

TEST(Vector, PopBack)
{
    // void pop_back();
    {
        ft::vector<int>  v;
        std::vector<int> sv;
        for (int i = 0; i < 1000; ++i)
        {
            int value = std::rand() % 1000;
            v.push_back(value);
            sv.push_back(value);
        }
        for (int i = 0; i < 1000; ++i)
            EXPECT_EQ(v[i], sv[i]);
        for (int i = 0; i < 1000; ++i)
        {
            v.pop_back();
            sv.pop_back();
        }
        EXPECT_EQ(v.size(), sv.size());
    }
}

TEST(Vector, Resize)
{
    // void resize( size_type count, T value = T() );
    {
        ft::vector<int> v;
        for (int i = 0; i < 100; ++i)
            v.push_back(i);
        std::vector<int> sv(v.begin(), v.end());
        v.resize(200, 42);
        sv.resize(200, 42);
        for (int i = 0; i < 200; ++i)
            EXPECT_EQ(v[i], sv[i]);
        EXPECT_EQ(v.size(), sv.size());
        v.resize(10, 42);
        sv.resize(10, 42);
        for (int i = 0; i < 10; ++i)
            EXPECT_EQ(v[i], sv[i]);
        EXPECT_EQ(v.size(), sv.size());
    }
}

TEST(Vector, Swap)
{
    // void swap( vector& other );
    {
        for (int cnt = 0; cnt < 10; ++cnt)
        {
            ft::vector<int> v1 = gen_random_vector(100 * cnt);
            ft::vector<int> cp_v1(v1);
            ft::vector<int> v2 = gen_random_vector(10 * cnt);
            ft::vector<int> cp_v2(v2);
            v1.swap(v2);
            EXPECT_EQ(v1, cp_v2);
            EXPECT_EQ(v2, cp_v1);
        }
    }
}

TEST(Vector, NonMemberFunctionsLexicographical)
{
    {
        ft::vector<int> v1;
        for (int i = 0; i < 10; ++i)
            v1.push_back(i);
        ft::vector<int> v2(v1);
        EXPECT_TRUE(v1 == v2);
        EXPECT_FALSE(v1 != v2);
        EXPECT_FALSE(v1 < v2);
        EXPECT_TRUE(v1 <= v2);
        EXPECT_FALSE(v1 > v2);
        EXPECT_TRUE(v1 >= v2);
    }
    {
        ft::vector<int> v1(3, 10);
        ft::vector<int> v2(3, 5);
        EXPECT_FALSE(v1 == v2);
        EXPECT_TRUE(v1 != v2);
        EXPECT_FALSE(v1 < v2);
        EXPECT_FALSE(v1 <= v2);
        EXPECT_TRUE(v1 > v2);
        EXPECT_TRUE(v1 >= v2);
    }
    {
        ft::vector<int> v1(5, 5);
        ft::vector<int> v2(3, 5);
        EXPECT_FALSE(v1 == v2);
        EXPECT_TRUE(v1 != v2);
        EXPECT_FALSE(v1 < v2);
        EXPECT_FALSE(v1 <= v2);
        EXPECT_TRUE(v1 > v2);
        EXPECT_TRUE(v1 >= v2);
    }
    {
        ft::vector<int> v1(5, 5);
        ft::vector<int> v2(3, 10);
        EXPECT_FALSE(v1 == v2);
        EXPECT_TRUE(v1 != v2);
        EXPECT_TRUE(v1 < v2);
        EXPECT_TRUE(v1 <= v2);
        EXPECT_FALSE(v1 > v2);
        EXPECT_FALSE(v1 >= v2);
    }
}

TEST(Vector, NonMemberFunctionsSwap)
{
    //  void swap( vector& other );
    {
        for (int cnt = 0; cnt < 10; ++cnt)
        {
            ft::vector<int> v1 = gen_random_vector(100 * cnt);
            ft::vector<int> cp_v1(v1);
            ft::vector<int> v2 = gen_random_vector(10 * cnt);
            ft::vector<int> cp_v2(v2);
            ft::swap(v1, v2);
            EXPECT_EQ(v1, cp_v2);
            EXPECT_EQ(v2, cp_v1);
        }
    }
    {
        ft::vector<int> v1;
        ft::vector<int> cp_v1(v1);
        ft::vector<int> v2;
        ft::vector<int> cp_v2(v2);
        ft::swap(v1, v2);
        EXPECT_EQ(v1, cp_v2);
        EXPECT_EQ(v2, cp_v1);
    }
}