/*

Copyright (C) 2012 Ryan Christensen, drawk llc, drawlabs

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef FILEJSON_H
#define FILEJSON_H

#include "stdio.h"
#include <iostream>
#include <fstream>

#include "json.h"

// This file is a wrapper for json-cpp a recommended JSON reading/writing library
// for C++.
// http://jsoncpp.sourceforge.net/ + http://json.org
//
// SAMPLE
/*

// Configuration options
{
// Default encoding for text
"encoding" : "UTF-8",

// Plug-ins loaded at start-up
"plug-ins" : [
"python",
"c++",
"ruby"
],

// Tab indent size
"indent" : { "length" : 3, "use_space" = true }
}

// parsing the above snippet

Json::Value root;   // will contains the root value after parsing.
Json::Reader reader;
bool parsingSuccessful = reader.parse( config_doc, root );
if ( !parsingSuccessful )
{
// report to the user the failure and their locations in the document.
std::cout  << "Failed to parse configuration\n"
<< reader.getFormatedErrorMessages();
return;
}

// Get the value of the member of root named 'encoding', return 'UTF-8' if there is no
// such member.
std::string encoding = root.get("encoding", "UTF-8" ).asString();
// Get the value of the member of root named 'encoding', return a 'null' value if
// there is no such member.
const Json::Value plugins = root["plug-ins"];
for ( int index = 0; index < plugins.size(); ++index )  // Iterates over the sequence elements.
loadPlugIn( plugins[index].asString() );

setIndentLength( root["indent"].get("length", 3).asInt() );
setIndentUseSpace( root["indent"].get("use_space", true).asBool() );

// ...
// At application shutdown to make the new configuration document:
// Since Json::Value has implicit constructor for all value types, it is not
// necessary to explicitly construct the Json::Value object:
root["encoding"] = getCurrentEncoding();
root["indent"]["length"] = getCurrentIndentLength();
root["indent"]["use_space"] = getCurrentIndentUseSpace();

Json::StyledWriter writer;
// Make a new JSON document for the configuration. Preserve original comments.
std::string outputConfig = writer.write( root );

// You can also use streams.  This will put the contents of any JSON
// stream at a particular sub-value, if you'd like.
std::cin >> root["subtree"];

// And you can write to a stream, using the StyledWriter automatically.
std::cout << root;

*/

using namespace std;

namespace GamePlatform {
	struct JsonValue{
		Json::Value mJsonValue;
		char* mpFilename;
	};

	class FileJson
	{
	public:
		JsonValue mJsonData;
		std::string mJsonString;

	public:

		FileJson();
		virtual ~FileJson();

		static bool FileExists(const char *fileName);

		bool OpenFile(const char *fileName);

		bool WriteFile(const char *fileName = NULL);

		inline char *GetFileName(void)
		{
			return mJsonData.mpFilename;
		}

		static bool IsStringValidJson(const string &data);
		static Json::Value GetJsonDataFromString(const string &data);
		static string GetStylizedJsonString(Json::Value data);

		static bool IsKeyNull(Json::Value &jsonValue, const char *key);
		static bool IsKeyInt(Json::Value &jsonValue, const char *key);
		static bool IsKeyUInt(Json::Value &jsonValue, const char *key);
		static bool IsKeyBool(Json::Value &jsonValue, const char *key);
		static bool IsKeyIntegral(Json::Value &jsonValue, const char *key);
		static bool IsKeyDouble(Json::Value &jsonValue, const char *key);
		static bool IsKeyNumeric(Json::Value &jsonValue, const char *key);
		static bool IsKeyString(Json::Value &jsonValue, const char *key);
		static bool IsKeyArray(Json::Value &jsonValue, const char *key);
		static bool IsKeyObject(Json::Value &jsonValue, const char *key);

		static string GetKeyAsString(Json::Value &jsonValue, const char *key, const string &defaultValue);
		static char *GetKeyAsCString(Json::Value &jsonValue, const char *key, char *defaultValue);
		static int GetKeyAsInt(Json::Value &jsonValue, const char *key, int defaultValue);

		static long long GetKeyAsLongLong(Json::Value &jsonValue, const char *key, long long defaultValue);
		static unsigned int GetKeyAsUInt(Json::Value &jsonValue, const char *key, unsigned int defaultValue);
		static bool GetKeyAsBool(Json::Value &jsonValue, const char *key, bool defaultValue);
		static double GetKeyAsDouble(Json::Value &jsonValue, const char *key, double defaultValue);
		static float GetKeyAsFloat(Json::Value &jsonValue, const char *key, float defaultValue);
		static Json::Value GetKeyAsJsonArray(Json::Value &jsonValue, const char *key);
		static Json::Value GetKeyAsJsonObject(Json::Value &jsonValue, const char *key);

	private:
	};
}

#endif
