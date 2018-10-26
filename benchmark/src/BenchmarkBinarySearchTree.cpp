#include <benchmark/benchmark.h>
#include <forest/BinarySearchTree.hpp>

static void BM_BinarySearchTree(benchmark::State & state) {
	forest::BinarySearchTree <int, int> BinarySearchTree;
	for (int i = 0; i < state.range(0); ++i) {
		BinarySearchTree.insert(i, 0);
	}

	for (auto _ : state) {
		benchmark::DoNotOptimize(BinarySearchTree.search(state.range(0)));
	}
}
BENCHMARK(BM_BinarySearchTree)->RangeMultiplier(2)->Range(1, 1 << 20)->Complexity();

BENCHMARK_MAIN();