//
//  threadSafe.hpp
//  threads
//
//  Created by Piotr Cieślik on 17/12/24.
//

#ifndef threadSafe_h
#define threadSafe_h

#include "threadsDefs.hpp"

namespace Threads
{
    class LockMechanism
    {
    private:
        native_mutex_t nNativeMutex;
    public:
        LockMechanism();
        void Lock();
        void Unlock();
        ~LockMechanism();

        class Guard
        {
        private:
            LockMechanism* pLockMechanism;
        public:
            Guard(LockMechanism* pLockMech);
            ~Guard();
        };
    };

    template<typename TYPE> class ThreadSafe
    {
    private:
        TYPE tValue;
        LockMechanism lLock;
    public:
        ThreadSafe();
        ThreadSafe(TYPE tValue);
        ThreadSafe&	operator=(const THING &value);
        operator TYPE() const;
        TYPE operator++(int);
        TYPE operator--(int);
        TYPE operator++();
        TYPE operator--();
        void operator+=(TYPE rhs);
        void operator-=(TYPE rhs);
        bool CompAndExch(TYPE tOld, TYPE tNew);
    };

    typedef class ThreadSafe<short> ThreadSafeInt16;
    
}

#endif