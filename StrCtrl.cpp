#include "StrCtrl.h"

CStrCtrl StrCtrl;

CStrCtrl::CStrCtrl()
{
}

CStrCtrl::~CStrCtrl()
{
}

std::wstring CStrCtrl::AnsiStringToWideString(std::string str)
{
	std::wstring result;

	result.assign(str.begin(), str.end());

	return result;
}

std::string CStrCtrl::WideStringToAnsiString(std::wstring str)
{
	std::string result;

	result.assign(str.begin(), str.end());

	return result;
}

int CStrCtrl::GetStringParsing(WCHAR* pString, WCHAR* pDelimiter, std::vector<std::wstring>* pVecString)
{
	if (pString == NULL || pDelimiter == NULL || pVecString == NULL)
	{
		return ERROR_INVALID_PARAMETER;
	}

	WCHAR* token;
	WCHAR* next_token = NULL;

	token = wcstok_s(pString, pDelimiter, &next_token);
	while (token != NULL)
	{
		pVecString->push_back(token);
		token = wcstok_s(NULL, pDelimiter, &next_token);
	}

	return ERROR_SUCCESS;
}
