﻿#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#pragma hdrstop
#include "CommonStruct.h"

#if WINSYSCOMMON_EXPORTS
#define WINSYSCOMMON_API __declspec(dllexport)
#else
#define WINSYSCOMMON_API __declspec(dllimport)
#endif


#ifdef CreateDirectory
#undef CreateDirectory
#endif

#ifdef CopyFile
#undef CopyFile
#endif

#ifdef ProjectName

#endif


#if __cplusplus
extern "C" {
#endif
	extern char g_ModuleName[MAX_PATH];
	#define DebugPrint(pFormat, ...)	DebugPrintA(g_ModuleName, __func__, __LINE__, pFormat, ##__VA_ARGS__ )
	
	WINSYSCOMMON_API void DebugPrintA(const char* pModuleName, const char* pFunctionName, const int nLine, const char* format, ...);
	

	/**
	 * 레지스트리를 관리하는 API.
	 */
	namespace RegCtrl_API {
		typedef bool(*fp_GetRegistory)(HKEY hKey, wchar_t* subKey, wchar_t* valueName, wchar_t* pBuf, int pBufMaxLength);
		typedef bool(*fp_SetRegistory)(HKEY hKey, wchar_t* subKey, wchar_t* valueName, wchar_t* data);

		/**
		 * GetRegistry는 지정된 레지스트리 키의 값을 검색합니다.
		 * @param hKey 열린 레지스트리 키에 대한 핸들입니다.
		 * @param subKey 검색할 레지스트리 하위 키의 이름입니다.
		 * @param valueName 레지스트리 값의 이름입니다.
		 * @param pBuf 지정된 키의 값이 들어갈 버퍼입니다.
		 * @param pBufMaxLength 버퍼의 최대 크기입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API bool GetRegistryA(HKEY hKey, const char* subKey, const char* valueName, char* pBuf, int nLenBuf);
		WINSYSCOMMON_API bool GetRegistryW(HKEY hKey, const wchar_t* subKey, const wchar_t* valueName, wchar_t* pBuf, int nLenBuf);

		/**
		 * SetRegistry는 레지스트리 하위 키에 지정된 이름을 가진 값을 설정합니다.
		 * @param hKey 열린 레지스트리 키에 대한 핸들입니다.
		 * @param subKey 값을 설정할 레지스트리 하위 키의 이름입니다.
		 * @param valueName 값을 설정할 레지스트리 값의 이름입니다.
		 * @param data 저장할 데이터입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API bool SetRegistryA(HKEY hKey, const char* subKey, const char* valueName, const char* data);
		WINSYSCOMMON_API bool SetRegistryW(HKEY hKey, const wchar_t* subKey, const wchar_t* valueName, const wchar_t* data);

		/**
		 * DeleteRegistry는 레지스트리 키를 삭제합니다.
		 * @param hKey 열린 레지스트리 키에 대한 핸들입니다.
		 * @param subKey 값을 설정할 레지스트리 하위 키의 이름입니다.
		 * @param valueName 값을 삭제할 레지스트리 값의 이름입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API bool DeleteRegistryA(HKEY hKey, const char* subKey, const char* valueName);
		WINSYSCOMMON_API bool DeleteRegistryW(HKEY hKey, const wchar_t* subKey, const wchar_t* valueName);
	}

	/**
	 * 파일 삭제, 복사, 유무를 관리하는 API.
	 */
	namespace FileCtrl_API {
		typedef BOOL(*fp_CreateDirectory)(const char* strPath);
		typedef BOOL(*fp_FileExist)(const char* strPath);
		typedef FileType(*fp_GetType)(const char* strPath);
		typedef BOOL(*fp_CopyFile)(const char* strSrc, const char* strDst);
		typedef BOOL(*fp_GetFiles)(const char* strSrc, std::vector<std::string>* files);
		typedef BOOL(*fp_FileVersion)(const char* pPath, int nLenPath, const char* pDst, int nMaxLenDst);

		/**
		 * CreateDirectory는 새 디렉터리를 만듭니다.
		 * @param strPath 만들 디렉터리의 이름입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL CreateDirectory(const char* strPath);

		/**
		 * FileExist는 파일이 존재하는지 여부를 결정합니다.
		 * @param strPath 테스트 할 파일 이름입니다.
		 * @return 파일이 존재하는 경우 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL FileExist(const char* strPath);

		/**
		 * GetType은 파일의 유형을 검색합니다.
		 * @param strPath 검색 할 파일 이름입니다.
		 * @return 파일의 유형입니다.
		 */
		WINSYSCOMMON_API FileType GetType(const char* strPath);

		/**
		 * RemoveFIle은 파일을 삭제합니다.
		 * @param strPath 삭제 할 파일의 이름입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL RemoveFIle(const char* strPath);

		/**
		 * CopyFile은 기존 파일을 새 파일로 복사합니다.
		 * @param strSrc 복사 할 기존 파일 이름입니다.
		 * @param strDst 새 파일의 이름입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL CopyFile(const char* strSrc, const char* strDst);

		/**
		 * GetFiles는 지정된 디렉터리의 모든 파일 이름을 추출합니다.
		 * @param strSrc 검색 할 디렉터리입니다.
		 * @param files 파일 이름을 수신하는 벡터입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL GetFiles(const char* strSrc, std::vector<std::string>* files);

		/**
		 * FileVersion는 특정 파일의 버전을 추출합니다.
		 * pDst 사용 전 NULL 값으로 초기화 필수
		 *
		 *
		 * @param pPath		- 버전을 갖여올 파일의 경로
		 * @param pDst		- 버전 정보가 담길 공간
		 * @param nMaxLenDst - Dstination 버퍼의 최대 크기
		 */
		WINSYSCOMMON_API BOOL FileVersion(const char* pPath, char* pDst, int nLenDst);

		/**
		 * 특정 파일이 64비트 헤더를 갖고 있는지 검사하는 기능.
		 *
		 * \param pPath - 정보를 얻고자 하는 파일의 경로
		 * \return
		 */
		WINSYSCOMMON_API BOOL Is64BitFile(const char* pPath);
	}

	/**
	 * 시스템 정보를 관리하는 API.
	 */
	namespace SysCtrl_API {
		typedef BOOL(*fp_GetEnviroment)(const char* key, const char* pBuf, int nBufSize);
		typedef BOOL(*fp_SetEnviroment)(const char* key, const char* value);
		typedef BOOL(*fp_GetSystemTimeEx)(const char* pBuf, int nBufSize);
		typedef BOOL(*fp_IsProcessElevated)();

		/**
		 * GetEnviroment는 지정된 환경 변수의 값을 검색합니다.
		 * @param key 환경 변수의 이름입니다.
		 * @param pBuf 지정된 환경 변수의 값을 받는 버퍼입니다.
		 * @param nLenBuf 버퍼의 최대 길이입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL GetEnviroment(const char* key, const char* pBuf, int nLenBuf);

		/**
		 * SetEnviroment는 지정된 환경 변수의 값을 설정합니다.
		 * @param key 환경 변수의 이름입니다.
		 * @param value 환경 변수의 새 값입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL SetEnviroment(const char* key, const char* value);

		/**
		 * GetSystemTimeEx는 로컬 시간과 날짜를 검색합니다.
		 * @param pBuf 시간 및 날짜를 받는 버퍼입니다.
		 * @param nBufSize 버퍼의 최대 크기입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL GetSystemTimeEx(const char* pBuf, int nBufSize);

		/**
		 * IsProcessElevated는 현재 프로세스가 관리자 권한으로 실행되고 있는지 여부를 결정합니다.
		 * @return 현재 프로세스가 관리자 권한으로 실행되는 경우 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL IsProcessElevated();

		/**
		 * AddStartProgram는 BinPath의 파일을 시작 프로그램으로 등록합니다.
		 * @param pName 시작 프로그램 이름
		 * @param nLenName 시작 프로그램 이름의 길이
		 * @param pBinPath 실행 바이너리 경로
		 * @param nLenPath 해당 경로의 길이
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL AddStartProgram(const char* pName, const char* pBinPath);
		/**
		 * DeleteStartProgram는 시작 프로그램을 삭제합니다.
		 * @param pName 시작 프로그램 이름
		 * @param nLenName 시작 프로그램 이름의 길이
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL DeleteStartProgram(const char* pName, int nLenName);

	}

	/**
	 * 프로세스를 관리하는 API.
	 */
	namespace ProcCtrl_API {
		typedef bool(*fp_StartProcess)(const char*);
		typedef bool(*fp_StopProcess)(const char*);
		typedef bool(*fp_IsProcessRunning)(const char*);
		typedef bool(*fp_SetProcessPriority)(const char*, DWORD);
		typedef bool(*fp_MonitorProcessResources)(const char*, PROCESS_RESOURCE_USAGE*);
		typedef int (*fp_InjectDLL)(const char* pDllPath, int nLenDllPath, DWORD dwPID);

		/**
		 * StartProcess는 새 프로세스를 시작합니다.
		 * @param szPath 실행할 실행 파일의 경로입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API bool StartProcess(const char* szPath, DWORD* pPID);

		/**
		 * StopProcess는 프로세스를 이름으로 종료합니다.
		 * @param szProcessName 종료할 프로세스의 이름입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API bool StopProcess(const char* szProcessName);

		/**
		* @brief 주어진 프로세스 이름의 프로세스가 실행 중인지 확인하는 함수
		* @param szProcName 확인할 프로세스의 이름
		* @param dwPID PID값을 받아올 포인터
		* @return 프로세스가 실행 중이면 true, 그렇지 않으면 false 반환
		*/
		WINSYSCOMMON_API bool IsProcessRunning(const char* szProcessName, DWORD* dwPID);

		/**
		 * SetProcessPriority는 지정된 프로세스의 우선 순위 클래스를 설정합니다.
		 * @param szProcName 프로세스의 이름입니다.
		 * @param dwPriority 프로세스의 우선 순위 클래스입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API bool SetProcessPriority(const char* szProcName, DWORD dwPriority);

		/**
		 * MonitorProcessResources는 프로세스에서 사용하는 리소스에 대한 정보를 검색합니다.
		 * @param szProcName 프로세스의 이름입니다.
		 * @param usage 리소스 사용 정보를 수신하는 PROCESS_RESOURCE_USAGE 구조체에 대한 포인터입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API bool MonitorProcessResources(const char* szProcName, PROCESS_RESOURCE_USAGE* usage);

		/**
		 * \brief 프로세스 ID로 특정 프로세스에 DLL을 인젝션 시키는 함수.
		 *
		 * \param strDllPath    - 인젝션 시킬 DLL 파일 경로
		 * \param dwPID         - 인젝션 시킬 Process ID 값
		 * \return 성공 - ERROR_SUCCESS, 실패 - ERROR_INVALID_PARAMETER
		 */
		WINSYSCOMMON_API int InjectDLL(const char* pDllPath, DWORD dwPID);
	}

	/**
	 * 문자열 변환을 관리하는 API.
	 */
	namespace StrCtrl_API {
		/**
		 * AnsiStringToWideString은 멀티바이트 문자열을 와이드 문자열로 변환합니다.
		 * @param pSrcBuf 변환할 멀티바이트 문자열입니다.
		 * @param nSrcBufSize 입력 버퍼의 최대 크기입니다.
		 * @param pDstBuf 변환된 문자열을 받는 버퍼입니다.
		 * @param pDstBufMaxSize 출력 버퍼의 최대 크기입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL AnsiStringToWideString(const char* pSrcBuf, wchar_t* pDstBuf, int pDstBufMaxSize);

		/**
		 * WideStringToAnsiString은 와이드 문자열을 멀티바이트 문자열로 변환합니다.
		 * @param pSrcBuf 변환할 와이드 문자열입니다.
		 * @param nSrcBufSize 입력 버퍼의 최대 크기입니다.
		 * @param pDstBuf 변환된 문자열을 받는 버퍼입니다.
		 * @param pDstBufMaxSize 출력 버퍼의 최대 크기입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL WideStringToAnsiString(const wchar_t* pSrc, char* pDst, int nLenDst);

		/**
		 * @brief 문자열을 구분자로 나누어 벡터에 저장합니다.
		 *
		 * @param pString 구분할 문자열입니다.
		 * @param pDelimiter 구분자입니다.
		 * @param pVecString 문자열을 저장할 벡터입니다.
		 * @return int ERROR_SUCCESS : 성공적으로 처리되었습니다.
		 * @return int ERROR_INVALID_PARAMETER : 입력된 매개변수 중 하나 이상이 NULL입니다.
		 */
		WINSYSCOMMON_API int GetStringParsing(const WCHAR* pString, const WCHAR* pDelimiter, std::vector<std::wstring>* pVecString);

		/**
		 * @brief 랜덤 문자열을 구합니다..
		 *
		 * @param pBuf 문자열이 담길 버퍼 공간입니다.
		 * @param nLenBuf 버퍼의 최대 길이입니다.
		 * @param length 만들고자 하는 문자열의 길이
		 * @return bool 성공 여부
		 *
		 */
		WINSYSCOMMON_API bool GetRandomString(char* pBuf, int nLenBuf, int length);

		/**
		 * @brief UTF8 문자열을 UTF16 으로 변환하는 함수.
		 * 
		 * @param pSrc UTF16으로 변경할 UTF8 문자열
		 * @param pDst UTF8로 저장될 공간
		 * @param nLenDst UTF8로 저장될 공간의 크기
		 * @return bool 성공 여부
		 */
		WINSYSCOMMON_API bool UTF8ToUTF16(const char* pSrc, wchar_t* pDst, int nLenDst);

		/**
		 * @brief UTF16 문자열을 UTF8 으로 변환하는 함수.
		 *
		 * @param pSrc UTF8으로 변경할 UTF8 문자열
		 * @param pDst UTF16로 저장될 공간
		 * @param nLenDst UTF16로 저장될 공간의 크기
		 * @return bool 성공 여부
		 */
		WINSYSCOMMON_API bool UTF16ToUTF8(const wchar_t* pSrc, char * pDst, int nLenDst);
	}

	namespace ServiceCtrl_API {
		typedef bool(*fp_Create)(const char* serviceName, const char* displayName, const char* binPath);
		typedef bool(*fp_Start)(const char* serviceName, bool force_admin);
		typedef bool(*fp_IsRunning)(const char* serviceName);
		typedef bool(*fp_Stop)(const char* serviceName);
		typedef bool(*fp_Restart)(const char* serviceName);
		typedef bool(*fp_Delete)(const char* serviceName);

		/**
		 * @brief 윈도우 서비스 생성
		 *
		 * @param serviceName : 생성할 서비스명
		 * @param displayName : 서비스 설명
		 * @param binPath : 서비스 실행 파일 경로
		 * @return true : 성공 / false : 실패
		 */
		WINSYSCOMMON_API bool Create(const char* serviceName, const char* displayName, const char* binPath);

		/**
		 * @brief 서비스가 실행중인지 확인한다.
		 * @param serviceName 서비스 이름
		 * @return 성공 여부
		 */
		WINSYSCOMMON_API bool IsRunning(const char* serviceName);

		/**
		 * @brief 윈도우 서비스 시작
		 *
		 * @param serviceName : 시작할 서비스명
		 * @param force_admin : 관리자 권한으로 실행 여부
		 * @return true : 성공 / false : 실패
		 */
		WINSYSCOMMON_API bool Start(const char* serviceName, bool force_admin = false);

		/**
		 * @brief 윈도우 서비스 중지
		 *
		 * @param serviceName : 중지할 서비스명
		 * @return true : 성공 / false : 실패
		 */
		WINSYSCOMMON_API bool Stop(const char* serviceName);

		/**
		 * @brief 윈도우 서비스 재시작
		 *
		 * @param serviceName : 재시작할 서비스명
		 * @return true : 성공 / false : 실패
		 */
		WINSYSCOMMON_API bool Restart(const char* serviceName);

		/**
		 * @brief 윈도우 서비스 삭제
		 *
		 * @param serviceName : 삭제할 서비스명
		 * @return true : 성공 / false : 실패
		 */
		WINSYSCOMMON_API bool Delete(const char* serviceName);

	}

#if __cplusplus
}
#endif