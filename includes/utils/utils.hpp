#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {
template <class _Tp, _Tp __v>
struct integral_constant {
    static const _Tp value = __v;
    typedef _Tp value_type;
    typedef integral_constant<_Tp, __v> type;
    const value_type operator()() const { return value; }
};

// integral_constantの特殊化true_type
typedef integral_constant<bool, true> true_type;
// integral_constantの特殊化false_type
typedef integral_constant<bool, false> false_type;

/// remove_cv
//// remove const
template <class _Tp>
struct remove_cv {
    typedef _Tp type;
};
template <class _Tp>
struct remove_cv<const _Tp> {
    typedef _Tp type;
};
/*
** volatile ... コンパイルの最適化を抑制する修飾子
*/
//// remove volatile
template <class _Tp>
struct remove_cv<volatile _Tp> {
    typedef _Tp type;
};
template <class _Tp>
struct remove_cv<const volatile _Tp> {
    typedef _Tp type;
};

/// is_same
template <class _Tp, class _Up>
struct is_same : public false_type {};
template <class _Tp>
struct is_same<_Tp, _Tp> : public true_type {};

/// is_integral_helpers
template <class _Tp>
struct is_integral_helper : public false_type {};
template <>
struct is_integral_helper<bool> : public true_type {};
template <>
struct is_integral_helper<char> : public true_type {};
template <>
struct is_integral_helper<wchar_t> : public true_type {};
template <>
struct is_integral_helper<signed char> : public true_type {};
template <>
struct is_integral_helper<unsigned char> : public true_type {};
template <>
struct is_integral_helper<short> : public true_type {};
template <>
struct is_integral_helper<unsigned short> : public true_type {};
template <>
struct is_integral_helper<int> : public true_type {};
template <>
struct is_integral_helper<unsigned int> : public true_type {};
template <>
struct is_integral_helper<long> : public true_type {};
template <>
struct is_integral_helper<unsigned long> : public true_type {};

// is_integral
/*
** ex. is_integral<int>::value == true
**     is_integral<float>::value == false
*/
template <class _Tp>
struct is_integral : is_integral_helper<typename remove_cv<_Tp>::type>::type {};

}; // namespace ft

#endif /* UTILS_HPP */
