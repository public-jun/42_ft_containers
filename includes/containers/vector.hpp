#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <reverse_iterator.hpp>
#include <utils.hpp>
#include <wrap_iter.hpp>
#include <algorithm.hpp>

#include <algorithm> // std::min
#include <iostream>
#include <iterator>
#include <limits>    // std::numeric_limits
#include <memory>    // std::uninitialized_fill_n std::uninitialized_copy
#include <stdexcept> // std::length_error, std::out_of_range

template <class T>
void debug(T& V)
{
    std::cout << "size:" << V.size() << " capacity:" << V.capacity()
              << std::endl;
    std::cout << "{ ";
    for (typename T::iterator it = V.begin(); it != V.end(); ++it)
        std::cout << *it << " ";
    std::cout << "}" << std::endl;
}

namespace ft {

template <typename T, typename Allocator = std::allocator<T> >
class vector
{
public:
    /*
    ** Member type
    */
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef wrap_iter<pointer> iterator;
    typedef wrap_iter<const_pointer> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    /*
    ** Member functions
    */
    vector()
        : first_(NULL), last_(NULL), capacity_last_(NULL),
          alloc_(allocator_type())
    {}

    explicit vector(const allocator_type& __alloc)
        : first_(NULL), last_(NULL), capacity_last_(NULL), alloc_(__alloc)
    {}

    vector(size_type __count, const T& __value = T(),
           const allocator_type& __alloc = allocator_type())
        : first_(NULL), last_(NULL), capacity_last_(NULL), alloc_(__alloc)
    {
        resize(__count, __value);
    }

    template <typename _InputIterator>
    vector(_InputIterator __first, _InputIterator __last,
           const Allocator& __allocator                   = Allocator(),
           typename ft::enable_if<!ft::is_integral<_InputIterator>::value,
                                  _InputIterator>::type* = NULL)
        : first_(NULL), last_(NULL), capacity_last_(NULL), alloc_(__allocator)
    {
        range_initialize(
            __first, __last,
            typename iterator_traits<_InputIterator>::iterator_category());
    }

    vector(const vector& __r)
        : first_(NULL), last_(NULL), capacity_last_(NULL), alloc_(__r.alloc_)
    {
        reserve(__r.size());
        pointer dest = first_;
        for (const_iterator src = __r.begin(), last = __r.end(); src != last;
             ++dest, ++src)
        {
            construct(dest, *src);
        }
        last_ = first_ + __r.size();
    }

    vector& operator=(const vector& __r)
    {
        if (this == &__r)
            return *this;
        if (size() == __r.size())
        {
            std::copy(__r.begin(), __r.end(), begin());
        }
        else if (capacity() >= __r.size())
        {
            std::copy(__r.begin(), __r.begin() + __r.size(), begin());
            last_ = first_ + __r.size();
        }
        else
        {
            destroy_until(rend()); // destroy_all()
            reserve(__r.size());
            pointer dest_pointer = first_;
            for (const_iterator src_iter = __r.begin(), src_end = __r.end();
                 src_iter != src_end; ++src_iter, ++dest_pointer, ++last_)
            {
                construct(dest_pointer, *src_iter);
            }
        }
        return *this;
    }

    ~vector()
    {
        clear();
        deallocate();
    }

    // assign
    void assign(size_type __n, const T& __value)
    {
        if (capacity() >= __n)
        {
            size_type sz = size();
            if (size() > __n)
                destroy_until(rbegin() + (sz - __n));
            std::fill_n(first_, __n, __value);
        }
        else
        {
            clear();
            deallocate();
            allocate(__n);
            std::uninitialized_fill_n(first_, __n, __value);
        }
        last_ = first_ + __n;
    }

    template <class _InputIterator>
    void assign(_InputIterator __first, _InputIterator __last,
                typename ft::enable_if<!ft::is_integral<_InputIterator>::value,
                                       _InputIterator>::type* = NULL)
    {
        size_type new_size = static_cast<size_type>(std::distance(__first, __last));
        if (new_size <= capacity())
        {
            _InputIterator mid = __last;
            if (new_size > size())
            {
                mid = __first;
                std::advance(mid, size());
                std::copy(__first, mid, begin());
                for (_InputIterator it = mid; it != __last; ++it)
                    construct(last_++, *it);
            }
            else
            {
                std::copy(__first, mid, begin());
                difference_type diff = size() - new_size;
                destroy_until(rbegin() + diff);
            }
        }
        else
        {
            clear();
            deallocate();
            allocate(new_size);
            for (_InputIterator it = __first; it != __last; ++it)
                construct(last_++, *it);
        }
    }

