/*

Copyright (C) 2012 Ryan Christensen, drawk llc, drawlabs

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef __THREAD_H
#define __THREAD_H

#include "GamePlatformHeader.h"

#ifndef _WIN32
#include <pthread.h>
#endif

namespace GamePlatform {
#ifdef _WIN32
	//typedef unsigned threadfunc_t;
	typedef LPTHREAD_START_ROUTINE threadfunc_t;
	typedef void * threadparam_t;
#define STDPREFIX __stdcall
#else
	typedef void * threadfunc_t;
	typedef void * threadparam_t;
#define STDPREFIX
#endif

	class Thread
	{
	public:
		Thread(bool release = true);
		virtual ~Thread();

		static threadfunc_t STDPREFIX StartThread(threadparam_t);

		void Start();
		virtual void Run() = 0;
#ifdef _WIN32
		HANDLE GetThread() { return mThread; }
		unsigned GetThreadId() { return mThreadId; }
#else
		pthread_t GetThread() { return mThread; }
#endif
		bool IsRunning();
		void SetRunning(bool x);
		bool IsReleased();
		void SetRelease(bool x);
		bool DeleteOnExit();
		void SetDeleteOnExit(bool x = true);
		bool IsDestructor();
	protected:
#ifdef _WIN32
		HANDLE mThread;
		unsigned mThreadId;
#else
		pthread_t mThread;
#endif
	private:
		Thread(const Thread& ) {}
		Thread& operator=(const Thread& ) { return *this; }
		bool mRunning;
		bool mRelease;
		bool mDeleteOnExit;
		bool mDestructor;
	};
}
#endif
