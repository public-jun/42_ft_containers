#ifndef STACK_HPP
#define STACK_HPP

#include <vector.hpp>

namespace ft {
template <class Tp, class Container = ft::vector<Tp> >
class stack
{
public:
    // Member type
    typedef Container                                container_type;
    typedef typename container_type::value_type      value_type;
    typedef typename container_type::reference       reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::size_type       size_type;

protected:
    container_type c;

public:
    // Member function
    explicit stack(const container_type& cont = Container()) : c(cont) {}
    stack(const stack& other) : c(other.c) {}
    ~stack() {}
    stack& operator=(const stack& other)
    {
        c = other.c;
        return *this;
    }

    reference       top() { return c.back(); }
    const_reference top() const { return c.back(); }

    bool empty() const { return c.empty(); }

    size_type size() const { return c.size(); }

    void push(const value_type& value) { c.push_back(value); }

    void pop() { c.pop_back(); }

    template <class T1, class C1>
    friend bool operator==(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);

    template <class T1, class C1>
    friend bool operator<(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);
};

// Non mamber function
template <class T1, class C1>
bool operator==(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs)
{
    return lhs.c == rhs.c;
}

template <class T1, class C1>
bool operator!=(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs)
{
    return !(lhs == rhs);
}

template <class T1, class C1>
bool operator<(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs)
{
    return lhs.c < rhs.c;
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
