#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm.hpp>
#include <reverse_iterator.hpp>
#include <type_traits.hpp>
#include <wrap_iter.hpp>

#include <algorithm> // std::min
#include <iterator>
#include <limits>    // std::numeric_limits
#include <memory>    // std::uninitialized_fill_n std::uninitialized_copy
#include <stdexcept> // std::length_error, std::out_of_range

namespace ft {

template <typename T, typename Allocator = std::allocator<T> >
class vector
{
public:
    // Member type
    typedef T                                    value_type;
    typedef Allocator                            allocator_type;
    typedef std::size_t                          size_type;
    typedef std::ptrdiff_t                       difference_type;
    typedef value_type&                          reference;
    typedef const value_type&                    const_reference;
    typedef typename Allocator::pointer          pointer;
    typedef typename Allocator::const_pointer    const_pointer;
    typedef wrap_iter<pointer>                   iterator;
    typedef wrap_iter<const_pointer>             const_iterator;
    typedef ft::reverse_iterator<iterator>       reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    // Member functions
    vector()
        : first_(NULL), last_(NULL), capacity_last_(NULL),
          alloc_(allocator_type())
    {}

    explicit vector(const allocator_type& alloc)
        : first_(NULL), last_(NULL), capacity_last_(NULL), alloc_(alloc)
    {}

    vector(size_type count, const T& value = T(),
           const allocator_type& alloc = allocator_type())
        : first_(NULL), last_(NULL), capacity_last_(NULL), alloc_(alloc)
    {
        resize(count, value);
    }

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last,
           const Allocator& allocator                   = Allocator(),
           typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                  InputIterator>::type* = NULL)
        : first_(NULL), last_(NULL), capacity_last_(NULL), alloc_(allocator)
    {
        __range_initialize(
            first, last,
            typename iterator_traits<InputIterator>::iterator_category());
    }

    vector(const vector& r)
        : first_(NULL), last_(NULL), capacity_last_(NULL), alloc_(r.alloc_)
    {
        reserve(r.size());
        pointer dest = first_;
        for (const_iterator src = r.begin(), last = r.end(); src != last;
             ++dest, ++src)
        {
            __construct(dest, *src);
        }
        last_ = first_ + r.size();
    }

    vector& operator=(const vector& r)
    {
        if (this == &r)
            return *this;
        if (size() == r.size())
        {
            std::copy(r.begin(), r.end(), begin());
        }
        else if (capacity() >= r.size())
        {
            std::copy(r.begin(), r.begin() + r.size(), begin());
            last_ = first_ + r.size();
        }
        else
        {
            __destroy_until(rend()); // destroy_all()
            reserve(r.size());
            pointer dest_pointer = first_;
            for (const_iterator src_iter = r.begin(), src_end = r.end();
                 src_iter != src_end; ++src_iter, ++dest_pointer, ++last_)
            {
                __construct(dest_pointer, *src_iter);
            }
        }
        return *this;
    }

    ~vector()
    {
        clear();
        __deallocate();
    }

    void assign(size_type n, const T& value)
    {
        if (capacity() >= n)
        {
            size_type sz = size();
            if (size() > n)
                __destroy_until(rbegin() + (sz - n));
            std::fill_n(first_, n, value);
        }
        else
        {
            clear();
            __deallocate();
            __allocate(n);
            std::uninitialized_fill_n(first_, n, value);
        }
        last_ = first_ + n;
    }

    template <class InputIterator>
    void assign(InputIterator first, InputIterator last,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                       InputIterator>::type* = NULL)
    {
        size_type new_size = static_cast<size_type>(std::distance(first, last));
        if (new_size <= capacity())
        {
            InputIterator mid = last;
            if (new_size > size())
            {
                mid = first;
                std::advance(mid, size());
                std::copy(first, mid, begin());
                for (InputIterator it = mid; it != last; ++it)
                    __construct(last_++, *it);
            }
            else
            {
                std::copy(first, mid, begin());
                difference_type diff = size() - new_size;
                __destroy_until(rbegin() + diff);
            }
        }
        else
        {
            clear();
            __deallocate();
            __allocate(new_size);
            for (InputIterator it = first; it != last; ++it)
                __construct(last_++, *it);
        }
    }

    allocator_type get_allocator() const { return (allocator_type(alloc_)); }

    size_type max_size() const
    {
        return std::min<size_type>(alloc_.max_size(),
                                   std::numeric_limits<difference_type>::max());
    }

    size_type size() const { return end() - begin(); }
    bool      empty() const { return begin() == end(); }
    size_type capacity() const { return capacity_last_ - first_; }

    reference       operator[](size_type i) { return first_[i]; }
    const_reference operator[](size_type i) const { return first_[i]; }
    reference       at(size_type i)
    {
        if (i >= size())
            __throw_out_of_range();
        return first_[i];
    }
    const_reference at(size_type i) const
    {
        if (i >= size())
            __throw_out_of_range();
        return first_[i];
    }
    reference       front() { return *first_; }
    const_reference front() const { return *first_; }
    reference       back() { return *(last_ - 1); }
    const_reference back() const { return *(last_ - 1); }

