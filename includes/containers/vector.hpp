#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <iterator>
#include <limits>

namespace ft {

template <typename T, typename Allocator = std::allocator<T> >
class vector
{
public:
    // value_type などのネストされた型名
    typedef T value_type;
    typedef T* pointer;
    typedef const pointer const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef Allocator allocator_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    // イテレータのエイリアス
    typedef pointer iterator;
    typedef const_pointer const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    // コンストラクタ
    // cppreference(https://en.cppreference.com/w/cpp/container/vector/vector)
    // (1)
    vector()
        : first(NULL), last(NULL), reserved_last(NULL), alloc(allocator_type())
    {}
    // (2)
    explicit vector(const allocator_type& alloc) noexcept : first(NULL),
                                                            last(NULL),
                                                            reserved_last(NULL),
                                                            alloc(alloc)
    {}
    // c++11なので除外
    // explicit vector(size_type size,
    //                 const allocator_type& alloc = allocator_type())
    //     : vector(alloc)
    // {
    //     resize(size);
    // }
    // (3)
    vector(size_type count, const T& value = T(),
           const allocator_type& alloc = allocator_type())
        : vector(alloc)
    {
        resize(count, value);
    }
    // (4)
    template <typename InputIterator>
    vector(InputIterator first, InputIterator last,
           const Allocator& allocator                    = Allocator(),
           typename std::enable_if<!std::is_integral<InputIterator>::value,
                                   InputIterator>::type* = NULL)
        : first(NULL), last(NULL), reserved_last(NULL), alloc(allocator)
    {
        reserve(std::distance(first, last));
        for (pointer i = first; i != last; ++i)
        {
            push_back(*i);
        }
    }

    // コピーコンストラクタ
    // コンテナのコピーにあたってアロケータをコピーすべきかどうかは、アロケータの実装が選べるようになっている
    vector(const vector& r)
        : first(NULL), last(NULL), reserved_last(NULL), alloc(r.alloc)
    {
        // コピー処理
        // 1. コピー元の要素数を保持できるだけのストレージを確保
        reserve(r.size());
        // 2. コピー元の要素をコピー構築
        // dest はコピー先
        // [src, last) はコピー元
        for (pointer dest = first, src = r.begin(), last = r.end(); src != last;
             ++dest, ++src)
        {
            construct(dest, *src);
        }
        last = first + r.size();
    }

    // コピー代入演算子
    vector& operator=(const vector& r)
    {
        // 1. 自分自身への代入なら何もしない
        if (this == &r)
            return *this;

        // 2. 要素数が同じならば
        if (size() == r.size())
        {
            // 要素ごとにコピー代入
            std::copy(r.begin(), r.end(), begin());
        }
        // 3. それ以外の場合で
        // 予約数が十分ならば、
        else if (capacity() >= r.size())
        {
            // 有効な要素はコピー
            std::copy(r.begin(), r.begin() + r.size(), begin());
            // 残りはコピー構築
            for (const_iterator src_iter = r.begin() + r.size(),
                                src_end  = r.end();
                 src_iter != src_end; ++src_iter, ++last)
            {
                construct(last, *src_iter);
            }
        }
        // 4. 予約数が不十分ならば
        else
        {
            // 要素を全て破棄
            destroy_until(rbegin()); // destroy_all()
            // 予約
            reserve(r.size());
            // コピー構築
            for (const_iterator src_iter = r.begin(), src_end = r.end(),
                                dest_iter = begin();
                 src_iter != src_end; ++src_iter, ++dest_iter, ++last)
            {
                construct(dest_iter, *src_iter);
            }
        }
        return *this;
    }

    // デストラクタ
    ~vector()
    {
        // 1. 要素を末尾から先頭に向かう順番で破棄
        clear();
        // 2. 生のメモリーを解放する
        deallocate();
    }
    // コピー
    // vector(const vector& x);
    // vector& operator=(const vector& x);

    //********************//
    //   メンバ関数       //
    //********************//
    // 容量確認
    size_type size() const noexcept { return end() - begin(); }
    bool empty() const noexcept { return begin() == end(); }
    size_type capacity() const noexcept { return reserved_last - first; }

