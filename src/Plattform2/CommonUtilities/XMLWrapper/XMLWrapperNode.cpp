#include "stdafx.h"
#include "XMLWrapperNode.h"
#include "tinyxml2/tinyxml2.h"
#include <assert.h>

XMLWrapperNode::XMLWrapperNode(const char* aNodeName, tinyxml2::XMLDocument& aXMLDocument)
{
	myXMLElement = aXMLDocument.NewElement(aNodeName);
}

XMLWrapperNode::~XMLWrapperNode()
{
}

void XMLWrapperNode::AddAttribute(const char* aAttributeName, const char* aText)
{
	myXMLElement->SetAttribute(aAttributeName, aText);
}

void XMLWrapperNode::AddAttribute(const char* aAttributeName, const double aValue)
{
	myXMLElement->SetAttribute(aAttributeName, aValue);
}

void XMLWrapperNode::SetText(const char* aText)
{
	myXMLElement->SetText(aText);
}

void XMLWrapperNode::AddChildNode(XMLWrapperNode* aXMLWrapperNode)
{
	assert(aXMLWrapperNode != nullptr && "Node to add can't be nullptr!");
	myXMLElement->InsertEndChild(aXMLWrapperNode->myXMLElement);
}
