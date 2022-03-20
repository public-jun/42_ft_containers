#ifndef TREE_HPP
#define TREE_HPP

#include <pair.hpp>

#include <cstddef>
#include <iterator>

namespace ft {

// node
enum r_b_color { kRed = false, kBlack = true };

template <class _Tp>
struct tree_key_value_types {
    typedef _Tp key_type;
};

template <class _Key, class _Tp>
struct tree_key_value_types<pair<_Key, _Tp> > {
    typedef _Key key_type;
};

template <class _Tp>
class tree_node
{
public:
    typedef _Tp                                          node_value_type;
    typedef typename tree_key_value_types<_Tp>::key_type key_type;
    typedef tree_node<node_value_type>                   node_type;
    typedef node_type*                                   node_pointer;

    node_pointer parent;
    node_pointer left;
    node_pointer right;

    bool            color;
    node_value_type value;

    tree_node() : parent(NULL), left(NULL), right(NULL), color(kBlack) {}
    tree_node(node_pointer nil, node_value_type v)
        : parent(nil), left(nil), right(nil), color(kRed), value(v)
    {}
    tree_node(node_value_type v)
        : parent(NULL), left(NULL), right(NULL), color(kRed), value(v)
    {}
};

template <class _Tp>
class tree_iterator
{
public:
    typedef _Tp                             value_type;
    typedef _Tp&                            reference;
    typedef _Tp*                            pointer;
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t                       difference_type;

private:
    typedef tree_iterator<_Tp> self_type;
    typedef tree_node<_Tp>*    node_pointer;

    node_pointer ptr_;
    node_pointer nil_;

public:
    node_pointer base() const { return ptr_; }

    tree_iterator() : ptr_(NULL) {}

    explicit tree_iterator(node_pointer x, node_pointer nil)
        : ptr_(x), nil_(nil)
    {}

    tree_iterator(const tree_iterator& other)
        : ptr_(other.ptr_), nil_(other.nil_)
    {}

    tree_iterator& operator=(const tree_iterator& other)
    {
        if (this != &other)
        {
            ptr_ = other.base();
            nil_ = other.nil_;
        }
        return *this;
    }

    ~tree_iterator() {}

    reference operator*() const { return ptr_->value; }

    pointer operator->() const { return &ptr_->value; }

    tree_iterator& operator++()
    {
        // ptr_ = tree_next_;
    }
};

template <class _Tp, class _Compare, class _Allocator>
class __tree
{
public:
    typedef _Tp               value_type;
    typedef value_type*       pointer;
    typedef const value_type* const_pointer;
    typedef value_type&       reference;
    typedef const value_type& const_reference;

    typedef tree_node<value_type>        node_type;
    typedef typename node_type::key_type key_type;
    typedef node_type*                   node_pointer;
    typedef const node_pointer           const_node_pointer;

    typedef _Compare value_compare;

    typedef _Allocator allocator_type;
    typedef typename allocator_type::template rebind<node_type>::other
                                                          node_allocator_type;
    typedef typename node_allocator_type::size_type       size_type;
    typedef typename node_allocator_type::difference_type difference_type;

    typedef tree_iterator<value_type> iterator;
    // typedef tree_const_iterator<value_type> const_iterator;
    // typedef ft::reverse_iterator<iterator>  reverse_iterator;
    // typedef ft::reverse_iterator<const_iterator>  const_reverse_iterator;

private:
    node_pointer nil_;
    node_pointer begin_;
    node_pointer end_;

    node_allocator_type node_alloc;
    size_type           size_;
    value_compare       comp_;
};
} // namespace ft

#endif
