#include "gbench.hpp"

static void BM_VectorConstructor(benchmark::State& state)
{
    for (auto _ : state)
    {
        USE_LIB::vector<int> v;
    }
}
BENCHMARK(BM_VectorConstructor);

static void BM_VectorConstructorWithSizeAndValue(benchmark::State& state)
{
    for (auto _ : state)
    {
        USE_LIB::vector<int> v(static_cast<size_t>(state.range(0)), 100);
    }
}
BENCHMARK(BM_VectorConstructorWithSizeAndValue)->Range(1, MAX_RANGE_SIZE);

static void BM_VectorPushBack(benchmark::State& state)
{
    USE_LIB::vector<int> v;
    for (auto _ : state)
    {
        for (int i = 0; i < state.range(0); ++i)
            v.push_back(i);
    }
}
BENCHMARK(BM_VectorPushBack)->Range(1, MAX_RANGE_SIZE);

static void BM_VectorClear(benchmark::State& state)
{
    USE_LIB::vector<int> v;
    for (int i = 0; i < state.range(0); ++i)
        v.push_back(i);
    for (auto _ : state)
        v.clear();
}
BENCHMARK(BM_VectorClear)->Range(1, MAX_RANGE_SIZE);

static void BM_VectorReserve(benchmark::State& state)
{
    USE_LIB::vector<int> v;
    for (auto _ : state)
        v.reserve(static_cast<size_t>(state.range(0)));
}
BENCHMARK(BM_VectorReserve)->Range(1, MAX_RANGE_SIZE);

static void BM_VectorInsert_from_begin(benchmark::State& state)
{
    USE_LIB::vector<int> v(1000);
    for (auto _ : state)
    {
        v.insert(v.begin(), state.range(0), 100);
    }
}
BENCHMARK(BM_VectorInsert_from_begin)->Range(1, MAX_RANGE_SIZE);

static void BM_VectorInsert_from_end(benchmark::State& state)
{
    USE_LIB::vector<int> v(1000);
    for (auto _ : state)
    {
        v.insert(v.end(), state.range(0), 100);
    }
}
BENCHMARK(BM_VectorInsert_from_end)->Range(1, MAX_RANGE_SIZE);

#include <sstream>

static void BM_VectorInsert_input_iterator(benchmark::State& state)
{
    USE_LIB::vector<int> v(1000);
    std::stringstream    ss;
    for (int i = 0; i < state.range(0); ++i)
        ss << i << " ";
    std::istream_iterator<int> ii(ss);
    std::istream_iterator<int> eos;
    for (auto _ : state)
    {
        v.insert(v.begin(), ii, eos);
    }
}
BENCHMARK(BM_VectorInsert_input_iterator)->Range(1, MAX_RANGE_SIZE);

static void BM_VectorInsert_forward_iterator(benchmark::State& state)
{
    USE_LIB::vector<int> v(1000);
    USE_LIB::vector<int> v2(state.range(0));
    for (auto _ : state)
    {
        v.insert(v.begin(), v2.begin(), v2.end());
    }
}
BENCHMARK(BM_VectorInsert_forward_iterator)->Range(1, MAX_RANGE_SIZE);

static void BM_VectorAssign(benchmark::State& state)
{
    USE_LIB::vector<int> v(1000);
    for (auto _ : state)
    {
        v.assign(static_cast<size_t>(state.range(0)), 100);
    }
}
BENCHMARK(BM_VectorAssign)->Range(1, MAX_RANGE_SIZE);

static void BM_VectorSwap(benchmark::State& state)
{
    USE_LIB::vector<int> v(1000);
    USE_LIB::vector<int> v2(state.range(0));
    for (auto _ : state)
    {
        v.swap(v2);
    }
}
BENCHMARK(BM_VectorSwap)->Range(1, MAX_RANGE_SIZE);