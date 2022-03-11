#ifndef STACK_HPP
#define STACK_HPP

#include <vector.hpp>

namespace ft {
template <class Tp, class Container = ft::vector<Tp> >
class stack
{
public:
    typedef Container container_type;
    typedef typename container_type::value_type value_type;
    typedef typename container_type::reference reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::size_type size_type;

protected:
    container_type c;
};
} // namespace ft

#endif // STACK_HPP
