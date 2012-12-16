#include "GamePlatformHeader.h"
#include "ThreadUtil.h"

namespace GamePlatform
{
	ThreadUtil::ThreadUtil(void)
	{
	}

	ThreadUtil::~ThreadUtil(void)
	{
	}

	void ThreadUtil::WaitForSeconds(int seconds)
	{
#ifdef WIN32
		Sleep(1000 * seconds);
#else
		sleep(1 * seconds);
#endif
	}
}