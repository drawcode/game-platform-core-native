/*

Copyright (C) 2012 Ryan Christensen, drawk llc, drawlabs

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef FILESTREAM_H
#define FILESTREAM_H

#include "stdio.h"
#include <iostream>
#include <fstream>

namespace GamePlatform {
	struct FileStreamInfo
	{
		std::string mDataString;
		std::string mFileName;
	};

	class FileStream
	{
	public:

		FileStreamInfo mInfo;

	public:

		FileStream();
		virtual ~FileStream();

		static bool FileExists(const char *fileName);
		static bool WriteFileData(const char *fileName, const char* fileData);
		static const char* OpenFileData(const char *fileName);

		static bool WriteFileBinaryData(const char *fileName, const char* fileData);
		static const char* OpenFileBinaryData(const char *fileName);

		virtual bool OpenFile(const char *fileName);
		virtual bool WriteFile(const char *fileName, const char* fileData);
		virtual bool WriteFile(const char *fileName);

		virtual bool OpenFileBinary(const char *fileName);
		virtual bool WriteFileBinary(const char *fileName, const char* fileData);
		virtual bool WriteFileBinary(const char *fileName, std::string fileData);
		virtual bool WriteFileBinary(const char *fileName);
	};
}

#endif // FILESTREAM_H
