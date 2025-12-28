/* Minimal pyconfig.h for Typthon CMake build
 * NOTE: This is a stub. A proper build requires running ./configure
 * to generate a complete pyconfig.h with platform-specific settings.
 */

#ifndef Py_PYCONFIG_H
#define Py_PYCONFIG_H

/* Platform detection */
#if defined(_WIN32) || defined(_WIN64)
    #define MS_WINDOWS
    #define MS_WIN32
#elif defined(__linux__)
    #define __linux__ 1
#elif defined(__APPLE__)
    #define __APPLE__ 1
#endif

/* Basic configuration - these are minimal stubs */
#define SIZEOF_INT 4
#define SIZEOF_LONG 8
#define SIZEOF_VOID_P 8
#define SIZEOF_SIZE_T 8
#define SIZEOF_TIME_T 8
#define SIZEOF_WCHAR_T 4
#define SIZEOF_SHORT 2
#define SIZEOF_FLOAT 4
#define SIZEOF_DOUBLE 8
#define SIZEOF_FPOS_T 16
#define SIZEOF_LONG_LONG 8

/* Enable threading */
#ifndef MS_WINDOWS
    #define WITH_THREAD 1
    #define HAVE_PTHREAD_H 1
#endif

/* Common POSIX features */
#ifndef MS_WINDOWS
    #define HAVE_UNISTD_H 1
    #define HAVE_FCNTL_H 1
    #define HAVE_SYS_TYPES_H 1
    #define HAVE_SYS_STAT_H 1
    #define HAVE_DIRENT_H 1
    #define HAVE_DLFCN_H 1
#endif

/* Standard C features */
#define HAVE_STDINT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRING_H 1
#define HAVE_ERRNO_H 1
#define HAVE_STDIO_H 1

/* TODO: Add more platform-specific defines as needed */
/* This stub is incomplete. For a full build, use CPython's configure script */

#endif /* Py_PYCONFIG_H */
