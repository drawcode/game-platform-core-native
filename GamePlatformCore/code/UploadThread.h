/*
 
 Copyright (C) 2012 Ryan Christensen, drawk llc, drawlabs
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _UploadThread_h_
#define _UploadThread_h_

#include "Thread.h"

#include "Enum.h"

#include <vector>

namespace GamePlatform
{

	class UploadThread :
		public Thread
	{
	public:

		UploadThread(const std::string& serverHost, unsigned short serverPort,
			HttpRequestType serverRequestType, const std::string& serverRequestPath,
			const std::string& searchDirectory, const std::string& searchExtension);

		void Run();

	protected:
		void uploadFile(const std::string& fileName);

		std::string mServerHost;
		unsigned short mServerPort;
		HttpRequestType mServerRequestType;
		std::string mServerRequestPath;
		std::string mSearchDirectory;
		std::string mSearchExtension;
	};
	typedef std::vector<UploadThread*> UploadThreadVec;
}

#endif
