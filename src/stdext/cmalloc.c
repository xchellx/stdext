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

#include <stdext/cmalloc.h>

#include <stdlib.h>
#include <string.h>

void *_crealloc(void *prv, size_t size, bool zero) {
    void *new = NULL;
    if (prv) {
        if (zero) {
            size_t oldSize = cmalloc_usable_size(prv);
            new = realloc(prv, size);
            if (new) {
                size_t newSize = cmalloc_usable_size(new);
                if (oldSize < newSize)
                    memset(((char *) new) + oldSize, 0, newSize - oldSize);
            }
        } else
            new = realloc(prv, size);
    } else {
        new = malloc(size);
        if (zero)
            memset(new, 0, size);
    }
    return new;
}
