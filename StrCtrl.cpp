#include "StrCtrl.h"

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
