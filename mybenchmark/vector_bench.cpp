#include "bench.hpp"

#include <iomanip>
#include <iostream>
#include <vector.hpp>
#include <vector>

template <class Fn>
ft::StopWatch sw(Fn func, int cnt_max, unsigned long long loop)
{
    ft::StopWatch sw;
    sw.start();
    for (int cnt = 0; cnt < cnt_max; ++cnt)
    {
        for (unsigned long long i = 0; i < loop; ++i)
            func();
    }
    sw.end();
    return sw;
}

#define BM_VECTOR(name, ft_func, stl_func, loop, cnt_max)                       \
    {                                                                           \
        ft::StopWatch ft_sw  = sw(ft_func, cnt_max, loop);                      \
        ft::StopWatch stl_sw = sw(stl_func, cnt_max, loop);                     \
        ft::Measure   m      = ft::Measure(ft_sw, stl_sw, name, loop, cnt_max); \
        m.print_result();                                                       \
    }

template <class Vec>
void bm_vec_def_constructor()
{
    Vec v;
}

template <class Vec>
void bm_vec_alloc_constructor()
{
    Vec v((std::allocator<int>()));
}

template <class Vec>
void bm_vec_count_constructor()
{
    Vec v(1000, 42);
}

template <class Vec>
void bm_vec_range_constructor()
{
    std::vector<int> v1(1000, 42);
    Vec              v(v1.begin(), v1.end());
}

template <class Vec>
void bm_vec_copy_constructor()
{
    Vec v1(1000, 42);
    Vec v(v1);
}

template <class Vec>
void bm_vec_assign_operator()
{
    Vec v1(1000, 42);
    Vec v;
    v = v1;
}

template <class Vec>
void bm_vec_assign()
{
    Vec v;
    v.assign(1000, 42);
}

template <class Vec>
void bm_vec_assign_range()
{
    std::vector<int> v1(1000, 42);
    Vec              v;
    v.assign(v1.begin(), v1.end());
}

template <class Vec>
void bm_vec_get_allocator()
{
    Vec v;
    v.get_allocator();
}

template <class Vec>
void bm_vec_max_size()
{
    Vec v;
    v.max_size();
}

template <class Vec>
void bm_vec_size()
{
    Vec v;
    v.size();
}

template <class Vec>
void bm_vec_empty()
{
    Vec v;
    v.empty();
}

template <class Vec>
void bm_vec_capacity()
{
    Vec v;
    v.capacity();
}

template <class Vec>
void bm_vec_access_operator()
{
    Vec v(1, 1);
    v[0];
}

template <class Vec>
void bm_vec_const_access_operator()
{
    const Vec v(1, 1);
    v[0];
}

template <class Vec>
void bm_vec_at()
{
    Vec v(100, 42);
    for (int i = 0; i < 100; ++i)
        v.at(i);
}

template <class Vec>
void bm_vec_const_at()
{
    const Vec v(100, 42);
    for (int i = 0; i < 100; ++i)
        v.at(i);
}

template <class Vec>
void bm_vec_front()
{
    Vec v;
    v.front();
}

template <class Vec>
void bm_vec_back()
{
    Vec v(100, 42);
    v.back();
}

template <class Vec>
void bm_vec_begin()
{
    Vec v(100, 42);
    v.begin();
}

template <class Vec>
void bm_vec_end()
{
    Vec v(100, 42);
    v.end();
}

template <class Vec>
void bm_vec_rbegin()
{
    Vec v(100, 42);
    v.rbegin();
}

template <class Vec>
void bm_vec_rend()
{
    Vec v(100, 42);
    v.rend();
}

template <class Vec>
void bm_vec_clear()
{
    Vec v(1000, 42);
    v.clear();
}

template <class Vec>
void bm_vec_insert1()
{
    Vec v(100, 42);
    for (int i = 0; i < 100; ++i)
        v.insert(v.begin(), 10);
}

