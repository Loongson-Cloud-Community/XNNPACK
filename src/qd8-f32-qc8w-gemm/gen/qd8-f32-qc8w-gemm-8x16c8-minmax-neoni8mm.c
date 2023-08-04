// Auto-generated file. Do not edit!
//   Template: src/qs8-gemm/c8-neoni8mm.c.in
//   Generator: tools/xngen
//
// Copyright 2023 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <arm_neon.h>

#include <xnnpack/gemm.h>
#include <xnnpack/math.h>


void xnn_qd8_f32_qc8w_gemm_minmax_ukernel_8x16c8__neoni8mm(
    size_t mr,
    size_t nc,
    size_t kc,
    const int8_t* restrict a,
    size_t a_stride,
    const void* restrict w,
    float* restrict c,
    size_t cm_stride,
    size_t cn_stride,
    const union xnn_f32_minmax_params params[restrict XNN_MIN_ELEMENTS(1)],
    const struct xnn_qd8_quantization_params quantization_params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(mr != 0);
  assert(mr <= 8);
  assert(nc != 0);
  assert(kc != 0);
  assert(kc % sizeof(int8_t) == 0);
  assert(a != NULL);
  assert(w != NULL);
  assert(c != NULL);

  kc = round_up_po2(kc, 8 * sizeof(int8_t));
  const int8_t* a0 = a;
  float* c0 = c;
  const int8_t* a1 = (const int8_t*) ((uintptr_t) a0 + a_stride);
  float* c1 = (float*) ((uintptr_t) c0 + cm_stride);
  if XNN_UNPREDICTABLE(mr < 2) {
    a1 = a0;
    c1 = c0;
  }
  const int8_t* a2 = (const int8_t*) ((uintptr_t) a1 + a_stride);
  float* c2 = (float*) ((uintptr_t) c1 + cm_stride);
  if XNN_UNPREDICTABLE(mr <= 2) {
    a2 = a1;
    c2 = c1;
  }
  const int8_t* a3 = (const int8_t*) ((uintptr_t) a2 + a_stride);
  float* c3 = (float*) ((uintptr_t) c2 + cm_stride);
  if XNN_UNPREDICTABLE(mr < 4) {
    a3 = a2;
    c3 = c2;
  }
  const int8_t* a4 = (const int8_t*) ((uintptr_t) a3 + a_stride);
  float* c4 = (float*) ((uintptr_t) c3 + cm_stride);
  if XNN_UNPREDICTABLE(mr <= 4) {
    a4 = a3;
    c4 = c3;
  }
  const int8_t* a5 = (const int8_t*) ((uintptr_t) a4 + a_stride);
  float* c5 = (float*) ((uintptr_t) c4 + cm_stride);
  if XNN_UNPREDICTABLE(mr < 6) {
    a5 = a4;
    c5 = c4;
  }
  const int8_t* a6 = (const int8_t*) ((uintptr_t) a5 + a_stride);
  float* c6 = (float*) ((uintptr_t) c5 + cm_stride);
  if XNN_UNPREDICTABLE(mr <= 6) {
    a6 = a5;
    c6 = c5;
  }
  const int8_t* a7 = (const int8_t*) ((uintptr_t) a6 + a_stride);
  float* c7 = (float*) ((uintptr_t) c6 + cm_stride);
  if XNN_UNPREDICTABLE(mr != 8) {
    a7 = a6;
    c7 = c6;
  }

  // Loop over groups of 16 columns.
  do {
    // Initialize accumulators with bias. 16 bias values are loaded from the
    // weight matrix, at the start of the group of 16 columns.
    const int32x4_t vinput_zero_point01 = vld1q_s32(&quantization_params[0].zero_point);
    const int32x4_t vksum0123 = vld1q_s32(w); w = (const int32_t*) w + 4;
    const int32x4_t vksumzp0x0123 = vmulq_lane_s32(vksum0123, vget_low_s32(vinput_zero_point01), 0);
    const int32x4_t vksumzp1x0123 = vmulq_lane_s32(vksum0123, vget_high_s32(vinput_zero_point01), 0);
    const int32x4_t vksum4567 = vld1q_s32(w); w = (const int32_t*) w + 4;
    const int32x4_t vksumzp0x4567 = vmulq_lane_s32(vksum4567, vget_low_s32(vinput_zero_point01), 0);
    const int32x4_t vksumzp1x4567 = vmulq_lane_s32(vksum4567, vget_high_s32(vinput_zero_point01), 0);
    const int32x4_t vksum89AB = vld1q_s32(w); w = (const int32_t*) w + 4;
    const int32x4_t vksumzp0x89AB = vmulq_lane_s32(vksum89AB, vget_low_s32(vinput_zero_point01), 0);
    const int32x4_t vksumzp1x89AB = vmulq_lane_s32(vksum89AB, vget_high_s32(vinput_zero_point01), 0);
    const int32x4_t vksumCDEF = vld1q_s32(w); w = (const int32_t*) w + 4;
    const int32x4_t vksumzp0xCDEF = vmulq_lane_s32(vksumCDEF, vget_low_s32(vinput_zero_point01), 0);
    const int32x4_t vksumzp1xCDEF = vmulq_lane_s32(vksumCDEF, vget_high_s32(vinput_zero_point01), 0);
    const int32x4_t vinput_zero_point23 = vld1q_s32(&quantization_params[2].zero_point);
    const int32x4_t vksumzp2x0123 = vmulq_lane_s32(vksum0123, vget_low_s32(vinput_zero_point23), 0);
    const int32x4_t vksumzp3x0123 = vmulq_lane_s32(vksum0123, vget_high_s32(vinput_zero_point23), 0);
    const int32x4_t vksumzp2x4567 = vmulq_lane_s32(vksum4567, vget_low_s32(vinput_zero_point23), 0);
    const int32x4_t vksumzp3x4567 = vmulq_lane_s32(vksum4567, vget_high_s32(vinput_zero_point23), 0);
    const int32x4_t vksumzp2x89AB = vmulq_lane_s32(vksum89AB, vget_low_s32(vinput_zero_point23), 0);
    const int32x4_t vksumzp3x89AB = vmulq_lane_s32(vksum89AB, vget_high_s32(vinput_zero_point23), 0);
    const int32x4_t vksumzp2xCDEF = vmulq_lane_s32(vksumCDEF, vget_low_s32(vinput_zero_point23), 0);
    const int32x4_t vksumzp3xCDEF = vmulq_lane_s32(vksumCDEF, vget_high_s32(vinput_zero_point23), 0);
    const int32x4_t vinput_zero_point45 = vld1q_s32(&quantization_params[4].zero_point);
    const int32x4_t vksumzp4x0123 = vmulq_lane_s32(vksum0123, vget_low_s32(vinput_zero_point45), 0);
    const int32x4_t vksumzp5x0123 = vmulq_lane_s32(vksum0123, vget_high_s32(vinput_zero_point45), 0);
    const int32x4_t vksumzp4x4567 = vmulq_lane_s32(vksum4567, vget_low_s32(vinput_zero_point45), 0);
    const int32x4_t vksumzp5x4567 = vmulq_lane_s32(vksum4567, vget_high_s32(vinput_zero_point45), 0);
    const int32x4_t vksumzp4x89AB = vmulq_lane_s32(vksum89AB, vget_low_s32(vinput_zero_point45), 0);
    const int32x4_t vksumzp5x89AB = vmulq_lane_s32(vksum89AB, vget_high_s32(vinput_zero_point45), 0);
    const int32x4_t vksumzp4xCDEF = vmulq_lane_s32(vksumCDEF, vget_low_s32(vinput_zero_point45), 0);
    const int32x4_t vksumzp5xCDEF = vmulq_lane_s32(vksumCDEF, vget_high_s32(vinput_zero_point45), 0);
    const int32x4_t vinput_zero_point67 = vld1q_s32(&quantization_params[6].zero_point);
    const int32x4_t vksumzp6x0123 = vmulq_lane_s32(vksum0123, vget_low_s32(vinput_zero_point67), 0);
    const int32x4_t vksumzp7x0123 = vmulq_lane_s32(vksum0123, vget_high_s32(vinput_zero_point67), 0);
    const int32x4_t vksumzp6x4567 = vmulq_lane_s32(vksum4567, vget_low_s32(vinput_zero_point67), 0);
    const int32x4_t vksumzp7x4567 = vmulq_lane_s32(vksum4567, vget_high_s32(vinput_zero_point67), 0);
    const int32x4_t vksumzp6x89AB = vmulq_lane_s32(vksum89AB, vget_low_s32(vinput_zero_point67), 0);
    const int32x4_t vksumzp7x89AB = vmulq_lane_s32(vksum89AB, vget_high_s32(vinput_zero_point67), 0);
    const int32x4_t vksumzp6xCDEF = vmulq_lane_s32(vksumCDEF, vget_low_s32(vinput_zero_point67), 0);
    const int32x4_t vksumzp7xCDEF = vmulq_lane_s32(vksumCDEF, vget_high_s32(vinput_zero_point67), 0);
    int32x4_t vacc01x01 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vksumzp0x0123), vreinterpretq_u64_s32(vksumzp1x0123)));
    int32x4_t vacc01x23 = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vksumzp0x0123), vreinterpretq_u64_s32(vksumzp1x0123)));
    int32x4_t vacc01x45 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vksumzp0x4567), vreinterpretq_u64_s32(vksumzp1x4567)));
    int32x4_t vacc01x67 = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vksumzp0x4567), vreinterpretq_u64_s32(vksumzp1x4567)));
    int32x4_t vacc01x89 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vksumzp0x89AB), vreinterpretq_u64_s32(vksumzp1x89AB)));
    int32x4_t vacc01xAB = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vksumzp0x89AB), vreinterpretq_u64_s32(vksumzp1x89AB)));
    int32x4_t vacc01xCD = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vksumzp0xCDEF), vreinterpretq_u64_s32(vksumzp1xCDEF)));
    int32x4_t vacc01xEF = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vksumzp0xCDEF), vreinterpretq_u64_s32(vksumzp1xCDEF)));
    int32x4_t vacc23x01 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vksumzp2x0123), vreinterpretq_u64_s32(vksumzp3x0123)));
    int32x4_t vacc23x23 = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vksumzp2x0123), vreinterpretq_u64_s32(vksumzp3x0123)));
    int32x4_t vacc23x45 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vksumzp2x4567), vreinterpretq_u64_s32(vksumzp3x4567)));
    int32x4_t vacc23x67 = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vksumzp2x4567), vreinterpretq_u64_s32(vksumzp3x4567)));
    int32x4_t vacc23x89 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vksumzp2x89AB), vreinterpretq_u64_s32(vksumzp3x89AB)));
    int32x4_t vacc23xAB = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vksumzp2x89AB), vreinterpretq_u64_s32(vksumzp3x89AB)));
    int32x4_t vacc23xCD = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vksumzp2xCDEF), vreinterpretq_u64_s32(vksumzp3xCDEF)));
    int32x4_t vacc23xEF = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vksumzp2xCDEF), vreinterpretq_u64_s32(vksumzp3xCDEF)));
    int32x4_t vacc45x01 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vksumzp4x0123), vreinterpretq_u64_s32(vksumzp5x0123)));
    int32x4_t vacc45x23 = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vksumzp4x0123), vreinterpretq_u64_s32(vksumzp5x0123)));
    int32x4_t vacc45x45 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vksumzp4x4567), vreinterpretq_u64_s32(vksumzp5x4567)));
    int32x4_t vacc45x67 = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vksumzp4x4567), vreinterpretq_u64_s32(vksumzp5x4567)));
    int32x4_t vacc45x89 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vksumzp4x89AB), vreinterpretq_u64_s32(vksumzp5x89AB)));
    int32x4_t vacc45xAB = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vksumzp4x89AB), vreinterpretq_u64_s32(vksumzp5x89AB)));
    int32x4_t vacc45xCD = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vksumzp4xCDEF), vreinterpretq_u64_s32(vksumzp5xCDEF)));
    int32x4_t vacc45xEF = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vksumzp4xCDEF), vreinterpretq_u64_s32(vksumzp5xCDEF)));
    int32x4_t vacc67x01 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vksumzp6x0123), vreinterpretq_u64_s32(vksumzp7x0123)));
    int32x4_t vacc67x23 = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vksumzp6x0123), vreinterpretq_u64_s32(vksumzp7x0123)));
    int32x4_t vacc67x45 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vksumzp6x4567), vreinterpretq_u64_s32(vksumzp7x4567)));
    int32x4_t vacc67x67 = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vksumzp6x4567), vreinterpretq_u64_s32(vksumzp7x4567)));
    int32x4_t vacc67x89 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vksumzp6x89AB), vreinterpretq_u64_s32(vksumzp7x89AB)));
    int32x4_t vacc67xAB = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vksumzp6x89AB), vreinterpretq_u64_s32(vksumzp7x89AB)));
    int32x4_t vacc67xCD = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vksumzp6xCDEF), vreinterpretq_u64_s32(vksumzp7xCDEF)));
    int32x4_t vacc67xEF = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vksumzp6xCDEF), vreinterpretq_u64_s32(vksumzp7xCDEF)));

    // Inner accumulation loop along the 16 columns.
    size_t k = kc;
    // 2x partial unrolled loop to load 8 bytes at a time.
    while (k >= 16 * sizeof(int8_t)) {
      // Load a 8x16 block of activations.
      const int8x16_t va0x0123456789ABCDEF = vld1q_s8(a0); a0 += 16;
      const int8x16_t va1x0123456789ABCDEF = vld1q_s8(a1); a1 += 16;
      const int8x16_t va2x0123456789ABCDEF = vld1q_s8(a2); a2 += 16;
      const int8x16_t va3x0123456789ABCDEF = vld1q_s8(a3); a3 += 16;
      const int8x16_t va4x0123456789ABCDEF = vld1q_s8(a4); a4 += 16;
      const int8x16_t va5x0123456789ABCDEF = vld1q_s8(a5); a5 += 16;
      const int8x16_t va6x0123456789ABCDEF = vld1q_s8(a6); a6 += 16;
      const int8x16_t va7x0123456789ABCDEF = vld1q_s8(a7); a7 += 16;
      const int8x16_t va01x01234567 = vreinterpretq_s8_u64(vtrn1q_u64(vreinterpretq_u64_s8(va0x0123456789ABCDEF), vreinterpretq_u64_s8(va1x0123456789ABCDEF)));
      const int8x16_t va01x89ABCDEF = vreinterpretq_s8_u64(vtrn2q_u64(vreinterpretq_u64_s8(va0x0123456789ABCDEF), vreinterpretq_u64_s8(va1x0123456789ABCDEF)));
      const int8x16_t va23x01234567 = vreinterpretq_s8_u64(vtrn1q_u64(vreinterpretq_u64_s8(va2x0123456789ABCDEF), vreinterpretq_u64_s8(va3x0123456789ABCDEF)));
      const int8x16_t va23x89ABCDEF = vreinterpretq_s8_u64(vtrn2q_u64(vreinterpretq_u64_s8(va2x0123456789ABCDEF), vreinterpretq_u64_s8(va3x0123456789ABCDEF)));
      const int8x16_t va45x01234567 = vreinterpretq_s8_u64(vtrn1q_u64(vreinterpretq_u64_s8(va4x0123456789ABCDEF), vreinterpretq_u64_s8(va5x0123456789ABCDEF)));
      const int8x16_t va45x89ABCDEF = vreinterpretq_s8_u64(vtrn2q_u64(vreinterpretq_u64_s8(va4x0123456789ABCDEF), vreinterpretq_u64_s8(va5x0123456789ABCDEF)));
      const int8x16_t va67x01234567 = vreinterpretq_s8_u64(vtrn1q_u64(vreinterpretq_u64_s8(va6x0123456789ABCDEF), vreinterpretq_u64_s8(va7x0123456789ABCDEF)));
      const int8x16_t va67x89ABCDEF = vreinterpretq_s8_u64(vtrn2q_u64(vreinterpretq_u64_s8(va6x0123456789ABCDEF), vreinterpretq_u64_s8(va7x0123456789ABCDEF)));

      // Load a 16x16 block of weights.
      const int8x16_t vb01x01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
      const int8x16_t vb23x01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
      const int8x16_t vb45x01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
      const int8x16_t vb67x01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
      const int8x16_t vb89x01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
      const int8x16_t vb1011x01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
      const int8x16_t vb1213x01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
      const int8x16_t vb1415x01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
      const int8x16_t vb01x89ABCDEF = vld1q_s8(w); w = (const int8_t*) w + 16;
      const int8x16_t vb23x89ABCDEF = vld1q_s8(w); w = (const int8_t*) w + 16;
      const int8x16_t vb45x89ABCDEF = vld1q_s8(w); w = (const int8_t*) w + 16;
      const int8x16_t vb67x89ABCDEF = vld1q_s8(w); w = (const int8_t*) w + 16;
      const int8x16_t vb89x89ABCDEF = vld1q_s8(w); w = (const int8_t*) w + 16;
      const int8x16_t vb1011x89ABCDEF = vld1q_s8(w); w = (const int8_t*) w + 16;
      const int8x16_t vb1213x89ABCDEF = vld1q_s8(w); w = (const int8_t*) w + 16;
      const int8x16_t vb1415x89ABCDEF = vld1q_s8(w); w = (const int8_t*) w + 16;

      // Multiply-accumulate: 8x8 * 8x16 --> 8x16.
      vacc01x01 = vmmlaq_s32(vacc01x01, va01x01234567, vb01x01234567);
      vacc01x23 = vmmlaq_s32(vacc01x23, va01x01234567, vb23x01234567);
      vacc01x45 = vmmlaq_s32(vacc01x45, va01x01234567, vb45x01234567);
      vacc01x67 = vmmlaq_s32(vacc01x67, va01x01234567, vb67x01234567);
      vacc01x89 = vmmlaq_s32(vacc01x89, va01x01234567, vb89x01234567);
      vacc01xAB = vmmlaq_s32(vacc01xAB, va01x01234567, vb1011x01234567);
      vacc01xCD = vmmlaq_s32(vacc01xCD, va01x01234567, vb1213x01234567);
      vacc01xEF = vmmlaq_s32(vacc01xEF, va01x01234567, vb1415x01234567);
      vacc23x01 = vmmlaq_s32(vacc23x01, va23x01234567, vb01x01234567);
      vacc23x23 = vmmlaq_s32(vacc23x23, va23x01234567, vb23x01234567);
      vacc23x45 = vmmlaq_s32(vacc23x45, va23x01234567, vb45x01234567);
      vacc23x67 = vmmlaq_s32(vacc23x67, va23x01234567, vb67x01234567);
      vacc23x89 = vmmlaq_s32(vacc23x89, va23x01234567, vb89x01234567);
      vacc23xAB = vmmlaq_s32(vacc23xAB, va23x01234567, vb1011x01234567);
      vacc23xCD = vmmlaq_s32(vacc23xCD, va23x01234567, vb1213x01234567);
      vacc23xEF = vmmlaq_s32(vacc23xEF, va23x01234567, vb1415x01234567);
      vacc45x01 = vmmlaq_s32(vacc45x01, va45x01234567, vb01x01234567);
      vacc45x23 = vmmlaq_s32(vacc45x23, va45x01234567, vb23x01234567);
      vacc45x45 = vmmlaq_s32(vacc45x45, va45x01234567, vb45x01234567);
      vacc45x67 = vmmlaq_s32(vacc45x67, va45x01234567, vb67x01234567);
      vacc45x89 = vmmlaq_s32(vacc45x89, va45x01234567, vb89x01234567);
      vacc45xAB = vmmlaq_s32(vacc45xAB, va45x01234567, vb1011x01234567);
      vacc45xCD = vmmlaq_s32(vacc45xCD, va45x01234567, vb1213x01234567);
      vacc45xEF = vmmlaq_s32(vacc45xEF, va45x01234567, vb1415x01234567);
      vacc67x01 = vmmlaq_s32(vacc67x01, va67x01234567, vb01x01234567);
      vacc67x23 = vmmlaq_s32(vacc67x23, va67x01234567, vb23x01234567);
      vacc67x45 = vmmlaq_s32(vacc67x45, va67x01234567, vb45x01234567);
      vacc67x67 = vmmlaq_s32(vacc67x67, va67x01234567, vb67x01234567);
      vacc67x89 = vmmlaq_s32(vacc67x89, va67x01234567, vb89x01234567);
      vacc67xAB = vmmlaq_s32(vacc67xAB, va67x01234567, vb1011x01234567);
      vacc67xCD = vmmlaq_s32(vacc67xCD, va67x01234567, vb1213x01234567);
      vacc67xEF = vmmlaq_s32(vacc67xEF, va67x01234567, vb1415x01234567);
      vacc01x01 = vmmlaq_s32(vacc01x01, va01x89ABCDEF, vb01x89ABCDEF);
      vacc01x23 = vmmlaq_s32(vacc01x23, va01x89ABCDEF, vb23x89ABCDEF);
      vacc01x45 = vmmlaq_s32(vacc01x45, va01x89ABCDEF, vb45x89ABCDEF);
      vacc01x67 = vmmlaq_s32(vacc01x67, va01x89ABCDEF, vb67x89ABCDEF);
      vacc01x89 = vmmlaq_s32(vacc01x89, va01x89ABCDEF, vb89x89ABCDEF);
      vacc01xAB = vmmlaq_s32(vacc01xAB, va01x89ABCDEF, vb1011x89ABCDEF);
      vacc01xCD = vmmlaq_s32(vacc01xCD, va01x89ABCDEF, vb1213x89ABCDEF);
      vacc01xEF = vmmlaq_s32(vacc01xEF, va01x89ABCDEF, vb1415x89ABCDEF);
      vacc23x01 = vmmlaq_s32(vacc23x01, va23x89ABCDEF, vb01x89ABCDEF);
      vacc23x23 = vmmlaq_s32(vacc23x23, va23x89ABCDEF, vb23x89ABCDEF);
      vacc23x45 = vmmlaq_s32(vacc23x45, va23x89ABCDEF, vb45x89ABCDEF);
      vacc23x67 = vmmlaq_s32(vacc23x67, va23x89ABCDEF, vb67x89ABCDEF);
      vacc23x89 = vmmlaq_s32(vacc23x89, va23x89ABCDEF, vb89x89ABCDEF);
      vacc23xAB = vmmlaq_s32(vacc23xAB, va23x89ABCDEF, vb1011x89ABCDEF);
      vacc23xCD = vmmlaq_s32(vacc23xCD, va23x89ABCDEF, vb1213x89ABCDEF);
      vacc23xEF = vmmlaq_s32(vacc23xEF, va23x89ABCDEF, vb1415x89ABCDEF);
      vacc45x01 = vmmlaq_s32(vacc45x01, va45x89ABCDEF, vb01x89ABCDEF);
      vacc45x23 = vmmlaq_s32(vacc45x23, va45x89ABCDEF, vb23x89ABCDEF);
      vacc45x45 = vmmlaq_s32(vacc45x45, va45x89ABCDEF, vb45x89ABCDEF);
      vacc45x67 = vmmlaq_s32(vacc45x67, va45x89ABCDEF, vb67x89ABCDEF);
      vacc45x89 = vmmlaq_s32(vacc45x89, va45x89ABCDEF, vb89x89ABCDEF);
      vacc45xAB = vmmlaq_s32(vacc45xAB, va45x89ABCDEF, vb1011x89ABCDEF);
      vacc45xCD = vmmlaq_s32(vacc45xCD, va45x89ABCDEF, vb1213x89ABCDEF);
      vacc45xEF = vmmlaq_s32(vacc45xEF, va45x89ABCDEF, vb1415x89ABCDEF);
      vacc67x01 = vmmlaq_s32(vacc67x01, va67x89ABCDEF, vb01x89ABCDEF);
      vacc67x23 = vmmlaq_s32(vacc67x23, va67x89ABCDEF, vb23x89ABCDEF);
      vacc67x45 = vmmlaq_s32(vacc67x45, va67x89ABCDEF, vb45x89ABCDEF);
      vacc67x67 = vmmlaq_s32(vacc67x67, va67x89ABCDEF, vb67x89ABCDEF);
      vacc67x89 = vmmlaq_s32(vacc67x89, va67x89ABCDEF, vb89x89ABCDEF);
      vacc67xAB = vmmlaq_s32(vacc67xAB, va67x89ABCDEF, vb1011x89ABCDEF);
      vacc67xCD = vmmlaq_s32(vacc67xCD, va67x89ABCDEF, vb1213x89ABCDEF);
      vacc67xEF = vmmlaq_s32(vacc67xEF, va67x89ABCDEF, vb1415x89ABCDEF);

      k -= 16 * sizeof(int8_t);
    }
    // Handle up to 16 final positions of `k`
    if XNN_UNLIKELY(k != 0) {
      do {
        // Load a 8x8 block of activations.
        const int8x8_t va0x01234567 = vld1_s8(a0); a0 += 8;
        const int8x8_t va1x01234567 = vld1_s8(a1); a1 += 8;
        const int8x8_t va2x01234567 = vld1_s8(a2); a2 += 8;
        const int8x8_t va3x01234567 = vld1_s8(a3); a3 += 8;
        const int8x8_t va4x01234567 = vld1_s8(a4); a4 += 8;
        const int8x8_t va5x01234567 = vld1_s8(a5); a5 += 8;
        const int8x8_t va6x01234567 = vld1_s8(a6); a6 += 8;
        const int8x8_t va7x01234567 = vld1_s8(a7); a7 += 8;
        int8x16_t va01x01234567 = vcombine_s8(va0x01234567, va1x01234567);
        int8x16_t va23x01234567 = vcombine_s8(va2x01234567, va3x01234567);
        int8x16_t va45x01234567 = vcombine_s8(va4x01234567, va5x01234567);
        int8x16_t va67x01234567 = vcombine_s8(va6x01234567, va7x01234567);

        // Load a 16x16 block of weights.
        const int8x16_t vb01x01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
        const int8x16_t vb23x01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
        const int8x16_t vb45x01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
        const int8x16_t vb67x01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
        const int8x16_t vb89x01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
        const int8x16_t vb1011x01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
        const int8x16_t vb1213x01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;
        const int8x16_t vb1415x01234567 = vld1q_s8(w); w = (const int8_t*) w + 16;

        // Multiply-accumulate: 8x4 * 4x16 --> 8x16.
        vacc01x01 = vmmlaq_s32(vacc01x01, va01x01234567, vb01x01234567);
        vacc01x23 = vmmlaq_s32(vacc01x23, va01x01234567, vb23x01234567);
        vacc01x45 = vmmlaq_s32(vacc01x45, va01x01234567, vb45x01234567);
        vacc01x67 = vmmlaq_s32(vacc01x67, va01x01234567, vb67x01234567);
        vacc01x89 = vmmlaq_s32(vacc01x89, va01x01234567, vb89x01234567);
        vacc01xAB = vmmlaq_s32(vacc01xAB, va01x01234567, vb1011x01234567);
        vacc01xCD = vmmlaq_s32(vacc01xCD, va01x01234567, vb1213x01234567);
        vacc01xEF = vmmlaq_s32(vacc01xEF, va01x01234567, vb1415x01234567);
        vacc23x01 = vmmlaq_s32(vacc23x01, va23x01234567, vb01x01234567);
        vacc23x23 = vmmlaq_s32(vacc23x23, va23x01234567, vb23x01234567);
        vacc23x45 = vmmlaq_s32(vacc23x45, va23x01234567, vb45x01234567);
        vacc23x67 = vmmlaq_s32(vacc23x67, va23x01234567, vb67x01234567);
        vacc23x89 = vmmlaq_s32(vacc23x89, va23x01234567, vb89x01234567);
        vacc23xAB = vmmlaq_s32(vacc23xAB, va23x01234567, vb1011x01234567);
        vacc23xCD = vmmlaq_s32(vacc23xCD, va23x01234567, vb1213x01234567);
        vacc23xEF = vmmlaq_s32(vacc23xEF, va23x01234567, vb1415x01234567);
        vacc45x01 = vmmlaq_s32(vacc45x01, va45x01234567, vb01x01234567);
        vacc45x23 = vmmlaq_s32(vacc45x23, va45x01234567, vb23x01234567);
        vacc45x45 = vmmlaq_s32(vacc45x45, va45x01234567, vb45x01234567);
        vacc45x67 = vmmlaq_s32(vacc45x67, va45x01234567, vb67x01234567);
        vacc45x89 = vmmlaq_s32(vacc45x89, va45x01234567, vb89x01234567);
        vacc45xAB = vmmlaq_s32(vacc45xAB, va45x01234567, vb1011x01234567);
        vacc45xCD = vmmlaq_s32(vacc45xCD, va45x01234567, vb1213x01234567);
        vacc45xEF = vmmlaq_s32(vacc45xEF, va45x01234567, vb1415x01234567);
        vacc67x01 = vmmlaq_s32(vacc67x01, va67x01234567, vb01x01234567);
        vacc67x23 = vmmlaq_s32(vacc67x23, va67x01234567, vb23x01234567);
        vacc67x45 = vmmlaq_s32(vacc67x45, va67x01234567, vb45x01234567);
        vacc67x67 = vmmlaq_s32(vacc67x67, va67x01234567, vb67x01234567);
        vacc67x89 = vmmlaq_s32(vacc67x89, va67x01234567, vb89x01234567);
        vacc67xAB = vmmlaq_s32(vacc67xAB, va67x01234567, vb1011x01234567);
        vacc67xCD = vmmlaq_s32(vacc67xCD, va67x01234567, vb1213x01234567);
        vacc67xEF = vmmlaq_s32(vacc67xEF, va67x01234567, vb1415x01234567);
        k -= 8 * sizeof(int8_t);
      } while (k != 0);
    }

    int32x4_t vacc0x0123 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vacc01x01), vreinterpretq_u64_s32(vacc01x23)));
    int32x4_t vacc1x0123 = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vacc01x01), vreinterpretq_u64_s32(vacc01x23)));
    int32x4_t vacc0x4567 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vacc01x45), vreinterpretq_u64_s32(vacc01x67)));
    int32x4_t vacc1x4567 = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vacc01x45), vreinterpretq_u64_s32(vacc01x67)));
    int32x4_t vacc0x89AB = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vacc01x89), vreinterpretq_u64_s32(vacc01xAB)));
    int32x4_t vacc1x89AB = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vacc01x89), vreinterpretq_u64_s32(vacc01xAB)));
    int32x4_t vacc0xCDEF = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vacc01xCD), vreinterpretq_u64_s32(vacc01xEF)));
    int32x4_t vacc1xCDEF = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vacc01xCD), vreinterpretq_u64_s32(vacc01xEF)));
    int32x4_t vacc2x0123 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vacc23x01), vreinterpretq_u64_s32(vacc23x23)));
    int32x4_t vacc3x0123 = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vacc23x01), vreinterpretq_u64_s32(vacc23x23)));
    int32x4_t vacc2x4567 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vacc23x45), vreinterpretq_u64_s32(vacc23x67)));
    int32x4_t vacc3x4567 = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vacc23x45), vreinterpretq_u64_s32(vacc23x67)));
    int32x4_t vacc2x89AB = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vacc23x89), vreinterpretq_u64_s32(vacc23xAB)));
    int32x4_t vacc3x89AB = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vacc23x89), vreinterpretq_u64_s32(vacc23xAB)));
    int32x4_t vacc2xCDEF = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vacc23xCD), vreinterpretq_u64_s32(vacc23xEF)));
    int32x4_t vacc3xCDEF = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vacc23xCD), vreinterpretq_u64_s32(vacc23xEF)));
    int32x4_t vacc4x0123 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vacc45x01), vreinterpretq_u64_s32(vacc45x23)));
    int32x4_t vacc5x0123 = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vacc45x01), vreinterpretq_u64_s32(vacc45x23)));
    int32x4_t vacc4x4567 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vacc45x45), vreinterpretq_u64_s32(vacc45x67)));
    int32x4_t vacc5x4567 = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vacc45x45), vreinterpretq_u64_s32(vacc45x67)));
    int32x4_t vacc4x89AB = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vacc45x89), vreinterpretq_u64_s32(vacc45xAB)));
    int32x4_t vacc5x89AB = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vacc45x89), vreinterpretq_u64_s32(vacc45xAB)));
    int32x4_t vacc4xCDEF = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vacc45xCD), vreinterpretq_u64_s32(vacc45xEF)));
    int32x4_t vacc5xCDEF = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vacc45xCD), vreinterpretq_u64_s32(vacc45xEF)));
    int32x4_t vacc6x0123 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vacc67x01), vreinterpretq_u64_s32(vacc67x23)));
    int32x4_t vacc7x0123 = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vacc67x01), vreinterpretq_u64_s32(vacc67x23)));
    int32x4_t vacc6x4567 = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vacc67x45), vreinterpretq_u64_s32(vacc67x67)));
    int32x4_t vacc7x4567 = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vacc67x45), vreinterpretq_u64_s32(vacc67x67)));
    int32x4_t vacc6x89AB = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vacc67x89), vreinterpretq_u64_s32(vacc67xAB)));
    int32x4_t vacc7x89AB = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vacc67x89), vreinterpretq_u64_s32(vacc67xAB)));
    int32x4_t vacc6xCDEF = vreinterpretq_s32_u64(vtrn1q_u64(vreinterpretq_u64_s32(vacc67xCD), vreinterpretq_u64_s32(vacc67xEF)));
    int32x4_t vacc7xCDEF = vreinterpretq_s32_u64(vtrn2q_u64(vreinterpretq_u64_s32(vacc67xCD), vreinterpretq_u64_s32(vacc67xEF)));
    float32x4_t vout0x0123 = vcvtq_f32_s32(vacc0x0123);
    float32x4_t vout0x4567 = vcvtq_f32_s32(vacc0x4567);
    float32x4_t vout0x89AB = vcvtq_f32_s32(vacc0x89AB);
    float32x4_t vout0xCDEF = vcvtq_f32_s32(vacc0xCDEF);
    float32x4_t vout1x0123 = vcvtq_f32_s32(vacc1x0123);
    float32x4_t vout1x4567 = vcvtq_f32_s32(vacc1x4567);
    float32x4_t vout1x89AB = vcvtq_f32_s32(vacc1x89AB);
    float32x4_t vout1xCDEF = vcvtq_f32_s32(vacc1xCDEF);
    float32x4_t vout2x0123 = vcvtq_f32_s32(vacc2x0123);
    float32x4_t vout2x4567 = vcvtq_f32_s32(vacc2x4567);
    float32x4_t vout2x89AB = vcvtq_f32_s32(vacc2x89AB);
    float32x4_t vout2xCDEF = vcvtq_f32_s32(vacc2xCDEF);
    float32x4_t vout3x0123 = vcvtq_f32_s32(vacc3x0123);
    float32x4_t vout3x4567 = vcvtq_f32_s32(vacc3x4567);
    float32x4_t vout3x89AB = vcvtq_f32_s32(vacc3x89AB);
    float32x4_t vout3xCDEF = vcvtq_f32_s32(vacc3xCDEF);
    float32x4_t vout4x0123 = vcvtq_f32_s32(vacc4x0123);
    float32x4_t vout4x4567 = vcvtq_f32_s32(vacc4x4567);
    float32x4_t vout4x89AB = vcvtq_f32_s32(vacc4x89AB);
    float32x4_t vout4xCDEF = vcvtq_f32_s32(vacc4xCDEF);
    float32x4_t vout5x0123 = vcvtq_f32_s32(vacc5x0123);
    float32x4_t vout5x4567 = vcvtq_f32_s32(vacc5x4567);
    float32x4_t vout5x89AB = vcvtq_f32_s32(vacc5x89AB);
    float32x4_t vout5xCDEF = vcvtq_f32_s32(vacc5xCDEF);
    float32x4_t vout6x0123 = vcvtq_f32_s32(vacc6x0123);
    float32x4_t vout6x4567 = vcvtq_f32_s32(vacc6x4567);
    float32x4_t vout6x89AB = vcvtq_f32_s32(vacc6x89AB);
    float32x4_t vout6xCDEF = vcvtq_f32_s32(vacc6xCDEF);
    float32x4_t vout7x0123 = vcvtq_f32_s32(vacc7x0123);
    float32x4_t vout7x4567 = vcvtq_f32_s32(vacc7x4567);
    float32x4_t vout7x89AB = vcvtq_f32_s32(vacc7x89AB);
    float32x4_t vout7xCDEF = vcvtq_f32_s32(vacc7xCDEF);

    const float32x4_t vinput_scale01 = vreinterpretq_f32_s32(vld1q_s32(&quantization_params[0].zero_point));
    vout0x0123 = vmulq_lane_f32(vout0x0123, vget_low_f32(vinput_scale01), 1);
    vout1x0123 = vmulq_lane_f32(vout1x0123, vget_high_f32(vinput_scale01), 1);
    vout0x4567 = vmulq_lane_f32(vout0x4567, vget_low_f32(vinput_scale01), 1);
    vout1x4567 = vmulq_lane_f32(vout1x4567, vget_high_f32(vinput_scale01), 1);
    vout0x89AB = vmulq_lane_f32(vout0x89AB, vget_low_f32(vinput_scale01), 1);
    vout1x89AB = vmulq_lane_f32(vout1x89AB, vget_high_f32(vinput_scale01), 1);
    vout0xCDEF = vmulq_lane_f32(vout0xCDEF, vget_low_f32(vinput_scale01), 1);
    vout1xCDEF = vmulq_lane_f32(vout1xCDEF, vget_high_f32(vinput_scale01), 1);
    const float32x4_t vinput_scale23 = vreinterpretq_f32_s32(vld1q_s32(&quantization_params[2].zero_point));
    vout2x0123 = vmulq_lane_f32(vout2x0123, vget_low_f32(vinput_scale23), 1);
    vout3x0123 = vmulq_lane_f32(vout3x0123, vget_high_f32(vinput_scale23), 1);
    vout2x4567 = vmulq_lane_f32(vout2x4567, vget_low_f32(vinput_scale23), 1);
    vout3x4567 = vmulq_lane_f32(vout3x4567, vget_high_f32(vinput_scale23), 1);
    vout2x89AB = vmulq_lane_f32(vout2x89AB, vget_low_f32(vinput_scale23), 1);
    vout3x89AB = vmulq_lane_f32(vout3x89AB, vget_high_f32(vinput_scale23), 1);
    vout2xCDEF = vmulq_lane_f32(vout2xCDEF, vget_low_f32(vinput_scale23), 1);
    vout3xCDEF = vmulq_lane_f32(vout3xCDEF, vget_high_f32(vinput_scale23), 1);
    const float32x4_t vinput_scale45 = vreinterpretq_f32_s32(vld1q_s32(&quantization_params[4].zero_point));
    vout4x0123 = vmulq_lane_f32(vout4x0123, vget_low_f32(vinput_scale45), 1);
    vout5x0123 = vmulq_lane_f32(vout5x0123, vget_high_f32(vinput_scale45), 1);
    vout4x4567 = vmulq_lane_f32(vout4x4567, vget_low_f32(vinput_scale45), 1);
    vout5x4567 = vmulq_lane_f32(vout5x4567, vget_high_f32(vinput_scale45), 1);
    vout4x89AB = vmulq_lane_f32(vout4x89AB, vget_low_f32(vinput_scale45), 1);
    vout5x89AB = vmulq_lane_f32(vout5x89AB, vget_high_f32(vinput_scale45), 1);
    vout4xCDEF = vmulq_lane_f32(vout4xCDEF, vget_low_f32(vinput_scale45), 1);
    vout5xCDEF = vmulq_lane_f32(vout5xCDEF, vget_high_f32(vinput_scale45), 1);
    const float32x4_t vinput_scale67 = vreinterpretq_f32_s32(vld1q_s32(&quantization_params[6].zero_point));
    vout6x0123 = vmulq_lane_f32(vout6x0123, vget_low_f32(vinput_scale67), 1);
    vout7x0123 = vmulq_lane_f32(vout7x0123, vget_high_f32(vinput_scale67), 1);
    vout6x4567 = vmulq_lane_f32(vout6x4567, vget_low_f32(vinput_scale67), 1);
    vout7x4567 = vmulq_lane_f32(vout7x4567, vget_high_f32(vinput_scale67), 1);
    vout6x89AB = vmulq_lane_f32(vout6x89AB, vget_low_f32(vinput_scale67), 1);
    vout7x89AB = vmulq_lane_f32(vout7x89AB, vget_high_f32(vinput_scale67), 1);
    vout6xCDEF = vmulq_lane_f32(vout6xCDEF, vget_low_f32(vinput_scale67), 1);
    vout7xCDEF = vmulq_lane_f32(vout7xCDEF, vget_high_f32(vinput_scale67), 1);

    const float32x4_t vfilter_output_scale0123 = vld1q_f32(w); w = (const float*) w + 4;
    const float32x4_t vfilter_output_scale4567 = vld1q_f32(w); w = (const float*) w + 4;
    const float32x4_t vfilter_output_scale89AB = vld1q_f32(w); w = (const float*) w + 4;
    const float32x4_t vfilter_output_scaleCDEF = vld1q_f32(w); w = (const float*) w + 4;

    const float32x4_t vbias0123 = vld1q_f32(w); w = (const float*) w + 4;
    #if XNN_ARCH_ARM64
      vout0x0123 = vfmaq_f32(vbias0123, vout0x0123, vfilter_output_scale0123);
      vout1x0123 = vfmaq_f32(vbias0123, vout1x0123, vfilter_output_scale0123);
      vout2x0123 = vfmaq_f32(vbias0123, vout2x0123, vfilter_output_scale0123);
      vout3x0123 = vfmaq_f32(vbias0123, vout3x0123, vfilter_output_scale0123);
      vout4x0123 = vfmaq_f32(vbias0123, vout4x0123, vfilter_output_scale0123);
      vout5x0123 = vfmaq_f32(vbias0123, vout5x0123, vfilter_output_scale0123);
      vout6x0123 = vfmaq_f32(vbias0123, vout6x0123, vfilter_output_scale0123);
      vout7x0123 = vfmaq_f32(vbias0123, vout7x0123, vfilter_output_scale0123);
    #else
      vout0x0123 = vmlaq_f32(vbias0123, vout0x0123, vfilter_output_scale0123);
      vout1x0123 = vmlaq_f32(vbias0123, vout1x0123, vfilter_output_scale0123);
      vout2x0123 = vmlaq_f32(vbias0123, vout2x0123, vfilter_output_scale0123);
      vout3x0123 = vmlaq_f32(vbias0123, vout3x0123, vfilter_output_scale0123);
      vout4x0123 = vmlaq_f32(vbias0123, vout4x0123, vfilter_output_scale0123);
      vout5x0123 = vmlaq_f32(vbias0123, vout5x0123, vfilter_output_scale0123);
      vout6x0123 = vmlaq_f32(vbias0123, vout6x0123, vfilter_output_scale0123);
      vout7x0123 = vmlaq_f32(vbias0123, vout7x0123, vfilter_output_scale0123);
    #endif
    const float32x4_t vbias4567 = vld1q_f32(w); w = (const float*) w + 4;
    #if XNN_ARCH_ARM64
      vout0x4567 = vfmaq_f32(vbias4567, vout0x4567, vfilter_output_scale4567);
      vout1x4567 = vfmaq_f32(vbias4567, vout1x4567, vfilter_output_scale4567);
      vout2x4567 = vfmaq_f32(vbias4567, vout2x4567, vfilter_output_scale4567);
      vout3x4567 = vfmaq_f32(vbias4567, vout3x4567, vfilter_output_scale4567);
      vout4x4567 = vfmaq_f32(vbias4567, vout4x4567, vfilter_output_scale4567);
      vout5x4567 = vfmaq_f32(vbias4567, vout5x4567, vfilter_output_scale4567);
      vout6x4567 = vfmaq_f32(vbias4567, vout6x4567, vfilter_output_scale4567);
      vout7x4567 = vfmaq_f32(vbias4567, vout7x4567, vfilter_output_scale4567);
    #else
      vout0x4567 = vmlaq_f32(vbias4567, vout0x4567, vfilter_output_scale4567);
      vout1x4567 = vmlaq_f32(vbias4567, vout1x4567, vfilter_output_scale4567);
      vout2x4567 = vmlaq_f32(vbias4567, vout2x4567, vfilter_output_scale4567);
      vout3x4567 = vmlaq_f32(vbias4567, vout3x4567, vfilter_output_scale4567);
      vout4x4567 = vmlaq_f32(vbias4567, vout4x4567, vfilter_output_scale4567);
      vout5x4567 = vmlaq_f32(vbias4567, vout5x4567, vfilter_output_scale4567);
      vout6x4567 = vmlaq_f32(vbias4567, vout6x4567, vfilter_output_scale4567);
      vout7x4567 = vmlaq_f32(vbias4567, vout7x4567, vfilter_output_scale4567);
    #endif
    const float32x4_t vbias89AB = vld1q_f32(w); w = (const float*) w + 4;
    #if XNN_ARCH_ARM64
      vout0x89AB = vfmaq_f32(vbias89AB, vout0x89AB, vfilter_output_scale89AB);
      vout1x89AB = vfmaq_f32(vbias89AB, vout1x89AB, vfilter_output_scale89AB);
      vout2x89AB = vfmaq_f32(vbias89AB, vout2x89AB, vfilter_output_scale89AB);
      vout3x89AB = vfmaq_f32(vbias89AB, vout3x89AB, vfilter_output_scale89AB);
      vout4x89AB = vfmaq_f32(vbias89AB, vout4x89AB, vfilter_output_scale89AB);
      vout5x89AB = vfmaq_f32(vbias89AB, vout5x89AB, vfilter_output_scale89AB);
      vout6x89AB = vfmaq_f32(vbias89AB, vout6x89AB, vfilter_output_scale89AB);
      vout7x89AB = vfmaq_f32(vbias89AB, vout7x89AB, vfilter_output_scale89AB);
    #else
      vout0x89AB = vmlaq_f32(vbias89AB, vout0x89AB, vfilter_output_scale89AB);
      vout1x89AB = vmlaq_f32(vbias89AB, vout1x89AB, vfilter_output_scale89AB);
      vout2x89AB = vmlaq_f32(vbias89AB, vout2x89AB, vfilter_output_scale89AB);
      vout3x89AB = vmlaq_f32(vbias89AB, vout3x89AB, vfilter_output_scale89AB);
      vout4x89AB = vmlaq_f32(vbias89AB, vout4x89AB, vfilter_output_scale89AB);
      vout5x89AB = vmlaq_f32(vbias89AB, vout5x89AB, vfilter_output_scale89AB);
      vout6x89AB = vmlaq_f32(vbias89AB, vout6x89AB, vfilter_output_scale89AB);
      vout7x89AB = vmlaq_f32(vbias89AB, vout7x89AB, vfilter_output_scale89AB);
    #endif
    const float32x4_t vbiasCDEF = vld1q_f32(w); w = (const float*) w + 4;
    #if XNN_ARCH_ARM64
      vout0xCDEF = vfmaq_f32(vbiasCDEF, vout0xCDEF, vfilter_output_scaleCDEF);
      vout1xCDEF = vfmaq_f32(vbiasCDEF, vout1xCDEF, vfilter_output_scaleCDEF);
      vout2xCDEF = vfmaq_f32(vbiasCDEF, vout2xCDEF, vfilter_output_scaleCDEF);
      vout3xCDEF = vfmaq_f32(vbiasCDEF, vout3xCDEF, vfilter_output_scaleCDEF);
      vout4xCDEF = vfmaq_f32(vbiasCDEF, vout4xCDEF, vfilter_output_scaleCDEF);
      vout5xCDEF = vfmaq_f32(vbiasCDEF, vout5xCDEF, vfilter_output_scaleCDEF);
      vout6xCDEF = vfmaq_f32(vbiasCDEF, vout6xCDEF, vfilter_output_scaleCDEF);
      vout7xCDEF = vfmaq_f32(vbiasCDEF, vout7xCDEF, vfilter_output_scaleCDEF);
    #else
      vout0xCDEF = vmlaq_f32(vbiasCDEF, vout0xCDEF, vfilter_output_scaleCDEF);
      vout1xCDEF = vmlaq_f32(vbiasCDEF, vout1xCDEF, vfilter_output_scaleCDEF);
      vout2xCDEF = vmlaq_f32(vbiasCDEF, vout2xCDEF, vfilter_output_scaleCDEF);
      vout3xCDEF = vmlaq_f32(vbiasCDEF, vout3xCDEF, vfilter_output_scaleCDEF);
      vout4xCDEF = vmlaq_f32(vbiasCDEF, vout4xCDEF, vfilter_output_scaleCDEF);
      vout5xCDEF = vmlaq_f32(vbiasCDEF, vout5xCDEF, vfilter_output_scaleCDEF);
      vout6xCDEF = vmlaq_f32(vbiasCDEF, vout6xCDEF, vfilter_output_scaleCDEF);
      vout7xCDEF = vmlaq_f32(vbiasCDEF, vout7xCDEF, vfilter_output_scaleCDEF);
    #endif

    const float32x4_t voutput_min = vld1q_dup_f32(&params->scalar.min);
    vout0x0123 = vmaxq_f32(vout0x0123, voutput_min);
    vout0x4567 = vmaxq_f32(vout0x4567, voutput_min);
    vout0x89AB = vmaxq_f32(vout0x89AB, voutput_min);
    vout0xCDEF = vmaxq_f32(vout0xCDEF, voutput_min);
    vout1x0123 = vmaxq_f32(vout1x0123, voutput_min);
    vout1x4567 = vmaxq_f32(vout1x4567, voutput_min);
    vout1x89AB = vmaxq_f32(vout1x89AB, voutput_min);
    vout1xCDEF = vmaxq_f32(vout1xCDEF, voutput_min);
    vout2x0123 = vmaxq_f32(vout2x0123, voutput_min);
    vout2x4567 = vmaxq_f32(vout2x4567, voutput_min);
    vout2x89AB = vmaxq_f32(vout2x89AB, voutput_min);
    vout2xCDEF = vmaxq_f32(vout2xCDEF, voutput_min);
    vout3x0123 = vmaxq_f32(vout3x0123, voutput_min);
    vout3x4567 = vmaxq_f32(vout3x4567, voutput_min);
    vout3x89AB = vmaxq_f32(vout3x89AB, voutput_min);
    vout3xCDEF = vmaxq_f32(vout3xCDEF, voutput_min);
    vout4x0123 = vmaxq_f32(vout4x0123, voutput_min);
    vout4x4567 = vmaxq_f32(vout4x4567, voutput_min);
    vout4x89AB = vmaxq_f32(vout4x89AB, voutput_min);
    vout4xCDEF = vmaxq_f32(vout4xCDEF, voutput_min);
    vout5x0123 = vmaxq_f32(vout5x0123, voutput_min);
    vout5x4567 = vmaxq_f32(vout5x4567, voutput_min);
    vout5x89AB = vmaxq_f32(vout5x89AB, voutput_min);
    vout5xCDEF = vmaxq_f32(vout5xCDEF, voutput_min);
    vout6x0123 = vmaxq_f32(vout6x0123, voutput_min);
    vout6x4567 = vmaxq_f32(vout6x4567, voutput_min);
    vout6x89AB = vmaxq_f32(vout6x89AB, voutput_min);
    vout6xCDEF = vmaxq_f32(vout6xCDEF, voutput_min);
    vout7x0123 = vmaxq_f32(vout7x0123, voutput_min);
    vout7x4567 = vmaxq_f32(vout7x4567, voutput_min);
    vout7x89AB = vmaxq_f32(vout7x89AB, voutput_min);
    vout7xCDEF = vmaxq_f32(vout7xCDEF, voutput_min);

    const float32x4_t voutput_max = vld1q_dup_f32(&params->scalar.max);
    vout0x0123 = vminq_f32(vout0x0123, voutput_max);
    vout0x4567 = vminq_f32(vout0x4567, voutput_max);
    vout0x89AB = vminq_f32(vout0x89AB, voutput_max);
    vout0xCDEF = vminq_f32(vout0xCDEF, voutput_max);
    vout1x0123 = vminq_f32(vout1x0123, voutput_max);
    vout1x4567 = vminq_f32(vout1x4567, voutput_max);
    vout1x89AB = vminq_f32(vout1x89AB, voutput_max);
    vout1xCDEF = vminq_f32(vout1xCDEF, voutput_max);
    vout2x0123 = vminq_f32(vout2x0123, voutput_max);
    vout2x4567 = vminq_f32(vout2x4567, voutput_max);
    vout2x89AB = vminq_f32(vout2x89AB, voutput_max);
    vout2xCDEF = vminq_f32(vout2xCDEF, voutput_max);
    vout3x0123 = vminq_f32(vout3x0123, voutput_max);
    vout3x4567 = vminq_f32(vout3x4567, voutput_max);
    vout3x89AB = vminq_f32(vout3x89AB, voutput_max);
    vout3xCDEF = vminq_f32(vout3xCDEF, voutput_max);
    vout4x0123 = vminq_f32(vout4x0123, voutput_max);
    vout4x4567 = vminq_f32(vout4x4567, voutput_max);
    vout4x89AB = vminq_f32(vout4x89AB, voutput_max);
    vout4xCDEF = vminq_f32(vout4xCDEF, voutput_max);
    vout5x0123 = vminq_f32(vout5x0123, voutput_max);
    vout5x4567 = vminq_f32(vout5x4567, voutput_max);
    vout5x89AB = vminq_f32(vout5x89AB, voutput_max);
    vout5xCDEF = vminq_f32(vout5xCDEF, voutput_max);
    vout6x0123 = vminq_f32(vout6x0123, voutput_max);
    vout6x4567 = vminq_f32(vout6x4567, voutput_max);
    vout6x89AB = vminq_f32(vout6x89AB, voutput_max);
    vout6xCDEF = vminq_f32(vout6xCDEF, voutput_max);
    vout7x0123 = vminq_f32(vout7x0123, voutput_max);
    vout7x4567 = vminq_f32(vout7x4567, voutput_max);
    vout7x89AB = vminq_f32(vout7x89AB, voutput_max);
    vout7xCDEF = vminq_f32(vout7xCDEF, voutput_max);

    if XNN_LIKELY(nc >= 16) {
      vst1q_f32(c7, vout7x0123);
      vst1q_f32(c7 + 4, vout7x4567);
      vst1q_f32(c7 + 8, vout7x89AB);
      vst1q_f32(c7 + 12, vout7xCDEF);
      vst1q_f32(c6, vout6x0123);
      vst1q_f32(c6 + 4, vout6x4567);
      vst1q_f32(c6 + 8, vout6x89AB);
      vst1q_f32(c6 + 12, vout6xCDEF);
      vst1q_f32(c5, vout5x0123);
      vst1q_f32(c5 + 4, vout5x4567);
      vst1q_f32(c5 + 8, vout5x89AB);
      vst1q_f32(c5 + 12, vout5xCDEF);
      vst1q_f32(c4, vout4x0123);
      vst1q_f32(c4 + 4, vout4x4567);
      vst1q_f32(c4 + 8, vout4x89AB);
      vst1q_f32(c4 + 12, vout4xCDEF);
      vst1q_f32(c3, vout3x0123);
      vst1q_f32(c3 + 4, vout3x4567);
      vst1q_f32(c3 + 8, vout3x89AB);
      vst1q_f32(c3 + 12, vout3xCDEF);
      vst1q_f32(c2, vout2x0123);
      vst1q_f32(c2 + 4, vout2x4567);
      vst1q_f32(c2 + 8, vout2x89AB);
      vst1q_f32(c2 + 12, vout2xCDEF);
      vst1q_f32(c1, vout1x0123);
      vst1q_f32(c1 + 4, vout1x4567);
      vst1q_f32(c1 + 8, vout1x89AB);
      vst1q_f32(c1 + 12, vout1xCDEF);
      vst1q_f32(c0, vout0x0123);
      vst1q_f32(c0 + 4, vout0x4567);
      vst1q_f32(c0 + 8, vout0x89AB);
      vst1q_f32(c0 + 12, vout0xCDEF);

      a0 = (const int8_t*) ((uintptr_t) a0 - kc);
      a1 = (const int8_t*) ((uintptr_t) a1 - kc);
      a2 = (const int8_t*) ((uintptr_t) a2 - kc);
      a3 = (const int8_t*) ((uintptr_t) a3 - kc);
      a4 = (const int8_t*) ((uintptr_t) a4 - kc);
      a5 = (const int8_t*) ((uintptr_t) a5 - kc);
      a6 = (const int8_t*) ((uintptr_t) a6 - kc);
      a7 = (const int8_t*) ((uintptr_t) a7 - kc);

      c0 = (float*) ((uintptr_t) c0 + cn_stride);
      c1 = (float*) ((uintptr_t) c1 + cn_stride);
      c2 = (float*) ((uintptr_t) c2 + cn_stride);
      c3 = (float*) ((uintptr_t) c3 + cn_stride);
      c4 = (float*) ((uintptr_t) c4 + cn_stride);
      c5 = (float*) ((uintptr_t) c5 + cn_stride);
      c6 = (float*) ((uintptr_t) c6 + cn_stride);
      c7 = (float*) ((uintptr_t) c7 + cn_stride);

      nc -= 16;
    } else {
     if (nc & 8) {
       vst1q_f32(c7, vout7x0123); c7 += 4;
       vout7x0123 = vout7x89AB;
       vst1q_f32(c6, vout6x0123); c6 += 4;
       vout6x0123 = vout6x89AB;
       vst1q_f32(c5, vout5x0123); c5 += 4;
       vout5x0123 = vout5x89AB;
       vst1q_f32(c4, vout4x0123); c4 += 4;
       vout4x0123 = vout4x89AB;
       vst1q_f32(c3, vout3x0123); c3 += 4;
       vout3x0123 = vout3x89AB;
       vst1q_f32(c2, vout2x0123); c2 += 4;
       vout2x0123 = vout2x89AB;
       vst1q_f32(c1, vout1x0123); c1 += 4;
       vout1x0123 = vout1x89AB;
       vst1q_f32(c0, vout0x0123); c0 += 4;
       vout0x0123 = vout0x89AB;
       vst1q_f32(c7, vout7x4567); c7 += 4;
       vout7x4567 = vout7xCDEF;
       vst1q_f32(c6, vout6x4567); c6 += 4;
       vout6x4567 = vout6xCDEF;
       vst1q_f32(c5, vout5x4567); c5 += 4;
       vout5x4567 = vout5xCDEF;
       vst1q_f32(c4, vout4x4567); c4 += 4;
       vout4x4567 = vout4xCDEF;
       vst1q_f32(c3, vout3x4567); c3 += 4;
       vout3x4567 = vout3xCDEF;
       vst1q_f32(c2, vout2x4567); c2 += 4;
       vout2x4567 = vout2xCDEF;
       vst1q_f32(c1, vout1x4567); c1 += 4;
       vout1x4567 = vout1xCDEF;
       vst1q_f32(c0, vout0x4567); c0 += 4;
       vout0x4567 = vout0xCDEF;
     }
     if (nc & 4) {
       vst1q_f32(c7, vout7x0123); c7 += 4;
       vout7x0123 = vout7x4567;
       vst1q_f32(c6, vout6x0123); c6 += 4;
       vout6x0123 = vout6x4567;
       vst1q_f32(c5, vout5x0123); c5 += 4;
       vout5x0123 = vout5x4567;
       vst1q_f32(c4, vout4x0123); c4 += 4;
       vout4x0123 = vout4x4567;
       vst1q_f32(c3, vout3x0123); c3 += 4;
       vout3x0123 = vout3x4567;
       vst1q_f32(c2, vout2x0123); c2 += 4;
       vout2x0123 = vout2x4567;
       vst1q_f32(c1, vout1x0123); c1 += 4;
       vout1x0123 = vout1x4567;
       vst1q_f32(c0, vout0x0123); c0 += 4;
       vout0x0123 = vout0x4567;
     }
     float32x2_t vout7x01 = vget_low_f32(vout7x0123);
     float32x2_t vout6x01 = vget_low_f32(vout6x0123);
     float32x2_t vout5x01 = vget_low_f32(vout5x0123);
     float32x2_t vout4x01 = vget_low_f32(vout4x0123);
     float32x2_t vout3x01 = vget_low_f32(vout3x0123);
     float32x2_t vout2x01 = vget_low_f32(vout2x0123);
     float32x2_t vout1x01 = vget_low_f32(vout1x0123);
     float32x2_t vout0x01 = vget_low_f32(vout0x0123);
     if (nc & 2) {
       vst1_f32(c7, vout7x01); c7 += 2;
       vst1_f32(c6, vout6x01); c6 += 2;
       vst1_f32(c5, vout5x01); c5 += 2;
       vst1_f32(c4, vout4x01); c4 += 2;
       vst1_f32(c3, vout3x01); c3 += 2;
       vst1_f32(c2, vout2x01); c2 += 2;
       vst1_f32(c1, vout1x01); c1 += 2;
       vst1_f32(c0, vout0x01); c0 += 2;
       vout7x01 = vget_high_f32(vout7x0123);
       vout6x01 = vget_high_f32(vout6x0123);
       vout5x01 = vget_high_f32(vout5x0123);
       vout4x01 = vget_high_f32(vout4x0123);
       vout3x01 = vget_high_f32(vout3x0123);
       vout2x01 = vget_high_f32(vout2x0123);
       vout1x01 = vget_high_f32(vout1x0123);
       vout0x01 = vget_high_f32(vout0x0123);
     }
     if (nc & 1) {
       vst1_lane_f32(c7, vout7x01, 0);
       vst1_lane_f32(c6, vout6x01, 0);
       vst1_lane_f32(c5, vout5x01, 0);
       vst1_lane_f32(c4, vout4x01, 0);
       vst1_lane_f32(c3, vout3x01, 0);
       vst1_lane_f32(c2, vout2x01, 0);
       vst1_lane_f32(c1, vout1x01, 0);
       vst1_lane_f32(c0, vout0x01, 0);
     }
      nc = 0;
    }
  } while (nc != 0);
}