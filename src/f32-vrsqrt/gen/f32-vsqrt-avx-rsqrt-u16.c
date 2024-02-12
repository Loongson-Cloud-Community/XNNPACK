// Auto-generated file. Do not edit!
//   Template: src/f32-vrsqrt/avx-rsqrt.c.in
//   Generator: tools/xngen
//
// Copyright 2024 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>
#include <immintrin.h>
#include <stddef.h>
#include <stdint.h>
#include <xmmintrin.h>
#include <xnnpack/common.h>
#include <xnnpack/microparams.h>
#include <xnnpack/vunary.h>


// In the following, we do a single Newton-Raphson step on the equation
// $x^{-2} - a$, which expands to:
//
//  $$x_{k+1} = 0.5 * x_k * (3.0 - a * x_k^2)$$
//
// So we do the following steps:
//
//  1. t0 = x_k
//  2. t1 = t0 * t0   (x_k^2)
//  3. t2 = a * t1    (a * x_k^2)
//  4. t3 = 3.0 - t2  (3.0 - a * x_k^2)
//  5. t4 = 0.5 * t0  (0.5 * x_k)
//  6. y  = t3 * t4   (0.5 * x_k * (3.0 - a * x_k^2))
//
// Where $x_k$ is the original 12-bit approximation and `y` contains the final
// 24-bit approximation $x_{k+1}$.

void xnn_f32_vrsqrt_ukernel__avx_recip_sqrt_u16(
    size_t batch, const float* input, float* output,
    const union xnn_f32_rsqrt_params params[restrict XNN_MIN_ELEMENTS(1)])
    XNN_OOB_READS {
  assert(batch != 0);
  assert(batch % sizeof(float) == 0);
  assert(input != NULL);
  assert(output != NULL);
  
  // Constants for the Newton-Raphson iteration.
  const __m256 kThree = _mm256_set1_ps(3.0f);
  const __m256 kHalf = _mm256_set1_ps(0.5f);

  for (; batch >= 16 * sizeof(float); batch -= 16 * sizeof(float)) {
    const __m256 va01234567 = _mm256_loadu_ps(input);
    const __m256 va89ABCDEF = _mm256_loadu_ps(input + 8);
    input += 16;

    // Generate the initial 12-bit approximation.
    const __m256 vt0_01234567 = _mm256_rsqrt_ps(va01234567);
    const __m256 vt0_89ABCDEF = _mm256_rsqrt_ps(va89ABCDEF);

    // Do a single Newton-Raphson step as described above.
    const __m256 vt1_01234567 = _mm256_mul_ps(vt0_01234567, vt0_01234567);
    const __m256 vt1_89ABCDEF = _mm256_mul_ps(vt0_89ABCDEF, vt0_89ABCDEF);
    const __m256 vt2_01234567 = _mm256_mul_ps(va01234567, vt1_01234567);
    const __m256 vt2_89ABCDEF = _mm256_mul_ps(va89ABCDEF, vt1_89ABCDEF);
    const __m256 vt3_01234567 = _mm256_sub_ps(kThree, vt2_01234567);
    const __m256 vt3_89ABCDEF = _mm256_sub_ps(kThree, vt2_89ABCDEF);
    const __m256 vt4_01234567 = _mm256_mul_ps(kHalf, vt0_01234567);
    const __m256 vt4_89ABCDEF = _mm256_mul_ps(kHalf, vt0_89ABCDEF);
    const __m256 vy01234567 = _mm256_mul_ps(vt3_01234567, vt4_01234567);
    const __m256 vy89ABCDEF = _mm256_mul_ps(vt3_89ABCDEF, vt4_89ABCDEF);

    // Store the results.
    _mm256_storeu_ps(output, vy01234567);
    _mm256_storeu_ps(output + 8, vy89ABCDEF);
    output += 16;
  }
  for (; batch >= 8 * sizeof(float); batch -= 8 * sizeof(float)) {
    const __m256 va = _mm256_loadu_ps(input);
    input += 8;

    // Generate the initial 12-bit approximation.
    const __m256 vt0 = _mm256_rsqrt_ps(va);

    // Do a single Newton-Raphson step as described above.
    const __m256 vt1 = _mm256_mul_ps(vt0, vt0);
    const __m256 vt2 = _mm256_mul_ps(va, vt1);
    const __m256 vt3 = _mm256_sub_ps(kThree, vt2);
    const __m256 vt4 = _mm256_mul_ps(kHalf, vt0);
    const __m256 vy = _mm256_mul_ps(vt3, vt4);

    _mm256_storeu_ps(output, vy);
    output += 8;
  }
  if XNN_UNLIKELY(batch != 0) {
    assert(batch >= 1 * sizeof(float));
    assert(batch <= 7 * sizeof(float));
    const __m256i vmask = _mm256_loadu_si256(
        (const __m256i*)((uintptr_t)&params->avx.mask_table[7] - batch));

    const __m256 va = _mm256_maskload_ps(input, vmask);

    // Generate the initial 12-bit approximation.
    const __m256 vt0 = _mm256_rsqrt_ps(va);

    // Do a single Newton-Raphson step as described above.
    const __m256 vt1 = _mm256_mul_ps(vt0, vt0);
    const __m256 vt2 = _mm256_mul_ps(va, vt1);
    const __m256 vt3 = _mm256_sub_ps(kThree, vt2);
    const __m256 vt4 = _mm256_mul_ps(kHalf, vt0);
    __m256 vy = _mm256_mul_ps(vt3, vt4);

    __m128 vy_lo = _mm256_castps256_ps128(vy);
    if (batch & (4 * sizeof(float))) {
      _mm_storeu_ps(output, vy_lo);
      vy_lo = _mm256_extractf128_ps(vy, 1);
      output += 4;
    }
    if (batch & (2 * sizeof(float))) {
      _mm_storel_pi((__m64*) output, vy_lo);
      vy_lo = _mm_movehl_ps(vy_lo, vy_lo);
      output += 2;
    }
    if (batch & (1 * sizeof(float))) {
      _mm_store_ss(output, vy_lo);
    }
  }
}
