﻿#pragma once
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <iostream>

class CProcCtrl;
extern  CProcCtrl ProcCtrl;


typedef struct _PROCESS_RESOURCE_USAGE {
    DWORD workingSetSize;
    DWORD quotaPagedPoolUsage;
    DWORD quotaNonPagedPoolUsage;
    DWORD pagefileUsage;
} PROCESS_RESOURCE_USAGE, * PPROCESS_RESOURCE_USAGE;



/**
 * @brief 프로세스 실행, 종료, 조회, 우선순위 설정 및 자원 모니터링 관련 기능을 제공하는 클래스
 */
class CProcCtrl {
public:
    /**
     * @brief CProcCtrl 클래스의 생성자
     */
    CProcCtrl();
    /**
     * @brief CProcCtrl 클래스의 소멸자
     */
    ~CProcCtrl();

    /**
     * @brief 주어진 경로의 프로세스를 실행하는 함수
     * @param szPath 실행할 프로세스의 경로
     * @return 프로세스 실행에 성공하면 true, 실패하면 false 반환
     */
    bool StartProcess(const std::wstring& szPath);

    /**
     * @brief 주어진 프로세스 이름의 프로세스를 종료하는 함수
     * @param szProcName 종료할 프로세스의 이름
     * @return 프로세스 종료에 성공하면 true, 실패하면 false 반환
     */
    bool StopProcess(const std::wstring& szProcName);

    /**
     * @brief 주어진 프로세스 이름의 프로세스가 실행 중인지 확인하는 함수
     * @param szProcName 확인할 프로세스의 이름
     * @return 프로세스가 실행 중이면 true, 그렇지 않으면 false 반환
     */
    bool IsProcessRunning(const std::wstring& szProcName);

    /**
     * @brief 주어진 프로세스 이름의 프로세스의 우선순위를 설정하는 함수
     * @param szProcName 우선순위를 설정할 프로세스의 이름
     * @param dwPriority 설정할 우선순위 값
     * @return 우선순위 설정에 성공하면 true, 실패하면 false 반환
     */
    bool SetProcessPriority(const std::wstring& szProcName, DWORD dwPriority);

    /**
     * @brief 주어진 프로세스 이름의 자원 사용량을 모니터링하는 함수
     * @param szProcName 모니터링할 프로세스의 이름
     * @return 프로세스를 찾지 못하면 false, 그렇지 않으면 true 반환
     */
    bool MonitorProcessResources(const std::wstring& szProcName, PROCESS_RESOURCE_USAGE& usage);

private:
    HANDLE m_hSnapShot; ///< 프로세스 스냅샷의 핸들
    PROCESSENTRY32 m_pe; ///< 프로세스 정보를 저장하는 구조체
};
