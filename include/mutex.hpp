//
//  mutex.hpp
//  threads
//
//  Created by Piotr Cieślik on 17/12/24.
//

#ifndef mutex_h
#define mutex_h

#include "threadsDefs.hpp"

namespace Threads
{
    class MutexRep
	{
	private:
		const char* cName;
		bool bAlwaysWaitForever;
		uint32_t iLockCount;
		const char* cReason[16];
		native_thread_handle_t nOwner;
		native_mutex_t nPlatformMutex;
	public:
		MutexRep(const char* name, bool locksWaitsForever);
		void Reset(const char* name, bool lockWaitsForever);
		bool Lock(const char* reason, MicrosecondTime waitTime);
		ThreadErrorCode Unlock(const char* reason);
		bool IsLockByThisThread();
		~MutexRep();
	};


    class Mutex
    {
    private:
        MutexRep* iRep;
        Mutex(const Mutex&);
		Mutex& operator=(const Mutex&);
		
	public:
		explicit Mutex(const char *name = NULL,	bool lockWaitsForever = true);
		virtual ~Mutex();
		virtual bool Lock(const char* reason = NULL, MicrosecondTime waitTime = kThreadWaitForever);
		void Reset(const char *name, bool lockWaitsForever);

		ThreadErrorCode Unlock(const char *reason = NULL);
		bool IsLockedByThisThread();
		void SetCooperativeWaits(bool makeAboutToBlockCallsWhenWaiting);
    };

    class MutexTenure
	{
	private:
		Mutex &iMutex;
		const char* iReason;
		bool iReleased;
		bool iGotLock;

		MutexTenure(const MutexTenure&);
		MutexTenure& operator=(const MutexTenure&);

	public:
		explicit MutexTenure(Mutex &theMutex, const char* theReason = NULL);
		explicit MutexTenure(Mutex& theMutex, MicrosecondTime lockTimeout, const char* theReason = NULL);
		bool IsLocked();
		virtual void Release();
		virtual void Reclaim();
		virtual ~MutexTenure();
	};
	
	class GlobalMutexTenure : public MutexTenure
	{
	private:
		GlobalMutexTenure(const GlobalMutexTenure&);
		GlobalMutexTenure& operator=(const GlobalMutexTenure&);
	
	public:
		explicit GlobalMutexTenure(const char* theReason = NULL);
		virtual ~GlobalMutexTenure();
		static bool GlobalLock(const char *reason, MicrosecondTime waitTime);
		static ThreadErrorCode GlobalUnlock( const char *reason);
	};
}

#endif