//
//  threadsDefs.hpp
//  plants_watersystem
//
//  Created by Piotr Cieślik on 17/12/24.
//

#ifndef threadsDef_h
#define threadsDef_h

#undef THREADS_GCC_COMPILER
#undef THREADS_CLANG_COMPILER
#undef THREADS_MSVC_COMPILER
#undef THREADS_CW_COMPILER
#undef THREADS_STM_COMPILER

#if defined(__GNUC__) || defined(__GNUG__)
    #define THREADS_GCC_COMPILER 1
#elif defined(_MSC_VER)
    #define THREADS_MSVC_COMPILER 1
#elif defined(__clang__)
    #define THREADS_CLANG_COMPILER 1
#elif defined(__MWERKS__)
    #define THREADS_CW_COMPILER 1
#elif defined(TARGET_STM)
    #define THREADS_STM_COMPILER 1
#else
    #error "Unknown compiler!"
#endif

#undef THREADS_MACOS
#undef THREADS_WINOS
#undef THREADS_LINUXOS
#undef THREADS_STM32OS
#undef THREADS_FREEBSDOS

#if defined(_WIN32)
    #define THREADS_WINOS 1
#elif defined(macintosh) || (defined(__MACH__) && defined(__APPLE__))
    #define THREADS_MACOS 1
#elif defined(__linux__)
    #define THREADS_LINUXOS 1
#elif defined(__FreeBSD__)
    #define THREADS_FREEBSDOS 1
#elif defined(TARGET_STM)
    #define THREADS_STM32OS 1
#else
    #error "Unknown OS!"
#endif



#endif /* threadsDef_h */