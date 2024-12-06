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

#include <stdext/catexit.h>

#include <stdlib.h>

#include <stdext/cmacros.h>

volatile sig_atomic_t catexit_loopSafety = true;

static catexitHandler __cregsignalHandler__ = SIG_DFL;

#define CATEXIT_SIG_COUNT 5
static int catexitSigs[CATEXIT_SIG_COUNT] = {
#ifdef SIGHUP
    SIGHUP,
#else
    -1,
#endif
#ifdef SIGQUIT
    SIGQUIT,
#else
    -1,
#endif
#ifdef SIGTSTP
    SIGTSTP,
#else
    -1,
#endif
#ifdef SIGINT
    SIGINT,
#else
    -1,
#endif
#ifdef SIGBREAK
    SIGBREAK,
#else
    -1,
#endif
};

static void __catexitHandler__(void) {
    __cregsignalHandler__(-1);
}

static void __csignalHandler__(int sig) {
    __cregsignalHandler__(sig);
}

int catexit(catexitHandler handler) {
    int success = 0;
    __cregsignalHandler__ = handler;
    success += !atexit(__catexitHandler__);
    for (int i = 0; catexit_loopSafety && i < CATEXIT_SIG_COUNT; i++) {
        if (catexitSigs[i] != -1) {
#ifdef _WIN32
            success += signal(catexitSigs[i], __csignalHandler__) != SIG_ERR;
#else
            struct sigaction act;
            act.sa_handler = __csignalHandler__;
            act.sa_flags = 0;
            sigemptyset(&act.sa_mask);
            success += sigaction(catexitSigs[i], &act, NULL) != -1;
#endif
        }
    }
    return catexit_loopSafety ? success : 0;
}

void catexit_defaultExitHandler(int sig) {
    FAKEREF(sig);
    
    catexit_loopSafety = false;
}
