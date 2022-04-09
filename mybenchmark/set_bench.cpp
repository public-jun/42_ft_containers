#include "./bench_lib/bench.hpp"

#include <set.hpp>
#include <set>

std::set<int> g_ss;
ft::set<int>  g_fs;

template <class set>
void bm_set_def_constructor()
{
    set m;
}

template <class set>
void bm_set_constructor()
{
    set m;
}

template <class set>
void bm_set_range_constructor()
{
    set m(g_ss.begin(), g_ss.end());
}

template <>
void bm_set_range_constructor<ft::set<int> >()
{
    ft::set<int> m(g_fs.begin(), g_fs.end());
}

template <class set>
void bm_set_copy_constructor()
{
    set m(g_ss);
}

template <>
void bm_set_copy_constructor<ft::set<int> >()
{
    ft::set<int> m(g_fs);
}

template <class set>
void bm_set_assign_operator()
{
    set m;
    m = g_ss;
}

template <>
void bm_set_assign_operator<ft::set<int> >()
{
    ft::set<int> m;
    m = g_fs;
}

template <class set>
void bm_set_get_allocator()
{
    set m;
    m.get_allocator();
}

template <class set>
void bm_set_begin()
{
    set m(g_ss);
    m.begin();
}

template <>
void bm_set_begin<ft::set<int> >()
{
    ft::set<int> m(g_fs);
    m.begin();
}

template <class set>
void bm_set_end()
{
    set m(g_ss);
    m.end();
}

template <>
void bm_set_end<ft::set<int> >()
{
    ft::set<int> m(g_fs);
    m.end();
}

template <class set>
void bm_set_rbegin()
{
    set m(g_ss);
    m.rbegin();
}

template <>
void bm_set_rbegin<ft::set<int> >()
{
    ft::set<int> m(g_fs);
    m.rbegin();
}

template <class set>
void bm_set_rend()
{
    set m(g_ss);
    m.rend();
}

template <>
void bm_set_rend<ft::set<int> >()
{
    ft::set<int> m(g_fs);
    m.rend();
}

template <class set>
void bm_set_empty()
{
    set m;
    m.empty();
}

template <class set>
void bm_set_size()
{
    g_ss.size();
}

template <>
void bm_set_size<ft::set<int> >()
{
    g_fs.size();
}

template <class set>
void bm_set_max_size()
{
    set m;
    m.max_size();
}

template <class set>
void bm_set_clear()
{
    set m(g_ss);
    m.clear();
}

template <>
void bm_set_clear<ft::set<int> >()
{
    ft::set<int> m(g_fs);
    m.clear();
}

template <class set>
void bm_set_insert()
{
    set m(g_ss);
    for (int i = 0; i < 1000; ++i)
        m.insert(i);
}

template <>
void bm_set_insert<ft::set<int> >()
{
    ft::set<int> m(g_fs);
    for (int i = 0; i < 1000; ++i)
        m.insert(i);
}

template <class set>
void bm_set_insert_hint()
{
    set m(g_ss);
    m.insert(m.begin(), 1);
}

template <>
void bm_set_insert_hint<ft::set<int> >()
{
    ft::set<int> m(g_fs);
    m.insert(m.begin(), 1);
}

template <class set>
void bm_set_insert_range()
{
    set m;
    m.insert(g_ss.begin(), g_ss.end());
}

template <>
void bm_set_insert_range<ft::set<int> >()
{
    ft::set<int> m;
    m.insert(g_fs.begin(), g_fs.end());
}

template <class set>
void bm_set_erase()
{
    set m(g_ss);
    for (int i = 0; i < 1000; ++i)
        m.erase(m.begin());
}

template <>
void bm_set_erase<ft::set<int> >()
{
    ft::set<int> m(g_fs);
    for (int i = 0; i < 1000; ++i)
        m.erase(m.begin());
}

template <class set>
void bm_set_erase_range()
{
    set m(g_ss);
    m.erase(m.begin(), m.end());
}

