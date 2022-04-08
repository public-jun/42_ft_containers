#include "stack_bench.cpp"
#include "vector_bench.cpp"
#include "map_bench.cpp"
#include "set_bench.cpp"

#include <iomanip>
#include <iostream>

void print_title()
{
    std::cout << std::left << std::setw(30) << "TEST" << std::flush;
    std::cout << std::left << std::setw(15) << "loop" << std::flush;
    std::cout << std::left << std::setw(15) << "FT_CPU(ms)" << std::flush;
    std::cout << std::left << std::setw(15) << "STL_CPU(ms)" << std::flush;
    std::cout << std::left << std::setw(15) << "Rate(FT / STL)" << std::endl;
}

int main()
{
    print_title();
    vector_bench();
    stack_bench();
    map_bench();
    set_bench();
}