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

#ifndef __CDATA_H__
#define __CDATA_H__
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <stdext/cmacros.h>

#if CHAR_BIT != 8
#error cdata.h assumes that a byte is 8 bits
#endif

#ifndef IS_LITTLE_ENDIAN
#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define IS_LITTLE_ENDIAN 1
#else
#define IS_LITTLE_ENDIAN 0
#endif
#endif

#ifndef IS_BIG_ENDIAN
#if defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define IS_BIG_ENDIAN 1
#else
#define IS_BIG_ENDIAN 0
#endif
#endif

#if IS_LITTLE_ENDIAN == 0 && IS_BIG_ENDIAN == 0
#error Unknown or unsupported architecture for cdata.h
#endif

#ifdef _WIN32
#include <stdlib.h>
#define bswap_16(x) _byteswap_ushort((x))
#define bswap_32(x) _byteswap_ulong((x))
#define bswap_64(x) _byteswap_uint64((x))
#else
#include <byteswap.h>
#endif

#if IS_BIG_ENDIAN == 1
#define ntohll(x) (x)
#define ntohl(x) (x)
#define ntohs(x) (x)
#define htonll(x) (x)
#define htonl(x) (x)
#define htons(x) (x)
#elif IS_LITTLE_ENDIAN == 1
#define ntohll(x) bswap_64((x))
#define ntohl(x) bswap_32((x))
#define ntohs(x) bswap_16((x))
#define htonll(x) bswap_64((x))
#define htonl(x) bswap_32((x))
#define htons(x) bswap_16((x))
#endif

#define CD_DEF_BSWAPU_DEFN(tn, v) ( bswap_ ## tn ((v)))

#define CD_DEF_BSWAPS_DEFN(tn, v) (( int ## tn ## _t ) ( bswap_ ## tn ((( uint ## tn ## _t ) ((v))))))

#define Dat_BSwapU16(v) CD_DEF_BSWAPU_DEFN(16, (v))
#define Dat_BSwapS16(v) CD_DEF_BSWAPS_DEFN(16, (v))

#define Dat_BSwapU32(v) CD_DEF_BSWAPU_DEFN(32, (v))
#define Dat_BSwapS32(v) CD_DEF_BSWAPS_DEFN(32, (v))

#define Dat_BSwapU64(v) CD_DEF_BSWAPU_DEFN(64, (v))
#define Dat_BSwapS64(v) CD_DEF_BSWAPS_DEFN(64, (v))

#if IS_BIG_ENDIAN == 1
#define Dat_BSwapLE_indp(tn, v) Dat_BSwap ## tn ((v))
#else
#define Dat_BSwapLE_indp(tn, v) (v)
#endif

#if IS_LITTLE_ENDIAN == 1
#define Dat_BSwapBE_indp(tn, v) Dat_BSwap ## tn ((v))
#else
#define Dat_BSwapBE_indp(tn, v) (v)
#endif

#define CD_SETNAME(tn) \
Dat_Set ## tn

#define CD_SETDECL(tn, t) \
FORCE_INLINE void CD_SETNAME(tn) ( uint8_t *s, t v )

#ifdef STDEXT_TEST_ALIGNMENT
#define CD_SETDEFN(tn, t) \
CD_SETDECL(tn, t) { \
    *(( t *) (s)) = v; \
}
#else
#define CD_SETDEFN(tn, t) \
CD_SETDECL(tn, t) { \
    memcpy(s, &v, sizeof( t )); \
}
#endif

#define CD_SETLENAME(tn) \
Dat_Set ## tn ## LE

#define CD_SETLEDECL(tn, t) \
FORCE_INLINE void CD_SETLENAME(tn) ( uint8_t *s, t v )

#ifdef STDEXT_TEST_ALIGNMENT
#define CD_SETLEDEFN(tn, t) \
CD_SETLEDECL(tn, t) { \
    t sv = Dat_BSwapLE_indp(tn, v); \
    *(( t *) (s)) = sv; \
}
#else
#define CD_SETLEDEFN(tn, t) \
CD_SETLEDECL(tn, t) { \
    t sv = Dat_BSwapLE_indp(tn, v); \
    memcpy(s, &sv, sizeof( t )); \
}
#endif

#define CD_SETBENAME(tn) \
Dat_Set ## tn ## BE

