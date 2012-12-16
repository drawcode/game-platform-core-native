/*

Copyright (C) 2012 Ryan Christensen, drawk llc, drawlabs

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef __GAME_PLATFORM_HEADER_H_
#define __GAME_PLATFORM_HEADER_H_

#pragma warning (disable :4996)

#include "Build.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <assert.h>
#include <stdexcept> // std::runtime_error
#include <sstream>
#include <errno.h>

#include <cstdio>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <time.h>

#ifdef WIN32
#include <tchar.h>
#endif

#ifdef LINUX
#include <netdb.h>
#endif

#ifdef MACOSX
#include <netdb.h>
#endif

#ifdef IPHONE
#include <netdb.h>
#endif

#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#endif

#define _DEBUG_PRINT(X)   /* X */

#define SEND_RQ(MSG) \
	/*cout<<send_str;*/ \
	send(sock,MSG,strlen(MSG),0);

#define SEND_RQ_SECURE(MSG) \
	/*cout<<send_str;*/ \
	SSL_write(sslSocket,MSG,strlen(MSG));

template <class T>
inline std::string to_string(const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

#endif
