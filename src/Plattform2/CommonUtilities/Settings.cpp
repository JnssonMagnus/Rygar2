#include "stdafx.h"
#include "Settings.h"
#include "../Systems/XmlWrapper/XmlWrapper/xmlwrapper.h"
#include "debugger/DebugLabbExempel/DL_Debug.h"
#include <postmaster/postmaster.h>
#include <postmaster/message.h>

Settings* Settings::myInstance = nullptr;

Settings::Settings()
{
	myMasterVolume = 1.f;
	myMusicVolume = 1.f;
	myScreenWidth = -1;
	myScreenHeight = -1;
	myFixedFramerate = 60;
	SetFlag(eSetting::ePhysics, true);
	SetFlag(eSetting::eSound, true);
}

void Settings::LoadSettings(const char* aFilename)
{
	XMLWrapper settingsLoader;
	settingsLoader.LoadXMLDocument(aFilename);
	settingsLoader.NextChildElement();

	for (; settingsLoader.IsAtEnd() == false; settingsLoader.NextSiblingElement())
	{
		if (settingsLoader.GetCurrentElementName() == "screensize")
		{
			myScreenWidth = settingsLoader.GetIntAttribute("width");
			myScreenHeight = settingsLoader.GetIntAttribute("height");
		}
		else if (settingsLoader.GetCurrentElementName() == "fullscreen")
		{
			myFlags[static_cast<int>(eSetting::eFullscreen)] = settingsLoader.GetTextAsBool();
		}
		else if (settingsLoader.GetCurrentElementName() == "title")
		{
			myWindowTitle = settingsLoader.GetText(); 
		}
		else if (settingsLoader.GetCurrentElementName() == "soundLibrary")
		{
			mySoundLibrary = settingsLoader.GetText();
		}
		else if (settingsLoader.GetCurrentElementName() == "musicLibrary")
		{
			myMusicLibrary = settingsLoader.GetText();
		}
		else if (settingsLoader.GetCurrentElementName() == "fixedframerate")
		{
			myFixedFramerate = settingsLoader.GetTextAsInt();
		}
		else if (settingsLoader.GetCurrentElementName() == "masterVolume")
		{
			myMasterVolume  = settingsLoader.GetTextAsFloat();
		}
		else if (settingsLoader.GetCurrentElementName() == "musicVolume")
		{
			myMusicVolume = settingsLoader.GetTextAsFloat();
		}
		else if (settingsLoader.GetCurrentElementName() == "VR")
		{
			myFlags[static_cast<int>(eSetting::eVRActive)] = settingsLoader.GetTextAsBool();
		}
		else if (settingsLoader.GetCurrentElementName() == "sound")
		{
			SetFlag(eSetting::eSound, settingsLoader.GetTextAsBool());
		}
		else if (settingsLoader.GetCurrentElementName() == "music")
		{
			SetFlag(eSetting::eMusic, settingsLoader.GetTextAsBool());
		}
		else
		{
			assert(false && "Unkown element found when loading settings.");
		}
	}
}

int Settings::GetScreenWidth() 
{
	return myScreenWidth;
}

int Settings::GetScreenHeight() 
{
	return myScreenHeight;
}

int Settings::GetFixedFramerate()
{
	return myFixedFramerate;
}

const std::string& Settings::GetWindowTitle()
{
	return myWindowTitle;
}

const std::string& Settings::GetSoundLibrary()
{
	return mySoundLibrary;
}

const std::string& Settings::GetMusicLibrary()
{
	return myMusicLibrary;
}

bool Settings::GetFlag(const eSetting aSetting)
{
	return myFlags[static_cast<int>(aSetting)];
}

void Settings::SetFlag(const eSetting aSetting, bool aValue)
{
	myFlags[static_cast<int>(aSetting)] = aValue;
	PostMaster::GetInstance()->SendMessage(Message(eMessageTypes::eSettingChanged, static_cast<int>(aSetting)));
}

float Settings::GetMasterVolume()
{
	return myMasterVolume;
}

void Settings::SetMasterVolume(const float aVolume)
{
	myMasterVolume = RANGE(aVolume, 0.f, 1.f);
}

float Settings::GetMusicVolume()
{
	return myMusicVolume;
}

void Settings::SetMusicVolume(const float aVolume)
{
	myMusicVolume = RANGE(aVolume, 0.f, 1.f);
}

Settings& Settings::GetInstance()
{
	DL_ASSERT(myInstance != nullptr && "Settings class not created!");
	return *myInstance;
}

void Settings::Create()
{
	DL_ASSERT(myInstance == nullptr && "Instance already created for settings!");
	myInstance = new Settings();
}

void Settings::Destroy()
{
	DL_ASSERT(myInstance != nullptr && "Instance is already destroyed or not created!");
	SAFE_DELETE(myInstance);
}
