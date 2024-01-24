// Copyright 2024 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#ifndef __XNNPACK_BENCH_F32_VUNARY_BENCHMARK_H_
#define __XNNPACK_BENCH_F32_VUNARY_BENCHMARK_H_

#include <xnnpack.h>
#include <xnnpack/aligned-allocator.h>
#include <xnnpack/common.h>
#include <xnnpack/microfnptr.h>
#include <xnnpack/microparams-init.h>
#include <xnnpack/vunary.h>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <random>
#include <vector>

#include "bench/utils.h"
#include <benchmark/benchmark.h>

// Parameter initialization function, templated on the `UKernelParams` type,
// used in `f32_vunary_benchmark` below.
template <typename UKernelParams>
using InitParamsFunction =
    size_t (*)(UKernelParams params[XNN_MIN_ELEMENTS(1)]);

// Template function to generate unary benchmarks. Creates a vector of size
// `state.range(0)` containing uniformly distributed random numbers in the range
// [`range_min`, `range_max`) and calls `ukernel` on it.
//
// The `init_params` and `isa_check` parameters may be `nullptr`.
//
// For an example of how to use this template in benchmarks, see `f32-vsqrt.cc`.
template <typename UKernelFunction, typename UKernelParams>
void f32_vunary_benchmark(benchmark::State& state, UKernelFunction ukernel,
                          InitParamsFunction<UKernelParams> init_params,
                          benchmark::utils::IsaCheckFunction isa_check,
                          float range_min, float range_max) {
  if (isa_check != nullptr && !isa_check(state)) {
    return;
  }

  const size_t num_elements = state.range(0);
  std::vector<float, AlignedAllocator<float, 64>> input(num_elements);
  std::vector<float, AlignedAllocator<float, 64>> output(num_elements);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto f32rng =
      std::bind(std::uniform_real_distribution<float>(range_min, range_max),
                std::ref(rng));
  std::generate(input.begin(), input.end(), std::ref(f32rng));
  std::fill(output.begin(), output.end(), std::nanf(""));

  UKernelParams params;
  if (init_params != nullptr) {
    init_params(&params);
  }
  for (auto _ : state) {
    ukernel(num_elements * sizeof(float), input.data(), output.data(), &params);
  }

  const uint64_t cpu_frequency = benchmark::utils::GetCurrentCpuFrequency();
  if (cpu_frequency != 0) {
    state.counters["cpufreq"] = cpu_frequency;
  }

  const size_t elements_per_iteration = num_elements;
  state.counters["elements"] = benchmark::Counter(
      static_cast<uint64_t>(state.iterations()) * elements_per_iteration,
      benchmark::Counter::kIsRate);

  const size_t bytes_per_iteration = 2 * num_elements * sizeof(float);
  state.counters["bytes"] = benchmark::Counter(
      static_cast<uint64_t>(state.iterations()) * bytes_per_iteration,
      benchmark::Counter::kIsRate);
}

#endif  // __XNNPACK_BENCH_F32_VUNARY_BENCHMARK_H_
