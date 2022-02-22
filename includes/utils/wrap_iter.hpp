#ifndef WRAP_ITER_HPP
#define WRAP_ITER_HPP

#include <iterator.hpp>

namespace ft {
template <class Iter>
class wrap_iter
{
protected:
    Iter current_;
    typedef iterator_traits<Iter> traits_type;

public:
    typedef Iter iterator_type;
    typedef typename traits_type::value_type value_type;
    typedef typename traits_type::difference_type difference_type;
    typedef typename traits_type::pointer pointer;
    typedef typename traits_type::reference reference;
    typedef typename traits_type::iterator_category category;

    // Member functions
    //// constructor
    wrap_iter() : current_() {}
    wrap_iter(iterator_type x) : current_(x) {}
    //// copy constructor
    wrap_iter(const wrap_iter& other) : current_(other.base()) {}
    //// assignment operator
    template <class U>
    wrap_iter& operator=(const wrap_iter<U>& other)
    {
        if (this != &other)
            current_ = other.base();
        return *this;
    }
    //// destructor
    ~wrap_iter() {}

    iterator_type base() const { return current_; }
    reference operator*() const { return *current_; }
    pointer operator->() const { return &(operator*()); }
    reference operator[](difference_type n) const { return *(*this + n); }
    wrap_iter& operator++()
    {
        ++current_;
        return *this;
    }
    wrap_iter& operator--()
    {
        --current_;
        return *this;
    }
    wrap_iter operator++(int)
    {
        wrap_iter tmp = *this;
        ++current_;
        return tmp;
    }
    wrap_iter operator--(int)
    {
        wrap_iter tmp = *this;
        --current_;
        return tmp;
    }
    wrap_iter operator+(difference_type n) const
    {
        return wrap_iter(current_ + n);
    }
    wrap_iter operator-(difference_type n) const
    {
        return wrap_iter(current_ - n);
    }
    wrap_iter& operator+=(difference_type n)
    {
        current_ += n;
        return *this;
    }
    wrap_iter& operator-=(difference_type n)
    {
        current_ -= n;
        return *this;
    }
};

}; // namespace ft

#endif /* WRAP_ITER_HPP */