    iterator               begin() { return iterator(first_); }
    iterator               end() { return iterator(last_); }
    const_iterator         begin() const { return const_iterator(first_); }
    const_iterator         end() const { return const_iterator(last_); }
    reverse_iterator       rbegin() { return reverse_iterator(end()); }
    reverse_iterator       rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(begin());
    }
    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(end());
    }

    void clear() { __destroy_until(rend()); }

    iterator insert(iterator pos, const_reference value)
    {
        difference_type diff = pos - begin();
        insert(pos, 1, value);
        pointer p_pos = first_ + diff;
        return iterator(p_pos);
    }

    void insert(iterator pos, size_type count, const_reference value)
    {
        difference_type offset   = pos - begin();
        size_type       new_size = size() + count;

        if (count > 0)
        {
            if (new_size >= capacity())
            {
                __extend_capacity(count);
            }

            pointer p_pos    = first_ + offset;
            pointer old_last = last_;

            size_type after_pos_size = static_cast<size_type>(last_ - p_pos);
            size_type left_count     = count;

            __move_range(p_pos, old_last, count);
            if (count > after_pos_size)
            {
                size_type unini_size = count - after_pos_size;
                std::uninitialized_fill_n(old_last, unini_size, value);
                left_count -= unini_size;
            }
            if (left_count > 0)
            {
                std::fill_n(p_pos, left_count, value);
            }
            last_ += count;
        }
    }

    template <class InputIterator>
    typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                           void>::type // void
    insert(iterator pos, InputIterator first, InputIterator last)
    {
        __range_insert(
            pos, first, last,
            typename iterator_traits<InputIterator>::iterator_category());
    }

    iterator erase(iterator pos)
    {
        if (pos != end())
        {
            std::copy(pos + 1, end(), pos);
            --last_;
            __destroy(last_);
        }
        return (pos);
    }

    iterator erase(iterator first, iterator last)
    {
        difference_type erase_size = std::distance(first, last);
        if (first != last)
        {
            if (last != end())
                std::copy(last, end(), first);
            __destroy_until(rbegin() + erase_size);
        }
        return first;
    }

    void reserve(size_type sz)
    {
        if (sz <= capacity())
            return;
        if (sz > max_size())
            __throw_length_error();
        pointer   old_first    = first_;
        pointer   old_last     = last_;
        size_type old_capacity = capacity();
        __allocate(sz);
        for (pointer old_iter = old_first; old_iter != old_last;
             ++old_iter, ++last_)
        {
            __construct(last_, *old_iter);
        }
        for (pointer riter = old_first; riter != old_last; ++riter)
        {
            __destroy(riter);
        }
        alloc_.deallocate(old_first, old_capacity);
    }

    void push_back(const_reference value)
    {
        __extend_capacity(1);
        __construct(last_, value);
        ++last_;
    }

    void pop_back() { __destroy_until(rbegin() + 1); }

    void resize(size_type count, value_type value = value_type())
    {
        if (count < size())
        {
            erase(end() - (size() - count), end());
        }
        else if (count > size())
        {
            insert(end(), count - size(), value);
        }
    }

    void swap(vector& other)
    {
        std::swap(first_, other.first_);
        std::swap(last_, other.last_);
        std::swap(capacity_last_, other.capacity_last_);
    }

private:
    pointer        first_;
    pointer        last_;
    pointer        capacity_last_;
    allocator_type alloc_;

