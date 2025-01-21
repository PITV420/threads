//
//  message.hpp
//  threads
//
//  Created by Piotr Cieślik on 17/12/24.
//

#ifndef message_h
#define message_h

#include <stdint.h>
#include <stdlib.h>

#include "threadPtr.hpp"
#include "threadsDefs.hpp"
namespace Threads
{
    class Message
	{
	private:
		int iMessageCode;
		const char *iName;

	public:
		explicit Message(int messageCode, const char *messageName = nullptr);
		virtual ~Message();	
		virtual int MessageReceived();
		virtual void MessageCompleted(bool received);
		inline int GetMessageCode() const;
		inline const char* GetName() const;
		virtual bool IsExceptionMessage() const;
	};

	class QuitMessage : public Message
	{
	public:
		QuitMessage();
		virtual longInt MessageReceived();
	};

	extern QuitMessage kThreadExitMessage;
	const longInt kThreadTimeoutCode = -1;
	const longInt kExitMessageCode = -2;
	extern Message kThreadTimeoutMessage;
	extern Message kThreadExitMessageNoThrow;

	typedef enum
	{
		kMessageStatusDone = 0,
		kMessageStatusPending,
		kMessageStatusInProcess,
	} MessageStatus_t;

	class MessageTag
	{
	private:
		ThreadPtr iOwner;
		extraLongInt iMessageNumer;
		MessageTag(ThreadPtr owner, extraLongInt messageNumber);
	public:
		MessageTag();
		MessageTag(const MessageTag& rhs);
		MessageTag& operator=(const MessageTag& rhs);
		~MessageTag();
		MessageStatus_t Status();
		MessageStatus_t WaitUntilDone(MicrosecondTime waitTime = kThreadWaitForever);
		bool AdvancePendingMessage();
		bool DeletePendingMessage();
		inline bool operator == (const MessageTag& rhs) const;
		inline bool operator != (const MessageTag& rhs) const;
	};

	extern const MessageTag kNullMessageTag;
}

#endif