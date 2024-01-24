// Auto-generated file. Do not edit!
//   Template: src/f32-vrsqrt/sse-rsqrt.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>
#include <xmmintrin.h>
#include <xnnpack/common.h>
#include <xnnpack/vunary.h>


void xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_u4(
    size_t batch, const float* input, float* output,
    const union xnn_f32_rsqrt_params params[restrict XNN_MIN_ELEMENTS(1)])
    XNN_OOB_READS {
  assert(batch != 0);
  assert(batch % sizeof(float) == 0);
  assert(input != NULL);
  assert(output != NULL);
  
  // Constants for the Newton-Raphson iteration.
  const __m128 kOne = _mm_set1_ps(1.0f);

  for (; batch >= 4 * sizeof(float); batch -= 4 * sizeof(float)) {
    const __m128 vx = _mm_loadu_ps(input);
    input += 4;

    const __m128 vt = _mm_sqrt_ps(vx);
    const __m128 vy = _mm_div_ps(kOne, vt);

    _mm_storeu_ps(output, vy);
    output += 4;
  }
  if XNN_UNLIKELY(batch != 0) {
    const __m128 vx = _mm_loadu_ps(input);

    const __m128 vt = _mm_sqrt_ps(vx);
    __m128 vy = _mm_div_ps(kOne, vt);

    if (batch & (2 * sizeof(float))) {
      _mm_storel_pi((__m64*) output, vy);
      vy = _mm_movehl_ps(vy, vy);
      output += 2;
    }
    if (batch & (1 * sizeof(float))) {
      _mm_store_ss(output, vy);
    }
  }
}
