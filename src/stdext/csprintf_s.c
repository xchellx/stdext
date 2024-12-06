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

#include <stdext/csprintf_s.h>

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

char *csprintf_s(char *format, ...) {
    if (format) {
        va_list args;
        
        va_start(args, format);
        int buffSz = vsnprintf(NULL, 0, format, args);
        va_end(args);
        
        assert(!!buffSz);
        if (!buffSz)
            return NULL;
        
        char *buff = malloc(buffSz + 1);
        if (buff) {
            va_start(args, format);
            vsnprintf(buff, buffSz + 1, format, args);
            va_end(args);
            buff[buffSz] = '\0';
            
            return buff;
        } else
            return NULL;
    } else
        return NULL;
}
