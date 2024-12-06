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

#ifndef __CSLPRINTF_H__
#define __CSLPRINTF_H__
#include <stdio.h>
#include <stdbool.h>

#if defined(STDEXT_CSLPRINTF_H_INLINE_CLANG) && defined(STDEXT_CSLPRINTF_H_INLINE_GCC)
#error Cannot inline cslprintf.h functions for both clang and gcc at the same time, choose either one (or neither)
#endif

#if !defined(STDEXT_CSLPRINTF_H_INLINE_CLANG) && !defined(STDEXT_CSLPRINTF_H_INLINE_GCC)
#include <stdarg.h>
#endif

#ifdef STDEXT_CSLPRINTF_H_INLINE_GCC
#include <stdext/cmacros.h>
#endif

#ifdef STDEXT_CSLPRINTF_H_INLINE_CLANG
// va_list cannot be inlined and __builtin_va_arg_pack is GCC only so macros must be used instead in this case.
// To avoid the `gnu-zero-variadic-macro-arguments` warning, "format" is part of the macro's variadic arguments.
// __VA_OPT__ isn't that portable either but it is at least getting wide spread adoption, including from MSVC.
#define CP_DEF_CPRINTF_DEFN(o, ...) (fprintf(o __VA_OPT__(,) __VA_ARGS__))

#define CP_DEF_CSLPRINTF_DEFN(o, silent, ...) ((!(silent)) ? fprintf(o __VA_OPT__(,) __VA_ARGS__) : 0)

#define oprintf(...) CP_DEF_CPRINTF_DEFN(stdout __VA_OPT__(,) __VA_ARGS__)

#define eprintf(...) CP_DEF_CPRINTF_DEFN(stderr __VA_OPT__(,) __VA_ARGS__)

#define sloprintf(silent, ...) CP_DEF_CSLPRINTF_DEFN(stdout, (silent) __VA_OPT__(,) __VA_ARGS__)

#define sleprintf(silent, ...) CP_DEF_CSLPRINTF_DEFN(stderr, (silent) __VA_OPT__(,) __VA_ARGS__)
#else
#ifdef STDEXT_CSLPRINTF_H_INLINE_GCC
#define CP_INLINETYPE FORCE_INLINE int
#else
#define CP_INLINETYPE int
#endif

#define CP_CPRINTFNAME(tn) \
tn ## printf

#define CP_CPRINTFDECL(tn) \
CP_INLINETYPE CP_CPRINTFNAME(tn) (char *format, ...)

#ifdef STDEXT_CSLPRINTF_H_INLINE_GCC
#define CP_CPRINTFDEFN_BODY(o) \
    return fprintf(o, format, __builtin_va_arg_pack());
#else
#define CP_CPRINTFDEFN_BODY(o) \
    va_list args; \
    va_start(args, format); \
    int ret = vfprintf(o, format, args); \
    va_end(args); \
    return ret;
#endif

#define CP_CPRINTFDEFN(tn, o) \
CP_CPRINTFDECL(tn) { \
    CP_CPRINTFDEFN_BODY(o) \
}

#define CP_CSLPRINTFNAME(tn) \
sl ## tn ## printf

#define CP_CSLPRINTFDECL(tn) \
CP_INLINETYPE CP_CSLPRINTFNAME(tn) (bool silent, char *format, ...)

#ifdef STDEXT_CSLPRINTF_H_INLINE_GCC
#define CP_CSLPRINTFDEFN_BODY(o) \
    return !silent ? fprintf(o, format, __builtin_va_arg_pack()) : 0;
#else
#define CP_CSLPRINTFDEFN_BODY(o) \
    if (!silent) { \
        va_list args; \
        va_start(args, format); \
        int ret = vfprintf(o, format, args); \
        va_end(args); \
        return ret; \
    } else \
        return 0;
#endif

#define CP_CSLPRINTFDEFN(tn, o) \
CP_CSLPRINTFDECL(tn)  { \
    CP_CSLPRINTFDEFN_BODY(o) \
}

#ifdef STDEXT_CSLPRINTF_H_INLINE_GCC
CP_CPRINTFDEFN(o, stdout)
CP_CPRINTFDEFN(e, stderr)
CP_CSLPRINTFDEFN(o, stdout)
CP_CSLPRINTFDEFN(e, stderr)
#else
CP_CPRINTFDECL(o);
CP_CPRINTFDECL(e);
CP_CSLPRINTFDECL(o);
CP_CSLPRINTFDECL(e);
#endif

#endif

#endif
