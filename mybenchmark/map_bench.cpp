#include "./bench_lib/bench.hpp"

#include <map.hpp>
#include <map>
#include <vector>

std::map<int, int> g_sm;
ft::map<int, int>  g_fm;

template <class Map>
void bm_map_def_constructor()
{
    Map m;
}

template <class Map>
void bm_map_constructor()
{
    Map m;
}

template <class Map>
void bm_map_range_constructor()
{
    Map m(g_sm.begin(), g_sm.end());
}

template <>
void bm_map_range_constructor<ft::map<int, int> >()
{
    ft::map<int, int> m(g_fm.begin(), g_fm.end());
}

template <class Map>
void bm_map_copy_constructor()
{
    Map m(g_sm);
}

template <>
void bm_map_copy_constructor<ft::map<int, int> >()
{
    ft::map<int, int> m(g_fm);
}

template <class Map>
void bm_map_assign_operator()
{
    Map m;
    m = g_sm;
}

template <>
void bm_map_assign_operator<ft::map<int, int> >()
{
    ft::map<int, int> m;
    m = g_fm;
}

template <class Map>
void bm_map_get_allocator()
{
    Map m;
    m.get_allocator();
}

template <class Map>
void bm_map_access_operator()
{
    Map m(g_sm);
    for (int i = 0; i < 1000; ++i)
        m[i];
}

template <>
void bm_map_access_operator<ft::map<int, int> >()
{
    ft::map<int, int> m(g_fm);
    for (int i = 0; i < 1000; ++i)
        m[i];
}

template <class Map>
void bm_map_begin()
{
    Map m(g_sm);
    m.begin();
}

template <>
void bm_map_begin<ft::map<int, int> >()
{
    ft::map<int, int> m(g_fm);
    m.begin();
}

template <class Map>
void bm_map_end()
{
    Map m(g_sm);
    m.end();
}

template <>
void bm_map_end<ft::map<int, int> >()
{
    ft::map<int, int> m(g_fm);
    m.end();
}

template <class Map>
void bm_map_rbegin()
{
    Map m(g_sm);
    m.rbegin();
}

template <>
void bm_map_rbegin<ft::map<int, int> >()
{
    ft::map<int, int> m(g_fm);
    m.rbegin();
}

template <class Map>
void bm_map_rend()
{
    Map m(g_sm);
    m.rend();
}

template <>
void bm_map_rend<ft::map<int, int> >()
{
    ft::map<int, int> m(g_fm);
    m.rend();
}

template <class Map>
void bm_map_empty()
{
    Map m;
    m.empty();
}

template <class Map>
void bm_map_size()
{
    g_sm.size();
}

template <>
void bm_map_size<ft::map<int, int> >()
{
    g_fm.size();
}

template <class Map>
void bm_map_max_size()
{
    Map m;
    m.max_size();
}

template <class Map>
void bm_map_clear()
{
    Map m(g_sm);
    m.clear();
}

template <>
void bm_map_clear<ft::map<int, int> >()
{
    ft::map<int, int> m(g_fm);
    m.clear();
}

template <class Map>
void bm_map_insert()
{
    Map m(g_sm);
    for (int i = 0; i < 1000; ++i)
        m.insert(std::make_pair(i*2 + 1, i));
}

template <>
void bm_map_insert<ft::map<int, int> >()
{
    ft::map<int, int> m(g_fm);
    for (int i = 0; i < 1000; ++i)
        m.insert(ft::make_pair(i*2 + 1, i));
}

template <class Map>
void bm_map_insert_hint()
{
    Map m(g_sm);
    m.insert(m.begin(), std::make_pair(1, 1));
}

template <>
void bm_map_insert_hint<ft::map<int, int> >()
{
    ft::map<int, int> m(g_fm);
    m.insert(m.begin(), ft::make_pair(1, 1));
}

template <class Map>
void bm_map_insert_range()
{
    Map m;
    m.insert(g_sm.begin(), g_sm.end());
}

template <>
void bm_map_insert_range<ft::map<int, int> >()
{
    ft::map<int, int> m;
    m.insert(g_fm.begin(), g_fm.end());
}

