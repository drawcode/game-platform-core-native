#include "Mutex.h"

namespace GamePlatform {
	Mutex::Mutex()
	{
#ifdef _WIN32
		mMutex = ::CreateMutex(NULL, FALSE, NULL);
#else
		pthread_mutex_init(&mMutex, NULL);
#endif
	}

	Mutex::~Mutex()
	{
#ifdef _WIN32
		::CloseHandle(mMutex);
#else
		pthread_mutex_destroy(&mMutex);
#endif
	}

	void Mutex::Lock() const
	{
#ifdef _WIN32
		DWORD d = WaitForSingleObject(mMutex, INFINITE);
#else
		pthread_mutex_lock(&mMutex);
#endif
	}

	void Mutex::Unlock() const
	{
#ifdef _WIN32
		::ReleaseMutex(mMutex);
#else
		pthread_mutex_unlock(&mMutex);
#endif
	}
}