template <>
void bm_set_erase_range<ft::set<int> >()
{
    ft::set<int> m(g_fs);
    m.erase(m.begin(), m.end());
}

template <class set>
void bm_set_erase_key()
{
    set m(g_ss);
    for (int i = 0; i < 1000; ++i)
        m.erase(i);
}

template <>
void bm_set_erase_key<ft::set<int> >()
{
    ft::set<int> m(g_fs);
    for (int i = 0; i < 1000; ++i)
        m.erase(i);
}

template <class set>
void bm_set_swap()
{
    set m(g_ss);
    set m1;
    m1.swap(m);
}

template <>
void bm_set_swap<ft::set<int> >()
{
    ft::set<int> m(g_fs);
    ft::set<int> m1;
    m1.swap(m);
}

template <class set>
void bm_set_count()
{
    set m(g_ss);
    for (int i = 0; i < 1000; ++i)
        m.count(i);
}

template <>
void bm_set_count<ft::set<int> >()
{
    ft::set<int> m(g_fs);
    for (int i = 0; i < 1000; ++i)
        m.count(i);
}

template <class set>
void bm_set_find()
{
    set m(g_ss);
    for (int i = 0; i < 1000; ++i)
        m.find(i);
}

template <>
void bm_set_find<ft::set<int> >()
{
    ft::set<int> m(g_fs);
    for (int i = 0; i < 1000; ++i)
        m.find(i);
}

template <class set>
void bm_set_equal_range()
{
    set m(g_ss);
    for (int i = 0; i < 1000; ++i)
        m.equal_range(i);
}

template <>
void bm_set_equal_range<ft::set<int> >()
{
    ft::set<int> m(g_fs);
    for (int i = 0; i < 1000; ++i)
        m.equal_range(i);
}

template <class set>
void bm_set_lower_bound()
{
    set m(g_ss);
    for (int i = 0; i < 1000; ++i)
        m.lower_bound(i);
}

template <>
void bm_set_lower_bound<ft::set<int> >()
{
    ft::set<int> m(g_fs);
    for (int i = 0; i < 1000; ++i)
        m.lower_bound(i);
}

template <class set>
void bm_set_upper_bound()
{
    set m(g_ss);
    for (int i = 0; i < 1000; ++i)
        m.upper_bound(i);
}

template <>
void bm_set_upper_bound<ft::set<int> >()
{
    ft::set<int> m(g_fs);
    for (int i = 0; i < 1000; ++i)
        m.upper_bound(i);
}

template <class set>
void bm_set_key_comp()
{
    set m;
    m.key_comp();
}

template <class set>
void bm_set_value_comp()
{
    set m;
    m.value_comp();
}

template <class set>
void bm_set_equal()
{
    set m1, m2;
    (void)(m1 == m2);
}

template <class set>
void bm_set_not_equal()
{
    set m1, m2;
    (void)(m1 != m2);
}

template <class set>
void bm_set_less()
{
    set m1, m2;
    (void)(m1 < m2);
}

template <class set>
void bm_set_greater()
{
    set m1, m2;
    (void)(m1 > m2);
}

template <class set>
void bm_set_less_equal()
{
    set m1, m2;
    (void)(m1 <= m2);
}

template <class set>
void bm_set_greater_equal()
{
    set m1, m2;
    (void)(m1 >= m2);
}

