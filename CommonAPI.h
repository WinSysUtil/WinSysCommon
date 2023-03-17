﻿#pragma once
#include <Windows.h>
#pragma hdrstop
#include "FileCtrl.h"
#include "SysCtrl.h"

#if WINSYSCOMMON_EXPORTS
#define WINSYSCOMMON_API _declspec(dllexport) 
#else
#define WINSYSCOMMON_API _declspec(dllexport) 
#endif

#if __cplusplus
extern "C" {
#endif
	/**
	 * 파일 삭제, 복사, 유무를 관리하는 API.
	 */
	namespace FileCtrl_API {
		typedef BOOL(*fp_CreateDirectory)(char* strPath);
		typedef BOOL(*fp_FileExist)(char* strPath);
		typedef FileType(*fp_GetType)(char* strPath);
		typedef BOOL(*fp_CopyFile)(char* strSrc, char* strDst);
		typedef BOOL(*fp_GetFiles)(char* strSrc, std::vector<std::string>* files);

		WINSYSCOMMON_API BOOL CreateDirectory(char* strPath);
		WINSYSCOMMON_API BOOL FileExist(char* strPath);
		WINSYSCOMMON_API FileType GetType(char* strPath);
		WINSYSCOMMON_API BOOL CopyFile(char* strSrc, char* strDst);
		WINSYSCOMMON_API BOOL GetFiles(char* strSrc, std::vector<std::string>* files);

	}
	
	/**
	 * 시스템 정보를 관리하는 API.
	 */
	namespace SysCtrl_API {
		typedef BOOL(*fp_GetEnviroment)(char* key, char* pBuf, int nBufSize);
		typedef BOOL(*fp_SetEnviroment)(char* key, char* value);
		typedef BOOL(*fp_GetSystemTimeEx)(char* pBuf, int nBufSize);

		WINSYSCOMMON_API BOOL GetEnviroment(char * key, char * pBuf, int nBufSize);
		WINSYSCOMMON_API BOOL SetEnviroment(char * key, char *value);
		WINSYSCOMMON_API BOOL GetSystemTimeEx(char * pBuf, int nBufSize);

	}

	/**
	 * 문자열 변환을 관리하는 API.
	 */
	namespace StrCtrl_API {
		typedef BOOL(*fp_AnsiStringToWideString)(char* pSrcBuf, int nSrcBufSize, wchar_t* pDstBuf, int pDstBufMaxSize);
		typedef BOOL(*fp_WideStringToAnsiString)(wchar_t* pSrcBuf, int nSrcBufSize, char* pDstBuf, int pDstBufMaxSize);

		WINSYSCOMMON_API BOOL AnsiStringToWideString(char* pSrcBuf, int nSrcBufSize, wchar_t* pDstBuf, int pDstBufMaxSize);
		WINSYSCOMMON_API BOOL WideStringToAnsiString(wchar_t* pSrcBuf, int nSrcBufSize, char* pDstBuf, int pDstBufMaxSize);

	}
#if __cplusplus
}
#endif