template <class Map>
void bm_map_erase()
{
    Map m(g_sm);
    for (int i = 0; i < 1000; ++i)
        m.erase(m.begin());
}

template <>
void bm_map_erase<ft::map<int, int> >()
{
    ft::map<int, int> m(g_fm);
    for (int i = 0; i < 1000; ++i)
        m.erase(m.begin());
}

template <class Map>
void bm_map_erase_range()
{
    Map m(g_sm);
    m.erase(m.begin(), m.end());
}

template <>
void bm_map_erase_range<ft::map<int, int> >()
{
    ft::map<int, int> m(g_fm);
    m.erase(m.begin(), m.end());
}

template <class Map>
void bm_map_erase_key()
{
    Map m(g_sm);
    for (int i = 0; i < 1000; ++i)
        m.erase(i);
}

template <>
void bm_map_erase_key<ft::map<int, int> >()
{
    ft::map<int, int> m(g_fm);
    for (int i = 0; i < 1000; ++i)
        m.erase(i);
}

template <class Map>
void bm_map_swap()
{
    Map m(g_sm);
    Map m1;
    m1.swap(m);
}

template <>
void bm_map_swap<ft::map<int, int> >()
{
    ft::map<int, int> m(g_fm);
    ft::map<int, int> m1;
    m1.swap(m);
}

template <class Map>
void bm_map_count()
{
    Map m(g_sm);
    for (int i = 0; i < 1000; ++i)
        m.count(i);
}

template <>
void bm_map_count<ft::map<int, int> >()
{
    ft::map<int, int> m(g_fm);
    for (int i = 0; i < 1000; ++i)
        m.count(i);
}

template <class Map>
void bm_map_find()
{
    Map m(g_sm);
    for (int i = 0; i < 1000; ++i)
        m.find(i);
}

template <>
void bm_map_find<ft::map<int, int> >()
{
    ft::map<int, int> m(g_fm);
    for (int i = 0; i < 1000; ++i)
        m.find(i);
}

template <class Map>
void bm_map_equal_range()
{
    Map m(g_sm);
    for (int i = 0; i < 1000; ++i)
        m.equal_range(i);
}

template <>
void bm_map_equal_range<ft::map<int, int> >()
{
    ft::map<int, int> m(g_fm);
    for (int i = 0; i < 1000; ++i)
        m.equal_range(i);
}

template <class Map>
void bm_map_lower_bound()
{
    Map m(g_sm);
    for (int i = 0; i < 1000; ++i)
        m.lower_bound(i);
}

template <>
void bm_map_lower_bound<ft::map<int, int> >()
{
    ft::map<int, int> m(g_fm);
    for (int i = 0; i < 1000; ++i)
        m.lower_bound(i);
}

template <class Map>
void bm_map_upper_bound()
{
    Map m(g_sm);
    for (int i = 0; i < 1000; ++i)
        m.upper_bound(i);
}

template <>
void bm_map_upper_bound<ft::map<int, int> >()
{
    ft::map<int, int> m(g_fm);
    for (int i = 0; i < 1000; ++i)
        m.upper_bound(i);
}

template <class Map>
void bm_map_key_comp()
{
    Map m;
    m.key_comp();
}

template <class Map>
void bm_map_value_comp()
{
    Map m;
    m.value_comp();
}

template <class Map>
void bm_map_equal()
{
    Map m1, m2;
    (void)(m1 == m2);
}

template <class Map>
void bm_map_not_equal()
{
    Map m1, m2;
    (void)(m1 != m2);
}

template <class Map>
void bm_map_less()
{
    Map m1, m2;
    (void)(m1 < m2);
}

template <class Map>
void bm_map_greater()
{
    Map m1, m2;
    (void)(m1 > m2);
}

template <class Map>
void bm_map_less_equal()
{
    Map m1, m2;
    (void)(m1 <= m2);
}

template <class Map>
void bm_map_greater_equal()
{
    Map m1, m2;
    (void)(m1 >= m2);
}

