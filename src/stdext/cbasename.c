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

#include <stdext/cbasename.h>

#include <stdlib.h>
#include <string.h>

#include <stdext/csprintf_s.h>

char *__csafename(char *path, __csafename_Type_t__ type, bool strip) {
    if (path) {
        int pathLen = strlen(path);
        char *newPath = NULL;
        
        if (type == __CSN_CEN__)
            newPath = strrchr(path, '.');
        else if (type == __CSN_CBN__) {
            newPath = strrchr(path, '/');
            if (!newPath)
                newPath = strrchr(path, '\\');
        }
        
        if (newPath) {
            if (strip && newPath < (path + pathLen))
                newPath += 1;
            
            return newPath;
        } else
            return NULL;
    } else
        return NULL;
}

char *__cmemsafename(char *path, char **outPtr, __cmemsafename_Type_t__ type, bool strip) {
    if (path && outPtr) {
        char *buff = csprintf_s("%s", path);
        if (buff) {
            *outPtr = buff;
            
            char *buffPtr = NULL;
            if (type == __SMN_CPN__ || type == __SMN_CFN__)
                buffPtr = cextnameraw(buff);
            else if (type == __SMN_CDN__)
                buffPtr = strip ? cbasenameraw(buff) : cbasename(buff);
            
            if (buffPtr >= buff) {
                if (buffPtr != buff)
                    *buffPtr = '\0';
                if (type == __SMN_CFN__) {
                    char *cbn = cbasename(buff);
                    return cbn ? cbn : buff;
                } else
                    return buff;
            } else {
                free(buff);
                *outPtr = NULL;
                return NULL;
            }
        } else {
            *outPtr = NULL;
            return NULL;
        }
    } else {
        if (outPtr)
            *outPtr = NULL;
        return NULL;
    }
}
