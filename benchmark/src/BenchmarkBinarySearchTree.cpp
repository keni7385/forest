#include <benchmark/benchmark.h>
#include <forest/BinarySearchTree.hpp>
#include <random>

static void BM_BinarySearchTree_Search_Worst_Case(benchmark::State & state) {
	forest::BinarySearchTree <int, int> BinarySearchTree;

	for (int i = 0; i < state.range(0); ++i) {
		BinarySearchTree.insert(i, 0);
	}

	for (auto _ : state) {
		benchmark::DoNotOptimize(BinarySearchTree.search(state.range(0) - 1));
	}
	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_BinarySearchTree_Search_Worst_Case)->RangeMultiplier(2)->Range(1, 1 << 15)->Complexity(benchmark::oN);

static void BM_BinarySearchTree_Search_Average_Case(benchmark::State & state) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, state.range(0) - 1);

	forest::BinarySearchTree <int, int> BinarySearchTree;
	for (int i = 0; i < state.range(0); ++i) {
		BinarySearchTree.insert(dis(gen), 0);
	}

	for (auto _ : state) {
		benchmark::DoNotOptimize(BinarySearchTree.search(dis(gen)));
	}
	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_BinarySearchTree_Search_Average_Case)->RangeMultiplier(2)->Range(1, 1 << 15)->Complexity(benchmark::oLogN);

static void BM_BinarySearchTree_Insert_Worst_Case(benchmark::State & state) {
	forest::BinarySearchTree <int, int> BinarySearchTree;

	for (auto _ : state) {
		for (int i = 0; i < state.range(0); ++i) {
			BinarySearchTree.insert(i, 0);
		}
		state.PauseTiming();
		BinarySearchTree.clear();
		state.ResumeTiming();
	}
	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_BinarySearchTree_Insert_Worst_Case)->RangeMultiplier(2)->Range(1, 1 << 15)->Complexity(benchmark::oNSquared);

static void BM_BinarySearchTree_Insert_Average_Case(benchmark::State & state) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, state.range(0) - 1);

	forest::BinarySearchTree <int, int> BinarySearchTree;

	for (auto _ : state) {
		for (int i = 0; i < state.range(0); ++i) {
			BinarySearchTree.insert(dis(gen), 0);
		}
		state.PauseTiming();
		BinarySearchTree.clear();
		state.ResumeTiming();
	}
	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_BinarySearchTree_Insert_Average_Case)->RangeMultiplier(2)->Range(1, 1 << 15)->Complexity(benchmark::oNLogN);

BENCHMARK_MAIN();