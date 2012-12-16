#include "IMutex.h"
#include "Lock.h"

namespace GamePlatform {
	Lock::Lock(const IMutex& m) : mMutex(m)
	{
		mMutex.Lock();
	}

	Lock::~Lock()
	{
		mMutex.Unlock();
	}
}