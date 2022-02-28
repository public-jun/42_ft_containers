#include <tester.hpp>

template <typename T>
void pout(T s)
{
    static int no;
    cout << endl;
    cout << "--- [" << ++no << "]:" << s << " ---" << endl;
}

template <class T>
void vdebug(T& V)
{
    cout << "size:" << V.size() << " capacity:" << V.capacity() << endl;
    cout << "{ ";
    for (typename T::iterator it = V.begin(); it != V.end(); ++it)
        cout << *it << " ";
    cout << "}" << endl;
}

void def_constructor_test()
{
    pout("vector()");
    ft::vector<int> v;
    vdebug(v);
}

void alloc_constructor_test()
{
    pout("vector(allocator_type&)");
    std::allocator<int> alloc;
    ft::vector<int> v1(alloc);
    vdebug(v1);

    ft::vector<int> v3(5, 123, alloc);
    vdebug(v3);
    ft::vector<int> v4(v3);
    v4[0] = 100;
    vdebug(v4);
    vdebug(v3);
    ft::vector<int> v5;
    v5 = v3;
    vdebug(v5);
    v3[0] = 42;
    vdebug(v3);
    vdebug(v5);
    // std::vector<int> v;
}

void count_value_constructor_test() { pout("vector(size, value)"); }

void at_test()
{
    pout("vector::at");

    ft::vector<int> v;
    for (int i = 1; i <= 5; ++i)
        v.push_back(i);
    for (ft::vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v.at(i) << endl;
    try
    {
        v.at(5);
    } catch (const std::exception& e)
    {
        cerr << e.what() << endl;
    }
}

void vector_test()
{
    cout << "Vector TEST" << endl;
    def_constructor_test();
    alloc_constructor_test();
    at_test();
}
