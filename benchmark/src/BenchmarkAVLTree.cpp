#include <benchmark/benchmark.h>
#include <forest/AVLTree.hpp>

static void BM_AVLTree(benchmark::State & state) {
	forest::AVLTree <int, int> AVLTree;
	for (int i = 0; i < state.range(0); ++i) {
		AVLTree.insert(i, 0);
	}

	for (auto _ : state) {
		benchmark::DoNotOptimize(AVLTree.search(state.range(0)));
	}
}
BENCHMARK(BM_AVLTree)->RangeMultiplier(2)->Range(1, 1 << 20)->Complexity();

BENCHMARK_MAIN();