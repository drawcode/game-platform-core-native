#include "UploadThread.h"

#include "WebRequest.h"

#include "json.h"

#include <fstream>
#include "xdirent.h"

namespace GamePlatform
{
	UploadThread::UploadThread(const std::string& serverHost, unsigned short serverPort,
		HttpRequestType serverRequestType, const std::string& serverRequestPath,
		const std::string& searchDirectory, const std::string& searchExtension)
		: mServerHost(serverHost), mServerPort(serverPort),
		mServerRequestType(serverRequestType), mServerRequestPath(serverRequestPath),
		mSearchDirectory(searchDirectory), mSearchExtension(searchExtension)
	{
	}

	void UploadThread::uploadFile(const std::string& fileName)
	{
		std::ifstream file(fileName.c_str(), std::ios::in);
		if(file) {
			file.seekg(0,std::ios::end);
			std::streampos fileLength = file.tellg();
			file.seekg(0,std::ios::beg);

			std::string fileData;
			fileData.resize(fileLength);
			file.read(&fileData[0],fileLength);

			fileData.insert(0, "data=");

			GamePlatform::WebRequest request;
			request.Request(
				mServerRequestType,
				mServerHost,
				mServerPort,
				mServerRequestPath,
				fileData);

			// If there was a socket error exit the thread. Updates
			//	will try again the next time report data is committed
			if(request.mError < 0)
				return;

			if(!request.mMessageBody.empty()) {
				Json::Value resultValue;
				Json::Reader resultReader;
				if(resultReader.parse(request.GetMessageBodyString(), resultValue, false)) {
					Json::Value errorValue = resultValue["error"];
					if(errorValue.isInt() && errorValue.asInt() == 0) {
						// Guaranteed success delete the file
						unlink(fileName.c_str());
					}
				}
			}
		}
	}

	void UploadThread::Run()
	{
		DIR *dir = opendir(mSearchDirectory.c_str());

		if(dir) {
			dirent* entry;
			while((entry = readdir(dir)) != NULL) {
				std::string entryName = entry->d_name;
				std::string::size_type extPos = entryName.find_last_of('.');

				if(extPos != std::string::npos && entryName.substr(extPos+1) == mSearchExtension) {
					uploadFile(mSearchDirectory + "/" + entryName);
				}
			}
		}

		closedir(dir);
	}
}