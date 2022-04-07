#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <time.h>

namespace ft {

class StopWatch
{
public:
    StopWatch() {}
    ~StopWatch() {}

    void start() { c_start_ = clock(); }

    void end()
    {
        c_end_  = clock();
        cpu_ms_ = (c_end_ - c_start_) * 1000 / CLOCKS_PER_SEC;
    }

    double get_cpu_ms() const { return cpu_ms_; }

    void clear()
    {
        c_start_ = 0;
        c_end_   = 0;
        cpu_ms_  = 0;
    }

private:
    clock_t c_start_, c_end_;
    double  cpu_ms_;
};

} // namespace ft
#endif // STOPWATCH_HPP