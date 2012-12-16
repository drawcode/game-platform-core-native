#include "GamePlatformHeader.h"
#include "WebRequest.h"
#include "WebRequestThreaded.h"
#include "Thread.h"
#include "Mutex.h"

using namespace GamePlatform;

void run_test_single_request() 
{
	WebRequest *webreq1 = new WebRequest();

	std::string _data = "data={\"profileId\":\"22222222-2222-2222-2222-222222222222\",\"clientId\":\"33333333-3333-3333-3333-333333333333\",\"usage\":[{\"id\":\"7BFD78EB-A3AC-45C3-AB21-FFF5EBE9F41F\",\"pid\":1,\"timeOnScreen\":162.2949829101563}]}&h=1";
	
	int success = webreq1->Request(HTTP_POST, "yourserver.com", 80, "/api/action/", _data);        
		
	printf("Completed request...");
	printf("HEADER %s", webreq1->mMessageHeader.c_str());
	printf("BODY %s", webreq1->GetMessageBodyString().c_str());
}

void run_test_multiple_request_threaded()
{
	WebRequest *webreq1 = new WebRequest();

	std::string _data = "data={\"profileId\":\"22222222-2222-2222-2222-222222222222\",\"clientId\":\"33333333-3333-3333-3333-333333333333\",\"usage\":[{\"id\":\"7BFD78EB-A3AC-45C3-AB21-FFF5EBE9F41F\",\"pid\":1,\"timeOnScreen\":162.2949829101563}]}&h=1";
	
	int success = webreq1->Request(HTTP_POST, "google.com", 80, "/api/action/", _data);        
		
	printf("Completed request...");
	printf("HEADER %s", webreq1->mMessageHeader.c_str());
	printf("BODY %s", webreq1->GetMessageBodyString().c_str());

	WebRequest *webreq2 = new WebRequest();

	printf("\r\nSTARTING THREAD CREATION");

	unsigned int i = 0;
	for (i = 0;i < 10; i++)
	{
	    WebRequestThreaded *webthread1 = new WebRequestThreaded(webreq1);
	    WebRequestThreaded *webthread2 = new WebRequestThreaded(webreq2);
	}

	printf("\r\nCOMPLETED THREAD CREATION...");

	printf("Running request...");
   
	webreq1->Request(HTTP_GET, "google.com", 80, "/api/action", "");
	webreq1->Request(HTTP_GET, "google.com", 80, "", "");
	webreq1->Request(HTTPS_GET, "google.com", 443, "/", "");
	webreq2->Request(HTTPS_GET, "google.com", 443, "/", "");

	//printf("Completed request...");
	//printf("%s", webreq1->GetMessageBodyString().c_str());
   // printf(webreq1->mMessageHeader.c_str());
	//printf("%d", sizeof(webreq1->mMessageHeader.c_str()));

	//printf("tester");

}

int main(int argc, char *argv[])
{        
	run_test_single_request();

	run_test_multiple_request_threaded();

	std::cin.get();

	return 0;
}



	/*


	std::clock_t start;
	double diff;

	start = std::clock();
	for ( int i = 0; i < 1000000; i++ )
	{
	    diff = ( std::clock() - start ) / (double)CLOCKS_PER_SEC;

	    std::cout<<"printf: "<< diff <<'\n';
	}



	FILE *file;
	long size;
	char * buffer;
	size_t result;

	file = fopen("c:\\_backup_\\ad.report", "rb");
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
	*/