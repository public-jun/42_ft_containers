#ifndef STACK_HPP
#define STACK_HPP

#include <vector.hpp>

namespace ft {
template <class Tp, class Container = ft::vector<Tp> >
class stack
{
public:
    // Member type
    typedef Container container_type;
    typedef typename container_type::value_type value_type;
    typedef typename container_type::reference reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::size_type size_type;

protected:
    container_type c_;

public:
    // Member function
    explicit stack(const container_type& cont = Container()) : c_(cont) {}
    stack(const stack& other) : c_(other.c_) {}
    ~stack() {}
    stack& operator=(const stack& other)
    {
        c_ = other.c_;
        return *this;
    }

    reference top() { return c_.back(); }
    const_reference top() const { return c_.back(); }

    bool empty() const { return c_.empty(); }

    size_type size() const { return c_.size(); }

    void push(const value_type& value) { c_.push_back(value); }

    void pop() { c_.pop_back(); }

    template <class T1, class C1>
    friend bool operator==(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);

    template <class T1, class C1>
    friend bool operator<(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);
};

// Non mamber function
template <class T1, class C1>
bool operator==(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs)
{
    return lhs.c_ == rhs.c_;
}

template <class T1, class C1>
bool operator!=(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs)
{
    return !(lhs == rhs);
}

template <class T1, class C1>
bool operator<(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs)
{
    return lhs.c_ < rhs.c_;
}

template <class T1, class C1>
bool operator<=(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs)
{
    return !(lhs > rhs);
}

template <class T1, class C1>
bool operator>(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs)
{
    return rhs < lhs;
}

template <class T1, class C1>
bool operator>=(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs)
{
    return !(lhs < rhs);
}
} // namespace ft

#endif // STACK_HPP
