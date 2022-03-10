#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

// #include <iostream> //std::cout  will remove
// #define CALLED std::cout << "called" << std::endl;

namespace ft {

template <class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
{
    for (; first1 != last1; ++first1, ++first2)
    {
        if (*first1 != *first2)
        {
            return false;
        }
    }
    return true;
}

template <class InputIt1, class InputIt2, class BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last2, InputIt2 first2, BinaryPredicate p)
{
    for (; first1 != last2; ++first1, ++first2)
    {
        if (!p(*first1, *first2))
        {
            return false;
        }
    }
    return true;
}

template <class _InputIterator1, class _InputIterator2>
bool lexicographical_compare(_InputIterator1 __first1, _InputIterator1 __last1,
                             _InputIterator2 __first2, _InputIterator2 __last2)
{
    for (; __first1 != __last1 && __first2 != __last2; ++__first1, ++__first2)
    {
        if (*__first1 < *__first2)
            return true;
        if (*__first2 < *__first1)
            return false;
    }

    return __first1 == __last1 && __first2 != __last2;
}

template <class _InputIterator1, class _InputIterator2, class _Compare>
bool lexicographical_compare(_InputIterator1 __first1, _InputIterator1 __last1,
                             _InputIterator2 __first2, _InputIterator2 __last2, _Compare __comp)
{
    for (; __first1 != __last1 && __first2 != __last2; ++__first1, ++__first2)
    {
        if (__comp(*__first1, *__first2))
            return true;
        if (__comp(*__first2, *__first1))
            return false;
    }

    return __first1 == __last1 && __first2 != __last2;
}
} // namespace ft

#endif
