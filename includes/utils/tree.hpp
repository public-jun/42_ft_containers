#ifndef TREE_HPP
#define TREE_HPP

#include <pair.hpp>
#include <tree_utils.hpp>

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
        ptr_ = tree_next(ptr_, nil_);
        return *this;
    }

    tree_iterator operator++(int)
    {
        tree_iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    tree_iterator& operator--()
    {
        ptr_ = tree_prev(ptr_, nil_);
        return *this;
    }

    tree_iterator operator--(int)
    {
        tree_iterator tmp(*this);
        --(*this);
        return tmp;
    }

    friend bool operator==(const tree_iterator& lhs, const tree_iterator& rhs)
    {
        return lhs.ptr_ == rhs.ptr_;
    }

    friend bool operator!=(const tree_iterator& lhs, const tree_iterator& rhs)
    {
        return !(lhs == rhs);
    }
};

template <class _Tp, class _Compare, class _Allocator>
class rb_tree
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

public:
    rb_tree()
    {
        size_      = 0;
        comp_      = value_compare();
        node_alloc = node_allocator_type();
        initialize_node();
    }

    rb_tree(const value_compare&  comp,
            const allocator_type& alloc = allocator_type())
    {
        size_ = 0;
        comp_ = comp;
        node_alloc(node_allocator_type(alloc));
        initialize_node();
    }

    iterator begin() { return iterator(begin_, nil_); }
    iterator end() { return iterator(end_, nil_); }

    // private:
    node_pointer nil_;
    node_pointer begin_;
    node_pointer end_;

    node_allocator_type node_alloc;
    size_type           size_;
    value_compare       comp_;

private:
    // node を作成する
    void initialize_node()
    {
        nil_ = node_alloc.allocate(1);
        node_alloc.construct(nil_);
        nil_->left = nil_;
        nil_->right = nil_;

        end_ = node_alloc.allocate(1);
        node_alloc.construct(end_);
        end_->left = nil_;
        begin_ = end_;
    }

public:
    node_pointer create_node(const value_type& value)
    {
        node_pointer new_node = node_alloc.allocate(1);
        node_alloc.construct(new_node, value);
        new_node->parent = nil_;
        new_node->left   = nil_;
        new_node->right  = nil_;
        return new_node;
    }

    void destroy(node_pointer node)
    {
        if (node != nil_)
        {
            destroy(node->left);
            destroy(node->right);
            delete_node(node);
        }
    }

    void delete_node(node_pointer node)
    {
        node_alloc.destroy(node);
        node_alloc.deallocate(node, 1);
    }

    // void clear()
    void clear(node_pointer node)
    {
        // destroy(root);
        destroy(node);
        size_      = 0;
        begin_     = end_;
        end_->left = NULL;
    }
};
} // namespace ft

#endif
