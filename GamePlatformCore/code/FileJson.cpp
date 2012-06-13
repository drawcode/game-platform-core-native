#include "FileJson.h"

namespace GamePlatform {

//---------------------------------------------------------------------------
FileJson::FileJson()
{

}

//---------------------------------------------------------------------------
FileJson::~FileJson()
{      

}

//---------------------------------------------------------------------------
bool FileJson::IsStringValidJson(const string &data)
{
    Json::Value dataValue;
    Json::Reader reader;
    return reader.parse(data, dataValue);
}
    
//---------------------------------------------------------------------------
Json::Value FileJson::GetJsonDataFromString(const string &data)
{
    Json::Value dataValue;
    Json::Reader reader;
    bool parsedSuccessfully = reader.parse(data, dataValue);
    if(parsedSuccessfully)
    {
       return dataValue;
    }
    // returns a null json obj;
    return dataValue;
}    
    
//---------------------------------------------------------------------------
string FileJson::GetStylizedJsonString(Json::Value data)
{
	// Returns nice formatted and indented json string for better 
	// human readability.
    Json::StyledWriter writer;
    return writer.write(data);
}    

//---------------------------------------------------------------------------
// Opens a parameter block file for read access.
bool FileJson::FileExists(const char *fileName)
{
    std::ifstream file(fileName, std::ios::in);
    if(file) 
    {
        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
// Opens a parameter block file for read access.
bool FileJson::OpenFile(const char *fileName)
{
    // currently using std, may swap for XL but in the matter of speed...
    std::ifstream file(fileName, std::ios::in);
	if(file) 
    {

		file.seekg(0,std::ios::end);
		std::streampos fileLength = file.tellg();
		file.seekg(0,std::ios::beg);

		std::string fileData;
		fileData.resize(fileLength);
		file.read(&fileData[0],fileLength);

        Json::Reader reader;
        if(reader.parse(fileData, mJsonData.mJsonValue, false)) 
        {
            mJsonString = fileData;
        }

        return true;
    }
    
    return false;
}

//---------------------------------------------------------------------------
// Writes the current values to file
bool FileJson::WriteFile(const char *fileName)
{
    if(fileName)
    {
	    std::string tmpFileName = fileName;
	    std::ofstream stream(tmpFileName.c_str(), std::ios::out);
	    if(!stream)
		    return false;

	    stream << mJsonData.mJsonValue;

	    stream.close();

        return true;
    }
  
    return false;
}

//---------------------------------------------------------------------------
bool FileJson::IsKeyNull(Json::Value &jsonValue, const char *key)
{
    if(jsonValue[key].isNull())
    {
        return true;
    }
    return false;
}


//---------------------------------------------------------------------------
bool FileJson::IsKeyInt(Json::Value &jsonValue, const char *key)
{
    if(!IsKeyNull(jsonValue, key))
    {
        if(jsonValue[key].isInt())
        {
            return true;
        }
    }
    return false;
}

//---------------------------------------------------------------------------
bool FileJson::IsKeyUInt(Json::Value &jsonValue, const char *key)
{
    if(!jsonValue[key].isNull())
    {
        if(jsonValue[key].isInt())
        {
			// TODO temp type fix
			int val = jsonValue[key].asInt();
			if(val >=0)
			{
				return true;
			}
        }
    }
    return false;
}

//---------------------------------------------------------------------------
bool FileJson::IsKeyBool(Json::Value &jsonValue, const char *key)
{
    if(!IsKeyNull(jsonValue, key))
    {
        if(jsonValue[key].isBool())
        {
            return true;
        }
    }
    return false;
}

//---------------------------------------------------------------------------
bool FileJson::IsKeyIntegral(Json::Value &jsonValue, const char *key)
{
    if(!IsKeyNull(jsonValue, key))
    {
        if(jsonValue[key].isIntegral())
        {
            return true;
        }
    }
    return false;
}

//---------------------------------------------------------------------------
bool FileJson::IsKeyDouble(Json::Value &jsonValue, const char *key)
{
    if(!IsKeyNull(jsonValue, key))
    {
        if(jsonValue[key].isDouble())
        {
            return true;
        }
    }
    return false;
}

//---------------------------------------------------------------------------
bool FileJson::IsKeyNumeric(Json::Value &jsonValue, const char *key)
{
    if(!IsKeyNull(jsonValue, key))
    {
        if(jsonValue[key].isNumeric())
        {
            return true;
        }
    }
    return false;
}

//---------------------------------------------------------------------------
bool FileJson::IsKeyString(Json::Value &jsonValue, const char *key)
{
    if(!IsKeyNull(jsonValue, key))
    {
        if(jsonValue[key].isString())
        {
            return true;
        }
    }
    return false;
}

//---------------------------------------------------------------------------
bool FileJson::IsKeyArray(Json::Value &jsonValue, const char *key)
{
    if(!IsKeyNull(jsonValue, key))
    {
        if(jsonValue[key].isArray())
        {
            return true;
        }
    }
    return false;
}

//---------------------------------------------------------------------------
bool FileJson::IsKeyObject(Json::Value &jsonValue, const char *key)
{
    if(!IsKeyNull(jsonValue, key))
    {
        if(jsonValue[key].isObject())
        {
            return true;
        }
    }
    return false;
}

//---------------------------------------------------------------------------

string FileJson::GetKeyAsString(Json::Value &jsonValue, const char *key, const string &defaultValue)
{
    if(IsKeyString(jsonValue, key))
    {
        return jsonValue[key].asString();
    }
    else
    {
        return defaultValue;
    }
}

//---------------------------------------------------------------------------
char *FileJson::GetKeyAsCString(Json::Value &jsonValue, const char *key, char *defaultValue)
{
    if(IsKeyString(jsonValue, key))
    {
        return (char *)jsonValue[key].asCString();
    }
    else
    {
        return defaultValue;
    }
}


//---------------------------------------------------------------------------
long long FileJson::GetKeyAsLongLong(Json::Value &jsonValue, const char *key, long long defaultValue)
{
    if(IsKeyNumeric(jsonValue, key))
    {
        return jsonValue[key].asInt64();
    }
    else
    {
        return defaultValue;
    }
}

//---------------------------------------------------------------------------
int FileJson::GetKeyAsInt(Json::Value &jsonValue, const char *key, int defaultValue)
{
    if(IsKeyInt(jsonValue, key))
    {
        return jsonValue[key].asInt();
    }
    else
    {
        return defaultValue;
    }
}

//---------------------------------------------------------------------------
unsigned int FileJson::GetKeyAsUInt(Json::Value &jsonValue, const char *key, unsigned int defaultValue)
{
    if(IsKeyUInt(jsonValue, key))
    {
        return jsonValue[key].asUInt();
    }
    else
    {
        return defaultValue;
    }
}

//---------------------------------------------------------------------------
bool FileJson::GetKeyAsBool(Json::Value &jsonValue, const char *key, bool defaultValue)
{
    if(IsKeyBool(jsonValue, key))
    {
        return jsonValue[key].asBool();
    }
    else
    {
        return defaultValue;
    }
}

//---------------------------------------------------------------------------
double FileJson::GetKeyAsDouble(Json::Value &jsonValue, const char *key, double defaultValue)
{
    if(IsKeyDouble(jsonValue, key))
    {
        return jsonValue[key].asDouble();
    }
    else
    {
        return defaultValue;
    }
}

//---------------------------------------------------------------------------
float FileJson::GetKeyAsFloat(Json::Value &jsonValue, const char *key, float defaultValue)
{
    if(IsKeyDouble(jsonValue, key))
    {
        return (float)jsonValue[key].asDouble();
    }
    else
    {
        return defaultValue;
    }
}

//---------------------------------------------------------------------------
Json::Value FileJson::GetKeyAsJsonArray(Json::Value &jsonValue, const char *key)
{
    if(IsKeyArray(jsonValue, key))
    {
        return jsonValue;
    }
    else
    {
        Json::Value returnVal; // empty
        return returnVal;
    }
}

//---------------------------------------------------------------------------
Json::Value FileJson::GetKeyAsJsonObject(Json::Value &jsonValue, const char *key)
{
    if(IsKeyObject(jsonValue, key))
    {
        return jsonValue;
    }
    else
    {
        Json::Value returnVal; // empty
        return returnVal;
    }
}
}

