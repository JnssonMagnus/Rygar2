#pragma once
#include "tinyxml2/tinyxml2.h"
#include <string>
#include <stack>
#include <string.h>
#include <GrowingArray.h>

#define FOR_EACH_XML_NODE(name) for (name.NextChildElement(); name.IsAtEnd() == false; name.NextSiblingElement())

class XMLWrapperNode;

class XMLWrapper
{
public:
							XMLWrapper();
							~XMLWrapper();
	void					NewDocument();
	void					SaveDocument(const char* aFilename);
	XMLWrapperNode*			CreateNewNode(const char* aNodeName);
	void					AddRootNode(XMLWrapperNode* aXMLWrapperNode);

	void					LoadXMLDocument(const char* aFilename);
	void					CloseDocument();
	void					NextChildElement();
	void					NextSiblingElement();
	void					ReturnToParentElement();
	bool					IsAtEnd() const;

	int						GetIntAttribute(const char* aAttributeName) const;
	float					GetFloatAttribute(const char* aAttributeName) const;
	std::string				GetStringAttribut(const char* aAttributeName) const;
	bool					GetBoolAttribute(const char* aAttributeName) const;
	char					GetCharAttribute(const char* aAttributeName) const;

	char					GetTextAsChar() const;
	float					GetTextAsFloat() const;
	bool					GetTextAsBool() const;
	int						GetTextAsInt() const;
	std::string				GetText() const;
	std::string				GetCurrentElementName() const;
	static CU::GrowingArray<std::string>
							GetAsList(const char* aXMLDocument);

private:
	tinyxml2::XMLDocument*	myDocument;
	tinyxml2::XMLElement*	myCurrentElement;
	void					CheckError(const tinyxml2::XMLError& aError) const;
	void					CheckCommonErrors() const;
	std::stack<tinyxml2::XMLElement*>
							myElementStack;
};

