#include "stdafx.h"
#include "DataLoader.h"
#include "..\external\rapidJSON\reader.h"

DataLoader::DataLoader(const char* aFilename)
{
	std::ifstream file(std::string(gDataPath) + aFilename);
	DL_ASSERT(file.is_open() == true && "Can't open data source file");

	std::string text((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
	mDocument.Parse(text.c_str());
	DL_ASSERT(mDocument.HasParseError() == false && "Error while reading data file.");
}
