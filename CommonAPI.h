#pragma once
#include <Windows.h>
#pragma hdrstop
#include "FileCtrl.h"

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
	WINSYSCOMMON_API BOOL CreateDirectory(char* strPath);
	WINSYSCOMMON_API BOOL FileExist(char* strPath);
	WINSYSCOMMON_API FileType GetType(char* strPath);
	WINSYSCOMMON_API BOOL CopyFile(char* strSrc, char* strDst);
	WINSYSCOMMON_API BOOL GetFiles(char* strSrc, std::vector<std::string> * files);
#if __cplusplus
}
#endif