    allocator_type get_allocator() const { return (allocator_type(alloc_)); }

    size_type max_size() const
    {
        return std::min<size_type>(alloc_.max_size(),
                                   std::numeric_limits<difference_type>::max());
    }

    size_type size() const { return end() - begin(); }
    bool empty() const { return begin() == end(); }
    size_type capacity() const { return capacity_last_ - first_; }

    reference operator[](size_type __i) { return first_[__i]; }
    const_reference operator[](size_type __i) const { return first_[__i]; }
    reference at(size_type __i)
    {
        if (__i >= size())
            __throw_out_of_range();
        return first_[__i];
    }
    const_reference at(size_type __i) const
    {
        if (__i >= size())
            __throw_out_of_range();
        return first_[__i];
    }
    reference front() { return *first_; }
    const_reference front() const { return *first_; }
    reference back() { return *(last_ - 1); }
    const_reference back() const { return *(last_ - 1); }

    iterator begin() { return iterator(first_); }
    iterator end() { return iterator(last_); }
    const_iterator begin() const { return const_iterator(first_); }
    const_iterator end() const { return const_iterator(last_); }
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(begin());
    }
    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(end());
    }

    void clear() { destroy_until(rend()); }

    // insert
    iterator insert(iterator __pos, const_reference __value)
    {
        difference_type diff = __pos - begin();
        insert(__pos, 1, __value);
        pointer p_pos = first_ + diff;
        return iterator(p_pos);
    }

    void insert(iterator __pos, size_type __count, const_reference __value)
    {
        difference_type offset = __pos - begin();
        size_type new_size     = size() + __count;

        if (__count > 0)
        {
            if (new_size >= capacity())
            {
                extend_capacity(__count);
            }

            pointer p_pos    = first_ + offset;
            pointer old_last = last_;

            size_type after_pos_size = static_cast<size_type>(last_ - p_pos);
            size_type left_count     = __count;

            move_range(p_pos, old_last, __count);
            if (__count > after_pos_size)
            {
                size_type unini_size = __count - after_pos_size;
                std::uninitialized_fill_n(old_last, unini_size, __value);
                left_count -= unini_size;
            }
            if (left_count > 0)
            {
                std::fill_n(p_pos, left_count, __value);
            }
            last_ += __count;
        }
    }

    template <class _InputIterator>
    typename ft::enable_if<!ft::is_integral<_InputIterator>::value,
                           void>::type // void
    insert(iterator pos, _InputIterator first, _InputIterator last)
    {
        range_insert(
            pos, first, last,
            typename iterator_traits<_InputIterator>::iterator_category());
    }

    // erase
    iterator erase(iterator pos)
    {
        if (pos != end())
        {
            std::copy(pos + 1, end(), pos);
            --last_;
            destroy(last_);
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
            destroy_until(rbegin() + erase_size);
        }
        return first;
    }

    // Increase the capacity of the vector, when less that
    void reserve(size_type sz)
    {
        if (sz <= capacity())
            return;
        if (sz > max_size())
            __throw_length_error();
        pointer old_first      = first_;
        pointer old_last       = last_;
        size_type old_capacity = capacity();
        allocate(sz);
        for (pointer old_iter = old_first; old_iter != old_last;
             ++old_iter, ++last_)
        {
            construct(last_, *old_iter);
        }
        for (pointer riter = old_first; riter != old_last; ++riter)
        {
            destroy(riter);
        }
        alloc_.deallocate(old_first, old_capacity);
    }

    void push_back(const_reference value)
    {
        extend_capacity(1);
        construct(last_, value);
        ++last_;
    }

    void pop_back() { destroy_until(rbegin() + 1); }

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
    pointer first_;
    pointer last_;
    pointer capacity_last_;
    allocator_type alloc_;

