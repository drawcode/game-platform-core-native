#include "FileStream.h"

namespace GamePlatform {
	//---------------------------------------------------------------------------
	FileStream::FileStream()
	{
	}

	//---------------------------------------------------------------------------
	FileStream::~FileStream()
	{
	}

	//---------------------------------------------------------------------------
	// static
	bool FileStream::FileExists(const char *fileName)
	{
		std::ifstream file(fileName, std::ios::in);

		if(file.is_open())
		{
			return true;
		}

		return false;
	}

	//---------------------------------------------------------------------------
	// static
	const char* FileStream::OpenFileData(const char *fileName)
	{
		std::ifstream file(fileName, std::ios::in);

		if(file.is_open())
		{
			file.seekg(0,std::ios::end);
			std::streampos fileLength = file.tellg();
			file.seekg(0,std::ios::beg);

			std::string fileData;
			fileData.resize(fileLength);
			file.read(&fileData[0],fileLength);
			file.close();

			return fileData.c_str();
		}

		return NULL;
	}

	//---------------------------------------------------------------------------
	// static
	bool FileStream::WriteFileData(const char *fileName, const char* fileData)
	{
		if(fileName)
		{
			std::ofstream stream(fileName, std::ios::out);

			if(!stream)
				return false;

			stream << fileData;

			stream.flush();
			stream.close();

			return true;
		}

		return false;
	}

	//---------------------------------------------------------------------------
	// static
	const char* FileStream::OpenFileBinaryData(const char *fileName)
	{
		std::ifstream file(fileName, std::ios::in|std::ios::binary);

		if(file.is_open())
		{
			file.seekg(0,std::ios::end);
			std::streampos fileLength = file.tellg();
			file.seekg(0,std::ios::beg);

			std::string fileData;
			fileData.resize(fileLength);
			file.read(&fileData[0],fileLength);
			file.close();

			return fileData.c_str();
		}

		return NULL;
	}

	//---------------------------------------------------------------------------
	// static
	bool FileStream::WriteFileBinaryData(const char *fileName, const char* fileData)
	{
		if(fileName)
		{
			std::ofstream stream(fileName, std::ios::out|std::ios::binary);

			if(!stream)
				return false;

			stream << fileData;

			stream.close();

			return true;
		}

		return false;
	}

	//---------------------------------------------------------------------------
	bool FileStream::OpenFile(const char *fileName)
	{
		std::ifstream file(fileName, std::ios::in);

		if(file.is_open())
		{
			file.seekg(0,std::ios::end);
			std::streampos fileLength = file.tellg();
			file.seekg(0,std::ios::beg);

			mInfo.mFileName = (char*)fileName;

			std::string fileData;
			fileData.resize(fileLength);
			file.read(&fileData[0],fileLength);
			file.close();

			mInfo.mDataString = fileData;

			return true;
		}

		return false;
	}

	//---------------------------------------------------------------------------
	bool FileStream::OpenFileBinary(const char *fileName)
	{
		std::ifstream file(fileName, std::ios::in|std::ios::binary);

		if(file.is_open())
		{
			file.seekg(0,std::ios::end);
			std::streampos fileLength = file.tellg();
			file.seekg(0,std::ios::beg);

			mInfo.mFileName = (char*)fileName;

			std::string fileData;
			fileData.resize(fileLength);
			file.read(&fileData[0],fileLength);
			file.close();

			mInfo.mDataString = fileData;

			return true;
		}

		return false;
	}

	//---------------------------------------------------------------------------
	bool FileStream::WriteFile(const char *fileName, const char* fileData)
	{
		if(fileName)
		{
			mInfo.mFileName = (char*)fileName;

			std::ofstream stream(fileName, std::ios::out);

			if(!stream)
				return false;

			mInfo.mFileName = (char*)fileName;

			stream << fileData;

			stream.flush();

			stream.close();

			return true;
		}

		return false;
	}

	//---------------------------------------------------------------------------
	bool FileStream::WriteFileBinary(const char *fileName, const char* fileData)
	{
		if(fileName)
		{
			std::ofstream stream(fileName, std::ios::out|std::ios::binary);

			if(!stream)
				return false;

			mInfo.mDataString = (char*)fileData;
			mInfo.mFileName = (char*)fileName;

			stream.write(mInfo.mDataString.c_str(), mInfo.mDataString.size());

			stream.flush();

			stream.close();

			return true;
		}

		return false;
	}

	//---------------------------------------------------------------------------
	bool FileStream::WriteFileBinary(const char *fileName, std::string fileData)
	{
		if(fileName)
		{
			std::ofstream stream(fileName, std::ios::out|std::ios::binary);

			if(!stream)
				return false;

			mInfo.mDataString = fileData;
			mInfo.mFileName = (char*)fileName;

			stream.write(mInfo.mDataString.c_str(), mInfo.mDataString.size());

			stream.flush();

			stream.close();

			return true;
		}

		return false;
	}

	//---------------------------------------------------------------------------
	bool FileStream::WriteFile(const char *fileName)
	{
		if(fileName)
		{
			std::ofstream stream(fileName, std::ios::out);

			if(!stream)
				return false;

			stream << mInfo.mDataString.c_str();

			mInfo.mFileName = (char*)fileName;

			stream.flush();

			stream.close();

			return true;
		}

		return false;
	}

	//---------------------------------------------------------------------------
	bool FileStream::WriteFileBinary(const char *fileName)
	{
		if(fileName)
		{
			mInfo.mFileName = (char*)fileName;

			std::ofstream stream(fileName, std::ios::out|std::ios::binary);

			if(!stream)
				return false;

			mInfo.mFileName = (char*)fileName;

			stream.write(mInfo.mDataString.c_str(), mInfo.mDataString.size());

			stream.flush();

			stream.close();

			return true;
		}

		return false;
	}
}