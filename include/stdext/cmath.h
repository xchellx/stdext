/*
 * MIT License
 * 
 * Copyright (c) 2024 Yonder
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __CMATH_H__
#define __CMATH_H__
#include <stddef.h>
#include <stdint.h>

#include <stdext/cmacros.h>

#define CM_MINNAME(tn) \
Math_Min ## tn

#define CM_MINDECL(tn, t) \
FORCE_INLINE t CM_MINNAME(tn) ( t n, t min )

#define CM_MINDEFN(tn, t) \
CM_MINDECL(tn, t) { \
    return n < min ? n : min; \
}

#define CM_MAXNAME(tn) \
Math_Max ## tn

#define CM_MAXDECL(tn, t) \
FORCE_INLINE t CM_MAXNAME(tn) ( t n, t max )

#define CM_MAXDEFN(tn, t) \
CM_MAXDECL(tn, t) { \
    return n > max ? n : max; \
}

#define CM_CLAMPNAME(tn) \
Math_Clamp ## tn

#define CM_CLAMPDECL(tn, t) \
FORCE_INLINE t CM_CLAMPNAME(tn) ( t n, t min, t max )

#define CM_CLAMPDEFN(tn, t) \
CM_CLAMPDECL(tn, t) { \
    return CM_MAXNAME(tn) (min, CM_MINNAME(tn) (n, max)); \
}

#define CM_FLIPNAME(tn) \
Math_Flip ## tn

#define CM_FLIPDECL(tn, t) \
FORCE_INLINE t CM_FLIPNAME(tn) ( t c, t sz )

#define CM_FLIPDEFN(tn, t) \
CM_FLIPDECL(tn, t) { \
    return sz - c - 1; \
}

#define CM_COMPARENAME(tn) \
Math_Compare ## tn

#define CM_COMPAREDECL(tn, t) \
int CM_COMPARENAME(tn) (const void *a, const void *b)

#define CM_COMPAREDEFN(tn, t) \
CM_COMPAREDECL(tn, t) { \
    t ai = *(( t *) a); \
    t bi = *(( t *) b); \
    if (ai < bi) \
        return -1; \
    else if (ai > bi) \
        return 1; \
    else \
        return 0; \
}

#define CM_ALLTGRP(grp, ...) \
grp(Sz, size_t) __VA_OPT__(SEMICOLON) \
grp(Pd, ptrdiff_t) __VA_OPT__(SEMICOLON) \
grp(U8, uint8_t) __VA_OPT__(SEMICOLON) \
grp(S8, int8_t) __VA_OPT__(SEMICOLON) \
grp(U16, uint16_t) __VA_OPT__(SEMICOLON) \
grp(S16, int16_t) __VA_OPT__(SEMICOLON) \
grp(U32, uint32_t) __VA_OPT__(SEMICOLON) \
grp(S32, int32_t) __VA_OPT__(SEMICOLON) \
grp(U64, uint64_t) __VA_OPT__(SEMICOLON) \
grp(S64, int64_t) __VA_OPT__(SEMICOLON) \
grp(Fl, float) __VA_OPT__(SEMICOLON) \
grp(Db, double) __VA_OPT__(SEMICOLON)

CM_ALLTGRP(CM_MINDEFN,)
CM_ALLTGRP(CM_MAXDEFN,)
CM_ALLTGRP(CM_CLAMPDEFN,)
CM_ALLTGRP(CM_FLIPDEFN,)

CM_ALLTGRP(CM_COMPAREDECL,_)
#endif
