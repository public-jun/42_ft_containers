#ifndef BENCH_HPP
#define BENCH_HPP

#include "StopWatch.hpp"
#include "Measure.hpp"

#define LOOP 1 << 22
#define LOOP2 1 << 13
#define LOOP3 1 << 4

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

#endif
