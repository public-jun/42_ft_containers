#include <vector.hpp>

#include <gtest/gtest.h>
#include <time.h>
#include <vector>

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

template <class T>
void judge_equal_vector_value(T v1, T v2)
{
    typename T::iterator it1 = v1.begin();
    typename T::iterator it2 = v2.begin();
    for (typename T::iterator end = v1.end(); it1 != end; ++it1, ++it2)
        EXPECT_EQ(*it1, *it2);
}

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
    {}

    // const_reference at( size_type pos ) const;
    {}
}

TEST(Vector, OperatorAccess)
{
    // reference operator[]( size_type pos );
    {}

    // const_reference operator[]( size_type pos ) const;
    {}
}

TEST(Vector, Front)
{
    //  reference front();
    {}

    // const_reference front() const;
    {}
}

TEST(Vector, Back)
{
    // reference back();
    {}

    // const_reference back() const;
    {}
}

TEST(Vector, Iterator) {}

TEST(Vector, ReverseIterator) {}

TEST(Vector, Empty)
{
    // bool empty() const;
}

TEST(Vector, Size)
{
    // size_type size() const;
}

TEST(Vector, MaxSize)
{
    // size_type max_size() const;
}

TEST(Vector, Reserve)
{
    // void reserve( size_type new_cap );
}

TEST(Vector, Capacity)
{
    // size_type capacity() const;
}

TEST(Vector, Clear)
{
    // void clear();
}

TEST(Vector, Insert)
{
    // iterator insert( iterator pos, const T& value );
    {}

    // void insert( iterator pos, size_type count, const T& value );
    {}

    // template< class InputIt >
    // void insert( iterator pos, InputIt first, InputIt last);
    {}
}

TEST(Vector, Erase)
{
    // iterator erase( iterator pos );
    {}

    // iterator erase( iterator first, iterator last );
    {}
}

TEST(Vector, PushBack)
{
    // void push_back( const T& value );
    {}
}

TEST(Vector, PopBack)
{
    // void pop_back();
    {}
}

TEST(Vector, Resize)
{
    // void resize( size_type count, T value = T() );
    {}
}

TEST(Vector, Swap)
{
    // void swap( vector& other );
    {}
}

TEST(Vector, NonMemberFunctionsLexicographical) {}

TEST(Vector, NonMemberFunctionsSwap)
{
    //  void swap( vector& other );
    {}
}