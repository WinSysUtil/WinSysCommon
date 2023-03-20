#pragma once
#include <Windows.h>
#include <vector>
#pragma hdrstop
#include "CommonStruct.h"

#if WINSYSCOMMON_EXPORTS
#define WINSYSCOMMON_API _declspec(dllexport)
#else
#define WINSYSCOMMON_API _declspec(dllexport)
#endif


#ifdef CreateDirectory
#undef CreateDirectory
#endif

#ifdef CopyFile
#undef CopyFile
#endif



#if __cplusplus
extern "C" {
#endif
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
		WINSYSCOMMON_API bool GetRegistry(HKEY hKey, wchar_t* subKey, wchar_t* valueName, wchar_t* pBuf, int pBufMaxLength);

		/**
		 * SetRegistry는 레지스트리 하위 키에 지정된 이름을 가진 값을 설정합니다.
		 * @param hKey 열린 레지스트리 키에 대한 핸들입니다.
		 * @param subKey 값을 설정할 레지스트리 하위 키의 이름입니다.
		 * @param valueName 값을 설정할 레지스트리 값의 이름입니다.
		 * @param data 저장할 데이터입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API bool SetRegistry(HKEY hKey, wchar_t* subKey, wchar_t* valueName, wchar_t* data);
	}

	/**
	 * 파일 삭제, 복사, 유무를 관리하는 API.
	 */
	namespace FileCtrl_API {
		typedef BOOL(*fp_CreateDirectory)(char* strPath);
		typedef BOOL(*fp_FileExist)(char* strPath);
		typedef FileType(*fp_GetType)(char* strPath);
		typedef BOOL(*fp_CopyFile)(char* strSrc, char* strDst);
		typedef BOOL(*fp_GetFiles)(char* strSrc, std::vector<std::string>* files);
		typedef BOOL(*fp_FileVersion)(char* pPath, int nLenPath, char* pDst, int nMaxLenDst);

		/**
		 * CreateDirectory는 새 디렉터리를 만듭니다.
		 * @param strPath 만들 디렉터리의 이름입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL CreateDirectory(char* strPath);

		/**
		 * FileExist는 파일이 존재하는지 여부를 결정합니다.
		 * @param strPath 테스트 할 파일 이름입니다.
		 * @return 파일이 존재하는 경우 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL FileExist(char* strPath);

		/**
		 * GetType은 파일의 유형을 검색합니다.
		 * @param strPath 검색 할 파일 이름입니다.
		 * @return 파일의 유형입니다.
		 */
		WINSYSCOMMON_API FileType GetType(char* strPath);

		/**
		 * RemoveFIle은 파일을 삭제합니다.
		 * @param strPath 삭제 할 파일의 이름입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL RemoveFIle(char* strPath);

		/**
		 * CopyFile은 기존 파일을 새 파일로 복사합니다.
		 * @param strSrc 복사 할 기존 파일 이름입니다.
		 * @param strDst 새 파일의 이름입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL CopyFile(char* strSrc, char* strDst);

		/**
		 * GetFiles는 지정된 디렉터리의 모든 파일 이름을 추출합니다.
		 * @param strSrc 검색 할 디렉터리입니다.
		 * @param files 파일 이름을 수신하는 벡터입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL GetFiles(char* strSrc, std::vector<std::string>* files);

		/**
		 * FileVersion는 특정 파일의 버전을 추출합니다.
		 * pDst 사용 전 NULL 값으로 초기화 필수
		 * 
		 * 
		 * @param pPath		- 버전을 갖여올 파일의 경로
		 * @param nLenPath	- 해당 경로의 길이
		 * @param pDst		- 버전 정보가 담길 공간
		 * @param nMaxLenDst - Dst의 최대 크기
		 */
		WINSYSCOMMON_API BOOL FileVersion(char* pPath, int nLenPath, char* pDst, int nMaxLenDst);
	}

	/**
	 * 시스템 정보를 관리하는 API.
	 */
	namespace SysCtrl_API {
		typedef BOOL(*fp_GetEnviroment)(char* key, char* pBuf, int nBufSize);
		typedef BOOL(*fp_SetEnviroment)(char* key, char* value);
		typedef BOOL(*fp_GetSystemTimeEx)(char* pBuf, int nBufSize);
		typedef BOOL(*fp_IsProcessElevated)();

		/**
		 * GetEnviroment는 지정된 환경 변수의 값을 검색합니다.
		 * @param key 환경 변수의 이름입니다.
		 * @param pBuf 지정된 환경 변수의 값을 받는 버퍼입니다.
		 * @param nBufSize 버퍼의 최대 크기입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL GetEnviroment(char* key, char* pBuf, int nBufSize);

		/**
		 * SetEnviroment는 지정된 환경 변수의 값을 설정합니다.
		 * @param key 환경 변수의 이름입니다.
		 * @param value 환경 변수의 새 값입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL SetEnviroment(char* key, char* value);

		/**
		 * GetSystemTimeEx는 로컬 시간과 날짜를 검색합니다.
		 * @param pBuf 시간 및 날짜를 받는 버퍼입니다.
		 * @param nBufSize 버퍼의 최대 크기입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL GetSystemTimeEx(char* pBuf, int nBufSize);

		/**
		 * IsProcessElevated는 현재 프로세스가 관리자 권한으로 실행되고 있는지 여부를 결정합니다.
		 * @return 현재 프로세스가 관리자 권한으로 실행되는 경우 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL IsProcessElevated();
	}

	/**
	 * 프로세스를 관리하는 API.
	 */
	namespace ProcCtrl_API {
		typedef bool(*fp_StartProcess)(char*);
		typedef bool(*fp_StopProcess)(char*);
		typedef bool(*fp_IsProcessRunning)(char*);
		typedef bool(*fp_SetProcessPriority)(char*, DWORD);
		typedef bool(*fp_MonitorProcessResources)(char*, PROCESS_RESOURCE_USAGE*);
		typedef int (*fp_InjectDLL)(char* pDllPath, int nLenDllPath, DWORD dwPID);

		/**
		 * StartProcess는 새 프로세스를 시작합니다.
		 * @param szPath 실행할 실행 파일의 경로입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API bool StartProcess(char* szPath, DWORD* pPID);

		/**
		 * StopProcess는 프로세스를 이름으로 종료합니다.
		 * @param szProcessName 종료할 프로세스의 이름입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API bool StopProcess(char* szProcessName);

		/**
		 * IsProcessRunning은 프로세스가 실행 중인지 여부를 결정합니다.
		 * @param szProcessName 테스트할 프로세스의 이름입니다.
		 * @return 프로세스가 실행 중이면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API bool IsProcessRunning(char* szProcessName);

		/**
		 * SetProcessPriority는 지정된 프로세스의 우선 순위 클래스를 설정합니다.
		 * @param szProcName 프로세스의 이름입니다.
		 * @param dwPriority 프로세스의 우선 순위 클래스입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API bool SetProcessPriority(char* szProcName, DWORD dwPriority);

		/**
		 * MonitorProcessResources는 프로세스에서 사용하는 리소스에 대한 정보를 검색합니다.
		 * @param szProcName 프로세스의 이름입니다.
		 * @param usage 리소스 사용 정보를 수신하는 PROCESS_RESOURCE_USAGE 구조체에 대한 포인터입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API bool MonitorProcessResources(char* szProcName, PROCESS_RESOURCE_USAGE* usage);

		/**
		 * \brief 프로세스 ID로 특정 프로세스에 DLL을 인젝션 시키는 함수.
		 *
		 * \param strDllPath    - 인젝션 시킬 DLL 파일 경로
		 * \param dwPID         - 인젝션 시킬 Process ID 값
		 * \return 성공 - ERROR_SUCCESS, 실패 - ERROR_INVALID_PARAMETER
		 */
		WINSYSCOMMON_API int InjectDLL(char * pDllPath, int nLenDllPath, DWORD dwPID);
	}

	/**
	 * 문자열 변환을 관리하는 API.
	 */
	namespace StrCtrl_API {
		typedef BOOL(*fp_AnsiStringToWideString)(char* pSrcBuf, int nSrcBufSize, wchar_t* pDstBuf, int pDstBufMaxSize);
		typedef BOOL(*fp_WideStringToAnsiString)(wchar_t* pSrcBuf, int nSrcBufSize, char* pDstBuf, int pDstBufMaxSize);
		typedef BOOL(*fp_GetStringParsing)(WCHAR* pString, WCHAR* pDelimiter, std::vector<std::wstring>* pVecString);

		/**
		 * AnsiStringToWideString은 멀티바이트 문자열을 와이드 문자열로 변환합니다.
		 * @param pSrcBuf 변환할 멀티바이트 문자열입니다.
		 * @param nSrcBufSize 입력 버퍼의 최대 크기입니다.
		 * @param pDstBuf 변환된 문자열을 받는 버퍼입니다.
		 * @param pDstBufMaxSize 출력 버퍼의 최대 크기입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL AnsiStringToWideString(char* pSrcBuf, int nSrcBufSize, wchar_t* pDstBuf, int pDstBufMaxSize);

		/**
		 * WideStringToAnsiString은 와이드 문자열을 멀티바이트 문자열로 변환합니다.
		 * @param pSrcBuf 변환할 와이드 문자열입니다.
		 * @param nSrcBufSize 입력 버퍼의 최대 크기입니다.
		 * @param pDstBuf 변환된 문자열을 받는 버퍼입니다.
		 * @param pDstBufMaxSize 출력 버퍼의 최대 크기입니다.
		 * @return 함수가 성공하면 true를, 그렇지 않으면 false를 반환합니다.
		 */
		WINSYSCOMMON_API BOOL WideStringToAnsiString(wchar_t* pSrcBuf, int nSrcBufSize, char* pDstBuf, int pDstBufMaxSize);

		/**
		 * @brief 문자열을 구분자로 나누어 벡터에 저장합니다.
		 *
		 * @param pString 구분할 문자열입니다.
		 * @param pDelimiter 구분자입니다.
		 * @param pVecString 문자열을 저장할 벡터입니다.
		 * @return int ERROR_SUCCESS : 성공적으로 처리되었습니다.
		 * @return int ERROR_INVALID_PARAMETER : 입력된 매개변수 중 하나 이상이 NULL입니다.
		 */
		WINSYSCOMMON_API int GetStringParsing(WCHAR* pString, WCHAR* pDelimiter, std::vector<std::wstring>* pVecString);

	}

#if __cplusplus
}
#endif