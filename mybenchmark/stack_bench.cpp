#include "./bench_lib/bench.hpp"


#include <stack.hpp>
#include <stack>

template <class Stack>
void bm_stack_def_constructor()
{
    Stack v;
}

template <class Stack>
void bm_stack_copy_constructor()
{
    Stack v1;
    Stack v2(v1);
}

template <class Stack>
void bm_stack_assign_operator()
{
    Stack v1;
    Stack v2;
    v2 = v1;
}

template <class Stack>
void bm_stack_top()
{
    Stack v1;
    v1.push(1);
    v1.top();
}

template <class Stack>
void bm_stack_empty()
{
    Stack v1;
    v1.empty();
}

template <class Stack>
void bm_stack_size()
{
    Stack v1;
    v1.size();
}

template <class Stack>
void bm_stack_push()
{
    Stack v1;
    for (int i = 0; i < 100; ++i)
        v1.push(i);
}

template <class Stack>
void bm_stack_pop()
{
    Stack v1;
    for (int i = 0; i < 100; ++i)
        v1.push(i);
    for (int i = 0; i < 100; ++i)
        v1.pop();
}

template <class Stack>
void bm_stack_equal()
{
    Stack v1;
    Stack v2;
    (void)(v1 == v2);
}

template <class Stack>
void bm_stack_not_equal()
{
    Stack v1;
    Stack v2;
    (void)(v1 != v2);
}

template <class Stack>
void bm_stack_less()
{
    Stack v1;
    Stack v2;
    (void)(v1 < v2);
}

template <class Stack>
void bm_stack_greater()
{
    Stack v1;
    Stack v2;
    (void)(v1 > v2);
}

template <class Stack>
void bm_stack_less_equal()
{
    Stack v1;
    Stack v2;
    (void)(v1 <= v2);
}

template <class Stack>
void bm_stack_greater_equal()
{
    Stack v1;
    Stack v2;
    (void)(v1 >= v2);
}

void stack_bench()
{
    BM_REGIST("stack_def_constructor",
              bm_stack_def_constructor<ft::stack<int> >,
              bm_stack_def_constructor<std::stack<int> >, LOOP, 1);
    BM_REGIST("stack_copy_constructor",
              bm_stack_copy_constructor<ft::stack<int> >,
              bm_stack_copy_constructor<std::stack<int> >, LOOP, 1);
    BM_REGIST("stack_assign_operator",
              bm_stack_assign_operator<ft::stack<int> >,
              bm_stack_assign_operator<std::stack<int> >, LOOP2, 1);
    BM_REGIST("stack_top", bm_stack_top<ft::stack<int> >,
              bm_stack_top<std::stack<int> >, LOOP2, 1);
    BM_REGIST("stack_empty", bm_stack_empty<ft::stack<int> >,
              bm_stack_empty<std::stack<int> >, LOOP2, 1);
    BM_REGIST("stack_size", bm_stack_size<ft::stack<int> >,
              bm_stack_size<std::stack<int> >, LOOP2, 1);
    BM_REGIST("stack_push", bm_stack_push<ft::stack<int> >,
              bm_stack_push<std::stack<int> >, LOOP2, 1);
    BM_REGIST("stack_pop", bm_stack_pop<ft::stack<int> >,
              bm_stack_pop<std::stack<int> >, LOOP2, 1);
    BM_REGIST("stack_equal", bm_stack_equal<ft::stack<int> >,
              bm_stack_equal<std::stack<int> >, LOOP, 1);
    BM_REGIST("stack_not_equal", bm_stack_not_equal<ft::stack<int> >,
              bm_stack_not_equal<std::stack<int> >, LOOP, 1);
    BM_REGIST("stack_less", bm_stack_less<ft::stack<int> >,
              bm_stack_less<std::stack<int> >, LOOP, 1);
    BM_REGIST("stack_greater", bm_stack_greater<ft::stack<int> >,
              bm_stack_greater<std::stack<int> >, LOOP, 1);
    BM_REGIST("stack_less_equal", bm_stack_less_equal<ft::stack<int> >,
              bm_stack_less_equal<std::stack<int> >, LOOP, 1);
    BM_REGIST("stack_greater_equal", bm_stack_greater_equal<ft::stack<int> >,
              bm_stack_greater_equal<std::stack<int> >, LOOP, 1);
}