template <class Vec>
void bm_vec_insert2()
{
    Vec v(100, 42);
    for (int i = 0; i < 100; ++i)
        v.insert(v.end(), 10);
}

template <class Vec>
void bm_vec_insert_count1()
{
    Vec v(100, 42);
    v.insert(v.begin(), 100, 24);
}

template <class Vec>
void bm_vec_insert_count2()
{
    Vec v(100, 42);
    v.insert(v.end(), 100, 24);
}

void vector_bench()
{
    BM_VECTOR("vector_def_constructor",
              bm_vec_def_constructor<ft::vector<int> >,
              bm_vec_def_constructor<std::vector<int> >, LOOP, 1);
    BM_VECTOR("vector_alloc_constructor",
              bm_vec_alloc_constructor<ft::vector<int> >,
              bm_vec_alloc_constructor<std::vector<int> >, LOOP, 1);
    BM_VECTOR("vector_count_constructor",
              bm_vec_count_constructor<ft::vector<int> >,
              bm_vec_count_constructor<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_range_constructor",
              bm_vec_range_constructor<ft::vector<int> >,
              bm_vec_range_constructor<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_assign_operator",
              bm_vec_assign_operator<ft::vector<int> >,
              bm_vec_assign_operator<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_assign", bm_vec_assign<ft::vector<int> >,
              bm_vec_assign<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_assign_range", bm_vec_assign_range<ft::vector<int> >,
              bm_vec_assign_range<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_get_allocator", bm_vec_get_allocator<ft::vector<int> >,
              bm_vec_get_allocator<std::vector<int> >, LOOP, 10);
    BM_VECTOR("vector_max_size", bm_vec_max_size<ft::vector<int> >,
              bm_vec_max_size<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_size", bm_vec_size<ft::vector<int> >,
              bm_vec_size<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_empty", bm_vec_empty<ft::vector<int> >,
              bm_vec_empty<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_capacity", bm_vec_capacity<ft::vector<int> >,
              bm_vec_capacity<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_access_operator",
              bm_vec_access_operator<ft::vector<int> >,
              bm_vec_access_operator<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_const_access_operator",
              bm_vec_const_access_operator<ft::vector<int> >,
              bm_vec_const_access_operator<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_at", bm_vec_at<ft::vector<int> >,
              bm_vec_at<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_const_at", bm_vec_const_at<ft::vector<int> >,
              bm_vec_const_at<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_const_at", bm_vec_const_at<ft::vector<int> >,
              bm_vec_const_at<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_front", bm_vec_front<ft::vector<int> >,
              bm_vec_front<std::vector<int> >, LOOP2, 100);
    BM_VECTOR("vector_front", bm_vec_front<ft::vector<int> >,
              bm_vec_front<std::vector<int> >, LOOP2, 100);
    BM_VECTOR("vector_back", bm_vec_back<ft::vector<int> >,
              bm_vec_back<std::vector<int> >, LOOP2, 100);
    BM_VECTOR("vector_end", bm_vec_end<ft::vector<int> >,
              bm_vec_end<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_rbegin", bm_vec_rbegin<ft::vector<int> >,
              bm_vec_rbegin<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_rend", bm_vec_rend<ft::vector<int> >,
              bm_vec_rend<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_clear", bm_vec_clear<ft::vector<int> >,
              bm_vec_clear<std::vector<int> >, LOOP2, 1);
    BM_VECTOR("vector_insert1", bm_vec_insert1<ft::vector<int> >,
              bm_vec_insert1<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_insert2", bm_vec_insert2<ft::vector<int> >,
              bm_vec_insert2<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_insert_count1", bm_vec_insert_count1<ft::vector<int> >,
              bm_vec_insert_count1<std::vector<int> >, LOOP2, 10);
    BM_VECTOR("vector_insert_count2", bm_vec_insert_count2<ft::vector<int> >,
              bm_vec_insert_count2<std::vector<int> >, LOOP2, 10);
}