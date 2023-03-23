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

std::string CStrCtrl::GetRandomString(int length)
{
	std::string randomString = "";
	srand(time(NULL)); // 랜덤 시드 초기화

	for (int i = 0; i < length; i++) {
		char randomChar = 'A' + rand() % 26; // 알파벳 대문자 랜덤 생성
		randomString += randomChar;
	}

	return randomString;
}
