#ifndef WRAP_ITER_HPP
#define WRAP_ITER_HPP

#include <iterator_traits.hpp>

namespace ft {
template <class Iter>
class wrap_iter
{
protected:
    Iter                          current_;
    typedef iterator_traits<Iter> traits_type;

public:
    typedef Iter                                    iterator_type;
    typedef typename traits_type::value_type        value_type;
    typedef typename traits_type::difference_type   difference_type;
    typedef typename traits_type::pointer           pointer;
    typedef typename traits_type::reference         reference;
    typedef typename traits_type::iterator_category iterator_category;

    // Member functions
    //// constructor
    wrap_iter() : current_(NULL) {}
    explicit wrap_iter(iterator_type x) : current_(x) {}
    //// copy constructor
    template <class U>
    wrap_iter(const wrap_iter<U>& other) : current_(other.base())
    {}

    //// assignment operator
    template <class U>
    wrap_iter& operator=(const wrap_iter<U>& other)
    {
        // std::cout << "assignment called" << std::endl;
        if (current_ != other.base())
            current_ = other.base();
        return *this;
    }
    //// destructor
    ~wrap_iter() {}

    iterator_type base() const { return current_; }
    reference     operator*() const { return *current_; }
    pointer       operator->() const { return current_; }
    reference     operator[](difference_type n) const { return *(*this + n); }
    wrap_iter&    operator++()
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

// Non member functions
//// operator==
template <class Iterator>
bool operator==(const wrap_iter<Iterator>& lhs, const wrap_iter<Iterator>& rhs)
{
    return lhs.base() == rhs.base();
}
template <class Iterator1, class Iterator2>
bool operator==(const wrap_iter<Iterator1>& lhs,
                const wrap_iter<Iterator2>& rhs)
{
    return lhs.base() == rhs.base();
}

//// operator!=
template <class Iterator>
bool operator!=(const wrap_iter<Iterator>& lhs, const wrap_iter<Iterator>& rhs)
{
    return lhs.base() != rhs.base();
}
template <class Iterator1, class Iterator2>
bool operator!=(const wrap_iter<Iterator1>& lhs,
                const wrap_iter<Iterator2>& rhs)
{
    return lhs.base() != rhs.base();
}

//// operator<
template <class Iterator>
bool operator<(const wrap_iter<Iterator>& lhs, const wrap_iter<Iterator>& rhs)
{
    return lhs.base() < rhs.base();
}
template <class Iterator1, class Iterator2>
bool operator<(const wrap_iter<Iterator1>& lhs, const wrap_iter<Iterator2>& rhs)
{
    return lhs.base() < rhs.base();
}

//// operator<=
template <class Iterator>
bool operator<=(const wrap_iter<Iterator>& lhs, const wrap_iter<Iterator>& rhs)
{
    return lhs.base() <= rhs.base();
}
template <class Iterator1, class Iterator2>
bool operator<=(const wrap_iter<Iterator1>& lhs,
                const wrap_iter<Iterator2>& rhs)
{
    return lhs.base() <= rhs.base();
}

//// operator>
template <class Iterator>
bool operator>(const wrap_iter<Iterator>& lhs, const wrap_iter<Iterator>& rhs)
{
    return lhs.base() > rhs.base();
}
template <class Iterator1, class Iterator2>
bool operator>(const wrap_iter<Iterator1>& lhs, const wrap_iter<Iterator2>& rhs)
{
    return lhs.base() > rhs.base();
}

//// operator>=
template <class Iterator>
bool operator>=(const wrap_iter<Iterator>& lhs, const wrap_iter<Iterator>& rhs)
{
    return lhs.base() >= rhs.base();
}
template <class Iterator1, class Iterator2>
bool operator>=(const wrap_iter<Iterator1>& lhs,
                const wrap_iter<Iterator2>& rhs)
{
    return lhs.base() >= rhs.base();
}

//// operator+
template <class Iterator>
wrap_iter<Iterator> operator+(typename wrap_iter<Iterator>::difference_type n,
                              wrap_iter<Iterator>                           it)
{
    it += n;
    return it;
}

//// operator-
template <class Iterator1, class Iterator2>
typename wrap_iter<Iterator1>::difference_type
operator-(const wrap_iter<Iterator1>& lhs, const wrap_iter<Iterator2>& rhs)
{
    return lhs.base() - rhs.base();
}

} // namespace ft

#endif /* WRAP_ITER_HPP */
