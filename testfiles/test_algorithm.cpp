#include <tester.hpp>
#include <vector>

template <class Iterator1, class Iterator2>
void judge_equal(Iterator1 first1, Iterator1 last1, Iterator2 first2)
{
    if (ft::equal(first1, last1, first2) == true)
        cout << "EQUAL" << endl;
    else
        cout << "NOT EQUAL" << endl;
}

template <class Iterator1, class Iterator2, class BinaryPredicate>
void judge_equal(Iterator1 first1, Iterator1 last1, Iterator2 first2,
                 BinaryPredicate pred)
{
    // cout << "CALLED" << endl;
    if (ft::equal(first1, last1, first2, pred) == true)
        cout << "EQUAL" << endl;
    else
        cout << "NOT EQUAL" << endl;
}

bool func(int lhs, int rhs)
{
    if (lhs == rhs)
        return true;
    return false;
}

void equal_test()
{
    put_test_function("TEST std::equal");

    {
        pout("same range, equal value");
        std::vector<int> v1;
        for (int i = 0; i <= 5; ++i)
            v1.push_back(i);
        vdebug(v1);
        std::vector<int> v2;
        for (int i = 0; i <= 5; ++i)
            v2.push_back(i);
        vdebug(v2);

        judge_equal(v1.begin(), v1.end(), v2.begin());
    }

    {
        pout("same range, equal value");
        std::vector<int> v1;
        for (int i = 0; i <= 5; ++i)
            v1.push_back(i);
        vdebug(v1);
        std::vector<int> v2;
        for (int i = 0; i <= 10; ++i)
            v2.push_back(i);
        vdebug(v2);

        judge_equal(v1.begin(), v1.end(), v2.begin());
    }

    {
        pout("same range, not equal value");
        std::vector<int> v1;
        for (int i = 0; i <= 5; ++i)
            v1.push_back(i);
        vdebug(v1);
        std::vector<int> v2;
        for (int i = -1; i <= 4; ++i)
            v2.push_back(i);
        vdebug(v2);

        judge_equal(v1.begin(), v1.end(), v2.begin());
    }

    {
        pout("diff range, not equal value");
        std::vector<int> v1;
        for (int i = 0; i <= 5; ++i)
            v1.push_back(i);
        vdebug(v1);
        std::vector<int> v2;
        for (int i = -1; i <= 20; ++i)
            v2.push_back(i);
        vdebug(v2);

        judge_equal(v1.begin(), v1.end(), v2.begin());
    }

    {
        pout("same range, equal value");
        std::vector<int> v1;
        for (int i = 0; i <= 5; ++i)
            v1.push_back(i);
        vdebug(v1);
        std::vector<int> v2;
        for (int i = 0; i <= 5; ++i)
            v2.push_back(i);
        vdebug(v2);

        judge_equal(v1.begin(), v1.end(), v2.begin(), func);
    }

    {
        pout("same range, equal value");
        std::vector<int> v1;
        for (int i = 0; i <= 5; ++i)
            v1.push_back(i);
        vdebug(v1);
        std::vector<int> v2;
        for (int i = 0; i <= 10; ++i)
            v2.push_back(i);
        vdebug(v2);

        judge_equal(v1.begin(), v1.end(), v2.begin(), func);
    }

    {
        pout("same range, not equal value");
        std::vector<int> v1;
        for (int i = 0; i <= 5; ++i)
            v1.push_back(i);
        vdebug(v1);
        std::vector<int> v2;
        for (int i = -1; i <= 4; ++i)
            v2.push_back(i);
        vdebug(v2);

        judge_equal(v1.begin(), v1.end(), v2.begin(), func);
    }

    {
        pout("diff range, not equal value");
        std::vector<int> v1;
        for (int i = 0; i <= 5; ++i)
            v1.push_back(i);
        vdebug(v1);
        std::vector<int> v2;
        for (int i = -1; i <= 20; ++i)
            v2.push_back(i);
        vdebug(v2);

        judge_equal(v1.begin(), v1.end(), v2.begin(), func);
    }
}

void algorithm_test() { equal_test(); }