private:
    void __throw_out_of_range() const { throw std::out_of_range("vector"); }
    void __throw_length_error() const { throw std::length_error("vector"); }
    // allocate/deallocate
    void allocate(size_type n)
    {
        first_         = alloc_.allocate(n);
        last_          = first_;
        capacity_last_ = last_ + n;
    }
    void deallocate() { alloc_.deallocate(first_, capacity()); }

    // construct/destroy
    void construct(pointer ptr) { alloc_.construct(ptr, 0); }
    void construct(pointer ptr, const_reference value)
    {
        alloc_.construct(ptr, value);
    }
    void destroy(pointer ptr) { alloc_.destroy(ptr); }
    void destroy_until(reverse_iterator rend)
    {
        for (reverse_iterator riter = rbegin(); riter != rend; ++riter, --last_)
        {
            destroy(&*riter);
        }
    }

    template <class _InputIterator>
    void range_initialize(_InputIterator first, _InputIterator last,
                          std::input_iterator_tag)
    {
        for (; first != last; ++first)
        {
            push_back(*first);
        }
    }

    template <class _ForwardIterator>
    void range_initialize(_ForwardIterator first, _ForwardIterator last,
                          std::forward_iterator_tag)
    {
        reserve(std::distance(first, last));
        for (_ForwardIterator i = first; i != last; ++i)
        {
            push_back(*i);
        }
    }

    //  Precondition:  __new_size > capacity()
    size_type calc_new_size(size_type new_size) const
    {
        const size_type ms = max_size();
        if (new_size > ms)
            throw std::length_error("too long new_size");
        const size_type cap = capacity();
        if (cap >= ms / 2)
            return ms;
        return std::max<size_type>(2 * cap, new_size);
    }

    void extend_capacity(size_type amount_of_increase)
    {
        size_type want_size = size() + amount_of_increase;

        if (want_size > capacity())
        {
            size_type new_size = calc_new_size(want_size);
            reserve(new_size);
        }
    }

    void construct_at_end(size_type count, const_reference value)
    {
        for (std::size_t i = 0; i < count; ++i)
        {
            construct(last_, value);
            last_++;
        }
    }

    template <class _InputIterator>
    typename ft::enable_if<!ft::is_integral<_InputIterator>::value,
                           void>::type // void
    construct_at_end(_InputIterator first, _InputIterator last)
    {
        std::uninitialized_copy(first, last, end());
    }

    void move_range(pointer from_s, pointer from_e, size_type amount_move)
    {
        difference_type range_size = from_e - from_s;
        pointer old_tail           = from_e - 1;
        pointer new_tail           = old_tail + amount_move;
        pointer tmp_p              = new_tail;

        if (from_s != last_)
        {
            for (size_type i = 0; i < static_cast<size_type>(range_size);
                 ++i, --tmp_p)
            {
                if (tmp_p >= from_e)
                {
                    construct(tmp_p, *(old_tail - i));
                }
                else
                {
                    *tmp_p = *(old_tail - i);
                }
            }
        }
    }

    // input_iterator_tag ver
    template <class _InputIterator>
    void range_insert(iterator pos, _InputIterator first, _InputIterator last,
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

    // forward_iterator_tag ver
    template <class _ForwardIterator>
    void range_insert(iterator pos, _ForwardIterator first_it,
                      _ForwardIterator last_it, std::forward_iterator_tag)
    {
        difference_type offset      = pos - begin();
        difference_type insert_size = std::distance(first_it, last_it);

        if (insert_size > 0)
        {
            if (insert_size > capacity_last_ - last_)
            {
                extend_capacity(insert_size);
            }

            pointer p_pos    = first_ + offset;
            pointer old_last = last_;

            difference_type after_pos_size = last_ - p_pos;
            size_type left_insert_size     = insert_size;
            _ForwardIterator m_it           = last_it;

            if (insert_size > after_pos_size)
            {
                m_it = first_it;
                std::advance(m_it, after_pos_size);
                construct_at_end(m_it, last_it);
                left_insert_size = after_pos_size;
            }
            if (left_insert_size > 0)
            {
                move_range(p_pos, old_last, insert_size);
                std::copy(first_it, m_it, p_pos);
            }
            last_ += insert_size;
        }
    }
};

/*
** Non Member functions
*/

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

} // namespace ft

namespace std {

template <class _Tp, class _Allocator>
void swap(ft::vector<_Tp, _Allocator>& __lhs,
          ft::vector<_Tp, _Allocator>& __rhs)
{
    __lhs.swap(__rhs);
}

} // namespace std

#endif
