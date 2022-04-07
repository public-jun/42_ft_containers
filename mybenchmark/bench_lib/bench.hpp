#ifndef BENCH_HPP
#define BENCH_HPP

#include "Measure.hpp"
#include "StopWatch.hpp"

#define LOOP 1 << 22
#define LOOP2 1 << 13
#define LOOP3 1 << 4

#define BM_REGIST(name, ft_func, stl_func, loop, cnt_max)                       \
    {                                                                           \
        ft::StopWatch ft_sw  = sw(ft_func, cnt_max, loop);                      \
        ft::StopWatch stl_sw = sw(stl_func, cnt_max, loop);                     \
        ft::Measure   m      = ft::Measure(ft_sw, stl_sw, name, loop, cnt_max); \
        m.print_result();                                                       \
    }

template <class Fn>
inline ft::StopWatch sw(Fn func, int cnt_max, unsigned long long loop)
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

#endif
