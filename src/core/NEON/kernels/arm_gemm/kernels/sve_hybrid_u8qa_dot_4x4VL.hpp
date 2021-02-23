/*
 * Copyright (c) 2019-2020 Arm Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#pragma once
#ifdef __ARM_FEATURE_SVE

#include "../std_transforms_sve.hpp"

#define ARGLIST  \
   unsigned int, const unsigned int *, \
   IndirectInputArg<uint8_t>, \
   size_t, size_t, \
   const uint8_t *, \
   IndirectOutputArg<uint8_t>, \
   const Requantize32 *, const int32_t *, unsigned int

namespace arm_gemm
{

// Actual kernel implementations
void sve_hybrid_u8qa_dot_4x4VL( ARGLIST );

class cls_sve_hybrid_u8qa_dot_4x4VL
{
public:
    typedef uint8_t operand_type;
    typedef uint8_t result_type;

    typedef void (*kern_type)( ARGLIST );

    /* Kernel blocking parameters */
    static constexpr unsigned int out_height()
    {
        return 4;
    }

    static unsigned int out_width()
    {
        return get_vector_length<uint32_t>() * 4;
    }

    static constexpr unsigned int k_unroll()
    {
        return 4;
    }

    static constexpr bool supports_accumulate()
    {
        return false;
    }

    StdTransformsSVE<operand_type, result_type, 4, 4, 4> transforms = {};

    // Default to the generic kernel
    kern_type kernel=sve_hybrid_u8qa_dot_4x4VL;

    cls_sve_hybrid_u8qa_dot_4x4VL(const CPUInfo *)
    {
    }
};

} // namespace arm_gemm

#undef ARGLIST
#endif // __ARM_FEATURE_SVE
