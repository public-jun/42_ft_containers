#ifndef TREE_HPP
#define TREE_HPP

namespace ft {

template <class _VoidPtr>
class __tree_node_base_types
{
    typedef _VoidPtr                             __void_pointer;

    typedef __tree_node_base<__void_pointer>     __node_base_type;
    typedef __node_base_type*                    __node_base_pointer;

    typedef __tree_end_node<__node_base_pointer> __end_node_type;
    typedef __end_node_type*                     __end_node_pointer;

    typedef __end_node_pointer                   __parent_pointer;
};

template <class _Pointer>
class __tree_end_node
{
public:
    typedef _Pointer pointer;
    pointer          __left_;

    __tree_end_node() : __left_() {}
};

template <class _VoidPtr>
class __tree_node_base
    : public __tree_node_base_types<_VoidPtr>::__end_node_type
{
    typedef __tree_node_base_types<_VoidPtr> _NodeBaseTypes;

public:
    typedef typename _NodeBaseTypes::__node_base_pointer pointer;
    typedef typename _NodeBaseTypes::__parent_pointer    __parent_pointer;

    pointer                                              __right_;
    __parent_pointer                                     __parent_;
    bool                                                 __is_black_;

    pointer __parent_unsafe() const { return static_cast<pointer>(__parent_); }

    void    __set_parent(pointer p)
    {
        __parent_ = static_cast<__parent_pointer>(p);
    }

private:
    ~__tree_node_base() {}
    __tree_node_base(const __tree_node_base&) {}
    __tree_node_base& operator=(const __tree_node_base&) { return *this; }
};

template <class _Tp, class _VoidPtr>
class __tree_node : public __tree_node_base<_VoidPtr>
{
public:
    typedef _Tp       __node_value_type;

    __node_value_type __value;

private:
    ~__tree_node() {}
    __tree_node(const __tree_node&) {}
    __tree_node& operator=(const __tree_node&) { return *this; }
};

template <class _Tp, class _Compare, class _Allocator>
class __tree
{
public:
    typedef _Tp        value_type;
    typedef _Compare   value_compare;
    typedef _Allocator allocator_type;
};
} // namespace ft

#endif
