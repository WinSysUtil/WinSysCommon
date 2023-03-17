#pragma once
#include <Windows.h>
#pragma hdrstop
#include "FileCtrl.h"
#include "SysCtrl.h"

#if WINSYSCOMMON_EXPORTS
#define WINSYSCOMMON_API _declspec(dllexport) 
#else
#define WINSYSCOMMON_API _declspec(dllexport) 
#endif


typedef BOOL(*fp_CreateDirectory)(char * strPath);
typedef BOOL(*fp_FileExist)(char* strPath);
typedef FileType (*fp_GetType)(char* strPath);
typedef BOOL(*fp_CopyFile)(char* strSrc, char* strDst);
typedef BOOL(*fp_GetFiles)(char* strSrc, std::vector<std::string>* files);

#if __cplusplus
extern "C" {
#endif
	/**
	 * 파일 삭제, 복사, 유무 확인을 하는 API.
	 */
	namespace FileCtrl_API {

		WINSYSCOMMON_API BOOL CreateDirectory(char* strPath);
		WINSYSCOMMON_API BOOL FileExist(char* strPath);
		WINSYSCOMMON_API FileType GetType(char* strPath);
		WINSYSCOMMON_API BOOL CopyFile(char* strSrc, char* strDst);
		WINSYSCOMMON_API BOOL GetFiles(char* strSrc, std::vector<std::string>* files);

	}
	
	/**
	 * 시스템 정보를 확인하는 API.
	 */
	namespace SysCtrl_API {
		WINSYSCOMMON_API BOOL GetEnviroment(char * key, char * pBuf, int nBufSize);
		WINSYSCOMMON_API BOOL SetEnviroment(char * key, char *value);
		WINSYSCOMMON_API BOOL GetSystemTimeEx(char * pBuf, int nBufSize);
	}
#if __cplusplus
}
#endif