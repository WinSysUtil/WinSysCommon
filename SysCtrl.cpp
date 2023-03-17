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

BOOL CSysCtrl::SetEnviroment(std::wstring key, std::wstring value)
{
	return SetEnviroment(std::string(key.begin(), key.end()), std::string(value.begin(), value.end()));
}

BOOL CSysCtrl::GetEnviroment(std::wstring key, std::wstring& value)
{
	BOOL ret = FALSE;
	std::string strTemp;
	if (TRUE == GetEnviroment(std::string(key.begin(), key.end()), strTemp))
	{
		value.clear();
		value.append(strTemp.begin(), strTemp.end());
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
