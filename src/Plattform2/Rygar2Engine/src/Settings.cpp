#include "Settings.h"
#include <assert.h>

Settings::Settings()
{
    mKeyFloatValues[Setting::eGravity] = 0.15f;
    mKeyFloatValues[Setting::ePlayerJumpForce] = 7.f;

    mKeyIntValues[Setting::eScreenWidth] = 400;
    mKeyIntValues[Setting::eScreenHeight] = 240;
    mKeyIntValues[Setting::eWindowsWidth] = 1280;
    mKeyIntValues[Setting::eWindowsHeight] = 768;
}

int Settings::GetFloat(const Setting setting) const
{
    assert(mKeyFloatValues.find(setting) != mKeyFloatValues.end() && "Key doesn't exist in settings!");
    return mKeyFloatValues.at(setting);
}

int Settings::GetInt(const Setting setting) const
{
    assert(mKeyIntValues.find(setting) != mKeyIntValues.end() && "Key doesn't exist in settings!");
    return mKeyIntValues.at(setting);

}

void Settings::SetFloat(const Setting setting, const float value)
{
    mKeyFloatValues[setting] = value;
}

void Settings::SetInt(const Setting setting, const float value)
{
    mKeyIntValues[setting] = value;
}

void Settings::Create()
{
    assert(ourInstance == nullptr && "Instance already created!");
    ourInstance = new Settings();
}

void Settings::Delete()
{
    delete ourInstance;
    ourInstance = nullptr;
}
