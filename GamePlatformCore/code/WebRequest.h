/*
 
 Copyright (C) 2012 Ryan Christensen, drawk llc, drawlabs
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
About:
This class is to greatly simplify and facilitate connecting to web services
via http and https for c++ clients.
*/
#ifndef __WEBREQUEST_H_
#define __WEBREQUEST_H_

#include "Header.h"
#include "Enum.h"

#include <vector>

namespace GamePlatform
{

class WebRequest
{
public:
    
    int mReadSize;
    int mError;

    std::string mMessageHeader;
    std::vector<unsigned char> mMessageBody;
    std::string mErrorMsg;

public:
    WebRequest(void);
    virtual ~WebRequest(void);

    virtual std::string GetHeader(std::string header_name);

    virtual std::string GetMessageBodyString();

    virtual int Request
    (
        int request_type
        , std::string url_host
        , int url_port
        , std::string url_path
        , std::string data
    );
	
private:
	virtual void CloseSocket(int socket); // should not be called directly...
};

}

#endif
