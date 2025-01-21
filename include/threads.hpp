//
//  threads.hpp
//  threads
//
//  Created by Piotr Cieślik on 17/12/24.
//

#ifndef threads_h
#define threads_h

#include "threadsDefs.hpp"
#include "message.hpp"
#include "threadPtr.hpp"
#include "threadBody.hpp"
#include <exception>

namespace Threads
{
    typedef struct ThreadInfo
    {
        int priority;
        ThreadInfo(int iPriority = kNormalPriority);
    } sThreadInfo;

    typedef void (*dprintfVarg)(const char* fmt, ...);
    typedef int (*dprintfRtn)(const char* fmt, va_list args);
    typedef bool (*MessageFilterRtn)(const Message* msg);

    class ThreadStateSaveRestore
    {
    public:
        virtual void SaveState() = 0;
        virtual void RestoreState() = 0;
        virtual ~ThreadStateSaveRestore();
    };

    class ExceptionId
    {
    public:
        virtual void DoStoredException() = 0;
        virtual ~ExceptionId();
    };

    class ExceptionLocker
    {
    public:
        virtual ExceptionId* StoreException(std::exception* ePtr) = 0;
        virtual ~ExceptionLocker();
    };

    class ThreadSpecificStorage
    {
    public:
        virtual ~ThreadSpecificStorage();
    };

    size_t GetNativeThreadId();

    class ThreadControl
    {
    private:
        static bool QuitAndWait(Message* quitMessageTouse, ThreadPtr target, char* exception = nullptr, MicrosecondTime timeout = kThreadWaitForever);
    public:
        ThreadPtr Self(const char* name = nullptr, const CreateOptions& options = kThreadDefaultOptionsEx);
        static bool IsAlice(ThreadPtr thread);
        static ThreadPtr Create(const Body& bBody = kDefaultThreadBody, const char* name = nullptr, int count = 1);
        static ThreadPtr Create(void (*threadBody)(void*), void* threadParam, const char* name = nullptr, const CreateOptions& options = kThreadDefaultOptionsEx, int count = 1);
        static ThreadPtr CreateEx(const BodyEx& bBody = kDefaultThreadBodyEx, const char* name = nullptr, int count = 1);
        static ThreadPtr CreateEx(void (*threadBody)(void*), void* threadParam, const char* name = nullptr, const CreateOptionsEx& options = kThreadDefaultOptionsEx, int count = 1);
        static void StartAnotherThread(ThreadPtr threadPtr);
        static ThreadPtr GetMainThread();
        static int GetProcessorCount();
        static void SetProcessorCountOverride(int iProcessorCountOverride);
        static int GetProcessorGroupCount();
        static int GetLogicalProcessorCoreCount();
        static int GetPhysicalProcessorPackageCount();
        static void InstallThreadExceptionFilter();
        static void UninstallThreadExceptionFilter();
        static void Join(ThreadStateSaveRestore* contextObj = nullptr);
        static ThreadStateSaveRestore Leave();
        static bool IsAThread();
        static void ThreadYield();
        static std::exception* GetCurrentException();
        static void SetCurrentException(std::exception* ePtr);
        static bool QuitAndWait(ThreadPtr target, char* exception = nullptr, MicrosecondTime timout = kThreadWaitForever);
        static bool QuitAndWaitNoThrow(ThreadPtr target, MicrosecondTime timeout = kThreadWaitForever);
        static ExceptionLocker* InstallExceptionLocker(ExceptionLocker* newLocker);
        static void SetPriority(int newPriority, const char* threadGroup);
        static void SetPriority(int newPriority, ThreadPtr tPtr);
        static void GetPriority(int* pPriority, ThreadPtr tPtr);
        static void GetPriority(int* pPriority, int32_t iThreadID = 0);
        static int32_t GetUniqueThreadSpecificStorageId(int32_t iId);
        static void SetThreadSpecificStorage(int32_t iId, ThreadSpecificStorage* pStorage);
        static ThreadSpecificStorage* GetThreadSpecificStorage(int32_t iId);
        static float SetThreadGroupBias(float fBiasFactor);
    };

    class Messaging
    {
    public:
        static int32_t WaitForThreadMessage(Message** incomingMessage = nullptr, MicrosecondTime waitTime = kThreadWaitForever, MessageFilterRtn filter = nullptr, int iObjectCount = 0, NativeHandle_t *objList = nullptr);
        static MessageTag SendThreadMessage(Message* msg, ThreadPtr tPtr, MicrosecondTime waitTime = kThreadWaitForever, bool sendToAll = false);
        static bool LockMessageQueue(ThreadPtr tPtr, MicrosecondTime waitTime = kThreadWaitForever);
        static ThreadErrorCode UnlockMessageQueue(ThreadPtr tPtr);
        static int32_t MessageWaitingCount(ThreadPtr tPtr);
        static MessageTag PeekIntoPendingMessage(Message** incomingMessage = nullptr, int32_t messageDepth = 0, ThreadPtr tPtr, MicrosecondTime waitTime = 0, int nativeObjectCount = 0, NativeHandle_t* objectList = nullptr);
        static void RaiseExcpetionInMainThread(std::exception* ePtr);
    };

    inline MicrosecondTime DeltaTime(MicrosecondTime t);
    inline MicrosecondTime AbsoluteTime(MicrosecondTime t);
    inline MicrosecondTime DeltaInMilliseconds(int32_t t);
    inline MicrosecondTime AbsoluteInMilliseconds(int32_t t);
    inline void SleepInMilliseconds(int32_t milliseconds);
    inline bool Wait(MicrosecondTime mSeconds);
}

#endif