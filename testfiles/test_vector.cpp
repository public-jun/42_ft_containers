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

template <class T>
void print_is_empty(T& v)
{
    if (v.empty())
    {
        cout << "vector is empty" << endl;
    }
    else
    {
        cout << "vector is not empty" << endl;
    }
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
        ft::vector<int> v(10);
        ft::vector<int> a;
        for (int i = 1; i <= 5; ++i)
            a.push_back(i);
        vdebug(v);
        vdebug(a);
        v.assign(a.begin(), a.end());
        vdebug(v);
    }

    {
        pout("capacity >= assign size > size");
        ft::vector<int> v;
        for (int i = -1; i >= -10; --i)
            v.push_back(i);
        ft::vector<int> a(12, 3);
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
        ft::vector<int> a(12, 3);
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
        int* p;
        int i = 0;
        p     = v.get_allocator().allocate(5);
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

void front_test()
{
    put_test_function("TEST vector::front");
    {
        pout("reference");
        ft::vector<int> v;
        for (int i = 1; i <= 5; ++i)
            v.push_back(i);
        vdebug(v);
        ft::vector<int>::reference ref = v.front();
        cout << ref << endl;
        ref = 42;
        vdebug(v);
    }

    {
        pout("const_reference");
        ft::vector<int> v;
        for (int i = 1; i <= 5; ++i)
            v.push_back(i);
        vdebug(v);
        ft::vector<int>::const_reference c_ref = v.front();
        cout << c_ref << endl;
        // c_ref = 42;
        vdebug(v);
    }

    {
        pout("const_reference change by other ref");
        ft::vector<int> v;
        for (int i = 1; i <= 5; ++i)
            v.push_back(i);
        vdebug(v);
        ft::vector<int>::const_reference c_ref = v.front();
        ft::vector<int>::reference ref         = v.front();
        cout << c_ref << endl;
        vdebug(v);
        ref = 55;
        vdebug(v);
        cout << c_ref << endl;
    }
}

void back_test()
{
    put_test_function("TEST vector::back");
    {
        pout("reference");
        ft::vector<int> v;
        for (int i = 1; i <= 5; ++i)
            v.push_back(i);
        vdebug(v);
        ft::vector<int>::reference ref = v.back();
        cout << ref << endl;
        ref = 42;
        vdebug(v);
    }

    {
        pout("const_reference");
        ft::vector<int> v;
        for (int i = 1; i <= 5; ++i)
            v.push_back(i);
        vdebug(v);
        ft::vector<int>::const_reference c_ref = v.back();
        cout << c_ref << endl;
        // c_ref = 42; error
        vdebug(v);
    }

    {
        pout("const_reference change by other ref");
        ft::vector<int> v;
        for (int i = 1; i <= 5; ++i)
            v.push_back(i);
        vdebug(v);
        ft::vector<int>::const_reference c_ref = v.back();
        ft::vector<int>::reference ref         = v.back();
        cout << c_ref << endl;
        vdebug(v);
        ref = 55;
        vdebug(v);
        cout << c_ref << endl;
    }
}

void data_test()
{
    put_test_function("TEST vector::data");
    {
        pout("pointer");
        ft::vector<int> v;
        for (int i = 1; i <= 5; ++i)
            v.push_back(i);
        vdebug(v);

        ft::vector<int>::pointer p = v.data();
        cout << *p << endl;
        vdebug(v);

        cout << *(++p) << endl;
        vdebug(v);

        cout << ++(*p) << endl;
        vdebug(v);
    }
    {
        pout("const_pointer");
        ft::vector<int> v;
        for (int i = 1; i <= 5; ++i)
            v.push_back(i);
        vdebug(v);

        ft::vector<int>::const_pointer p = v.data();
        cout << *p << endl;
        vdebug(v);

        cout << *(++p) << endl;
        vdebug(v);

        // cout << ++(*p) << endl;
        // vdebug(v);
    }

    {
        pout("const_pointer change by other pointer");
        ft::vector<int> v;
        for (int i = 1; i <= 5; ++i)
            v.push_back(i);
        vdebug(v);

        ft::vector<int>::const_pointer c_p = v.data();
        ft::vector<int>::pointer p         = v.data();

        cout << *c_p << endl;
        ++(*p);
        cout << *c_p << endl;
        vdebug(v);
    }
}

void empty_test()
{
    put_test_function("TEST vector::empty");
    {
        pout("const_pointer change by other pointer");
        ft::vector<int> v;
        print_is_empty(v);

        v.push_back(1);
        print_is_empty(v);
    }
}

void size_test()
{
    put_test_function("TEST vector::size");
    {
        pout("size");
        ft::vector<int> v;
        cout << "size: " << v.size() << endl;

        // simple
        for (int i = 1; i <= 5; ++i)
            v.push_back(i);
        vdebug(v);
        cout << "size: " << v.size() << endl;

        for (int i = 6; i <= 1000; ++i)
            v.push_back(i);
        cout << "size: " << v.size() << endl;

        v.reserve(10000);
        cout << "size: " << v.size() << endl;

        for (int i = 6; i <= 1000; ++i)
            v.push_back(i);
        cout << "size: " << v.size() << endl;
    }
}

void max_size_test()
{
    put_test_function("TEST vector::max_size");
    {
        pout("get vector<int> maximum size");
        std::vector<int> v;
        cout << "max_size: " << v.max_size() << endl;
    }

    {
        pout("get vector<char> maximum size");
        ft::vector<char> v;
        cout << "max_size: " << v.max_size() << endl;
    }

    {
        pout("get vector<wchar_t> maximum size");
        ft::vector<wchar_t> v;
        cout << "max_size: " << v.max_size() << endl;
    }

    {
        pout("get vector<short> maximum size");
        ft::vector<short> v;
        cout << "max_size: " << v.max_size() << endl;
    }

    {
        pout("get vector<long> maximum size");
        ft::vector<long> v;
        cout << "max_size: " << v.max_size() << endl;
    }

    {
        pout("get vector<float> maximum size");
        ft::vector<float> v;
        cout << "max_size: " << v.max_size() << endl;
    }

    {
        pout("get vector<double> maximum size");
        ft::vector<double> v;
        cout << "max_size: " << v.max_size() << endl;
    }

    {
        pout("get vector<long doule> maximum size");
        ft::vector<long double> v;
        cout << "max_size: " << v.max_size() << endl;
    }

    {
        pout("get vector<std::string> maximum size");
        ft::vector<std::string> v;
        cout << "max_size: " << v.max_size() << endl;
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
    front_test();
    back_test();
    data_test();
    empty_test();
    size_test();
    max_size_test();
}
