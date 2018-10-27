#include <benchmark/benchmark.h>
#include <forest/SplayTree.hpp>
#include <random>

static void BM_SplayTree_Search_Average_Case(benchmark::State & state) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, state.range(0) - 1);

	forest::SplayTree <int, int> SplayTree;
	for (int i = 0; i < state.range(0); ++i) {
		SplayTree.insert(dis(gen), 0);
	}

	for (auto _ : state) {
		benchmark::DoNotOptimize(SplayTree.search(dis(gen)));
	}
	state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_SplayTree_Search_Average_Case)->RangeMultiplier(2)->Range(1, 1 << 15)->Complexity(benchmark::oLogN);

BENCHMARK_MAIN();