#include <algorithm>
#include <random>
#include <vector>

#include <benchmark/benchmark.h>

// a simple binary search function
bool binary_search(std::vector<int> data_set, int target) {
  int low = 0;
  int high = data_set.size() - 1;

  while (low <= high) {
    // calculate mid to avoid potential overflow with (low + high) / 2
    int mid = low + (high - low) / 2;

    // check if the target is present at mid
    if (data_set[mid] == target) {
      return true; // target found, return its index
    }

    // if target is greater, ignore the left half
    if (data_set[mid] < target) {
      low = mid + 1;
    }
    // if target is smaller, ignore the right half
    else {
      high = mid - 1;
    }
  }

  return false; // target not found in the array
}

// Benchmark for Binary Search
static void Binary(benchmark::State &state) {
  auto set = std::vector<int>(state.range());

  for (int i = 0; i < set.size(); ++i) {
    set[i] = i;
  }
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(0, state.range());
  auto target = distr(gen);

  for (auto _ : state) {
    bool result = binary_search(set, target);
    benchmark::DoNotOptimize(result);
  }
}
// Register the benchmark
BENCHMARK(Binary)->RangeMultiplier(2)->Range(8, 8 << 10);

// Standard macro to run all registered benchmarks
BENCHMARK_MAIN();
