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

#ifndef __CSTRTO_S_H__
#define __CSTRTO_S_H__
#include <stdint.h>

typedef enum CStrToSError {
    STE_ERR_SUCCESS = 0,
    STE_ERR_NULLPTR,
    STE_ERR_NOTNUM,
    STE_ERR_NOTFULLNUM,
    STE_ERR_OORMINMAX,
    STE_ERR_OORNUMMIN,
    STE_ERR_OORNUMMAX
} CStrToSError_t;

#define __HTEM_STRTO_S__(n, t) CStrToSError_t n(char *__b, t *__o)

__HTEM_STRTO_S__(cstrtouc_s, uint8_t);

__HTEM_STRTO_S__(cstrtoc_s, int8_t);

__HTEM_STRTO_S__(cstrtous_s, uint16_t);

__HTEM_STRTO_S__(cstrtos_s, int16_t);

__HTEM_STRTO_S__(cstrtoui_s, uint32_t);

__HTEM_STRTO_S__(cstrtoi_s, int32_t);

__HTEM_STRTO_S__(cstrtoul_s, uint64_t);

__HTEM_STRTO_S__(cstrtol_s, int64_t);

char *CStrToSError_ToStr(CStrToSError_t strToError);
#endif
