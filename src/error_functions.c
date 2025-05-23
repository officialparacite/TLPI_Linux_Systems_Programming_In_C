#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "error_functions.h"
#include "tlpi_hdr.h"
#include "ename.c.inc"

/* compiler hint to tell the compiler not to generate more code,
since this function is going to return back to the caller function */
#ifdef __GNUC__
__attribute__ ((__noreturn__)) 
#endif

static void terminate(Boolean useExit3){
    char *s;
    s = getenv("EF_DUMPCORE");
    if(s != NULL && *s != '\0') abort(); // Cause a coredump
    else if (useExit3) exit(EXIT_FAILURE); // Graceful exit
    else _exit(EXIT_FAILURE); // Immediate exit
}

static void outputError(
    Boolean useErr,     // Whether to print system error info
    int err,            // Error number like errno
    Boolean flushStdout,// Whether to flush stdout before printing the error 
    const char* format, // User's error message format
    va_list ap          // Variable arguments list used in vsnprintf
)
{
    #define BUF_SIZE 500
    char buf[BUF_SIZE], userMsg[BUF_SIZE], errText[BUF_SIZE];

    vsnprintf(userMsg, BUF_SIZE, format, ap);

    if(useErr) snprintf(errText, BUF_SIZE, " [%s %s]", (err > 0 && err <= MAX_ENAME) ? ename[err] : "?UNKNOWN?", strerror(err));

    else snprintf(errText, BUF_SIZE, ":");

    snprintf(buf, BUF_SIZE, "ERROR%s %s\n", errText, userMsg);

    if(flushStdout) fflush(stdout);
    fputs(buf, stderr);
    fflush(stderr);
}
void errMsg(const char *format, ...){
    va_list argsList;
    int savedErrno;

    savedErrno = errno;

    va_start(argsList, format);
    outputError(TRUE, errno, TRUE, format, argsList);
    va_end(argsList);

    errno = savedErrno;
}
void errExit(const char *format, ...){
    va_list argList;

    va_start(argList, format);
    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);

    terminate(TRUE);
}
void err_exit(const char *format, ...){
    va_list argList;

    va_start(argList, format);
    outputError(TRUE, errno, FALSE, format, argList);
    va_end(argList);

    terminate(FALSE);
}
void errExitEN(int errnum, const char *format, ...){
    va_list argList;

    va_start(argList, format);
    outputError(TRUE, errnum, TRUE, format, argList);
    va_end(argList);

    terminate(TRUE);
}
void fatal(const char *format, ...){
    va_list argList;

    va_start(argList, format);
    outputError(FALSE, 0, TRUE, format, argList);
    va_end(argList);

    terminate(TRUE);
}
void usageErr(const char *format, ...){
    va_list argList;

    fflush(stdout);

    fprintf(stderr, "Usage: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);

    fflush(stderr);
    exit(EXIT_FAILURE);
}
void cmdLineErr(const char *format, ...){
    va_list argList;

    fflush(stdout);

    fprintf(stderr, "Command-line usage error: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);

    fflush(stderr);
    exit(EXIT_FAILURE);
}
