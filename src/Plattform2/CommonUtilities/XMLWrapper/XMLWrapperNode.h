#pragma once

namespace tinyxml2
{
	class XMLElement;
	class XMLDocument;
}

class XMLWrapperNode
{
public:
	XMLWrapperNode(const char* aNodeName, tinyxml2::XMLDocument& aXMLDocument);
	~XMLWrapperNode();
	void						AddAttribute(const char* aAttributeName, const char* aText);
	void						AddAttribute(const char* aAttributeName, const double aValue);
	void						SetText(const char* aText);
	void						AddChildNode(XMLWrapperNode* aXMLWrapperNode);
	friend class XMLWrapper;

private:
	tinyxml2::XMLElement		*myXMLElement;
};

