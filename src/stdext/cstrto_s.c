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

#include <stdext/cstrto_s.h>

#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#include <stdext/cmacros.h>

#define __CTEM_STRTO_S__(n, t, mi, ma, f, r, lm, ...) \
__HTEM_STRTO_S__(n, t) { \
    if (__b && __o) { \
        char *__end; \
        errno = 0; \
        r __v = f(__b, &__end, 10); \
        if (__b == __end) \
            return STE_ERR_NOTNUM; \
        else if (*__end != '\0') \
            return STE_ERR_NOTFULLNUM; \
        else if (errno == ERANGE && (__v == 0 || __v == lm)) \
            return STE_ERR_OORMINMAX; \
        __VA_OPT__( else if LPARAN __v < mi RPARAN ) \
            __VA_OPT__( return STE_ERR_OORNUMMIN SEMICOLON ) \
        else if (__v > ma) \
            return STE_ERR_OORNUMMAX; \
        else { \
            *__o = (t) __v; \
            return STE_ERR_SUCCESS; \
        } \
    } else \
        return STE_ERR_NULLPTR; \
}

#define __CTEM_STRTOU_S__(n, t, mi, ma) __CTEM_STRTO_S__(n, t, mi, ma, strtoul, unsigned long long, ULONG_MAX, _)

#define __CTEM_STRTOS_S__(n, t, mi, ma) __CTEM_STRTO_S__(n, t, mi, ma, strtol, long long, LONG_MAX,)

__CTEM_STRTOU_S__(cstrtouc_s, uint8_t, 0U, UCHAR_MAX)

__CTEM_STRTOS_S__(cstrtoc_s, int8_t, SCHAR_MIN, SCHAR_MAX)

__CTEM_STRTOU_S__(cstrtous_s, uint16_t, 0U, USHRT_MAX)

__CTEM_STRTOS_S__(cstrtos_s, int16_t, SHRT_MIN, SHRT_MAX)

__CTEM_STRTOU_S__(cstrtoui_s, uint32_t, 0U, UINT_MAX)

__CTEM_STRTOS_S__(cstrtoi_s, int32_t, INT_MIN, INT_MAX)

__CTEM_STRTOU_S__(cstrtoul_s, uint64_t, 0U, ULLONG_MAX)

__CTEM_STRTOS_S__(cstrtol_s, int64_t, LLONG_MIN, LLONG_MAX)

char *CStrToSError_ToStr(CStrToSError_t strToError) {
    switch (strToError) {
        case STE_ERR_SUCCESS:
            return "STE_ERR_SUCCESS"
#ifdef STDEXT_INCLUDE_ERROR_STRINGS
                ": Operation was successful."
#endif
            ;
        case STE_ERR_NULLPTR:
            return "STE_ERR_NULLPTR"
#ifdef STDEXT_INCLUDE_ERROR_STRINGS
                ": Input and/or output buffer is NULL."
#endif
            ;
        case STE_ERR_NOTNUM:
            return "STE_ERR_NOTNUM"
#ifdef STDEXT_INCLUDE_ERROR_STRINGS
                ": Not a decimal number."
#endif
            ;
        case STE_ERR_NOTFULLNUM:
            return "STE_ERR_NOTFULLNUM"
#ifdef STDEXT_INCLUDE_ERROR_STRINGS
                ": Extra characters at end of input."
#endif
            ;
        case STE_ERR_OORMINMAX:
            return "STE_ERR_OORMINMAX"
#ifdef STDEXT_INCLUDE_ERROR_STRINGS
                ": Out of range of type long."
#endif
            ;
        case STE_ERR_OORNUMMIN:
            return "STE_ERR_OORNUMMIN"
#ifdef STDEXT_INCLUDE_ERROR_STRINGS
                ": Less than target type minimum limit."
#endif
            ;
        case STE_ERR_OORNUMMAX:
            return "STE_ERR_OORNUMMAX"
#ifdef STDEXT_INCLUDE_ERROR_STRINGS
                ": Greater than target type maximum limit."
#endif
            ;
        default:
            return "UNKNOWN"
#ifdef STDEXT_INCLUDE_ERROR_STRINGS
                ": Invalid error code."
#endif
            ;
    }
}
