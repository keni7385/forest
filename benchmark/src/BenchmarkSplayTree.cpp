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
#include <forest/SplayTree.hpp>
#include <random>

static void BM_SplayTree_Create_Average_Case(benchmark::State & state) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, static_cast<int>(state.range(0)));

	forest::SplayTree<int, int> SplayTree;

	for (auto _ : state) {
		for (int i = 0; i < state.range(0); ++i) {
			SplayTree.insert(dis(gen), 0);
		}
		state.PauseTiming();
		SplayTree.clear();
		state.ResumeTiming();
	}

	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_SplayTree_Create_Average_Case)->RangeMultiplier(2)->Range(1, 1 << 15)->Complexity(benchmark::oNLogN);

static void BM_SplayTree_Search_Average_Case(benchmark::State & state) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, static_cast<int>(state.range(0)));

	forest::SplayTree<int, int> SplayTree;

	for (int i = 0; i < state.range(0); ++i) {
		SplayTree.insert(dis(gen), 0);
	}

	for (auto _ : state) {
		benchmark::DoNotOptimize(SplayTree.search(dis(gen)));
	}

	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_SplayTree_Search_Average_Case)->RangeMultiplier(2)->Range(1, 1 << 15)->Complexity(benchmark::oLogN);

static void BM_SplayTree_Minimum_Average_Case(benchmark::State & state) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, static_cast<int>(state.range(0)));

	forest::SplayTree<int, int> SplayTree;

	for (int i = 0; i < state.range(0); ++i) {
		SplayTree.insert(dis(gen), 0);
	}

	for (auto _ : state) {
		benchmark::DoNotOptimize(SplayTree.minimum());
	}

	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_SplayTree_Minimum_Average_Case)->RangeMultiplier(2)->Range(1, 1 << 15)->Complexity(benchmark::o1);

static void BM_SplayTree_Maximum_Average_Case(benchmark::State & state) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, static_cast<int>(state.range(0)));

	forest::SplayTree<int, int> SplayTree;

	for (int i = 0; i < state.range(0); ++i) {
		SplayTree.insert(dis(gen), 0);
	}

	for (auto _ : state) {
		benchmark::DoNotOptimize(SplayTree.maximum());
	}

	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_SplayTree_Maximum_Average_Case)->RangeMultiplier(2)->Range(1, 1 << 15)->Complexity(benchmark::o1);

BENCHMARK_MAIN();
