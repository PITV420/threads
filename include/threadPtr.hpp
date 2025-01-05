//
//  threadPtr.hpp
//  threads
//
//  Created by Piotr Cieślik on 17/12/24.
//

#ifndef threadPtr_h
#define threadPtr_h

#include "message.hpp"
#include "threadsDefs.hpp"

namespace Threads
{
    typedef bool (*MessageFilterRtn)(const Message *msg);

    const int iNormalPriority = 0;
    const int iIdlePriority = 999;
	const int iExtraLowPriority = 1000;
	const int iLowPriority = 1001;
	const int iRegularPriority = 1002;
	const int iHighPriority = 1003;
	const int iExtraHighPriority = 1004;

    class MessageQueue
    {
        virtual int Count() = 0;
		virtual int Size() = 0;
		virtual bool MessageIsInQueue(int64_t messageNumber) = 0;
		virtual bool Insert(Message* msg, bool sendToAllThreadsFlag, int64_t messageNumber) = 0;
		virtual int32_t RemoveNext(Message** msg, int64_t* messageNumber, bool* sendToAllThreadsFlag, Message** msg2, int64_t* messageNumber2, bool* sendToAllThreadsFlag2, int64_t waitTime, int nativeObjectCount, ThreadHandle_t *objectList, MessageFilterRtn filter) = 0;
		virtual void ClearSendToAllMode() = 0;
		virtual bool AllowsMultipleReaders() const;
		virtual bool AllowsMultipleWriters() const;
		virtual void Flush();
		virtual ~MessageQueue();
    };

    class MessageQueueFactory
    {
	public:
		virtual MessageQueue* NewMessageQueue(int messageQueueSize);
		virtual ~MessageQueueFactory();
    };

    class CreateOptions
    {
    private:
        CreateOptions& operator=(const CreateOptions&);
    public:
		int iMessageQueueSize;
		int iThreadBasePriority;
		bool iNeverVCopyThreadBody;
		const char* iGroupName;
		MessageQueueFactory* iMessageQueueFactory;
    };

	const uint16_t kDefaultProcessorGroup = (uint16_t)-1;

	class CreateOptionsEx : public CreateOptions
	{
	private:
		CreateOptionsEx& operator=(const CreateOptionsEx&);
	public:
		uint16_t iProcessorGroup;

		CreateOptionsEx();
		CreateOptionsEx(const CreateOptionsEx& copy);

		virtual ~CreateOptionsEx();
		virtual CreateOptions* VCopy() const;
	};

	extern const CreateOptionsEx kThreadDefaultOptionsEx;

	class Thread
	{
	protected:
		Thread();
	public:
		virtual ~Thread() noexcept(false);
		
		virtual const char *GetName() const;
		virtual int GetThreadCount() const;
		virtual void* GetNativeThreadHandleAndId(native_thread_handle_t *returnedId = NULL, int threadNumber = 0);
		virtual MessageQueue* GetMessageQueue() const;
		virtual void SetName(const char *newName);
		friend class ThreadPtr;
	};

	class ThreadPtr
	{
		static Thread sTheNullThread;
	private:
		Thread* iPointee;
	public:
		ThreadPtr( Thread* realPtr = NULL);
		ThreadPtr( const ThreadPtr& rhs);
		ThreadPtr & operator=( const ThreadPtr& rhs);
		bool operator ==( const ThreadPtr& rhs);
		bool operator !=( const ThreadPtr& rhs);
		~ThreadPtr();
		Thread*  operator ->() const;
		Thread&  operator *() const;
		bool IsNull() const;
	};
}

#endif