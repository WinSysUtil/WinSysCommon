#include "CommonAPI.h"

BOOL FileCtrl_API::CreateDirectory(char* strPath)
{
	return FileCtrl.CreateDirectory(strPath);
}

BOOL FileCtrl_API::FileExist(char* strPath)
{
	return FileCtrl.FileExists(strPath);
}

FileType FileCtrl_API::GetType(char* strPath)
{
	return FileCtrl.GetType(strPath);
}

BOOL FileCtrl_API::CopyFile(char* strSrc, char* strDst)
{
	return FileCtrl.CopyFile(strSrc, strDst);
}

BOOL FileCtrl_API::GetFiles(char* strSrc, std::vector<std::string>* files)
{
	return FileCtrl.GetFiles(strSrc, files);
}

BOOL SysCtrl_API::GetEnviroment(char* key, char* pBuf, int nBufSize)
{
	BOOL ret = FALSE;

	std::string value;
	if (TRUE == SysCtrl.GetEnviroment(key, value))
	{
		strcpy_s(pBuf, nBufSize, value.c_str());
	}


	return ret;
}

BOOL SysCtrl_API::SetEnviroment(char* key, char* value)
{
	BOOL ret = FALSE;
	if (TRUE == SysCtrl.SetEnviroment(key, value))
	{
		ret = TRUE;
	}

	return ret;
}

BOOL SysCtrl_API::GetSystemTimeEx(char* pBuf, int nBufSize)
{
	BOOL ret = FALSE;
	std::string strTime;
	if (TRUE == SysCtrl.GetSystemTime(strTime))
	{
		strcpy_s(pBuf, nBufSize, strTime.c_str());
		ret = TRUE;
	}


	return ret;
}

BOOL StrCtrl_API::AnsiStringToWideString(char* pSrcBuf, int nSrcBufSize, wchar_t* pDstBuf, int pDstBufMaxSize)
{
	BOOL ret = FALSE;
	auto wstrTemp = StrCtrl.AnsiStringToWideString(pSrcBuf);
	if (0 == wcsncpy_s(pDstBuf, pDstBufMaxSize, wstrTemp.c_str(), wstrTemp.length()))
	{
		ret = TRUE;
	}

	return ret;
}

BOOL StrCtrl_API::WideStringToAnsiString(wchar_t* pSrcBuf, int nSrcBufSize, char* pDstBuf, int pDstBufMaxSize)
{
	BOOL ret = FALSE;
	std::wstring wstrTemp(pSrcBuf, pSrcBuf + nSrcBufSize);
	auto strTemp = StrCtrl.WideStringToAnsiString(wstrTemp);
	if (0 == strncpy_s(pDstBuf, pDstBufMaxSize, strTemp.c_str(), strTemp.length()))
	{
		ret = TRUE;
	}

	return ret;
}
