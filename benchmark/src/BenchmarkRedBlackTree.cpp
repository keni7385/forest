#include <benchmark/benchmark.h>
#include <forest/RedBlackTree.hpp>
#include <random>

static void BM_RedBlackTree_Search_Average_Case(benchmark::State & state) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, state.range(0) - 1);

	forest::RedBlackTree <int, int> RedBlackTree;
	for (int i = 0; i < state.range(0); ++i) {
		RedBlackTree.insert(dis(gen), 0);
	}

	for (auto _ : state) {
		benchmark::DoNotOptimize(RedBlackTree.search(dis(gen)));
	}
	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_RedBlackTree_Search_Average_Case)->RangeMultiplier(2)->Range(1, 1 << 20)->Complexity(benchmark::oLogN);

BENCHMARK_MAIN();