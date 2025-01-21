//
//  threadsDefs.hpp
//  threads
//
//  Created by Piotr Cieślik on 17/12/24.
//

#ifndef threadsDef_h
#define threadsDef_h

#include <stdint.h>
#include <stdlib.h>

#undef THREADS_GCC_COMPILER
#undef THREADS_CLANG_COMPILER
#undef THREADS_MSVC_COMPILER
#undef THREADS_CW_COMPILER
#undef THREADS_STM_COMPILER

#if (defined(__ICCARM__) || defined(__CC_ARM)) && defined(__GNUC__)
    #define THREADS_STM_COMPILER 1
#elif defined(__GNUC__) || defined(__GNUG__)
    #define THREADS_GCC_COMPILER 1
#elif defined(_MSC_VER)
    #define THREADS_MSVC_COMPILER 1
#elif defined(__clang__)
    #define THREADS_CLANG_COMPILER 1
#elif defined(__MWERKS__)
    #define THREADS_CW_COMPILER 1
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
#elif (defined(__ICCARM__) || defined(__CC_ARM)) && defined(__GNUC__)
    #define THREADS_STM32OS 1
#else
    #error "Unknown OS!"
#endif

#if defined(THREADS_WINOS)
#elif defined(THREADS_MACOS)
	#include <pthread.h>
	#include <dispatch/dispatch.h>
#elif defined(THREADS_LINUXOS)
#elif defined(THREADS_FREEBSDOS)
#elif defined(THREADS_STM32OS)
#endif

namespace Threads
{
#if defined(THREADS_WINOS)

#elif defined(THREADS_MACOS)
	typedef pthread_mutex_t native_mutex_t;
	typedef pthread_cond_t native_cond_t;
	typedef pthread_t native_thread_handle_t;
	typedef pthread_key_t native_tls_key_t;
	typedef dispatch_semaphore_t native_sema_t;
#elif defined(THREADS_LINUXOS)
#elif defined(THREADS_FREEBSDOS)
#elif defined(THREADS_STM32OS)
#else
    #error "Unknown OS!"
#endif
	typedef void* NativeHandle_t;
	typedef int32_t longInt;
	typedef int64_t extraLongInt;
    typedef void* ThreadHandle_t;
	typedef extraLongInt MicrosecondTime;
	typedef uint64_t RawCPUTime;
	const MicrosecondTime kThreadWaitForever = 0x7FFFFFFFFFFFFFFFLL;
	const int kForeverInMilliseconds = 0x7FFFFFFF;

	typedef uint64_t RawCPUtime;

	typedef enum eThreadErrorCode
	{
		kNoThreadError = 0,
		kMutexReasonMismatch,
		kMutexNotLocked,
		kMutexNotOwned
	} ThreadErrorCode;

	const int kNormalPriority = 0;		// No changes from OS default
	const int kIdlePriority = 999;
	const int kExtraLowPriority = 1000;
	const int kLowPriority = 1001;
	const int kRegularPriority = 1002;
	const int kHighPriority = 1003;
	const int kExtraHighPriority = 1004;
}

#endif /* threadsDef_h */