private:
    void __throw_out_of_range() const { throw std::out_of_range("vector"); }
    void __throw_length_error() const { throw std::length_error("vector"); }

    void __allocate(size_type n)
    {
        first_         = alloc_.allocate(n);
        last_          = first_;
        capacity_last_ = last_ + n;
    }
    void __deallocate() { alloc_.deallocate(first_, capacity()); }

    void __construct(pointer ptr) { alloc_.construct(ptr, 0); }
    void __construct(pointer ptr, const_reference value)
    {
        alloc_.construct(ptr, value);
    }
    void __destroy(pointer ptr) { alloc_.destroy(ptr); }
    void __destroy_until(reverse_iterator rend)
    {
        for (reverse_iterator riter = rbegin(); riter != rend; ++riter, --last_)
        {
            __destroy(&*riter);
        }
    }

    template <class _InputIterator>
    void __range_initialize(_InputIterator first, _InputIterator last,
                            std::input_iterator_tag)
    {
        for (; first != last; ++first)
        {
            push_back(*first);
        }
    }

    template <class _ForwardIterator>
    void __range_initialize(_ForwardIterator first, _ForwardIterator last,
                            std::forward_iterator_tag)
    {
        reserve(std::distance(first, last));
        for (_ForwardIterator i = first; i != last; ++i)
        {
            push_back(*i);
        }
    }

    //  Precondition:  __new_size > capacity()
    size_type __calc_new_size(size_type new_size) const
    {
        const size_type ms = max_size();
        if (new_size > ms)
            throw std::length_error("too long new_size");
        const size_type cap = capacity();
        if (cap >= ms / 2)
            return ms;
        return std::max<size_type>(2 * cap, new_size);
    }

    void __extend_capacity(size_type amount_of_increase)
    {
        size_type want_size = size() + amount_of_increase;

        if (want_size > capacity())
        {
            size_type new_size = __calc_new_size(want_size);
            reserve(new_size);
        }
    }

    template <class _InputIterator>
    typename ft::enable_if<!ft::is_integral<_InputIterator>::value,
                           void>::type // void
    __construct_at_end(_InputIterator first, _InputIterator last)
    {
        std::uninitialized_copy(first, last, end());
    }

    void __move_range(pointer from_s, pointer from_e, size_type amount_move)
    {
        difference_type range_size = from_e - from_s;
        pointer         old_tail   = from_e - 1;
        pointer         new_tail   = old_tail + amount_move;
        pointer         tmp_p      = new_tail;

        if (from_s != last_)
        {
            for (size_type i = 0; i < static_cast<size_type>(range_size);
                 ++i, --tmp_p)
            {
                if (tmp_p >= from_e)
                {
                    __construct(tmp_p, *(old_tail - i));
                }
                else
                {
                    *tmp_p = *(old_tail - i);
                }
            }
        }
    }

    template <class _InputIterator>
    void __range_insert(iterator pos, _InputIterator first, _InputIterator last,
                        std::input_iterator_tag)
    {
        if (pos == end())
        {
            for (; first != last; ++first)
            {
                insert(end(), *first);
            }
        }
        if (first != last)
        {
            vector tmp_v(first, last, get_allocator());
            insert(pos, tmp_v.begin(), tmp_v.end());
        }
    }

    template <class _ForwardIterator>
    void __range_insert(iterator pos, _ForwardIterator first_it,
                        _ForwardIterator last_it, std::forward_iterator_tag)
    {
        difference_type offset      = pos - begin();
        difference_type insert_size = std::distance(first_it, last_it);

        if (insert_size > 0)
        {
            if (insert_size > capacity_last_ - last_)
            {
                __extend_capacity(insert_size);
            }

            pointer p_pos    = first_ + offset;
            pointer old_last = last_;

            difference_type  after_pos_size   = last_ - p_pos;
            size_type        left_insert_size = insert_size;
            _ForwardIterator m_it             = last_it;

            if (insert_size > after_pos_size)
            {
                m_it = first_it;
                std::advance(m_it, after_pos_size);
                __construct_at_end(m_it, last_it);
                left_insert_size = after_pos_size;
            }
            if (left_insert_size > 0)
            {
                __move_range(p_pos, old_last, insert_size);
                std::copy(first_it, m_it, p_pos);
            }
            last_ += insert_size;
        }
    }
};

// Non Member functions
template <class _Tp, class _Allocator>
bool operator==(const ft::vector<_Tp, _Allocator>& __lhs,
                const ft::vector<_Tp, _Allocator>& __rhs)
{
    return __lhs.size() == __rhs.size() &&
           ft::equal(__lhs.begin(), __lhs.end(), __rhs.begin());
}

template <class _Tp, class _Allocator>
bool operator!=(const ft::vector<_Tp, _Allocator>& __lhs,
                const ft::vector<_Tp, _Allocator>& __rhs)
{
    return !(__lhs == __rhs);
}

template <class _Tp, class _Allocator>
bool operator<(const ft::vector<_Tp, _Allocator>& __lhs,
               const ft::vector<_Tp, _Allocator>& __rhs)
{
    return ft::lexicographical_compare(__lhs.begin(), __lhs.end(),
                                       __rhs.begin(), __rhs.end());
}

template <class _Tp, class _Allocator>
bool operator<=(const ft::vector<_Tp, _Allocator>& __lhs,
                const ft::vector<_Tp, _Allocator>& __rhs)
{
    return !(__lhs > __rhs);
}

template <class _Tp, class _Allocator>
bool operator>(const ft::vector<_Tp, _Allocator>& __lhs,
               const ft::vector<_Tp, _Allocator>& __rhs)
{
    return __rhs < __lhs;
}

template <class _Tp, class _Allocator>
bool operator>=(const ft::vector<_Tp, _Allocator>& __lhs,
                const ft::vector<_Tp, _Allocator>& __rhs)
{
    return !(__lhs < __rhs);
}

template <class _Tp, class _Allocator>
void swap(ft::vector<_Tp, _Allocator>& __lhs,
          ft::vector<_Tp, _Allocator>& __rhs)
{
    __lhs.swap(__rhs);
}
} // namespace ft

#endif
