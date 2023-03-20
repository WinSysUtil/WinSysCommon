#pragma once
#include <Windows.h>
#include <string>
#include <vector>

class CStrCtrl;
extern CStrCtrl StrCtrl;

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

	/**
	 * @brief 문자열을 구분자로 나누어 벡터에 저장합니다.
	 *
	 * @param pString 구분할 문자열입니다.
	 * @param pDelimiter 구분자입니다.
	 * @param pVecString 문자열을 저장할 벡터입니다.
	 * @return int ERROR_SUCCESS : 성공적으로 처리되었습니다.
	 * @return int ERROR_INVALID_PARAMETER : 입력된 매개변수 중 하나 이상이 NULL입니다.
	 */
	int GetStringParsing(WCHAR* pString, WCHAR* pDelimiter, std::vector<std::wstring>* pVecString);
	
};

