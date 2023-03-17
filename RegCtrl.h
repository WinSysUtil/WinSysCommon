#pragma once

#include <vector>
#include <string>
#include <Windows.h>
#pragma hdrstop

class CRegCtrl;
extern CRegCtrl RegCtrl;

class CRegCtrl
{
public:
    CRegCtrl() = default;
    ~CRegCtrl() = default;

    bool SetRegistry(HKEY hKey, const std::wstring& subKey, const std::wstring& valueName, const std::wstring& data);
    bool GetRegistry(HKEY hKey, const std::wstring& subKey, const std::wstring& valueName, std::wstring& data);

private:
    bool OpenRegistryKey(HKEY hKey, const std::wstring& subKey, REGSAM access, HKEY& resultKey);
    bool QueryValue(HKEY resultKey, const std::wstring& valueName, std::wstring& data, DWORD& dataSize);
    bool SetValue(HKEY resultKey, const std::wstring& valueName, const std::wstring& data, DWORD dataSize);
    bool CloseRegistryKey(HKEY hKey);
};
