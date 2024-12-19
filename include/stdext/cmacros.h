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

#ifndef __CMACROS_H__
#define __CMACROS_H__

#ifndef ISEVEN
#define ISEVEN(n) !(n % 2)
#endif

#ifndef TOSTR
#define TOSTR(s) #s
#endif

#ifndef XTOSTR
#define XTOSTR(x) TOSTR(x)
#endif

#ifndef COMBINE
#define COMBINE(x, y) x ## y
#endif

#ifndef XCOMBINE
#define XCOMBINE(x, y) COMBINE(x, y)
#endif

#ifndef ALIGN
#define ALIGN __attribute__((packed, aligned(1)))
#endif

#ifndef PACK
#define PACK __attribute__((packed))
#endif

#ifndef INLINE
#define INLINE static inline
#endif

#ifndef FORCE_INLINE
#define FORCE_INLINE static inline __attribute__((always_inline))
#endif

#ifndef USED
#define USED __attribute__((used))
#endif

#ifndef FAKEREF
#define FAKEREF(v) ((void) v )
#endif

#ifndef EMPTY_STATEMENT
#define EMPTY_STATEMENT(v) ((void) 0)
#endif

#ifndef COMMA
#define COMMA ,
#endif

#ifndef SEMICOLON
#define SEMICOLON ;
#endif

#ifndef LPARAN
#define LPARAN (
#endif

#ifndef RPARAN
#define RPARAN )
#endif

#ifndef SLASH
#define SLASH /
#endif

#ifndef ASTERISK
#define ASTERISK *
#endif

#ifndef EXPORT
#ifndef _WIN32
#define EXPORT __attribute__((dllexport))
#else
#define EXPORT __attribute__((visibility("default")))
#endif
#endif

#endif
