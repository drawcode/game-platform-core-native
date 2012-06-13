#include "Header.h"
#include "WebRequest.h"
#include "WebRequestThreaded.h"
#include "Thread.h"
#include "Mutex.h"

using namespace GamePlatform;

int main(int argc, char *argv[])
{        
    WebRequest *webreq1 = new WebRequest();
    WebRequest *webreq2 = new WebRequest();

    printf("\r\nSTARTING THREAD CREATION");

    unsigned int i = 0;
    for (i = 0;i < 10; i++)
    {
        WebRequestThreaded *webthread1 = new WebRequestThreaded(webreq1);
        WebRequestThreaded *webthread2 = new WebRequestThreaded(webreq2);
    }

    printf("\r\nCOMPLETED THREAD CREATION...");

    //std::clock_t start;
    //double diff;

    //start = std::clock();
    //for ( int i = 0; i < 1000000; i++ )
    //{
    //    //printf ( "iamthwee" );
    //    diff = ( std::clock() - start ) / (double)CLOCKS_PER_SEC;

    //    std::cout<<"printf: "<< diff <<'\n';
    //}
 
    //printf("Running request...");

    ////boxreq->Request(HTTPS_GET, "live.2xlgames.com", 443, "/", "");
    //webreq->Request(HTTPS_GET, "live.2xlgames.com", 443, "/", "");

    //printf("Completed request...");

    //printf(webreq->mMessageBody.c_str());

    //printf("tester");

    std::cin.get();

    return 0;
}