#include <algorithm>
#include <random>
#include <vector>

#include <benchmark/benchmark.h>

// simply linear search function
bool linear_search(std::vector<int> data_set, int target) {
  for (auto &value : data_set) {
    if (value == target) {
      return true;
    }
  }
  return false;
}

// benchmark for Linear Search
static void Linear(benchmark::State &state) {
  // construct an inital vector of the correct size
  auto set = std::vector<int>(state.range());
  // iterate through the vector setting the values incrementally
  for (int i = 0; i < set.size(); ++i) {
    set[i] = i;
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(0, state.range());
  // randomly set the target
  int target = distr(gen);

  for (auto _ : state) {
    // code inside this loop is benchmarked
    bool result = linear_search(set, target);
    benchmark::DoNotOptimize(result); // prevents optimization
  }
}
// register the benchmark
BENCHMARK(Linear)->RangeMultiplier(2)->Range(8, 8 << 10);

// standard macro to run all registered benchmarks
BENCHMARK_MAIN();
