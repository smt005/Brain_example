
#include "Help.h"
#include "FileManager.h"

#include <iostream>

bool help::loadJson(const std::string& fileName, Json::Value& value)
{
	std::string mystring = Engine::FileManager::readTextFile(fileName);

	if (mystring.empty()) {
		return false;
	}

	Json::CharReaderBuilder readerBuilder;
	Json::CharReader *reader = readerBuilder.newCharReader();
	std::string err;
	if (reader->parse(mystring.c_str(), mystring.c_str() + mystring.length(), &value, &err)) {
		return true;
	}

	return false;
}

bool help::saveJson(const std::string& fileName, const Json::Value& value, const std::string& indentation)
{
	const std::string valueString = stringFroJson(value, indentation);
	return Engine::FileManager::writeTextFile(fileName, valueString);
}

std::string help::stringFroJson(const Json::Value& value, const std::string& indentation)
{
	Json::StreamWriterBuilder writerBuilder;
	writerBuilder["indentation"] = indentation; // If you want whitespace-less output
	return Json::writeString(writerBuilder, value);
}
