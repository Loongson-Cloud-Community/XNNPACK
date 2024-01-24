// Copyright 2019 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.
//
// Auto-generated file. Do not edit!
//   Specification: test/f32-vrsqrt.yaml
//   Generator: ./tools/generate-vunary-test.py

#include <xnnpack/common.h>
#include <xnnpack/isa-checks.h>
#include <xnnpack/vunary.h>

#include <cstddef>
#include <vector>

#include <gtest/gtest.h>
#include "vunary-microkernel-tester.h"


TEST(F32_VRSQRT__SCALAR_RECIP_SQRT_U1, batch_eq_1) {
  VUnaryMicrokernelTester()
    .batch_size(1)
    .Test(xnn_f32_vrsqrt_ukernel__scalar_recip_sqrt_u1);
}

TEST(F32_VRSQRT__SCALAR_RECIP_SQRT_U1, batch_gt_1) {
  for (size_t batch_size = 1 + 1; batch_size < 10; batch_size++) {
    VUnaryMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_vrsqrt_ukernel__scalar_recip_sqrt_u1);
  }
}

TEST(F32_VRSQRT__SCALAR_RECIP_SQRT_U1, inplace) {
  for (size_t batch_size = 1; batch_size <= 5; batch_size += 1) {
    VUnaryMicrokernelTester()
      .batch_size(batch_size)
      .inplace(true)
      .Test(xnn_f32_vrsqrt_ukernel__scalar_recip_sqrt_u1);
  }
}


TEST(F32_VRSQRT__SCALAR_RECIP_SQRT_U2, batch_eq_2) {
  VUnaryMicrokernelTester()
    .batch_size(2)
    .Test(xnn_f32_vrsqrt_ukernel__scalar_recip_sqrt_u2);
}

TEST(F32_VRSQRT__SCALAR_RECIP_SQRT_U2, batch_div_2) {
  for (size_t batch_size = 4; batch_size < 20; batch_size += 2) {
    VUnaryMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_vrsqrt_ukernel__scalar_recip_sqrt_u2);
  }
}

TEST(F32_VRSQRT__SCALAR_RECIP_SQRT_U2, batch_lt_2) {
  for (size_t batch_size = 1; batch_size < 2; batch_size++) {
    VUnaryMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_vrsqrt_ukernel__scalar_recip_sqrt_u2);
  }
}

TEST(F32_VRSQRT__SCALAR_RECIP_SQRT_U2, batch_gt_2) {
  for (size_t batch_size = 2 + 1; batch_size < 4; batch_size++) {
    VUnaryMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_vrsqrt_ukernel__scalar_recip_sqrt_u2);
  }
}

TEST(F32_VRSQRT__SCALAR_RECIP_SQRT_U2, inplace) {
  for (size_t batch_size = 1; batch_size <= 10; batch_size += 1) {
    VUnaryMicrokernelTester()
      .batch_size(batch_size)
      .inplace(true)
      .Test(xnn_f32_vrsqrt_ukernel__scalar_recip_sqrt_u2);
  }
}


TEST(F32_VRSQRT__SCALAR_RECIP_SQRT_U4, batch_eq_4) {
  VUnaryMicrokernelTester()
    .batch_size(4)
    .Test(xnn_f32_vrsqrt_ukernel__scalar_recip_sqrt_u4);
}

TEST(F32_VRSQRT__SCALAR_RECIP_SQRT_U4, batch_div_4) {
  for (size_t batch_size = 8; batch_size < 40; batch_size += 4) {
    VUnaryMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_vrsqrt_ukernel__scalar_recip_sqrt_u4);
  }
}

TEST(F32_VRSQRT__SCALAR_RECIP_SQRT_U4, batch_lt_4) {
  for (size_t batch_size = 1; batch_size < 4; batch_size++) {
    VUnaryMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_vrsqrt_ukernel__scalar_recip_sqrt_u4);
  }
}

TEST(F32_VRSQRT__SCALAR_RECIP_SQRT_U4, batch_gt_4) {
  for (size_t batch_size = 4 + 1; batch_size < 8; batch_size++) {
    VUnaryMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_vrsqrt_ukernel__scalar_recip_sqrt_u4);
  }
}

TEST(F32_VRSQRT__SCALAR_RECIP_SQRT_U4, inplace) {
  for (size_t batch_size = 1; batch_size <= 20; batch_size += 3) {
    VUnaryMicrokernelTester()
      .batch_size(batch_size)
      .inplace(true)
      .Test(xnn_f32_vrsqrt_ukernel__scalar_recip_sqrt_u4);
  }
}


