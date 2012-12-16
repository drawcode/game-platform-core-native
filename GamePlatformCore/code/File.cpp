#include "File.h"
namespace GamePlatform
{
	File::File(const char* filename)
		: file_(std::fopen(filename, "w+"))
	{
		if (!file_)
			throw std::runtime_error("file open failure");
	}

	File::~File(void)
	{
		if (std::fclose(file_)) // failed to flush latest changes?
		{
			// handle it
		}
	}

	void File::Write(char* str)
	{
		if (EOF == std::fputs(str, file_))
			throw std::runtime_error("file write failure");
	}

	void File::Write(const char* str)
	{
		if (EOF == std::fputs(str, file_))
			throw std::runtime_error("file write failure");
	}
}