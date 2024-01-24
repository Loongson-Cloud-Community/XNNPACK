// Copyright 2024 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <xnnpack.h>
#include <xnnpack/aligned-allocator.h>
#include <xnnpack/common.h>
#include <xnnpack/microfnptr.h>
#include <xnnpack/microparams-init.h>
#include <xnnpack/vunary.h>

#include <limits>

#include "bench/f32-vunary-benchmark.h"
#include "bench/utils.h"
#include <benchmark/benchmark.h>

void f32_vrsqrt(benchmark::State& state, xnn_f32_vrsqrt_ukernel_fn vrsqrt,
                xnn_init_f32_rsqrt_params_fn init_params = nullptr,
                benchmark::utils::IsaCheckFunction isa_check = nullptr) {
  f32_vunary_benchmark(state, vrsqrt, init_params, isa_check,
                       /*range_min=*/std::numeric_limits<float>::epsilon(),
                       /*range_max=*/10.0f);
}

#if XNN_ARCH_X86 || XNN_ARCH_X86_64
  BENCHMARK_CAPTURE(f32_vrsqrt, sse_rsqrt_u4,
                    xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_u4)
    ->Apply(benchmark::utils::UnaryElementwiseParameters<float, float>)
    ->UseRealTime();
  BENCHMARK_CAPTURE(f32_vrsqrt, sse_rsqrt_u8,
                    xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_u8)
    ->Apply(benchmark::utils::UnaryElementwiseParameters<float, float>)
    ->UseRealTime();

  BENCHMARK_CAPTURE(f32_vrsqrt, sse_rsqrt_iter_u4,
                    xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_iter_u4)
    ->Apply(benchmark::utils::UnaryElementwiseParameters<float, float>)
    ->UseRealTime();
  BENCHMARK_CAPTURE(f32_vrsqrt, sse_rsqrt_iter_u8,
                    xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_iter_u8)
    ->Apply(benchmark::utils::UnaryElementwiseParameters<float, float>)
    ->UseRealTime();

#endif  // XNN_ARCH_X86 || XNN_ARCH_X86_64

BENCHMARK_CAPTURE(f32_vrsqrt, scalar_recip_sqrt_u1,
                  xnn_f32_vrsqrt_ukernel__scalar_recip_sqrt_u1)
    ->Apply(benchmark::utils::UnaryElementwiseParameters<float, float>)
    ->UseRealTime();
BENCHMARK_CAPTURE(f32_vrsqrt, scalar_recip_sqrt_u2,
                  xnn_f32_vrsqrt_ukernel__scalar_recip_sqrt_u2)
    ->Apply(benchmark::utils::UnaryElementwiseParameters<float, float>)
    ->UseRealTime();
BENCHMARK_CAPTURE(f32_vrsqrt, scalar_recip_sqrt_u4,
                  xnn_f32_vrsqrt_ukernel__scalar_recip_sqrt_u4)
    ->Apply(benchmark::utils::UnaryElementwiseParameters<float, float>)
    ->UseRealTime();

#ifndef XNNPACK_BENCHMARK_NO_MAIN
BENCHMARK_MAIN();
#endif
