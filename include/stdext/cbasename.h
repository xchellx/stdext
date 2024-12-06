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

#ifndef __CBASENAME_H__
#define __CBASENAME_H__
#include <stdbool.h>

#include <stdext/cmacros.h>

typedef enum __csafename_Type__ {
    __CSN_CEN__ = 0,
    __CSN_CBN__
} __csafename_Type_t__;

char *__csafename(char *path, __csafename_Type_t__ type, bool strip);

#define cextname(path) __csafename((path), __CSN_CEN__, 1)

#define cextnameraw(path) __csafename((path), __CSN_CEN__, 0)

#define cbasename(path) __csafename((path), __CSN_CBN__, 1)

#define cbasenameraw(path) __csafename((path), __CSN_CBN__, 0)

typedef enum __cmemsafename_Type__ {
    __SMN_CPN__ = 0,
    __SMN_CDN__,
    __SMN_CFN__
} __cmemsafename_Type_t__;

char *__cmemsafename(char *path, char **outPtr, __cmemsafename_Type_t__ type, bool strip);

#define cpathname(path, outPtr) __cmemsafename((path), (outPtr), __SMN_CPN__, 1)

#define cdirname(path, outPtr) __cmemsafename((path), (outPtr), __SMN_CDN__, 1)

#define cdirnameraw(path, outPtr) __cmemsafename((path), (outPtr), __SMN_CDN__, 0)

#define cfilename(path, outPtr) __cmemsafename((path), (outPtr), __SMN_CFN__, 1)
#endif
