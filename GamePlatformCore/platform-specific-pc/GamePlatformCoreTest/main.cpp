#include "BBHeader.h"
#include "BBWebRequest.h"
#include "BBWebRequestThreaded.h"
#include "BBThread.h"
#include "BBMutex.h"

using namespace bb;

int main(int argc, char *argv[])
{        
    WebRequest *webreq1 = new WebRequest();

    FILE *file;
    long size;
    char * buffer;
    size_t result;

    file = fopen("c:\\_backup_\\ad.0.report", "rb");
    fseek(file, 0 , SEEK_END);
    size = ftell(file);
    rewind(file);

    buffer = (char*)malloc(sizeof(char)*size);
    if (buffer == NULL) {fputs("Memory error", stderr); exit (2);}

    result = fread(buffer, 1, size, file);
    if(result != size){fputs("Reading error", stderr); exit(3);}

    std::string _data(buffer);   // = "data={\"profileId\":\"22222222-2222-2222-2222-222222222222\",\"clientId\":\"33333333-3333-3333-3333-333333333333\",\"usage\":[{\"id\":\"7BFD78EB-A3AC-45C3-AB21-FFF5EBE9F41F\",\"pid\":1,\"timeOnScreen\":162.2949829101563}]}&h=1";
    _data.insert(0, "data=");

    printf(_data.c_str());

    fclose(file);
    free(buffer);
    
    int success = webreq1->Request(HTTP_POST, "rewards.blackboxinteractivelive.com", 80, "/api/v1/profile-ad-tracking/set/", _data);        
        
    printf("Completed request...");
    printf("HEADER %s", webreq1->mMessageHeader.c_str());
    printf("BODY %s", webreq1->GetMessageBodyString().c_str());
    




    //WebRequest *webreq2 = new WebRequest();

    //printf("\r\nSTARTING THREAD CREATION");

    //unsigned int i = 0;
    //for (i = 0;i < 10; i++)
    //{
    //    WebRequestThreaded *webthread1 = new WebRequestThreaded(webreq1);
    //    WebRequestThreaded *webthread2 = new WebRequestThreaded(webreq2);
    //}

    //printf("\r\nCOMPLETED THREAD CREATION...");

    //std::clock_t start;
    //double diff;

    //start = std::clock();
    //for ( int i = 0; i < 1000000; i++ )
    //{
    //    diff = ( std::clock() - start ) / (double)CLOCKS_PER_SEC;

    //    std::cout<<"printf: "<< diff <<'\n';
    //}
 
    //printf("Running request...");
    //http://www.blackboxinteractive.com/Members/ATVLite.ashx?pid=2&cid=9B4AA5CA-454E-40EC-B6A7-B2385F1522DE&ca=2&pkg=bb&profileIndex=9B4AA5CA-454E-40EC-B6A7-B2385F1522DE&udid=9B4AA5CA-454E-40EC-B6A7-B2385F1522DE

    //webreq1->Request(HTTP_GET, "www.blackboxinteractive.com", 80, "/Members/ATVLite.ashx?pid=2&cid=9B4AA5CA-454E-40EC-B6A7-B2385F1522DE&ca=2&pkg=bb&profileIndex=9B4AA5CA-454E-40EC-B6A7-B2385F1522DE&udid=9B4AA5CA-454E-40EC-B6A7-B2385F1522DE", "");
    //webreq1->Request(HTTPS_GET, "live.2xlgames.com", 443, "/", "");
    //webreq->Request(HTTPS_GET, "live.2xlgames.com", 443, "/", "");

    //printf("Completed request...");
    //printf("%s", webreq1->GetMessageBodyString().c_str());
   // printf(webreq1->mMessageHeader.c_str());
    //printf("%d", sizeof(webreq1->mMessageHeader.c_str()));

    //printf("tester");

    std::cin.get();

    return 0;
}