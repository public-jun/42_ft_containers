#ifndef TESTER_HPP
#define TESTER_HPP

#if TEST // -DTEST=1
#include <iterator>
#include <map>
#include <set>
#include <stack>
#include <vector>
namespace ft = std;
#else    // -DTEST=0
#include <vector.hpp>
#include <iterator.hpp>
#endif


#include <stdlib.h>
#include <time.h> // clock()

#include <algorithm> //std::copy
#include <cmath> //hypot set
#include <cstddef>   // size_t
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>  // cout
#include <list>      // std::list
#include <numeric>
#include <string>
#include <typeinfo>  //typeid

#define cout std::cout
#define endl std::endl
#define cerr std::cerr
#define rep(i, n) for (int i = 0; i < n; ++i)

//// tester
/**********************/
/*     tutorial.cpp   */
/**********************/
void tutorial_test(void);

//// helper


#endif
