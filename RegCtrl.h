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
    /**
     * @brief 레지스트리에 값을 설정합니다.
     * @param hKey 레지스트리 키
     * @param subKey 서브 키
     * @param valueName 값 이름
     * @param data 설정할 데이터
     * @return 설정 성공 여부
     */
    bool SetRegistry(HKEY hKey, const std::wstring& subKey, const std::wstring& valueName, const std::wstring& data);

    /**
     * @brief 레지스트리에서 값을 가져옵니다.
     * @param hKey 레지스트리 키
     * @param subKey 서브 키
     * @param valueName 값 이름
     * @param data 가져온 데이터
     * @return 가져오기 성공 여부
     */
    bool GetRegistry(HKEY hKey, const std::wstring& subKey, const std::wstring& valueName, std::wstring& data);

private:
    /**
     * @brief 레지스트리 키 열기
     * @param hKey 레지스트리 키
     * @param subKey 서브 키
     * @param access 레지스트리 접근 권한
     * @param resultKey 결과 키
     * @return 열기 성공 여부
     */
    bool OpenRegistryKey(HKEY hKey, const std::wstring& subKey, REGSAM access, HKEY& resultKey);

    /**
     * @brief 값을 쿼리합니다.
     * @param resultKey 결과 키
     * @param valueName 값 이름
     * @param data 가져온 데이터
     * @param dataSize 가져온 데이터 크기
     * @return 쿼리 성공 여부
     */
    bool QueryValue(HKEY resultKey, const std::wstring& valueName, std::wstring& data, DWORD& dataSize);

    /**
     * @brief 값을 설정합니다.
     * @param resultKey 결과 키
     * @param valueName 값 이름
     * @param data 설정할 데이터
     * @param dataSize 설정할 데이터 크기
     * @return 설정 성공 여부
     */
    bool SetValue(HKEY resultKey, const std::wstring& valueName, const std::wstring& data, DWORD dataSize);

    /**
     * @brief 레지스트리 키 닫기
     * @param hKey 레지스트리 키
     * @return 닫기 성공 여부
     */
    bool CloseRegistryKey(HKEY hKey);
};
