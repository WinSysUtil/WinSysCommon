#include "SysCtrl.h"

CSysCtrl SysCtrl;

CSysCtrl::CSysCtrl()
{
}

CSysCtrl::~CSysCtrl()
{
}

BOOL CSysCtrl::SetEnviroment(std::string key, std::string value)
{
	std::string strEnv;
	strEnv += key;
	strEnv += "=";
	strEnv += value;

	int nResult = _putenv(strEnv.c_str());
	
	BOOL ret = FALSE;
	if (nResult == 0)
		ret = TRUE;
	
	return ret;
}

BOOL CSysCtrl::SetEnviroment(std::wstring key, std::wstring value)
{
	return SetEnviroment(StrCtrl.WideStringToAnsiString(key), StrCtrl.WideStringToAnsiString(value));
}

BOOL CSysCtrl::GetEnviroment(std::string key, std::string& value)
{
	BOOL ret = FALSE;

	char* pValue = nullptr;
	size_t nLen = 0;
	errno_t err = _dupenv_s(&pValue, &nLen, "PATH");
	if (err == 0 && pValue != NULL) 
	{
		value.assign(pValue, pValue + nLen);
		free(pValue);
		ret = TRUE;
	}
	
	return ret;
}

BOOL CSysCtrl::GetEnviroment(std::wstring key, std::wstring& value)
{
	BOOL ret = FALSE;
	std::string strTemp;
	if (TRUE == GetEnviroment(StrCtrl.WideStringToAnsiString(key), strTemp))
	{
		value = StrCtrl.AnsiStringToWideString(strTemp);
		ret = TRUE;
	}

	return ret;
}

BOOL CSysCtrl::GetSystemTime(std::string& strTime)
{
	BOOL ret = FALSE;

	std::time_t now = std::time(nullptr);
	std::tm tm_now;
	errno_t err = localtime_s(&tm_now, &now);
	if (err == 0) {
		char time_str[26];
		err = asctime_s(time_str, sizeof(time_str), &tm_now);
		if (err == 0) {
			strTime.clear();
			strTime.append(time_str);
			ret = TRUE;
		}
		else {
			//std::cerr << "Error converting time" << std::endl;
		}
	}
	else {
		//std::cerr << "Error converting time" << std::endl;
	}

	return ret;
}

BOOL CSysCtrl::IsProcessElevated()
{
	BOOL isAdmin;
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	PSID AdministratorsGroup;
	BOOL Result = AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &AdministratorsGroup);
	if (Result) {
		if (!CheckTokenMembership(NULL, AdministratorsGroup, &isAdmin)) {
			isAdmin = false;
		}
		FreeSid(AdministratorsGroup);
	}
	return isAdmin;
}
