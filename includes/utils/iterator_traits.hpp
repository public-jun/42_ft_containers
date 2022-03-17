#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <cstddef> // ptrdiff_t
#include <iterator>

namespace ft {

/*
** ft Iterator Tsgs
**
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};
*/

/**
 *  @brief  Common %iterator class.
 *
 *  This class does nothing but define nested typedefs.  %Iterator classes
 *  can inherit from this class to save some work.  The typedefs are then
 *  used in specializations and overloading.
 */
template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
struct iterator {
    typedef Category  iterator_category;
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
};

/**
 *  @brief  Traits class for iterators.
 *
 *  This class does nothing but define nested typedefs.
 */
/// iterator_traits
template <class Iterator>
struct iterator_traits {
    typedef typename Iterator::difference_type   difference_type;
    typedef typename Iterator::value_type        value_type;
    typedef typename Iterator::pointer           pointer;
    typedef typename Iterator::reference         reference;
    typedef typename Iterator::iterator_category iterator_category;
};

/// Partial specialization for pointer types
template <class T>
struct iterator_traits<T*> {
    typedef ptrdiff_t                       difference_type;
    typedef T                               value_type;
    typedef T*                              pointer;
    typedef T&                              reference;
    typedef std::random_access_iterator_tag iterator_category;
};

/// Partial specialization for const pointer types.
template <class T>
struct iterator_traits<const T*> {
    typedef ptrdiff_t                       difference_type;
    typedef T                               value_type;
    typedef const T*                        pointer;
    typedef const T&                        reference;
    typedef std::random_access_iterator_tag iterator_category;
};
} // namespace ft

#endif