void map_bench()
{
    for (int i = 0; i < 1000; ++i)
    {
        g_sm.insert(std::make_pair(i*2, i));
        g_fm.insert(ft::make_pair(i*2, i));
    }
    BM_REGIST("map_def_constructor",
              (bm_map_def_constructor<ft::map<int, int> >),
              (bm_map_def_constructor<std::map<int, int> >), LOOP, 1);
    BM_REGIST("map_constructor",
              (bm_map_constructor<ft::map<int, int, std::greater<int> > >),
              (bm_map_constructor<std::map<int, int, std::greater<int> > >),
              LOOP, 1);
    BM_REGIST("map_range_constructor",
              (bm_map_range_constructor<ft::map<int, int> >),
              (bm_map_range_constructor<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_copy_constructor",
              (bm_map_copy_constructor<ft::map<int, int> >),
              (bm_map_copy_constructor<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_assign_operator",
              (bm_map_assign_operator<ft::map<int, int> >),
              (bm_map_assign_operator<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_get_allocator", (bm_map_get_allocator<ft::map<int, int> >),
              (bm_map_get_allocator<std::map<int, int> >), LOOP, 1);
    BM_REGIST("map_access_operator",
              (bm_map_access_operator<ft::map<int, int> >),
              (bm_map_access_operator<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_begin", (bm_map_begin<ft::map<int, int> >),
              (bm_map_begin<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_end", (bm_map_end<ft::map<int, int> >),
              (bm_map_end<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_rbegin", (bm_map_rbegin<ft::map<int, int> >),
              (bm_map_rbegin<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_rend", (bm_map_rend<ft::map<int, int> >),
              (bm_map_rend<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_empty", (bm_map_empty<ft::map<int, int> >),
              (bm_map_empty<std::map<int, int> >), LOOP, 1);
    BM_REGIST("map_size", (bm_map_size<ft::map<int, int> >),
              (bm_map_size<std::map<int, int> >), LOOP, 1);
    BM_REGIST("map_max_size", (bm_map_max_size<ft::map<int, int> >),
              (bm_map_max_size<std::map<int, int> >), LOOP, 1);
    BM_REGIST("map_clear", (bm_map_clear<ft::map<int, int> >),
              (bm_map_clear<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_insert", (bm_map_insert<ft::map<int, int> >),
              (bm_map_insert<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_insert_hint", (bm_map_insert_hint<ft::map<int, int> >),
              (bm_map_insert_hint<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_insert_range", (bm_map_insert_range<ft::map<int, int> >),
              (bm_map_insert_range<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_erase", (bm_map_erase<ft::map<int, int> >),
              (bm_map_erase<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_erase_range", (bm_map_erase_range<ft::map<int, int> >),
              (bm_map_erase_range<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_erase_key", (bm_map_erase_key<ft::map<int, int> >),
              (bm_map_erase_key<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_swap", (bm_map_swap<ft::map<int, int> >),
              (bm_map_swap<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_count", (bm_map_count<ft::map<int, int> >),
              (bm_map_count<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_find", (bm_map_find<ft::map<int, int> >),
              (bm_map_find<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_equal_range", (bm_map_equal_range<ft::map<int, int> >),
              (bm_map_equal_range<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_lower_bound", (bm_map_lower_bound<ft::map<int, int> >),
              (bm_map_lower_bound<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_upper_bound", (bm_map_upper_bound<ft::map<int, int> >),
              (bm_map_upper_bound<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_key_comp", (bm_map_key_comp<ft::map<int, int> >),
              (bm_map_key_comp<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_value_comp", (bm_map_value_comp<ft::map<int, int> >),
              (bm_map_value_comp<std::map<int, int> >), LOOP, 1);
    BM_REGIST("map_equal", (bm_map_equal<ft::map<int, int> >),
              (bm_map_equal<std::map<int, int> >), LOOP, 1);
    BM_REGIST("map_not_equal", (bm_map_not_equal<ft::map<int, int> >),
              (bm_map_not_equal<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_less", (bm_map_less<ft::map<int, int> >),
              (bm_map_less<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_greater", (bm_map_greater<ft::map<int, int> >),
              (bm_map_greater<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_less_equal", (bm_map_less_equal<ft::map<int, int> >),
              (bm_map_less_equal<std::map<int, int> >), LOOP2, 1);
    BM_REGIST("map_greater_equal", (bm_map_greater_equal<ft::map<int, int> >),
              (bm_map_greater_equal<std::map<int, int> >), LOOP2, 1);
}