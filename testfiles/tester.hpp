#ifndef TESTER_HPP
#define TESTER_HPP

#if TEST // -DTEST=1
#include <iterator>
#include <map>
#include <set>
#include <stack>
#include <vector>
namespace ft = std;
#else // -DTEST=0
#include <algorithm.hpp>
#include <utils.hpp>
#include <vector.hpp>
#endif

#include <color.hpp>

#include <stdlib.h>
#include <time.h> // clock()

#include <algorithm> //std::copy
#include <cmath>     //hypot set
#include <cstddef>   // size_t
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream> // cout
#include <list>     // std::list
#include <memory>
#include <numeric>
#include <sstream>
#include <string>
#include <typeinfo> //typeid

#define cout std::cout
#define endl std::endl
#define cerr std::cerr
#define rep(i, n) for (int i = 0; i < n; ++i)

template<typename T> void put_test_function(T s)
{
    cout << "\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << std::setw(25) << s << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n" << endl;
}

template <typename T>
void pout(T s)
{
    static int no;
    cout << endl;
    cout << "--- [" << ++no << "]:" << s << " ---" << endl;
}

template <class T>
void vdebug(T& V)
{
    cout << "size:" << V.size() << " capacity:" << V.capacity() << endl;
    cout << "{ ";
    for (typename T::iterator it = V.begin(); it != V.end(); ++it)
        cout << *it << " ";
    cout << "}" << endl;
}

template <class T>
void print_is_empty(T& v)
{
    if (v.empty())
    {
        cout << "vector is empty" << endl;
    }
    else
    {
        cout << "vector is not empty" << endl;
    }
}

//// tester
/**********************/
/*     tutorial.cpp   */
/**********************/
void tutorial_test(void);
void vector_test();
void algorithm_test();

//// helper

#endif