#define CD_SETBEDECL(tn, t) \
FORCE_INLINE void CD_SETBENAME(tn) ( uint8_t *s, t v )

#ifdef STDEXT_TEST_ALIGNMENT
#define CD_SETBEDEFN(tn, t) \
CD_SETBEDECL(tn, t) { \
    t sv = Dat_BSwapBE_indp(tn, v); \
    *(( t *) (s)) = sv; \
}
#else
#define CD_SETBEDEFN(tn, t) \
CD_SETBEDECL(tn, t) { \
    t sv = Dat_BSwapBE_indp(tn, v); \
    memcpy(s, &sv, sizeof( t )); \
}
#endif

#define CD_GETNAME(tn) \
Dat_Get ## tn

#define CD_GETDECL(tn, t) \
FORCE_INLINE t CD_GETNAME(tn) (uint8_t *s)

#ifdef STDEXT_TEST_ALIGNMENT
#define CD_GETDEFN(tn, t) \
CD_GETDECL(tn, t) { \
    t v = *(( t *) (s)); \
    return v; \
}
#else
#define CD_GETDEFN(tn, t) \
CD_GETDECL(tn, t) { \
    t v = 0; \
    memcpy(&v, s, sizeof( t )); \
    return v; \
}
#endif

#define CD_GETLENAME(tn) \
Dat_Get ## tn ## LE

#define CD_GETLEDECL(tn, t) \
FORCE_INLINE t CD_GETLENAME(tn) (uint8_t *s)

#ifdef STDEXT_TEST_ALIGNMENT
#define CD_GETLEDEFN(tn, t) \
CD_GETLEDECL(tn, t) { \
    t v = *(( t *) (s)); \
    return Dat_BSwapLE_indp(tn, v); \
}
#else
#define CD_GETLEDEFN(tn, t) \
CD_GETLEDECL(tn, t) { \
    t v = 0; \
    memcpy(&v, s, sizeof( t )); \
    return Dat_BSwapLE_indp(tn, v); \
}
#endif

#define CD_GETBENAME(tn) \
Dat_Get ## tn ## BE

#define CD_GETBEDECL(tn, t) \
FORCE_INLINE t CD_GETBENAME(tn) (uint8_t *s)

#ifdef STDEXT_TEST_ALIGNMENT
#define CD_GETBEDEFN(tn, t) \
CD_GETBEDECL(tn, t) { \
    t v = *(( t *) (s)); \
    return Dat_BSwapBE_indp(tn, v); \
}
#else
#define CD_GETBEDEFN(tn, t) \
CD_GETBEDECL(tn, t) { \
    t v = 0; \
    memcpy(&v, s, sizeof( t )); \
    return Dat_BSwapBE_indp(tn, v); \
}
#endif

#define CD_ALIGNNAME(tn) \
Dat_Align ## tn

#define CD_ALIGNDECL(tn, t) \
FORCE_INLINE t CD_ALIGNNAME(tn) (t s, t n)

#define CD_ALIGNDEFN(tn, t) \
CD_ALIGNDECL(tn, t) { \
    return (s + (n - 1)) & ~(n - 1); \
}

#define CD_PADNAME(tn) \
Dat_Pad ## tn

#define CD_PADDECL(tn, t) \
FORCE_INLINE t CD_PADNAME(tn) (t s, t n)

#define CD_PADDEFN(tn, t) \
CD_PADDECL(tn, t) { \
    return (s + (n - 1)) & ~(n - 1); \
}

#define CD_ALLTGRP(grp) \
grp(U16, uint16_t) \
grp(S16, int16_t) \
grp(U32, uint32_t) \
grp(S32, int32_t) \
grp(U64, uint64_t) \
grp(S64, int64_t)

CD_ALLTGRP(CD_SETDEFN)
CD_ALLTGRP(CD_SETLEDEFN)
CD_ALLTGRP(CD_SETBEDEFN)
CD_ALLTGRP(CD_GETDEFN)
CD_ALLTGRP(CD_GETLEDEFN)
CD_ALLTGRP(CD_GETBEDEFN)
CD_ALLTGRP(CD_ALIGNDEFN)
CD_ALLTGRP(CD_PADDEFN)

FORCE_INLINE size_t Dat_PtrDiff(void *start, void *offset) {
    return (size_t) (((uintptr_t) offset) - ((uintptr_t) start));
}
#endif
