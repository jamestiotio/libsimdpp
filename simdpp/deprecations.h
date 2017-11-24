/*  Copyright (C) 2017  Povilas Kanapickas <povilas@radix.lt>

    Distributed under the Boost Software License, Version 1.0.
        (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef LIBSIMDPP_SIMDPP_DEPRETATIONS_H
#define LIBSIMDPP_SIMDPP_DEPRETATIONS_H


/*  Clang supports a native vector extension that defines operators between
    vector types. SSE types such as __m128 and __m128i are implemented on top
    of this extension, which causes code like this being possible:

__m128i a, b; a = a + b;

    Previously, all libsimdpp types had an implicit conversion operator to
    native vector type. For example, both uint8<16> and uint16<8> could be
    implicitly converted to __m128i. This leads to code like this being
    accepted on clang.

uint8<16> a;
uint16<8> b;
a = a + b;

    Here, both a and b are implicitly converted to __m128i values and they are
    added using an operator provided by the clang vector extension.
    Unexpectedly, the result is paddq instruction (64-bit integer addition).

    Because of this, the implicit native vector type conversion operators are
    deprecated and a native() method is provided as a replacement in libsimdpp
    vector types. This change only affects code that interacts with native
    intrinsics. Altivec/VSX and MSA are affected only slightly, because
    intrinsics of those instruction sets never accepted implicit conversions
    from libsimdpp types.
*/
#ifndef SIMDPP_DEFINE_IMPLICIT_CONVERSION_OPERATOR_TO_NATIVE_TYPES
    #define SIMDPP_DEFINE_IMPLICIT_CONVERSION_OPERATOR_TO_NATIVE_TYPES 1
#endif
#if SIMDPP_DEFINE_IMPLICIT_CONVERSION_OPERATOR_TO_NATIVE_TYPES
    #define SIMDPP_IMPLICIT_CONVERSION_DEPRECATION_MSG                          \
        SIMDPP_DEPRECATED(                                                      \
            "Implicit conversion operators may lead to wrong code being "       \
            "accepted without a compile error on Clang. Use the native() "      \
            "method as a replacement.")
#endif

#endif