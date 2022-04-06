#include <iostream>
#include <vector>

#include "ft_test.hpp"

#define SIZE 1000
#define cout std::cout
#define endl std::endl

test_func_vec_type  test_functions;
testf_func_vec_type testf_functions;

/***** Include all the files that use GoogleTest to test *****/

#if STL // -DTEST=1
#else   // -DTEST=0
#include "./other/pair_test.cpp"
#include "./other/tree_test.cpp"
#endif

#include "./containers/map_test.cpp"
#include "./containers/set_test.cpp"
#include "./containers/stack_test.cpp"
#include "./containers/vector_test.cpp"

namespace ft {
namespace test {

bool MakeAndRegisterTestInfo(std::string test_name, test_func_type func)
{
    test_functions.push_back(test_func_pair_type(test_name, func));
    return true;
}

bool MakeAndRegisterTestInfo(std::string test_name, testing::Test* func)
{
    testf_functions.push_back(testf_func_pair_type(test_name, func));
    return true;
}

} // namespace test
} // namespace ft

int main()
{
    typedef test_func_vec_type::iterator  test_func_vec_iterator;
    typedef testf_func_vec_type::iterator testf_func_vec_iterator;

    cout << "Test Start!!" << endl;
    cout << "Test count: " << test_functions.size() << endl;

    for (test_func_vec_iterator it = test_functions.begin();
         it != test_functions.end(); ++it)
    {
        std::string    test_func_name = (*it).first;
        test_func_type test_func      = (*it).second;

        cout << "RUN:     " << test_func_name << endl;
        test_func();
        cout << "SUCCESS: " << test_func_name << "\n" << endl;
    }

    cout << "Test Finished!!" << endl;

    cout << "RUN TEST_F()" << endl;
    for (testf_func_vec_iterator it = testf_functions.begin();
         it != testf_functions.end(); ++it)
    {
        std::string    test_func_name = (*it).first;
        testing::Test* test_obj       = (*it).second;

        cout << "RUN:     " << test_func_name << endl;
        test_obj->Run();
        cout << "SUCCESS: " << test_func_name << "\n" << endl;
    }

    cout << "All tests succeeded." << endl;
}