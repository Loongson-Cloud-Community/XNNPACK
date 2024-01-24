#!/bin/sh
# Copyright 2024 Google LLC
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.

#################################### Scalar ###################################
tools/xngen src/f32-vrsqrt/scalar-rsqrt.c.in -D BATCH_TILE=1 -o src/f32-vrsqrt/gen/f32-vrsqrt-scalar-recip-sqrt-u1.c &
tools/xngen src/f32-vrsqrt/scalar-rsqrt.c.in -D BATCH_TILE=2 -o src/f32-vrsqrt/gen/f32-vrsqrt-scalar-recip-sqrt-u2.c &
tools/xngen src/f32-vrsqrt/scalar-rsqrt.c.in -D BATCH_TILE=4 -o src/f32-vrsqrt/gen/f32-vrsqrt-scalar-recip-sqrt-u4.c &

################################# x86 128-bit #################################
tools/xngen src/f32-vrsqrt/sse-rsqrt.c.in -D BATCH_TILE=4 -o src/f32-vrsqrt/gen/f32-vsqrt-sse-rsqrt-u4.c &
tools/xngen src/f32-vrsqrt/sse-rsqrt.c.in -D BATCH_TILE=8 -o src/f32-vrsqrt/gen/f32-vsqrt-sse-rsqrt-u8.c &
tools/xngen src/f32-vrsqrt/sse-rsqrt-iter.c.in -D BATCH_TILE=4 -o src/f32-vrsqrt/gen/f32-vsqrt-sse-rsqrt-iter-u4.c &
tools/xngen src/f32-vrsqrt/sse-rsqrt-iter.c.in -D BATCH_TILE=8 -o src/f32-vrsqrt/gen/f32-vsqrt-sse-rsqrt-iter-u8.c &

wait
