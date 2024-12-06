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

#ifndef __CSTAT_H__
#define __CSTAT_H__
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/stat.h>

#include <stdext/cmacros.h>

#ifdef _WIN32
#define mkdir(A, B) mkdir(A)
#endif

FORCE_INLINE bool cmkdir(char *path) {
    return mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) && errno != EEXIST;
}

FORCE_INLINE bool cfexists(char *path, bool *isDir) {
    struct stat pathStat;
    int err = stat(path, &pathStat);
    *isDir = !!S_ISDIR(pathStat.st_mode);
    return !!err;
}

FORCE_INLINE bool cfopen(char *path, char *mode, FILE **file) {
    return !(*file = fopen(path, mode));
}

FORCE_INLINE bool cfclose(FILE *stream) {
    return fclose(stream) == EOF;
}

FORCE_INLINE bool cfread(void *buffer, size_t size, size_t count, FILE *stream) {
    return fread(buffer, size, count, stream) != count;
}

FORCE_INLINE bool cfwrite(void *buffer, size_t size, size_t count, FILE *stream) {
    return fwrite(buffer, size, count, stream) != count;
}

FORCE_INLINE bool cfsize(size_t *size, FILE *stream) {
    if (!size)
        return true;
    if (fseek(stream, 0, SEEK_END))
        return true;
    int64_t lsize = ftell(stream);
    if (lsize == -1L)
        return true;
    int olderrno = errno;
    errno = 0;
    rewind(stream);
    if (errno)
        return true;
    errno = olderrno;
    *size = lsize;
    return false;
}
#endif
