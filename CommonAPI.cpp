#include "FileCtrl.h"
#include "SysCtrl.h"
#include "ProcCtrl.h"
#include "RegCtrl.h"
#include "ServiceCtrl.h"
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

bool RegCtrl_API::DeleteRegistry(HKEY hKey, wchar_t* subKey, wchar_t* valueName)
{
	return RegCtrl.DeleteRegistry(hKey, subKey, valueName);
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

BOOL SysCtrl_API::AddStartProgram(char* pName, int nLenName, char* pBinPath, int nLenPath)
{
	return RegCtrl.SetRegistry(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
		StrCtrl.AnsiStringToWideString(std::string(pName, pName + nLenName)),
		StrCtrl.AnsiStringToWideString(std::string(pBinPath, pBinPath + nLenPath)));
}

BOOL SysCtrl_API::DeleteStartProgram(char* pName, int nLenName)
{
	return RegCtrl.DeleteRegistry(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
		StrCtrl.AnsiStringToWideString(std::string(pName, pName + nLenName)));
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

int StrCtrl_API::GetStringParsing(WCHAR* pString, WCHAR* pDelimiter, std::vector<std::wstring>* pVecString)
{
	return StrCtrl.GetStringParsing(pString, pDelimiter, pVecString);
}

// =============================================================================================== //
// Process Control API
// =============================================================================================== //

bool ProcCtrl_API::StartProcess(char* szPath, DWORD* pPID)
{
	DWORD dwPID = 0;
	bool bRet = ProcCtrl.StartProcess(StrCtrl.AnsiStringToWideString(szPath), dwPID);
	if (bRet = true)
		(*pPID) = dwPID;
	return bRet;
}

bool ProcCtrl_API::StopProcess(char* szProcessName)
{
	return ProcCtrl.StopProcess(StrCtrl.AnsiStringToWideString(szProcessName));

}

bool ProcCtrl_API::IsProcessRunning(char* szProcessName, DWORD* dwPID)
{
	DWORD dwTemp = 0;
	bool nRet =  ProcCtrl.IsProcessRunning(StrCtrl.AnsiStringToWideString(szProcessName), dwTemp);
	// 프로세스가 실행중이고, 매개변수 dwPID가 존재하는 경우
	if (true == nRet && nullptr != dwPID)
	{
		(*dwPID) = dwTemp;
	}

	return nRet;

}

bool ProcCtrl_API::SetProcessPriority(char* szProcName, DWORD dwPriority)
{
	return ProcCtrl.SetProcessPriority(StrCtrl.AnsiStringToWideString(szProcName), dwPriority);
}

bool ProcCtrl_API::MonitorProcessResources(char * szProcName, PROCESS_RESOURCE_USAGE* usage)
{
	return ProcCtrl.MonitorProcessResources(StrCtrl.AnsiStringToWideString(szProcName), *usage);
}

int ProcCtrl_API::InjectDLL(char* pDllPath, int nLenDllPath, DWORD dwPID)
{
	std::wstring wstrPath(pDllPath, pDllPath + nLenDllPath);
	return ProcCtrl.InjectDLL(wstrPath, dwPID);
}

// =============================================================================================== //
// Service Control API
// =============================================================================================== //

bool ServiceCtrl_API::Create(char* serviceName, char* displayName, char* binPath)
{
	return ServiceCtrl.Create(serviceName, displayName, binPath);
}

bool ServiceCtrl_API::IsRunning(char* serviceName)
{
	return ServiceCtrl.IsRunning(serviceName);
}

bool ServiceCtrl_API::Start(char* serviceName, bool force_admin)
{
	return ServiceCtrl.Start(serviceName, force_admin);

}

bool ServiceCtrl_API::Stop(char* serviceName)
{
	return ServiceCtrl.Stop(serviceName);
}

bool ServiceCtrl_API::Restart(char* serviceName)
{
	return ServiceCtrl.Restart(serviceName);
}

bool ServiceCtrl_API::Delete(char* serviceName)
{
	return ServiceCtrl.Stop(serviceName);
}

void DebugPrintA(const char* pModuleName, const char* pFunctionName, const int nLine, const char* format, ...)
{
	va_list argList;
	va_start(argList, format);

	// 버퍼 크기를 동적으로 할당
	int bufferSize = vsnprintf(NULL, 0, format, argList) + 1;
	char* buffer = (char*)malloc(bufferSize);

	// 다시 가변 인자 목록을 초기화
	va_end(argList);
	va_start(argList, format);

	vsnprintf(buffer, bufferSize, format, argList);

	std::string message{ std::format("[{}|{}({})] ", pModuleName, pFunctionName, nLine) };
	message.append(buffer, bufferSize);

	OutputDebugStringA(message.c_str());

	free(buffer);
	va_end(argList);
}
