#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <iterator_traits.hpp>

namespace ft {

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
    Iter                              current_;
    typedef ft::iterator_traits<Iter> traits_type;

public:
    // Member type
    typedef Iter                                    iterator_type;
    typedef typename traits_type::iterator_category iterator_category;
    typedef typename traits_type::value_type        value_type;
    typedef typename traits_type::difference_type   difference_type;
    typedef typename traits_type::pointer           pointer;
    typedef typename traits_type::reference         reference;

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
          const reverse_iterator<Iter>&                    it)
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

} /* namespace ft */

#endif /* ITERATOR_HPP */
