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

#include <stdext/cgetchar.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#endif

#include <stdext/catexit.h>

char cgetchar(bool echoc) {
    int c = '\0';
    
#ifdef _WIN32
    while (catexit_loopSafety && (c = (echoc ? getche() : getch())) != EOF) {
        if (c != '\0') {
            if (echoc && !iscntrl(c))
                printf("\n");
            break;
        }
    }
#else
    
    struct termios newf;
    tcgetattr(STDIN_FILENO, &newf);
    struct termios oldf = newf;
    
    if (!echoc)
        newf.c_lflag &= ~ECHO;
    newf.c_lflag &= ~(ECHONL | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newf);
    
    while (catexit_loopSafety && (c = getchar()) != EOF) {
        if (c != '\0') {
            if (echoc && !iscntrl(c))
                printf("\n");
            break;
        }
    }
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldf);
#endif
    
    if (c == '\r')
        c = '\n';
    return (char) c;
}
