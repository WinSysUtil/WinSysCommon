#pragma once
#include <Windows.h>
#include <string>

class CStrCtrl
{
public:
	CStrCtrl();
	~CStrCtrl();

public:
	/**
	 * Ansi 타입의 문자열을 Wide 타입의 문자열로 변환해주는 함수.
	 * 
	 * \param str - Ansi 타입 문자열
	 * \return - Wide 타입 문자열
	 */
	std::wstring AnsiStringToWideString(std::string str);
	/**
	 * Wide 타입의 문자열을 Ansi 타입의 문자열로 변환해주는 함수.
	 *
	 * \param str - Wide 타입 문자열
	 * \return - Ansi 타입 문자열
	 */
	std::string WideStringToAnsiString(std::wstring str);
};

