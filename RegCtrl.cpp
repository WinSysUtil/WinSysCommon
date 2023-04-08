#include "RegCtrl.h"
CRegCtrl RegCtrl;

bool CRegCtrl::SetRegistry(HKEY hKey, const std::string& subKey, const std::string& valueName, const std::string& data)
{
    return SetRegistry(hKey,
        StrCtrl.AnsiStringToWideString(subKey),
        StrCtrl.AnsiStringToWideString(valueName),
        StrCtrl.AnsiStringToWideString(data)
    );
}

bool CRegCtrl::SetRegistry(HKEY hKey, const std::wstring& subKey, const std::wstring& valueName, const std::wstring& data)
{
    HKEY resultKey;
    if (!OpenRegistryKey(hKey, subKey, KEY_ALL_ACCESS, resultKey))
    {
        return false;
    }

    DWORD dataSize = static_cast<DWORD>(data.size() * sizeof(wchar_t));
    bool result = SetValue(resultKey, valueName, data, dataSize);

    CloseRegistryKey(resultKey);
    return result;
}

bool CRegCtrl::GetRegistry(HKEY hKey, const std::string& subKey, const std::string& valueName, std::string& data)
{
    std::wstring wstrTemp;
    auto ret =  GetRegistry(hKey,
        StrCtrl.AnsiStringToWideString(subKey),
        StrCtrl.AnsiStringToWideString(valueName),
        wstrTemp
    );

    data = StrCtrl.WideStringToAnsiString(wstrTemp);
    return ret;
}

bool CRegCtrl::GetRegistry(HKEY hKey, const std::wstring& subKey, const std::wstring& valueName, std::wstring& data)
{
    HKEY resultKey;
    if (!OpenRegistryKey(hKey, subKey, KEY_READ, resultKey))
    {
        return false;
    }

    DWORD dataSize = 0;
    bool result = QueryValue(resultKey, valueName, data, dataSize);
    if (!result)
    {
        CloseRegistryKey(resultKey);
        return false;
    }

    CloseRegistryKey(resultKey);
    return true;
}

bool CRegCtrl::DeleteRegistry(HKEY hKey, const std::string& subKey, const std::string& valueName)
{
    return DeleteRegistry(hKey,
        StrCtrl.AnsiStringToWideString(subKey),
        StrCtrl.AnsiStringToWideString(valueName)
    );
}

bool CRegCtrl::DeleteRegistry(HKEY hKey, const std::wstring& subKey, const std::wstring& valueName)
{
    HKEY resultKey;
    if (!OpenRegistryKey(hKey, subKey, KEY_ALL_ACCESS, resultKey))
    {
        return false;
    }

    bool result = RegDeleteValueW(resultKey, valueName.c_str()) == ERROR_SUCCESS;

    CloseRegistryKey(resultKey);
    return result;
}

bool CRegCtrl::OpenRegistryKey(HKEY hKey, const std::wstring& subKey, REGSAM access, HKEY& resultKey)
{
    if (RegOpenKeyExW(hKey, subKey.c_str(), 0, access, &resultKey) != ERROR_SUCCESS)
    {
        return false;
    }

    return true;
}

bool CRegCtrl::QueryValue(HKEY resultKey, const std::wstring& valueName, std::wstring& data, DWORD& dataSize)
{
    DWORD type;
    bool result = RegQueryValueExW(resultKey, valueName.c_str(), 0, &type, nullptr, &dataSize) == ERROR_SUCCESS;
    if (!result)
    {
        return false;
    }

    if (type != REG_SZ && type != REG_EXPAND_SZ)
    {
        return false;
    }

    data.resize(dataSize / sizeof(wchar_t));
    result = RegQueryValueExW(resultKey, valueName.c_str(), 0, &type, reinterpret_cast<BYTE*>(&data[0]), &dataSize) == ERROR_SUCCESS;
    if (!result)
    {
        return false;
    }

    return true;
}

bool CRegCtrl::SetValue(HKEY resultKey, const std::wstring& valueName, const std::wstring& data, DWORD dataSize)
{
    const BYTE* pData = reinterpret_cast<const BYTE*>(data.c_str());
    bool result = RegSetValueExW(resultKey, valueName.c_str(), 0, REG_SZ, pData, dataSize) == ERROR_SUCCESS;

    return result;
}

bool CRegCtrl::CloseRegistryKey(HKEY hKey)
{
    if (RegCloseKey(hKey) != ERROR_SUCCESS)
    {
        return false;
    }

    return true;
}