void set_bench()
{
    for (int i = 0; i < 1000; ++i)
    {
        g_ss.insert(i * 2);
        g_fs.insert(i * 2);
    }
    BM_REGIST("set_def_constructor", (bm_set_def_constructor<ft::set<int> >),
              (bm_set_def_constructor<std::set<int> >), LOOP2, 100);
    BM_REGIST("set_constructor",
              (bm_set_constructor<ft::set<int, std::greater<int> > >),
              (bm_set_constructor<std::set<int, std::greater<int> > >), LOOP2,
              100);
    BM_REGIST("set_range_constructor",
              (bm_set_range_constructor<ft::set<int> >),
              (bm_set_range_constructor<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_copy_constructor", (bm_set_copy_constructor<ft::set<int> >),
              (bm_set_copy_constructor<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_assign_operator", (bm_set_assign_operator<ft::set<int> >),
              (bm_set_assign_operator<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_get_allocator", (bm_set_get_allocator<ft::set<int> >),
              (bm_set_get_allocator<std::set<int> >), LOOP, 1);
    BM_REGIST("set_begin", (bm_set_begin<ft::set<int> >),
              (bm_set_begin<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_end", (bm_set_end<ft::set<int> >),
              (bm_set_end<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_rbegin", (bm_set_rbegin<ft::set<int> >),
              (bm_set_rbegin<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_rend", (bm_set_rend<ft::set<int> >),
              (bm_set_rend<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_empty", (bm_set_empty<ft::set<int> >),
              (bm_set_empty<std::set<int> >), LOOP, 1);
    BM_REGIST("set_size", (bm_set_size<ft::set<int> >),
              (bm_set_size<std::set<int> >), LOOP, 1);
    BM_REGIST("set_max_size", (bm_set_max_size<ft::set<int> >),
              (bm_set_max_size<std::set<int> >), LOOP, 1);
    BM_REGIST("set_clear", (bm_set_clear<ft::set<int> >),
              (bm_set_clear<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_insert", (bm_set_insert<ft::set<int> >),
              (bm_set_insert<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_insert_hint", (bm_set_insert_hint<ft::set<int> >),
              (bm_set_insert_hint<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_insert_range", (bm_set_insert_range<ft::set<int> >),
              (bm_set_insert_range<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_erase", (bm_set_erase<ft::set<int> >),
              (bm_set_erase<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_erase_range", (bm_set_erase_range<ft::set<int> >),
              (bm_set_erase_range<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_erase_key", (bm_set_erase_key<ft::set<int> >),
              (bm_set_erase_key<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_swap", (bm_set_swap<ft::set<int> >),
              (bm_set_swap<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_count", (bm_set_count<ft::set<int> >),
              (bm_set_count<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_find", (bm_set_find<ft::set<int> >),
              (bm_set_find<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_equal_range", (bm_set_equal_range<ft::set<int> >),
              (bm_set_equal_range<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_lower_bound", (bm_set_lower_bound<ft::set<int> >),
              (bm_set_lower_bound<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_upper_bound", (bm_set_upper_bound<ft::set<int> >),
              (bm_set_upper_bound<std::set<int> >), LOOP3, 100);
    BM_REGIST("set_key_comp", (bm_set_key_comp<ft::set<int> >),
              (bm_set_key_comp<std::set<int> >), LOOP2, 100);
    BM_REGIST("set_value_comp", (bm_set_value_comp<ft::set<int> >),
              (bm_set_value_comp<std::set<int> >), LOOP2, 100);
    BM_REGIST("set_equal", (bm_set_equal<ft::set<int> >),
              (bm_set_equal<std::set<int> >), LOOP, 1);
    BM_REGIST("set_not_equal", (bm_set_not_equal<ft::set<int> >),
              (bm_set_not_equal<std::set<int> >), LOOP, 1);
    BM_REGIST("set_less", (bm_set_less<ft::set<int> >),
              (bm_set_less<std::set<int> >), LOOP, 1);
    BM_REGIST("set_greater", (bm_set_greater<ft::set<int> >),
              (bm_set_greater<std::set<int> >), LOOP, 1);
    BM_REGIST("set_less_equal", (bm_set_less_equal<ft::set<int> >),
              (bm_set_less_equal<std::set<int> >), LOOP, 1);
    BM_REGIST("set_greater_equal", (bm_set_greater_equal<ft::set<int> >),
              (bm_set_greater_equal<std::set<int> >), LOOP, 1);
}
