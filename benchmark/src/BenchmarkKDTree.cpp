/*
	MIT License

	Copyright(c) 2017 George Fotopoulos

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include <benchmark/benchmark.h>
#include <forest/KDTree.hpp>
#include <random>

static void BM_KDTree_Create_Average_Case(benchmark::State & state) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-state.range(0) / 2, state.range(0) / 2);

	forest::KDTree <double, 2> KDTree;

	for (auto _ : state) {
		state.PauseTiming();
		KDTree.clear();
		state.ResumeTiming();
		for (int i = 0; i < state.range(0); ++i) {
			KDTree.insert({ dis(gen), dis(gen) });
		}
	}

	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_KDTree_Create_Average_Case)->RangeMultiplier(2)->Range(2, 1 << 20)->Complexity(benchmark::oNLogN);

static void BM_KDTree_Search_Average_Case(benchmark::State & state) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-state.range(0) / 2, state.range(0) / 2);

	forest::KDTree <double, 2> KDTree;

	for (int i = 0; i < state.range(0); ++i) {
		KDTree.insert({ dis(gen), dis(gen)});
	}

	for (auto _ : state) {
		benchmark::DoNotOptimize(KDTree.search({ dis(gen), dis(gen) }));
	}

	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_KDTree_Search_Average_Case)->RangeMultiplier(2)->Range(2, 1 << 20)->Complexity(benchmark::oLogN);

BENCHMARK_MAIN();