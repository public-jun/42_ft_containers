#ifndef SET_HPP
#define SET_HPP

#include <algorithm.hpp>
#include <pair.hpp>
#include <tree.hpp>

#include <functional>
#include <memory>

namespace ft {
template <class _Key, class _Compare = std::less<_Key>,
          class _Allocator = std::allocator<_Key> >
class set
{
public:
    typedef _Key              key_type;
    typedef key_type          value_type;
    typedef _Compare          key_compare;
    typedef key_compare       value_compare;
    typedef _Allocator        allocator_type;
    typedef value_type&       reference;
    typedef const value_type& const_reference;

private:
    typedef rb_tree<value_type, value_compare, allocator_type> base;

    base tree_;

public:
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename base::iterator                  iterator;
    typedef typename base::const_iterator            const_iterator;
    typedef typename base::reverse_iterator          reverse_iterator;
    typedef typename base::const_reverse_iterator    const_reverse_iterator;

    // Member functions
    set() : tree_() {}

    explicit set(const value_compare&  comp,
                 const allocator_type& alloc = allocator_type())
        : tree_(comp, alloc)
    {}

    template <class _InputIterator>
    set(_InputIterator first, _InputIterator last,
        const value_compare&  comp  = value_compare(),
        const allocator_type& alloc = allocator_type())
        : tree_(comp, alloc)
    {
        insert(first, last);
    }

    set(const set& other) : tree_(other.tree_) {}

    set& operator=(const set& other)
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

    ~set() {}

    allocator_type get_allocator() const throw()
    {
        return allocator_type(tree_.alloc());
    }

    // Iterators
    iterator               begin() { return tree_.begin(); }
    const_iterator         begin() const { return tree_.begin(); }
    iterator               end() { return tree_.end(); }
    const_iterator         end() const { return tree_.end(); }
    reverse_iterator       rbegin() { return tree_.rbegin(); }
    const_reverse_iterator rbegin() const { return tree_.rbegin(); }
    reverse_iterator       rend() { return tree_.rend(); }
    const_reverse_iterator rend() const { return tree_.rend(); }

    // Capacity
    bool      empty() const { return tree_.size() == 0; }
    size_type size() const { return tree_.size(); }
    size_type max_size() const { return tree_.max_size(); }

    // Modifieres
    void clear() { tree_.clear(); }

    ft::pair<iterator, bool> insert(const value_type& value)
    {
        return tree_.insert(value);
    }

    iterator insert(iterator hint, const value_type& value)
    {
        return tree_.insert(hint, value);
    }

    template <class InputIt>
    void insert(InputIt first, InputIt last)
    {
        tree_.insert(first, last);
    }

    void erase(iterator pos) { tree_.erase(pos); }

    void erase(iterator first, iterator last) { tree_.erase(first, last); }

    size_type erase(const key_type& key) { return tree_.erase(key); }

    void swap(set& other) { tree_.swap(other.tree_); }

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

    // Observers
    key_compare key_comp() const { return tree_.value_comp(); }

    value_compare value_comp() const { return tree_.value_comp(); }
};

// Non-member functions
template <class _Key, class _Compare, class _Allocator>
inline bool operator==(const ft::set<_Key, _Compare, _Allocator>& lhs,
                       const ft::set<_Key, _Compare, _Allocator>& rhs)
{
    return lhs.size() == rhs.size() &&
           ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class _Key, class _Compare, class _Allocator>
inline bool operator!=(const ft::set<_Key, _Compare, _Allocator>& lhs,
                       const ft::set<_Key, _Compare, _Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <class _Key, class _Compare, class _Allocator>
inline bool operator<(const ft::set<_Key, _Compare, _Allocator>& lhs,
                      const ft::set<_Key, _Compare, _Allocator>& rhs)
{
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                       rhs.end());
}

template <class _Key, class _Compare, class _Allocator>
inline bool operator<=(const ft::set<_Key, _Compare, _Allocator>& lhs,
                       const ft::set<_Key, _Compare, _Allocator>& rhs)
{
    return !(lhs > rhs);
}

template <class _Key, class _Compare, class _Allocator>
inline bool operator>(const ft::set<_Key, _Compare, _Allocator>& lhs,
                      const ft::set<_Key, _Compare, _Allocator>& rhs)
{
    return rhs < lhs;
}

template <class _Key, class _Compare, class _Allocator>
inline bool operator>=(const ft::set<_Key, _Compare, _Allocator>& lhs,
                       const ft::set<_Key, _Compare, _Allocator>& rhs)
{
    return !(lhs < rhs);
}

template <class _Key, class _Compare, class _Allocator>
inline void swap(ft::set<_Key, _Compare, _Allocator>& lhs,
                 ft::set<_Key, _Compare, _Allocator>& rhs)
{
    lhs.swap(rhs);
}
} // namespace ft

#endif
