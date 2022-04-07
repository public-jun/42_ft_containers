#ifndef MEASURE_HPP
#define MEASURE_HPP

#include "../gtest/test_utils/color.hpp"
#include "StopWatch.hpp"
#include <iomanip>
#include <iostream>
#include <string>

namespace ft {
class Measure
{
public:
    Measure(ft::StopWatch ft_sw, ft::StopWatch stl_sw, std::string name,
            unsigned long long loop, int count)
        : fw_(ft_sw), sw_(stl_sw), t_name_(name), loop_(loop), count_(count)
    {}
    ~Measure() {}

    void print_result()
    {
        std::cout << std::left << std::setw(30) << t_name_ << std::flush;
        std::cout << std::left << std::setw(15) << loop_ << std::flush;
        std::cout << std::left << std::setw(15) << std::fixed
                  << std::setprecision(3) << fw_.get_cpu_ms() / count_
                  << std::flush;
        std::cout << std::left << std::setw(15) << std::fixed
                  << std::setprecision(3) << sw_.get_cpu_ms() / count_
                  << std::flush;
        double res = fw_.get_cpu_ms() / sw_.get_cpu_ms();
        if (res >= 20.0)
            std::cout << RED;
        std::cout << std::left << std::setw(15) << std::fixed << std::setprecision(3) << res << END << std::endl;
    }

private:
    Measure() {}
    ft::StopWatch      fw_;
    ft::StopWatch      sw_;
    std::string        t_name_;
    unsigned long long loop_;
    int                count_;
};

} // namespace ft

#endif