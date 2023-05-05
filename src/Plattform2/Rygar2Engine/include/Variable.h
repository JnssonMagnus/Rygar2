#pragma once
#include <..\external\rapidJSON\document.h>
#include <string>
#include <map>
#include <variant>

enum class VariableTypes
{
    None,
    i,
    d,
    s
};

class VariableContainer
{
public:
    VariableContainer() = default;
    ~VariableContainer() = default;

    void LoadJSON(const rapidjson::GenericArray<false, rapidjson::Value>& aVariables);

    template<class T>
    bool GetValue(const std::string& aKey, T& aOutValue) const;

    template<class T>
    T GetValue(const std::string& aKey) const;

private:
    std::map<std::string, std::variant<std::string, float, int>> myVariables;
};

template<class T>
inline bool VariableContainer::GetValue(const std::string& aKey, T& aOutValue) const
{
    auto it = myVariables.find(aKey);
    if (it == myVariables.end()) {
        return false;
    }

    aOutValue = std::get<T>(it->second);

    return true;
}


template<class T>
inline T VariableContainer::GetValue(const std::string& aKey) const
{
    DL_ASSERT(myVariables.find(aKey) != myVariables.end() && "Key is missing!");
    return std::get<T>(myVariables.at(aKey));
}
