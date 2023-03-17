#pragma once
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#pragma hdrstop

#include "StrCtrl.h"
#include "ErrorCtrl.h"

class CSysCtrl;
extern CSysCtrl SysCtrl;

/**
 * @class CSysCtrl
 * @brief CSysCtrl 클래스는 다양한 시스템 제어 기능을 제공합니다.
 * @details 이 클래스는 환경 변수를 가져오고 설정하며, 시스템 시간을 가져오고, UAC 권한을 확인하는 기능을 제공합니다.
 *          이 클래스는 CErrorCtrl 클래스에서 파생됩니다.
 */
class CSysCtrl : protected CErrorCtrl
{
public:
    /**
     * @brief CSysCtrl 객체를 생성합니다.
     */
    CSysCtrl();

    /**
     * @brief CSysCtrl 객체를 소멸시킵니다.
     */
    virtual ~CSysCtrl();

public:
    /**
     * @brief 환경 변수의 값을 가져옵니다.
     * @param key 환경 변수의 이름입니다.
     * @param value 환경 변수의 값을 저장할 문자열 변수에 대한 참조입니다.
     * @return BOOL, 환경 변수가 존재하면 TRUE, 그렇지 않으면 FALSE를 반환합니다.
     */
    BOOL GetEnviroment(std::string key, std::string& value);

    /**
     * @brief 환경 변수의 값을 가져옵니다.
     * @param key 환경 변수의 이름입니다.
     * @param value 환경 변수의 값을 저장할 wstring 변수에 대한 참조입니다.
     * @return BOOL, 환경 변수가 존재하면 TRUE, 그렇지 않으면 FALSE를 반환합니다.
     */
    BOOL GetEnviroment(std::wstring key, std::wstring& value);

    /**
     * @brief 환경 변수의 값을 설정합니다.
     * @param key 환경 변수의 이름입니다.
     * @param value 환경 변수의 새 값을 지정합니다.
     * @return BOOL, 환경 변수가 성공적으로 설정되면 TRUE, 그렇지 않으면 FALSE를 반환합니다.
     */
    BOOL SetEnviroment(std::string key, std::string value);

    /**
     * @brief 환경 변수의 값을 설정합니다.
     * @param key 환경 변수의 이름입니다.
     * @param value 환경 변수의 새 값을 지정합니다.
     * @return BOOL, 환경 변수가 성공적으로 설정되면 TRUE, 그렇지 않으면 FALSE를 반환합니다.
     */
    BOOL SetEnviroment(std::wstring key, std::wstring value);

    /**
     * @brief 현재 시스템 시간을 가져옵니다.
     * @param strTime 현재 시스템 시간을 문자열 형식으로 저장할 문자열 변수에 대한 참조입니다.
     * @return BOOL, 시스템 시간을 성공적으로 가져오면 TRUE, 그렇지 않으면 FALSE를 반환합니다.
     */
    BOOL GetSystemTime(std::string& strTime);

    /**
     * @brief 현재 프로세스가 권한을 상승시킬 수 있는지 확인합니다.
     * @return BOOL, 프로세스가 권한을 상승시킬 수 있으면 TRUE, 그렇지 않으면 FALSE를 반환합니다.
     */
    BOOL IsProcessElevated();
};