    // 要素アクセス
    reference operator[](size_type i) { return first[i]; }
    const_reference operator[](size_type i) const { return first[i]; }
    reference at(size_type i)
    {
        if (i >= size())
            throw std::out_of_range("index is out of range.");
        return first[i];
    }
    const_reference at(size_type i) const
    {
        if (i >= size())
            throw std::out_of_range("index is out of range.");
        return first[i];
    }
    reference front() { return *first; }
    const_reference front() const { return *first; }
    reference back() { return *(last - 1); }
    const_reference back() const { return *(last - 1); }
    pointer data() noexcept { return first; }
    const_pointer data() const noexcept { return first; }

    // イテレータアクセス
    iterator begin() noexcept { return first; }
    iterator end() noexcept { return last; }
    iterator begin() const noexcept { return first; }
    iterator end() const noexcept { return last; }
    // リバースイテレータアクセス
    reverse_iterator rbegin() noexcept { return reverse_iterator(last); }
    reverse_iterator rend() noexcept { return reverse_iterator(first); }
    const_reverse_iterator rbegin() const noexcept
    {
        return reverse_iterator{ last };
    }
    const_reverse_iterator rend() const noexcept
    {
        return reverse_iterator{ first };
    }

    void clear() noexcept { destroy_until(rend()); }

    void reserve(size_type sz)
    {
        // すでに指定された要素数以上に予約されているなら何もしない
        if (sz <= capacity())
            return;

        // 動的メモリ確保をする
        pointer ptr = allocate(sz);

        // 古いストレージの情報を保存
        pointer old_first      = first;
        pointer old_last       = last;
        size_type old_capacity = capacity();

        first         = ptr;
        last          = first;
        reserved_last = first + sz;

        // 古いストレージから新しいストレージに要素をコピー構築
        //  実際にはムーブ構築
        for (pointer old_iter = old_first; old_iter != old_last;
             ++old_iter, ++last)
        {
            construct(last, *old_iter);
        }

        // 新しいストレージにコピーし終えたので
        // 古いストレージの値は破棄
        for (reverse_iterator riter = reverse_iterator(old_last),
                              rend  = reverse_iterator(old_first);
             riter != rend; ++riter)
        {
            destroy(&*riter);
        }
        // scope_exit
        // によって自動的にストレージが破棄され亡くなるので、deallocate を追記
        alloc.deallocate(old_first, old_capacity);
    }

    void resize(size_type sz)
    {
        // 現在の要素数より少ない
        if (sz < size())
        {
            difference_type diff = size() - sz;
            // 破棄する要素数だけ末尾から破棄
            destroy_until(rbegin() + diff);
            last = first + sz;
        }
        // 現在の要素数より大きい
        else if (sz > size())
        {
            reserve(sz);
            for (; last != reserved_last; ++last)
            {
                construct(last);
            }
        }
    }
    void resize(size_type sz, const_reference value)
    {
        if (sz < size())
        {
            difference_type diff = size() - sz;
            destroy_until(rbegin() + diff);
            last = first + sz;
        }
        else if (sz > size())
        {
            reserve(sz);
            for (; last != reserved_last; ++last)
            {
                construct(last, value);
            }
        }
    }
    void push_back(const_reference value)
    {
        // 予約メモリーが足りなければ拡張
        if (size() + 1 > capacity())
        {
            // 現在のストレージサイズ
            size_type c = size();
            // 0の場合は1に
            if (c == 0)
                c = 1;
            else
                c *= 2;

            reserve(c);
        }
        // 要素を末尾に追加
        construct(last, value);
        // 有効な要素数を更新
        ++last;
    }

private:
    // 先頭の要素へのポインタ
    pointer first;
    // 最後の要素の一つ前方のポインタ
    pointer last;
    // 確保したストレージの終端
    pointer reserved_last;
    // アロケータの値
    allocator_type alloc;

private:
    // ユーザーからは使えないヘルパー関数

    // allocate/deallocate
    pointer allocate(size_type n) { return alloc.allocate(n); }
    void deallocate() { alloc.deallocate(first, capacity()); }

    // construct/destroy
    void construct(pointer ptr) { alloc.construct(ptr, 0); }
    void construct(pointer ptr, const_reference value)
    {
        alloc.construct(ptr, value);
    }
    void destroy(pointer ptr) { alloc.destroy(ptr); }
    void destroy_until(reverse_iterator rend)
    {
        for (reverse_iterator riter = rbegin(); riter != rend; ++riter, --last)
        {
            destroy(&*riter);
        }
    }
};
}; // namespace ft

#endif
