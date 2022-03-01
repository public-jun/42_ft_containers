#include <tester.hpp>

#include <array>
#include <vector>

template <typename T>
void put_test_function(T s)
{
    cout << "\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << std::setw(25) << s << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n" << endl;
}

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
}

void count_value_constructor_test()
{
    pout("vector(size, value)");

    std::allocator<int> alloc;
    ft::vector<int> v3(5, 123, alloc);
    vdebug(v3);

    ft::vector<int> v4(v3);
    v4[0] = 100;
    vdebug(v4);
    vdebug(v3);

    ft::vector<int> v5;
    v5 = v3;
    vdebug(v3);
    vdebug(v5);
    v3[0] = 42;
    vdebug(v3);
    vdebug(v5);
}

void inputiterator_constructor_test()
{
    pout("vector::vector(Iterator, Iterator)");

    // std::array<int, 3> a = {0, 1, 2};
    std::vector<int> a;
    for (int i = 1; i <= 5; ++i)
        a.push_back(i);
    ft::vector<int> v(a.begin(), a.end());
    vdebug(a);
    vdebug(v);
}

void copy_constructor_test()
{
    pout("vector::vector(const vector& r)");

    ft::vector<int> a;
    for (int i = 1; i <= 5; ++i)
        a.push_back(i);
    vdebug(a);
    ft::vector<int> v = a;
    vdebug(a);
    vdebug(v);
}

void operator_assign_test()
{
    put_test_function("TEST vector::operator=");

    {
        pout("assign self");
        ft::vector<int> a;
        ft::vector<int>& ref_a = a;
        ref_a                  = a;
    }

    {
        pout("equal size");
        ft::vector<int> a(5, 1);
        ft::vector<int> b(5, -1);
        vdebug(a);
        vdebug(b);
        b = a;
        vdebug(a);
        vdebug(b);
    }

    {
        pout("capacity is more than other's size");
        ft::vector<int> a(20, 3);
        ft::vector<int> b(5, 1);
        vdebug(a);
        vdebug(b);
        a = b;
        vdebug(a);
        vdebug(b);
    }

    {
        pout("capacity is less than other's size");
        ft::vector<int> a(2, 1);
        ft::vector<int> b(4, 2);
        vdebug(a);
        vdebug(b);
        a = b;
        vdebug(a);
        vdebug(b);
    }
}

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

void assign_test()
{
    put_test_function("TEST vector::assign()");

    {
        pout("capacity >= size >= assign size");
        ft::vector<int> v;
        for (int i = 1; i <= 10; ++i)
            v.push_back(i);
        vdebug(v);
        v.assign(5, 42);
        vdebug(v);
    }

    {
        pout("capacity >= assign size > size");
        ft::vector<int> v;
        for (int i = 1; i <= 10; ++i)
            v.push_back(i);
        vdebug(v);
        v.assign(12, 42);
        vdebug(v);
    }

    {
        pout("capacity is less than assign size");
        ft::vector<int> v;
        for (int i = 1; i <= 5; ++i)
            v.push_back(i);
        vdebug(v);
        v.assign(10, 42);
        vdebug(v);
    }

    put_test_function("TEST vector::assign<Iterator>");

    {
        pout("capacity >= size >= assign size");
        std::vector<int> v(10);
        std::vector<int> a;
        for (int i = 1; i <= 5; ++i)
            a.push_back(i);
        vdebug(v);
        v.assign(a.begin(), a.end());
        vdebug(v);
    }

    {
        pout("capacity >= assign size > size");
        std::vector<int> v;
        for (int i = -1; i >= -10; --i)
            v.push_back(i);
        std::vector<int> a(12, 3);
        vdebug(v);
        vdebug(a);
        v.assign(a.begin(), a.end());
        vdebug(v);
    }

    {
        pout("capacity is less than assign size");
        ft::vector<int> v;
        for (int i = 1; i <= 5; ++i)
            v.push_back(i);
        std::vector<int> a(12, 3);
        vdebug(v);
        vdebug(a);
        v.assign(a.begin(), a.end());
        vdebug(v);
    }
}

void get_allocator_test()
{
    put_test_function("TEST vector::get_allocator");

    {
        pout("Get allocator");
        ft::vector<int> v;
        int *p;
        int i = 0;
        p = v.get_allocator().allocate(5);
        for (i = 0; i < 5; i++)
            v.get_allocator().construct(&p[i], i);
        for (i = 0; i < 5; i++)
            cout << ' ' << p[i];
        cout << '\n';
        for (i = 0; i < 5; i++)
            v.get_allocator().destroy(&p[i]);
        v.get_allocator().deallocate(p, 5);
    }
}

void vector_test()
{
    cout << "Vector TEST" << endl;
    def_constructor_test();
    alloc_constructor_test();
    count_value_constructor_test();
    inputiterator_constructor_test();
    copy_constructor_test();
    operator_assign_test();
    at_test();
    assign_test();
    get_allocator_test();
}
