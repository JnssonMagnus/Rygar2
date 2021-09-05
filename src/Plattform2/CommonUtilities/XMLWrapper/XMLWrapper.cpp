#include "stdafx.h"
#include "XMLWrapper.h"
#include "XMLWrapperNode.h"
#include "tinyxml2/tinyxml2.h"
#include <assert.h>

XMLWrapper::XMLWrapper()
{
	myDocument = nullptr;
	myCurrentElement = nullptr;
}

XMLWrapper::~XMLWrapper()
{
	if (myDocument != nullptr)
	{
		CloseDocument();
	}
}

void XMLWrapper::NewDocument()
{
	myDocument = new tinyxml2::XMLDocument();
}

void XMLWrapper::SaveDocument(const char* aFilename)
{
	assert(myDocument != nullptr && "No XMLdocument is open or created!");
	auto result = myDocument->SaveFile(aFilename);
	CheckError(result);
}

XMLWrapperNode* XMLWrapper::CreateNewNode(const char* aNodeName)
{
	assert(myDocument != nullptr && "No XMLdocument is open or created!");
	return new XMLWrapperNode(aNodeName, *myDocument);
}

void XMLWrapper::AddRootNode(XMLWrapperNode * aXMLWrapperNode)
{
	assert(myDocument != nullptr && "No XMLdocument is open or created!");
	assert(aXMLWrapperNode != nullptr && "WrapperNode can't be nullptr");
	myDocument->InsertFirstChild(aXMLWrapperNode->myXMLElement);
}

void XMLWrapper::LoadXMLDocument(const char* aFilename)
{
	assert(myDocument == nullptr && "A xml document is already open!");
	myDocument = new tinyxml2::XMLDocument();
	CheckError(myDocument->LoadFile(aFilename));

	myCurrentElement = myDocument->FirstChildElement();
}

void XMLWrapper::CloseDocument()
{
	assert(myDocument != nullptr && "Can't close xml document, none is open.");
	delete myDocument;
	myDocument = nullptr;
}

void XMLWrapper::CheckError(const tinyxml2::XMLError& aError) const
{
	assert(aError != tinyxml2::XMLError::XML_ERROR_FILE_NOT_FOUND && "XML file not found!");
	assert(aError != tinyxml2::XMLError::XML_CAN_NOT_CONVERT_TEXT && "XML Can not convert text!");
	assert(aError != tinyxml2::XMLError::XML_ERROR_ELEMENT_MISMATCH && "XML Element mismatch!");
	assert(aError != tinyxml2::XMLError::XML_ERROR_FILE_COULD_NOT_BE_OPENED && "XML File could not be opened!");
 	assert(aError == tinyxml2::XMLError::XML_SUCCESS && "Error in XML!");
}

std::string	XMLWrapper::GetCurrentElementName() const
{	
	CheckCommonErrors();
	return std::string(myCurrentElement->Name());
}

CU::GrowingArray<std::string> XMLWrapper::GetAsList(const char* aXMLDocument)
{
	CU::GrowingArray<std::string> list;
	XMLWrapper wrapper;
	wrapper.LoadXMLDocument(aXMLDocument);
	//wrapper.NextChildElement();
	FOR_EACH_XML_NODE(wrapper)
	{
		list.Add(wrapper.GetText());
	}
		
	return list;
}

void XMLWrapper::NextChildElement()
{
	CheckCommonErrors();
	myElementStack.push(myCurrentElement);
	myCurrentElement = myCurrentElement->FirstChildElement();
}

void XMLWrapper::ReturnToParentElement()
{
	assert(myElementStack.empty() == false && "Can't return to parent xml element, already at top!");
	myCurrentElement = myElementStack.top();
	myElementStack.pop();
}

void XMLWrapper::NextSiblingElement()
{
	CheckCommonErrors();
	myCurrentElement = myCurrentElement->NextSiblingElement();
}

void XMLWrapper::CheckCommonErrors() const
{
	assert(myDocument != nullptr && "XML Document not loaded!");
	assert(myCurrentElement != nullptr && "Current xml element is nullptr!");
}

int	XMLWrapper::GetIntAttribute(const char* aAttributeName) const
{
	CheckCommonErrors();
	int value;
	CheckError(myCurrentElement->QueryIntAttribute(aAttributeName, &value));
	return value;
}

float XMLWrapper::GetFloatAttribute(const char* aAttributeName) const
{
	CheckCommonErrors();
	float value;
	CheckError(myCurrentElement->QueryFloatAttribute(aAttributeName, &value));
	return value;
}

bool XMLWrapper::GetBoolAttribute(const char* aAttributeName) const
{
	CheckCommonErrors();
	bool value;
	CheckError(myCurrentElement->QueryBoolAttribute(aAttributeName, &value));
	return value;
}

char XMLWrapper::GetCharAttribute(const char* aAttributeName) const
{
	CheckCommonErrors();
	int value;
	CheckError(myCurrentElement->QueryIntAttribute(aAttributeName, &value));
	assert(value >= -128 && value <= 127 && "Char value out of scope!");
	return static_cast<char>(value);
}

std::string	XMLWrapper::GetStringAttribut(const char* aAttributeName) const
{
	CheckCommonErrors();
	const char* txt = myCurrentElement->Attribute(aAttributeName);
	assert(txt != nullptr && "String attribute not found!");
	return txt;
}

std::string XMLWrapper::GetText() const
{
	CheckCommonErrors();
	return myCurrentElement->GetText();
}

int	XMLWrapper::GetTextAsInt() const
{
	return atoi(myCurrentElement->GetText());
}

bool XMLWrapper::GetTextAsBool() const
{
	return strcmp(myCurrentElement->GetText(), "true") == 0;
}

char XMLWrapper::GetTextAsChar() const
{
	int value = GetTextAsInt();
	assert(value >= CHAR_MIN && value <= CHAR_MAX && "Char value is out of scope!");
	return static_cast<char>(value);
}

float XMLWrapper::GetTextAsFloat() const
{
	return static_cast<float>(atof(myCurrentElement->GetText()));
}


bool XMLWrapper::IsAtEnd() const
{
	return (myCurrentElement == nullptr);
}
