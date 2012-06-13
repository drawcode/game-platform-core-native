#include "WebRequest.h"

// requires openssl http://www.openssl.org/source/
#include <openssl/crypto.h> 
#include <openssl/x509.h> 
#include <openssl/pem.h> 
#include <openssl/ssl.h> 
#include <openssl/err.h> 

namespace GamePlatform
{

WebRequest::WebRequest(void)
{
    mReadSize = 1024;
    mError = 0;
}

WebRequest::~WebRequest(void)
{ 
}

void WebRequest::CloseSocket(int s)
{
#ifdef WIN32
	closesocket(s);
#else
	close(s);
#endif
}

std::string WebRequest::GetMessageBodyString()
{
    std::string messageBody(mMessageBody.begin(), mMessageBody.end());
    return messageBody;
}

std::string WebRequest::GetHeader(std::string header_name)
{
    std::string header_value = "";
    std::string header_value_parse = "";
    size_t pos = mMessageHeader.find(header_name);
    // get start
    if(pos!=std::string::npos)
    {
        header_value = mMessageHeader.substr(pos);
    }

    // get end line
    pos = header_value.find("\n");
    if(pos!=std::string::npos)
    {
        header_value = header_value.substr(0, pos);
    }

    // parse out the actual value
    pos = header_value.find(":");
    if(pos!=std::string::npos)
    {
        header_value = header_value.substr(pos + 1, header_value.length());
    }

    // trim
    pos = header_value.find(" ");
    if(pos!=std::string::npos)
    {
        header_value = header_value.substr(pos + 1, header_value.length());
    }
       
    return header_value;
}


int WebRequest::Request
(
    int request_type
    , std::string url_host
    , int url_port
    , std::string url_path
    , std::string data
)
{
	bool secure = false;
	
    mMessageHeader = "";
	mMessageBody.clear();
    // temp fix for POST recognition
    data = "_start_=1&" + data + "&_end_=1";
    
    mReadSize = 1024;
    mError = 0;
	
	if(request_type == HTTPS_GET
	   || request_type == HTTPS_POST
	   || request_type == HTTPS_PUT
	   || request_type == HTTPS_DELETE)
	{
		secure = true;		
	}

    #ifdef WIN32
    WSADATA wsa;
	// startup winsock
    mError = WSAStartup(MAKEWORD(2,0),&wsa);
	if(mError)
	{
	  printf("Error in Startup = %d\n", mError);
      return -1;
	}
    #endif

	// socket 
	int socket = 0;

    // struct for socket
	struct sockaddr_in host_addr = {0};

	// information about host
	struct hostent *host = {0};

	// request of client
    std::string request;
    
	// SSL context
	SSL_CTX *sslContext = NULL;

	// SSL socket
	SSL *sslSocket = NULL;

	// get IP from name host
	host = gethostbyname(url_host.c_str());

	if (host == NULL) 
	{
	  printf("Unknown Host %s\n", url_host.c_str());
	  return -1;
	}

	// create socket TCP
	socket = ::socket(PF_INET, SOCK_STREAM, 0);

	if (socket < 0) 
	{
	  printf("Socket Error\n");
	  return -1;
	}

	// create host struct
	host_addr.sin_family = AF_INET;
	// set IP addres
	host_addr.sin_addr = *((struct in_addr *)host->h_addr);
	// set HTTP port
	host_addr.sin_port = htons(url_port);

    // connect
    mError = connect(socket, (struct sockaddr *)&host_addr, sizeof(host_addr));
	
	if (mError == -1) 
	{
	  CloseSocket(socket);
	  printf("Connection Error\n");
	  return -1;
	}

    if(secure)
    {
        // init OpenSSL
	    SSL_load_error_strings();
	    SSL_library_init();

	    // create context 
	    sslContext = SSL_CTX_new(SSLv23_client_method());

	    //create ssl socket
	    sslSocket = SSL_new(sslContext);
	    if(!sslSocket) 
	    {
	      CloseSocket(socket);
	      printf("SSL creation error\n");
	      return -1;
	    }

        // join sslSocket and socket
	    SSL_set_fd(sslSocket, socket);

	    // conect sslSocket
	    mError = SSL_connect(sslSocket);

	    if(!mError) 
	    {
	      CloseSocket(socket);
	      printf("SSL connect error = %d\n", mError);
	      mError = SSL_get_error(sslSocket, mError);
	      printf("SSL error: %d\n", mError);
          //std::cin.get();
	      return -1;
	    }
    }

    if(request_type == HTTP_GET || request_type == HTTPS_GET)
    {
	    //create get request
        request = "GET " + url_path + " HTTP/1.0\nHost: " + url_host + " \r\n\r\n";	  
    }
    else if(request_type == HTTP_POST || request_type == HTTPS_POST)
    {
	    //create get request
	    request = "POST " + url_path + " HTTP/1.0\nHost: " + url_host + "\nContent-Length: " + to_string(data.length()) + "\nContent-Type: application/x-www-form-urlencoded\n" + "\r\n\r\n" + data + "\r\n";	  
    }
    // TODO add DELETE and PUT
    // send data to server

    if(secure)
    {
        mError = SSL_write(sslSocket, request.c_str(), strlen(request.c_str()));
    }
    else
    {
        mError = send(socket, request.c_str(), strlen(request.c_str()), 0);
    }

	

    // read in header and body

    char bufferHeader[1];
    int readHeader;
    int lineLength;
    bool loop = true;
    bool bHeader = false;

    // header
    
    mMessageHeader = "";

    while(loop) {
        if(secure)
            readHeader = SSL_read(sslSocket, bufferHeader, 1);
        else
            readHeader = recv(socket, bufferHeader, 1, 0);
        if(readHeader < 0) loop = false;
        if(bufferHeader[0]=='\n') {
           if(lineLength == 0) loop = false;

           lineLength = 0;
           if(mMessageHeader.find("200") != std::string::npos)
               bHeader = true;

        }
        else if(bufferHeader[0]!='\r') lineLength++;

        mMessageHeader += bufferHeader[0];
    }

    // body

    mMessageBody.clear();

    if(bHeader) {
        unsigned char bufferBody[1024];
        if(secure)
        {
            while((readHeader = SSL_read(sslSocket, bufferBody, sizeof(bufferBody))) > 0)  
            {
				mMessageBody.insert(mMessageBody.end(), bufferBody, bufferBody + readHeader);
            }
        }
        else
        {
            while((readHeader = recv(socket, (char*)bufferBody, sizeof(bufferBody), 0)) > 0)  
            {
				mMessageBody.insert(mMessageBody.end(), bufferBody, bufferBody + readHeader);
            }
        }
    }

    if(secure)
    {
        switch(SSL_get_error( sslSocket, mReadSize ))
        {
	        case SSL_ERROR_ZERO_RETURN: printf( "\n\nSSL::ZERO\n\n" );  break;
            case SSL_ERROR_NONE:        printf( "\n\nSSL::No Error\n\n" );	break;
            case SSL_ERROR_SSL:         printf( "\n\nSSL::SSL ERROR\n\n" ); break;
        }
    }

    #if WIN32
 	    Sleep(1);   
    #else
 	    sleep(1); 
    #endif

    if(secure)
    {
	    //close SSLsocket
        SSL_shutdown(sslSocket);
	    //free memory
        SSL_free(sslSocket);
	    // free context
        SSL_CTX_free(sslContext);
    }

    //close scoket
    CloseSocket(socket);

    return 0;
}

}
