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

void vector_test() {}
