#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <iterator>
#include <limits>

namespace ft
{

template <typename T, typename Allocator = std::allocator<T> >
class vector
{
public:
    // value_type などのネストされた型名
    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = const pointer;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using allocator_type  = Allocator;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;

    // イテレータのエイリアス
    using iterator               = pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // コンストラクタ
    vector() : vector(allocator_type()) {}
    vector(const allocator_type& alloc) noexcept : alloc(alloc) {}
    vector(size_type size, const allocator_type& alloc = allocator_type())
        : vector(alloc)
    {
        resize(size);
    }
    vector(size_type size, const_reference value,
           const allocator_type& alloc = allocator_type())
        : vector(alloc)
    {
        resize(size, value);
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
    vector(const vector& x);
    vector& operator=(const vector& x);

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
    reference front() { return first; }
    const_reference front() const { return first; }
    reference back() { return last - 1; }
    const_reference back() const { return last - 1; }
    pointer data() noexcept { return first; }
    const_pointer data() const noexcept { return first; }

    // イテレータアクセス
    iterator begin() noexcept { return first; }
    iterator end() noexcept { return last; }
    iterator begin() const noexcept { return first; }
    iterator end() const noexcept { return last; }
    const_iterator cbegin() const noexcept { return first; }
    const_iterator cend() const noexcept { return last; }
    // リバースイテレータアクセス
    reverse_iterator rbegin() noexcept { return reverse_iterator{ last }; }
    reverse_iterator rend() noexcept { return reverse_iterator{ first }; }
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
        auto ptr = allocate(sz);

        // 古いストレージの情報を保存
        auto old_first = first;
        auto old_last  = last;
        // auto old_capacity = capacity();

        first         = ptr;
        last          = first;
        reserved_last = first + sz;

        // 例外安全のため
        // 関数を抜けるときに古いストレージを破棄する
        // std::scope_exit e(
        //     [&] { traits::dellocate(alloc, old_first, old_capacity); });

        // 古いストレージから新しいストレージに要素をコピー構築
        //  実際にはムーブ構築
        for (auto old_iter = old_first; old_iter != old_last;
             ++old_iter, ++last)
        {
            // このコピーの理解にはムーブせマンティクスの理解が必要
            construct(last, std::move(*old_iter));
        }

        // 新しいストレージにコピーし終えたので
        // 古いストレージの値は破棄
        for (auto riter = reverse_iterator(old_last),
                  rend  = reverse_iterator(old_first);
             riter != rend; ++riter)
        {
            destroy(&*riter);
        }
        // scope_exit によって自動的にストレージが破棄される
    }

    void resize(size_type sz)
    {
        // 現在の要素数より少ない
        if (sz < size())
        {
            auto diff = size() - sz;
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
            auto diff = size() - sz;
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
            auto c = size();
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
    using traits = std::allocator_traits<allocator_type>;

    // allocate/deallocate
    pointer allocate(size_type n) { return traits::allocate(alloc, n); }
    void deallocate() { traits::deallocate(alloc, first, capacity()); }

    // construct/destroy
    void construct(pointer ptr) { traits::construct(alloc, ptr); }
    void construct(pointer ptr, const_reference value)
    {
        traits::construct(alloc, ptr, value);
    }
    // move version
    void construct(pointer ptr, value_type&& value)
    {
        traits::construct(alloc, ptr, std::move(value));
    }
    void destroy(pointer ptr) { traits::destroy(alloc, ptr); }
    void destroy_until(reverse_iterator rend)
    {
        for (auto riter = rbegin(); riter != rend; ++riter, --last)
        {
            destroy(&*riter);
        }
    }
};
}; // namespace ft

#endif
