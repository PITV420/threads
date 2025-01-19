//
//  semaphore.hpp
//  threads
//
//  Created by Piotr Cieślik on 17/12/24.
//

#ifndef semaphore_h
#define semaphore_h

#include "threadsDefs.hpp"
#include "threadSafe.hpp"

namespace Threads
{
    class SemaRep
    {
    protected:
        const char* cName;
        uint32_t iMaxCount;
        ThreadSafeLong tCurrentCount;
        const char* cReason[16];
    public:
        SemaRep(const char* name, uint32_t maxCount);
        virtual bool Decrement(const char* reason, MicrosecondTime waitTime) = 0;
        virtual bool Increment(const char* reason, uint32_t count) = 0;
        inline const char* GetName() const;
        inline uint32_t GetCount() const;
        const char* GetReason(uint32_t position);
        virtual ~SemaRep();
    };

    class SemaRepNative : public SemaRep
    {
    private:
        native_sema_t nSema;
    public:
        SemaRepNative(const char* name, uint32_t maxCount);
        virtual bool Decrement(const char* reason, MicrosecondTime waitTime) override;
        virtual bool Increment(const char* reason, uint32_t count) override;
        virtual ~SemaRepNative();
    };

    class SemaRepThread : public SemaRep
    {
    private:
        native_mutex_t nMutex;
        native_cond_t nCondition;
    public:
        SemaRepThread(const char* name, uint32_t maxCount);
        virtual bool Decrement(const char* reason, MicrosecondTime waitTime) override;
        virtual bool Increment(const char* reason, uint32_t count) override;
        virtual ~SemaRepThread();
    };

    class Sema
    {
    private:
        SemaRep* sSemaRep;
    public:
        explicit Sema(const char* name = nullptr, uint32_t maxCount = 1);
        bool Decrement(const char* reason = nullptr, MicrosecondTime waitTime = kThreadWaitForever);
        bool Increment(const char* reason = nullptr, uint32_t count = 1);
        const char* GetName() const;
        uint32_t Count() const;
        const char* GetReason(uint32_t position);
        virtual ~Sema();
    };

    class ScopedSemaLock
    {
    private:
        bool bStatus;
        Sema* sLock;
    public:
        ScopedSemaLock();
        ScopedSemaLock(Sema* lock, const char* reason = nullptr, MicrosecondTime timeout = kThreadWaitForever);
        void AcquireLock(Sema* lock, const char* reason = nullptr, MicrosecondTime timeout = kThreadWaitForever);
        bool GetStatus() const;
        ~ScopedSemaLock();
    };
}

#endif