#if XNN_ARCH_X86 || XNN_ARCH_X86_64
  TEST(F32_VRSQRT__SSE_RECIP_SQRT_U4, batch_eq_4) {
    TEST_REQUIRES_X86_SSE;
    VUnaryMicrokernelTester()
      .batch_size(4)
      .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_u4);
  }

  TEST(F32_VRSQRT__SSE_RECIP_SQRT_U4, batch_div_4) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 8; batch_size < 40; batch_size += 4) {
      VUnaryMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_u4);
    }
  }

  TEST(F32_VRSQRT__SSE_RECIP_SQRT_U4, batch_lt_4) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 1; batch_size < 4; batch_size++) {
      VUnaryMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_u4);
    }
  }

  TEST(F32_VRSQRT__SSE_RECIP_SQRT_U4, batch_gt_4) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 4 + 1; batch_size < 8; batch_size++) {
      VUnaryMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_u4);
    }
  }

  TEST(F32_VRSQRT__SSE_RECIP_SQRT_U4, inplace) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 1; batch_size <= 20; batch_size += 3) {
      VUnaryMicrokernelTester()
        .batch_size(batch_size)
        .inplace(true)
        .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_u4);
    }
  }
#endif  // XNN_ARCH_X86 || XNN_ARCH_X86_64


#if XNN_ARCH_X86 || XNN_ARCH_X86_64
  TEST(F32_VRSQRT__SSE_RECIP_SQRT_U8, batch_eq_8) {
    TEST_REQUIRES_X86_SSE;
    VUnaryMicrokernelTester()
      .batch_size(8)
      .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_u8);
  }

  TEST(F32_VRSQRT__SSE_RECIP_SQRT_U8, batch_div_8) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 16; batch_size < 80; batch_size += 8) {
      VUnaryMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_u8);
    }
  }

  TEST(F32_VRSQRT__SSE_RECIP_SQRT_U8, batch_lt_8) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 1; batch_size < 8; batch_size++) {
      VUnaryMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_u8);
    }
  }

  TEST(F32_VRSQRT__SSE_RECIP_SQRT_U8, batch_gt_8) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 8 + 1; batch_size < 16; batch_size++) {
      VUnaryMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_u8);
    }
  }

  TEST(F32_VRSQRT__SSE_RECIP_SQRT_U8, inplace) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 1; batch_size <= 40; batch_size += 7) {
      VUnaryMicrokernelTester()
        .batch_size(batch_size)
        .inplace(true)
        .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_u8);
    }
  }
#endif  // XNN_ARCH_X86 || XNN_ARCH_X86_64


#if XNN_ARCH_X86 || XNN_ARCH_X86_64
  TEST(F32_VRSQRT__SSE_RECIP_SQRT_ITER_U4, batch_eq_4) {
    TEST_REQUIRES_X86_SSE;
    VUnaryMicrokernelTester()
      .batch_size(4)
      .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_iter_u4);
  }

  TEST(F32_VRSQRT__SSE_RECIP_SQRT_ITER_U4, batch_div_4) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 8; batch_size < 40; batch_size += 4) {
      VUnaryMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_iter_u4);
    }
  }

  TEST(F32_VRSQRT__SSE_RECIP_SQRT_ITER_U4, batch_lt_4) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 1; batch_size < 4; batch_size++) {
      VUnaryMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_iter_u4);
    }
  }

  TEST(F32_VRSQRT__SSE_RECIP_SQRT_ITER_U4, batch_gt_4) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 4 + 1; batch_size < 8; batch_size++) {
      VUnaryMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_iter_u4);
    }
  }

  TEST(F32_VRSQRT__SSE_RECIP_SQRT_ITER_U4, inplace) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 1; batch_size <= 20; batch_size += 3) {
      VUnaryMicrokernelTester()
        .batch_size(batch_size)
        .inplace(true)
        .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_iter_u4);
    }
  }
#endif  // XNN_ARCH_X86 || XNN_ARCH_X86_64


#if XNN_ARCH_X86 || XNN_ARCH_X86_64
  TEST(F32_VRSQRT__SSE_RECIP_SQRT_ITER_U8, batch_eq_8) {
    TEST_REQUIRES_X86_SSE;
    VUnaryMicrokernelTester()
      .batch_size(8)
      .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_iter_u8);
  }

  TEST(F32_VRSQRT__SSE_RECIP_SQRT_ITER_U8, batch_div_8) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 16; batch_size < 80; batch_size += 8) {
      VUnaryMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_iter_u8);
    }
  }

  TEST(F32_VRSQRT__SSE_RECIP_SQRT_ITER_U8, batch_lt_8) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 1; batch_size < 8; batch_size++) {
      VUnaryMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_iter_u8);
    }
  }

  TEST(F32_VRSQRT__SSE_RECIP_SQRT_ITER_U8, batch_gt_8) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 8 + 1; batch_size < 16; batch_size++) {
      VUnaryMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_iter_u8);
    }
  }

  TEST(F32_VRSQRT__SSE_RECIP_SQRT_ITER_U8, inplace) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 1; batch_size <= 40; batch_size += 7) {
      VUnaryMicrokernelTester()
        .batch_size(batch_size)
        .inplace(true)
        .Test(xnn_f32_vrsqrt_ukernel__sse_recip_sqrt_iter_u8);
    }
  }
#endif  // XNN_ARCH_X86 || XNN_ARCH_X86_64
