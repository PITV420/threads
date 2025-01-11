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
}

#endif