#pragma once
#include <windows.h>
#include <tchar.h>
#pragma hdrstop

#include "StrCtrl.h"

class CServiceCtrl;
extern CServiceCtrl ServiceCtrl;

/**
 * @brief CServiceCtrl 클래스 - Windows 서비스 컨트롤
 */
class CServiceCtrl {
private:
    SC_HANDLE serviceHandle; /**< 서비스 핸들 */

public:
    /**
     * @brief 생성자
     */
    CServiceCtrl();

    /**
     * @brief 새로운 서비스를 생성한다.
     * @param serviceName 서비스 이름
     * @param displayName 서비스 표시명
     * @param binPath 서비스 실행 파일 경로
     * @return 생성 성공 여부
     */
    bool Create(char* serviceName, char* displayName, char* binPath);

    /**
     * @brief 서비스를 시작한다.
     * @param serviceName 서비스 이름
     * @param force_admin 관리자 권한 강제 설정 여부
     * @return 시작 성공 여부
     */
    bool Start(char* serviceName, bool force_admin = false);

    /**
     * @brief 서비스를 중지한다.
     * @param serviceName 서비스 이름
     * @return 중지 성공 여부
     */
    bool Stop(char* serviceName);

    /**
     * @brief 서비스를 재시작한다.
     * @param serviceName 서비스 이름
     * @return 재시작 성공 여부
     */
    bool Restart(char* serviceName);

    /**
     * @brief 서비스를 삭제한다.
     * @param serviceName 서비스 이름
     * @return 삭제 성공 여부
     */
    bool Delete(char* serviceName);
};
