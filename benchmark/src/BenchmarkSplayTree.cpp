#include <benchmark/benchmark.h>
#include <forest/SplayTree.hpp>

static void BM_SplayTree(benchmark::State & state) {
	forest::SplayTree <int, int> SplayTree;
	for (int i = 0; i < state.range(0); ++i) {
		SplayTree.insert(i, 0);
	}

	for (auto _ : state) {
		benchmark::DoNotOptimize(SplayTree.search(state.range(0)));
	}
}
BENCHMARK(BM_SplayTree)->RangeMultiplier(2)->Range(1, 1 << 20)->Complexity();

BENCHMARK_MAIN();