#include <benchmark/benchmark.h>
#include <vector>
#include <MyUMap.hpp>
#include <unordered_map>


static UMap<std::string,int> map;
void MyUMapAddTest()
{
    for(int i = 0; i < 1000; ++i)
    {
        map.add("word" + std::to_string(i), i);
    }
}

void MyUMapGetValueTest()
{
    for(int i = 0; i < 1000; ++i)
    {
        map.getValue("word" + std::to_string(i));
    }
}

static std::unordered_map<std::string,int> stdmap;
void STDUMapAddTest()
{
    for(int i = 0; i < 1000; ++i)
    {
        stdmap["word" + std::to_string(i)] = i;
    }
}

void STDUMapGetValueTest()
{
    for(int i = 0; i < 1000; ++i)
    {
        stdmap["word" + std::to_string(i)];
    }
}

//BM - benchmark
static void BM_MyUMap_AddTest(benchmark::State& state)
{
    for(auto _ : state)
    {
        MyUMapAddTest();
    }
}

static void BM_MyUMap_GetValueTest(benchmark::State& state)
{
    for(auto _ : state)
    {
        MyUMapGetValueTest();
    }
}

static void BM_STDUMap_AddTest(benchmark::State& state)
{
    for(auto _ : state)
    {
        STDUMapAddTest();
    }
}

static void BM_STDUMap_GetValueTest(benchmark::State& state)
{
    for(auto _ : state)
    {
        STDUMapGetValueTest();
    }
}

BENCHMARK(BM_MyUMap_AddTest);
BENCHMARK(BM_STDUMap_AddTest);
BENCHMARK(BM_MyUMap_GetValueTest);
BENCHMARK(BM_STDUMap_GetValueTest);
BENCHMARK_MAIN();
