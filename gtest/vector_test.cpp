#include <gtest/gtest.h>
#include <vector.hpp>

TEST(Vector, Constructor)
{
    // vector();
    {
        ft::vector<int> v;
        EXPECT_EQ(0, v.size());
        EXPECT_TRUE(v.empty());
        EXPECT_EQ(0, v.capacity());
    }
    // explicit vector( const Allocator& alloc );
    {
        ft::vector<int> v((std::allocator<int>()));
    }

    // explicit vector( size_type count,
    //           const T& value = T(),
    //           const Allocator& alloc = Allocator());
    {}

    // template< class InputIt >
    // vector(InputIt first, InputIt last, const Allocator& alloc =
    // Allocator());
    {}

    // vector( const vector& other );
    {}

    // vector& operator=( const vector& other );
}

TEST(Vector, Assgin)
{
    // void assign( size_type count, const T& value );
    {}

    // template< class InputIt >
    // void assign(InputIt first, InputIt last);
    {}
}

TEST(Vector, GetAllocator)
{
    // allocator_type get_allocator() const;
    {}
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