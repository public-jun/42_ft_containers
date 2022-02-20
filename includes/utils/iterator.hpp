#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef> // ptrdiff_t

namespace ft {

/// Iterator Tags

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

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
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
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
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
};

/// Partial specialization for pointer types
template <class T>
struct iterator_traits<T*> {
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef ft::random_access_iterator_tag iterator_category;
};

/// Partial specialization for const pointer types.
template <class T>
struct iterator_traits<const T*> {
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef const T* pointer;
    typedef const T& reference;
    typedef ft::random_access_iterator_tag iterator_category;
};

/// reverse_iterator
template <class Iter>
class reverse_iterator
    : public iterator<typename ft::iterator_traits<Iter>::iterator_category,
                      typename ft::iterator_traits<Iter>::value_type,
                      typename ft::iterator_traits<Iter>::difference_type,
                      typename ft::iterator_traits<Iter>::pointer,
                      typename ft::iterator_traits<Iter>::reference>
{
protected:
    // Member objects
    Iter current_;
    typedef ft::iterator_traits<Iter> traits_type;

public:
    // Member type
    typedef Iter iterator_type;
    typedef typename traits_type::iterator_category iterator_category;
    typedef typename traits_type::value_type value_type;
    typedef typename traits_type::difference_type difference_type;
    typedef typename traits_type::pointer pointer;
    typedef typename traits_type::reference reference;

    // Member functions
    //// constructor
    reverse_iterator() : current_() {}
    explicit reverse_iterator(iterator_type x) : current_(x) {}
    template <class U>
    reverse_iterator(const reverse_iterator<U>& other) : current_(other.base())
    {}

    //// destructor
    virtual ~reverse_iterator() {}

    iterator_type base() const { return current_; }

    // operators
    template <class U>
    reverse_iterator& operator=(const reverse_iterator<U>& other)
    {
        current_ = other.base();
        return *this;
    }

    //// Dereference iterator
    reference operator*() const
    {
        Iter tmp = current_;
        return *--tmp;
    }
    pointer operator->() const { return &(operator*()); }

    reference operator[](difference_type n) const { return *(*this + n); }

    reverse_iterator& operator++()
    {
        --current_;
        return *this;
    }
    reverse_iterator& operator--()
    {
        ++current_;
        return *this;
    }
    reverse_iterator operator++(int)
    {
        reverse_iterator tmp = *this;
        ++(*this);
        return tmp;
    }
    reverse_iterator operator--(int)
    {
        reverse_iterator tmp = *this;
        --(*this);
        return tmp;
    }
    reverse_iterator operator+(difference_type n) const
    {
        return reverse_iterator(current_ - n);
    }
    reverse_iterator operator-(difference_type n) const
    {
        return reverse_iterator(current_ + n);
    }
    reverse_iterator& operator+=(difference_type n)
    {
        current_ -= n;
        return *this;
    }
    reverse_iterator& operator-=(difference_type n)
    {
        current_ += n;
        return *this;
    }
};

/// Non member functions
template <class Iterator1, class Iterator2>
bool operator==(const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() == rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator!=(const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() != rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<(const reverse_iterator<Iterator1>& lhs,
               const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() > rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<=(const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() >= rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>(const reverse_iterator<Iterator1>& lhs,
               const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() < rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator>=(const reverse_iterator<Iterator1>& lhs,
                const reverse_iterator<Iterator2>& rhs)
{
    return lhs.base() <= rhs.base();
}

template <class Iter>
reverse_iterator<Iter>
operator+(typename reverse_iterator<Iter>::difference_type n,
          const reverse_iterator<Iter>& it)
{
    return reverse_iterator<Iter>(it.base() - n);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator>& lhs,
          const reverse_iterator<Iterator>& rhs)
{
    return rhs.base() - lhs.base();
}

}; /* namespace ft */

#endif /* ITERATOR_HPP */
