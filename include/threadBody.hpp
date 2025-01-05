//
//  threadBody.hpp
//  threads
//
//  Created by Piotr Cieślik on 17/12/24.
//

#ifndef threadBody_h
#define threadBody_h

#include "threadPtr.hpp"

namespace Threads
{
	class CreateOptions;

	class Body
	{
	private:
        CreateOptions iOptionMemory;
        Body& operator=(const Body&);
	protected:
		Body(const Body& copy);
	public:
		CreateOptions *iOptions;
		virtual void ThreadBody();
		virtual Body *VCopy() const;
		Body();
		explicit Body( const CreateOptions& options );
		virtual ~Body();
	};

	extern const Body kDefaultThreadBody;

	class CreateOptionsEx;

	class BodyEx : public Body
	{
	private:
        CreateOptionsEx iOptionMemoryEx;
        BodyEx& operator=(const BodyEx&);
	protected:
		BodyEx(const BodyEx& copy);
	public:
		CreateOptionsEx *iOptionsEx;
		virtual Body *VCopy() const;
		BodyEx();
		explicit BodyEx( const CreateOptionsEx& options );
		virtual ~BodyEx();
	};

	extern const BodyEx kDefaultThreadBodyEx;
}

#endif