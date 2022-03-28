#ifndef MAP_HPP
#define MAP_HPP

#include <algorithm.hpp>
#include <pair.hpp>
#include <tree.hpp>

#include <functional>
#include <memory>

namespace ft {
template <class _Key, class _CP, class _Compare>
class map_value_compare : private _Compare
{
    _Compare comp_;

public:
    map_value_compare() : comp_() {}
    map_value_compare(_Compare c) : comp_(c) {}
    const _Compare& key_comp() const { return comp_; }
    bool            operator()(const _CP& x, const _CP& y) const
    {
        return comp_(x.first, y.first);
    }
    bool operator()(const _CP& x, const _Key& y) const
    {
        return comp_(x.first, y);
    }
    bool operator()(const _Key& x, const _CP& y) const
    {
        return comp_(x, y.first);
    }
    void swap(map_value_compare& y) { std::swap(comp_, y.comp_); }
};

template <class _Key, class _Tp, class _Compare = std::less<_Key>,
          class _Allocator = std::allocator<ft::pair<const _Key, _Tp> > >
class map
{
public:
    typedef _Key                                  key_type;
    typedef _Tp                                   mapped_type;
    typedef ft::pair<const key_type, mapped_type> value_type;
    typedef _Compare                              key_compare;
    typedef _Allocator                            allocator_type;
    typedef value_type&                           reference;
    typedef const value_type&                     const_reference;

public:
    class value_compare : std::binary_function<value_type, value_type, bool>
    {
        friend class map;

    public:
        typedef bool       result_type;
        typedef value_type first_argument_type;
        typedef value_type second_argument_type;

        bool operator()(const value_type& lhs, const value_type& rhs) const
        {
            return comp(lhs.first, rhs.first);
        }

    protected:
        key_compare comp;
        value_compare(key_compare c) : comp(c) {}
    };

private:
    typedef map_value_compare<key_type, value_type, key_compare> vc;
    typedef rb_tree<value_type, vc, allocator_type>              base;
    base                                                         tree_;

public:
    // many of these are specified differently in ISO, but the following are
    // "functionally equivalent"
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename base::iterator                  iterator;
    typedef typename base::const_iterator            const_iterator;
    typedef typename base::reverse_iterator          reverse_iterator;
    typedef typename base::const_reverse_iterator    const_reverse_iterator;

    map() : tree_(vc(key_compare())) {}

    explicit map(const _Compare& comp, const _Allocator& alloc = _Allocator())
        : tree_(vc(comp), alloc)
    {}

    template <class _InputIterator>
    map(_InputIterator first, _InputIterator last,
        const key_compare&    comp  = key_compare(),
        const allocator_type& alloc = allocator_type())
        : tree_(vc(comp), alloc)
    {
        insert(first, last);
    }

    map(const map& other) : tree_(other.tree_) {}

    map& operator=(const map& other)
    {
        if (this != &other)
        {
            clear();
            tree_.value_comp()     = other.tree_.value_comp();
            tree_.node_allocator() = other.tree_.node_allocator();
            insert(other.begin(), other.end());
        }
        return *this;
    }

    ~map() {}

    allocator_type get_allocator() const throw()
    {
        return allocator_type(tree_.alloc());
    }

    // Element access
    // Returns a reference to the value that is mapped to a key equivalent to
    // key, performing an insertion if such key does not already exist.
    mapped_type& operator[](const key_type& key)
    {
        return insert(ft::make_pair(key, mapped_type())).first->second;
    }

    iterator               begin() { return tree_.begin(); }
    const_iterator         begin() const { return tree_.begin(); }
    iterator               end() { return tree_.end(); }
    const_iterator         end() const { return tree_.end(); }
    reverse_iterator       rbegin() { return tree_.rbegin(); }
    const_reverse_iterator rbegin() const { return tree_.rbegin(); }
    reverse_iterator       rend() { return tree_.rend(); }
    const_reverse_iterator rend() const { return tree_.rend(); }

    bool      empty() { return tree_.size() == 0; }
    size_type size() const { return tree_.size(); }
    size_type max_size() const { return tree_.max_size(); }

    // Modifiers
    void clear() { tree_.clear(); }

    ft::pair<iterator, bool> insert(const value_type& v)
    {
        return tree_.insert(v);
    }

    template <class InputIt>
    void insert(InputIt first, InputIt last)
    {
        tree_.insert(first, last);
    }

    void swap(map& other) { tree_.swap(other.tree_); }

    // Lookup
    size_type count(const key_type& key) const { return tree_.count(key); }

    iterator find(const key_type& key) { return tree_.find(key); }

    const_iterator find(const key_type& key) const { return tree_.find(key); }

    ft::pair<iterator, iterator> equal_range(const key_type& key)
    {
        return tree_.equal_range(key);
    }

    ft::pair<const_iterator, const_iterator>
    equal_range(const key_type& key) const
    {
        return tree_.equal_range(key);
    }

    iterator lower_bound(const key_type& key) { return tree_.lower_bound(key); }

    const_iterator lower_bound(const key_type& key) const
    {
        return tree_.lower_bound(key);
    }

    iterator upper_bound(const key_type& key) { return tree_.upper_bound(key); }

    const_iterator upper_bound(const key_type& key) const
    {
        return tree_.upper_bound(key);
    }

    // Observes
    key_compare key_comp() const { return tree_.value_comp().key_comp(); }

    value_compare value_comp() const
    {
        return value_compare(tree_.value_comp().key_comp());
    }
};

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline bool operator==(const ft::map<_Key, _Tp, _Compare, _Allocator>& lhs,
                       const ft::map<_Key, _Tp, _Compare, _Allocator>& rhs)
{
    return lhs.size() == rhs.size() &&
           ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline bool operator!=(const ft::map<_Key, _Tp, _Compare, _Allocator>& lhs,
                       const ft::map<_Key, _Tp, _Compare, _Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline bool operator<(const ft::map<_Key, _Tp, _Compare, _Allocator>& lhs,
                      const ft::map<_Key, _Tp, _Compare, _Allocator>& rhs)
{
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                       rhs.end());
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline bool operator<=(const ft::map<_Key, _Tp, _Compare, _Allocator>& lhs,
                       const ft::map<_Key, _Tp, _Compare, _Allocator>& rhs)
{
    return !(lhs > rhs);
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline bool operator>(const ft::map<_Key, _Tp, _Compare, _Allocator>& lhs,
                      const ft::map<_Key, _Tp, _Compare, _Allocator>& rhs)
{
    return rhs < lhs;
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline bool operator>=(const ft::map<_Key, _Tp, _Compare, _Allocator>& lhs,
                       const ft::map<_Key, _Tp, _Compare, _Allocator>& rhs)
{
    return !(lhs < rhs);
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline void swap(ft::map<_Key, _Tp, _Compare, _Allocator>& lhs,
                 ft::map<_Key, _Tp, _Compare, _Allocator>& rhs)
{
    lhs.swap(rhs);
}
} // namespace ft
#endif
