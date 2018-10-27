#include <benchmark/benchmark.h>
#include <forest/AVLTree.hpp>
#include <random>

static void BM_AVLTree_Search_Average_Case(benchmark::State & state) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, state.range(0) - 1);

	forest::AVLTree <int, int> AVLTree;
	for (int i = 0; i < state.range(0); ++i) {
		AVLTree.insert(dis(gen), 0);
	}

	for (auto _ : state) {
		benchmark::DoNotOptimize(AVLTree.search(dis(gen)));
	}
	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_AVLTree_Search_Average_Case)->RangeMultiplier(2)->Range(1, 1 << 20)->Complexity(benchmark::oLogN);

static void BM_AVLTree_Insert_Worst_Case(benchmark::State & state) {
	forest::AVLTree <int, int> AVLTree;

	for (auto _ : state) {
		for (int i = 0; i < state.range(0); ++i) {
			AVLTree.insert(i, 0);
		}
		state.PauseTiming();
		AVLTree.clear();
		state.ResumeTiming();
	}
	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_AVLTree_Insert_Worst_Case)->RangeMultiplier(2)->Range(1, 1 << 20)->Complexity(benchmark::oNLogN);

static void BM_AVLTree_Insert_Average_Case(benchmark::State & state) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, state.range(0) - 1);

	forest::AVLTree <int, int> AVLTree;
	
	for (auto _ : state) {
		for (int i = 0; i < state.range(0); ++i) {
			AVLTree.insert(dis(gen), 0);
		}
		state.PauseTiming();
		AVLTree.clear();
		state.ResumeTiming();
	}
	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_AVLTree_Insert_Average_Case)->RangeMultiplier(2)->Range(1, 1 << 20)->Complexity(benchmark::oNLogN);

BENCHMARK_MAIN();