#include <benchmark/benchmark.h>
#include <forest/RedBlackTree.hpp>

static void BM_RedBlackTree(benchmark::State & state) {
	forest::RedBlackTree <int, int> RedBlackTree;
	for (int i = 0; i < state.range(0); ++i) {
		RedBlackTree.insert(i, 0);
	}

	for (auto _ : state) {
		benchmark::DoNotOptimize(RedBlackTree.search(state.range(0)));
	}
}
BENCHMARK(BM_RedBlackTree)->RangeMultiplier(2)->Range(1, 1 << 20)->Complexity();

BENCHMARK_MAIN();