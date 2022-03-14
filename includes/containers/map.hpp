#ifndef MAP_HPP
#define MAP_HPP

#include <pair.hpp>

#include <functional>
#include <memory>

namespace ft {
template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<std::pair<const Key, T> > >
class map
{
public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef ft::pair<const key_type, mapped_type> value_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;

public:
    class value_compare : std::binary_function<value_type, value_type, bool>
    {
        friend class map;

    public:
        typedef bool result_type;
        typedef value_type first_argument_type;
        typedef value_type second_argument_type;

        bool operator()(const value_type& lhs, const value_type& rhs) const
        {
            return comp(lhs.first, rhs.first);
        }

    protected:
        Compare comp;
        value_compare(Compare c) : comp(c) {}
    };

private:
    typedef rb_tree<key_type, value_type, key_compare, allocator_type> Rep_type;

    Rep_type M_t_;

public:
    // many of these are specified differently in ISO, but the following are
    // "functionally equivalent"
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef typename Allocator::reference reference;
    typedef typename Allocator::const_reference const_reference;
    typedef typename Rep_type::iterator iterator;
    typedef typename Rep_type::const_iterator const_iterator;
    typedef typename Rep_type::size_type size_type;
    typedef typename Rep_type::difference_type difference_type;
    typedef typename Rep_type::reverse_iterator reverse_iterator;
    typedef typename Rep_type::const_reverse_iterator const_reverse_iterator;

    map() : M_t_() {}

};
} // namespace ft
#endif
