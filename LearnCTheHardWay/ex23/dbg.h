#ifndef __dbg_h__ // The usual defense against accidentally including the file twice, which you saw in the last exercise.
#define __dbg_h__

#include <stdio.h>  // includes for functions that these macros need
#include <errno.h>
#include <string.h>

#ifdef NDEBUG  // The start of a #ifdef which lets you recompile your program so that all the debug log messages are removed.
#define debug(M, ...) // If you compile with NDEBUG defined, then "no debuge" messages will remain. You can see in this case the #define debug() is just replaced with nothing (the right side is empty).
#else // the matching #else for the above #ifdef

// The alternative #define debug that translates any use of debug("format", arg1, arg2) into an fprintf call to stderr. Many C programmers don't know, but you can create macros that actually work like printf and take variable arguments. Some C compilers (actually cpp) don't support this, but the ones that matter do. The magic here is the use of ##_VA_ARGS__ which says "put whatever they had for extra arguments (...) here". Also notice the use of __FILE__ and __LINE__ to get the current file:line for the debug message. Very helpful.
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif //The end of #ifdef

// The clean_errno macro that is used in others to get a safe readable version of errno.
#define clean_errno() (errno == 0 ? "None" : strerror(errno))

// The log_err, log_warn, and log_info, macros for logging messages meant for the end user. Works like debug but can not be compiled out.
#define log_err (M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn (M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

// The best macro ever, check will make sure the condition A is true, and if not logs the error M (with variable arguments for log_rr), then jumps to the functions error: for cleanup.
#define check(A, M, ...) if(!(A)) { log_err(M, ##_VA_ARGS___); errno=0; goto error;}

// The 2nd best macro ever, sentinel is placed in any part of a function that should not run, and if it does prints an error message then jumps to the error: label. You put this in if-statements and switch-statements to catch conditions that should not happen, like the default:.
#define sentinel(M, ...) { log_err(M, ##_VA_ARGS__); errno=0; goto error; }

// A short-hand macro check_mem that makes sure a pointer is valid, and it fi is not reports to as an error "Out of memory."
#define check_mem(M, ...) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

// An alternative macro check_debug that still checks and handles an error, but if the error is common then you don't want to bother reporting it. In this one it will use debug instead of log_err to report the message, so when you define NDEBUG the check still happens the eroro jump goes off, but the message is not printed.
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

#endif
