#include "GamePlatformHeader.h"
#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#endif
#include "Thread.h"

namespace GamePlatform {
	Thread::Thread(bool release)
		:mThread(0)
		,mRunning(false)
		,mRelease(release)
		,mDeleteOnExit(false)
		,mDestructor(false)
	{
	}

	void Thread::Start()
	{
#ifdef _WIN32
		mThread = ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&StartThread, this, 0, (LPDWORD)&mThreadId);
		//mThread = (HANDLE)_beginthreadex(NULL, 0, &StartThread, this, 0, &mThreadId);
		//mThread = (HANDLE)_beginthreadex(NULL, 0, &StartThread, this, 0, &mThreadId);
		//DWORD threadID;
		// ::CreateThread(0, 0, threadProc, _threadObj, 0, &mThreadId);
#else
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
		if (pthread_create(&mThread,&attr, StartThread,this) == -1)
		{
			perror("Thread: create failed");
			SetRunning(false);
		}
		//	pthread_attr_destroy(&attr);
#endif
	}

	Thread::~Thread()
	{
		mDestructor = true;
		if (mRunning)
		{
			SetRelease(true);
			SetRunning(false);
#ifdef _WIN32
			Sleep(1000);
#else
			sleep(1);
#endif
		}
#ifdef _WIN32
		if (mThread)
			::CloseHandle(mThread);
#endif
	}

	threadfunc_t STDPREFIX Thread::StartThread(threadparam_t param)
	{
		Thread *p = (Thread *)param;
		while (p -> mRunning && !p -> mRelease)
		{
#ifdef _WIN32
			Sleep(1000);
#else
			sleep(1);
#endif
		}
		if (!p -> mRunning)
		{
			p -> Run();
		}
		p -> SetRunning(false); // if return
		if (p -> DeleteOnExit() && !p -> IsDestructor())
		{
			delete p;
		}
#ifdef _WIN32
		_endthreadex(0);
#endif
		return (threadfunc_t)NULL;
	}

	bool Thread::IsRunning()
	{
		return mRunning;
	}

	void Thread::SetRunning(bool x)
	{
		mRunning = x;
	}

	bool Thread::IsReleased()
	{
		return mRelease;
	}

	void Thread::SetRelease(bool x)
	{
		mRelease = x;
	}

	bool Thread::DeleteOnExit()
	{
		return mDeleteOnExit;
	}

	void Thread::SetDeleteOnExit(bool x)
	{
		mDeleteOnExit = x;
	}

	bool Thread::IsDestructor()
	{
		return mDestructor;
	}
}