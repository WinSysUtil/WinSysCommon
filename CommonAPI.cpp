#include "FileCtrl.h"
#include "SysCtrl.h"
#include "ProcCtrl.h"
#include "RegCtrl.h"

#include "CommonAPI.h"


// =============================================================================================== //
// Registry Control API
// =============================================================================================== //

bool RegCtrl_API::GetRegistry(HKEY hKey, wchar_t* subKey, wchar_t* valueName, wchar_t* pBuf, int pBufMaxLength)
{
	std::wstring wstrData;
	bool ret = FALSE;
	if (true == RegCtrl.GetRegistry(hKey, subKey, valueName, wstrData))
	{
		if (0 == wcsncpy_s(pBuf, pBufMaxLength, wstrData.c_str(), wstrData.length()))
		{
			ret = TRUE;
		}
	}

	return ret;
}

bool RegCtrl_API::SetRegistry(HKEY hKey, wchar_t* subKey, wchar_t* valueName, wchar_t* data)
{
	return RegCtrl.SetRegistry(hKey, subKey, valueName, data);
}

// =============================================================================================== //
// File Control API
// =============================================================================================== //

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

BOOL FileCtrl_API::RemoveFIle(char* strPath)
{
	return FileCtrl.RemoveFile(strPath);
}

BOOL FileCtrl_API::CopyFile(char* strSrc, char* strDst)
{
	return FileCtrl.CopyFile(strSrc, strDst);
}

BOOL FileCtrl_API::GetFiles(char* strSrc, std::vector<std::string>* files)
{
	return FileCtrl.GetFiles(strSrc, files);
}

BOOL FileCtrl_API::FileVersion(char* pPath, int nLenPath, char* pDst, int nMaxLenDst)
{
	BOOL nRet = FALSE;

	std::string strPath(pPath, nLenPath);
	std::string version;
	if (FileCtrl.FileVersion(strPath, version))
	{
		if (0 == strncpy_s(pDst, nMaxLenDst, version.c_str(), version.length()))
			nRet = TRUE;
	}
	

	return nRet;
}

// =============================================================================================== //
// System Control API
// =============================================================================================== //

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

BOOL SysCtrl_API::IsProcessElevated()
{
	return SysCtrl.IsProcessElevated();

}


// =============================================================================================== //
// String Control API
// =============================================================================================== //

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

// =============================================================================================== //
// Process Control API
// =============================================================================================== //

bool ProcCtrl_API::StartProcess(char* szPath)
{
	return ProcCtrl.StartProcess(StrCtrl.AnsiStringToWideString(szPath));
}

bool ProcCtrl_API::StopProcess(char* szProcessName)
{
	return ProcCtrl.StopProcess(StrCtrl.AnsiStringToWideString(szProcessName));

}

bool ProcCtrl_API::IsProcessRunning(char* szProcessName)
{
	return ProcCtrl.IsProcessRunning(StrCtrl.AnsiStringToWideString(szProcessName));
}

bool ProcCtrl_API::SetProcessPriority(char* szProcName, DWORD dwPriority)
{
	return ProcCtrl.SetProcessPriority(StrCtrl.AnsiStringToWideString(szProcName), dwPriority);
}

bool ProcCtrl_API::MonitorProcessResources(char * szProcName, PROCESS_RESOURCE_USAGE* usage)
{
	return ProcCtrl.MonitorProcessResources(StrCtrl.AnsiStringToWideString(szProcName), *usage);
}
