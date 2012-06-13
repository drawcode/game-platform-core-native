#include "Header.h"
#include "WebRequest.h"
#include "WebRequestThreaded.h"
#include "Thread.h"
#include "ThreadUtil.h"

// Sample file - to make a threaded class copy this 
// file and do your synchronous actions that need 
// to happen in a thread within the Run method.

namespace GamePlatform
{

WebRequestThreaded::WebRequestThreaded(WebRequest *p)
:Thread(false)
,mWebRequest(p)
{
	// Creator will release
}

WebRequestThreaded::~WebRequestThreaded()
{
    if (IsRunning())
	{
		SetRelease(true);
		SetRunning(false);
        ThreadUtil::WaitForSeconds(1);
	}
}

void WebRequestThreaded::Run()
{
    printf("\r\nrunning....%d", GetThread());

    //mWebRequest->Request(HTTPS_GET, "live.2xlgames.com", 443, "/", "");
    mWebRequest->Request(HTTPS_GET, "www.godhhaddy.com", 443, "/", ""); // shows a bad request to ensure it doesn't lock up the main thread or other threads.

    ThreadUtil::WaitForSeconds(rand() % 10);

    printf("\r\ncompleted running....%d", GetThread());

    //printf(mWebRequest->mMessageBody.c_str());

    //printf("tester");
}

}