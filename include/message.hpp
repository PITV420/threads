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
		int32_t iMessageCode;
		const char *iName;

	public:
		explicit Message(int32_t messageCode, const char *messageName = nullptr);
		virtual ~Message();	
		virtual int32_t MessageReceived();
		virtual void MessageCompleted(bool received);
		inline int32_t GetMessageCode() const;
		inline const char* GetName() const;
		virtual bool IsExceptionMessage() const;
	};
}

#endif