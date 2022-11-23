#pragma once
#include "..\external\rapidJSON\document.h"

class DataLoader
{
public:
	DataLoader(const char* aFilename);

	template<class T> T Read(const char* key) const;
private:
	rapidjson::Document mDocument;

};

template<class T>
inline T DataLoader::Read(const char* key) const
{
	auto node = mDocument.FindMember(key);
	DL_ASSERT(node != mDocument.MemberEnd() && "Key not found");
	return node->value.Get<T>();
}
