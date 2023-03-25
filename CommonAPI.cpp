#include <memory>

#include "FileCtrl.h"
#include "SysCtrl.h"
#include "ProcCtrl.h"
#include "RegCtrl.h"
#include "ServiceCtrl.h"
#include "CommonAPI.h"


// =============================================================================================== //
// Registry Control API
// =============================================================================================== //

bool RegCtrl_API::GetRegistryA(HKEY hKey, const char* subKey, const char* valueName, char* pBuf, int nLenBuf)
{
	std::string strData;
	bool ret = false;
	if (true == RegCtrl.GetRegistry(hKey, subKey, valueName, strData))
	{
		if (0 == strncpy_s(pBuf, nLenBuf, strData.c_str(), strData.length()))
		{
			ret = true;
		}
	}

	return ret;
}

bool RegCtrl_API::GetRegistryW(HKEY hKey, const wchar_t* subKey, const wchar_t* valueName, wchar_t* pBuf, int nLenBuf)
{
	std::wstring wstrData;
	bool ret = false;
	if (true == RegCtrl.GetRegistry(hKey, subKey, valueName, wstrData))
	{
		if (0 == wcsncpy_s(pBuf, nLenBuf, wstrData.c_str(), wstrData.length()))
		{
			ret = true;
		}
	}

	return ret;
}

bool RegCtrl_API::SetRegistryA(HKEY hKey, const char * subKey, const char* valueName, const char* data)
{
	return RegCtrl.SetRegistry(hKey, subKey, valueName, data);
}

bool RegCtrl_API::SetRegistryW(HKEY hKey, const wchar_t* subKey, const wchar_t* valueName, const wchar_t* data)
{
	return RegCtrl.SetRegistry(hKey, subKey, valueName, data);
}

bool RegCtrl_API::DeleteRegistryA(HKEY hKey, const char* subKey, const char* valueName)
{
	return RegCtrl.DeleteRegistry(hKey, subKey, valueName);
}

bool RegCtrl_API::DeleteRegistryW(HKEY hKey, const wchar_t* subKey, const wchar_t* valueName)
{
	return RegCtrl.DeleteRegistry(hKey, subKey, valueName);
}

// =============================================================================================== //
// File Control API
// =============================================================================================== //

BOOL FileCtrl_API::CreateDirectory(const char* strPath)
{
	return FileCtrl.CreateDirectory(strPath);
}

BOOL FileCtrl_API::FileExist(const char* strPath)
{
	return FileCtrl.FileExists(strPath);
}

FileType FileCtrl_API::GetType(const char* strPath)
{
	return FileCtrl.GetType(strPath);
}

BOOL FileCtrl_API::RemoveFIle(const char* strPath)
{
	return FileCtrl.RemoveFile(strPath);
}

BOOL FileCtrl_API::CopyFile(const char* strSrc, const char* strDst)
{
	return FileCtrl.CopyFile(strSrc, strDst);
}

BOOL FileCtrl_API::GetFiles(const char* strSrc, std::vector<std::string>* files)
{
	return FileCtrl.GetFiles(strSrc, files);
}

BOOL FileCtrl_API::FileVersion(const char* pPath, char* pDst, int nLenDst)
{
	BOOL nRet = FALSE;

	std::string strPath(pPath);
	std::string version;
	if (FileCtrl.FileVersion(strPath, version))
	{
		if (0 == strncpy_s(const_cast<char*>(pDst), nLenDst, version.c_str(), version.length()))
			nRet = TRUE;
	}


	return nRet;
}

// =============================================================================================== //
// System Control API
// =============================================================================================== //

BOOL SysCtrl_API::GetEnviroment(const char* key, const char* pBuf, int nBufSize)
{
	BOOL ret = FALSE;

	std::string value;
	if (TRUE == SysCtrl.GetEnviroment(key, value))
	{
		strcpy_s(const_cast<char*>(pBuf), nBufSize, value.c_str());
	}


	return ret;
}

BOOL SysCtrl_API::SetEnviroment(const char* key, const char* value)
{
	BOOL ret = FALSE;
	if (TRUE == SysCtrl.SetEnviroment(key, value))
	{
		ret = TRUE;
	}

	return ret;
}

BOOL SysCtrl_API::GetSystemTimeEx(const char* pBuf, int nBufSize)
{
	BOOL ret = FALSE;
	std::string strTime;
	if (TRUE == SysCtrl.GetSystemTime(strTime))
	{
		strcpy_s(const_cast<char*>(pBuf), nBufSize, strTime.c_str());
		ret = TRUE;
	}


	return ret;
}

BOOL SysCtrl_API::IsProcessElevated()
{
	return SysCtrl.IsProcessElevated();

}

BOOL SysCtrl_API::AddStartProgram(const char* pName, const char* pBinPath)
{
	const int nLenName = strlen(pName);
	const int nLenPath = strlen(pBinPath);
	return RegCtrl.SetRegistry(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
		StrCtrl.AnsiStringToWideString(std::string(pName, pName + nLenName)),
		StrCtrl.AnsiStringToWideString(std::string(pBinPath, pBinPath + nLenPath)));
}

BOOL SysCtrl_API::DeleteStartProgram(const char* pName, int nLenName)
{
	return RegCtrl.DeleteRegistry(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
		StrCtrl.AnsiStringToWideString(std::string(pName, pName + nLenName)));
}


// =============================================================================================== //
// String Control API
// =============================================================================================== //

BOOL StrCtrl_API::AnsiStringToWideString(const char* pSrc, wchar_t* pDst, int nLenDst)
{
	BOOL ret = FALSE;
	auto wstrTemp = StrCtrl.AnsiStringToWideString(pSrc);
	if (0 == wcsncpy_s(pDst, nLenDst, wstrTemp.c_str(), wstrTemp.length()))
	{
		ret = TRUE;
	}

	return ret;
}

BOOL StrCtrl_API::WideStringToAnsiString(const wchar_t* pSrc, char* pDst, int nLenDst)
{
	BOOL ret = FALSE;
	std::wstring wstrTemp(pSrc);
	auto strTemp = StrCtrl.WideStringToAnsiString(wstrTemp);
	if (0 == strncpy_s(pDst, nLenDst, strTemp.c_str(), strTemp.length()))
	{
		ret = TRUE;
	}

	return ret;
}

int StrCtrl_API::GetStringParsing(const WCHAR* pString, const WCHAR* pDelimiter, std::vector<std::wstring>* pVecString)
{
	return StrCtrl.GetStringParsing(const_cast<wchar_t*>(pString), const_cast<wchar_t*>(pDelimiter), pVecString);
}

bool StrCtrl_API::GetRandomString(char* pBuf, int nLenBuf, int length)
{
	if (length >= nLenBuf) 
		return false;

	std::memset(pBuf, 0x00, sizeof(char) * nLenBuf);

	std::string strRand = StrCtrl.GetRandomString(length);
	if (strRand.length() == 0) 
		return false;

	if (0 == strcpy_s(pBuf, nLenBuf, strRand.c_str())) return true;


	return false;

}

// =============================================================================================== //
// Process Control API
// =============================================================================================== //

bool ProcCtrl_API::StartProcess(const char* szPath, DWORD* pPID)
{
	DWORD dwPID = 0;
	bool bRet = ProcCtrl.StartProcess(StrCtrl.AnsiStringToWideString(szPath), dwPID);
	if (bRet = true)
		(*pPID) = dwPID;
	return bRet;
}

bool ProcCtrl_API::StopProcess(const char* szProcessName)
{
	return ProcCtrl.StopProcess(StrCtrl.AnsiStringToWideString(szProcessName));

}

bool ProcCtrl_API::IsProcessRunning(const char* szProcessName, DWORD* dwPID)
{
	DWORD dwTemp = 0;
	bool nRet = ProcCtrl.IsProcessRunning(StrCtrl.AnsiStringToWideString(szProcessName), dwTemp);
	// 프로세스가 실행중이고, 매개변수 dwPID가 존재하는 경우
	if (true == nRet && nullptr != dwPID)
	{
		(*dwPID) = dwTemp;
	}

	return nRet;

}

bool ProcCtrl_API::SetProcessPriority(const char* szProcName, DWORD dwPriority)
{
	return ProcCtrl.SetProcessPriority(StrCtrl.AnsiStringToWideString(szProcName), dwPriority);
}

bool ProcCtrl_API::MonitorProcessResources(const char* szProcName, PROCESS_RESOURCE_USAGE* usage)
{
	return ProcCtrl.MonitorProcessResources(StrCtrl.AnsiStringToWideString(szProcName), *usage);
}

int ProcCtrl_API::InjectDLL(const char* pDllPath, DWORD dwPID)
{
	return ProcCtrl.InjectDLL(StrCtrl.AnsiStringToWideString(pDllPath), dwPID);
}

// =============================================================================================== //
// Service Control API
// =============================================================================================== //

bool ServiceCtrl_API::Create(const char* serviceName, const char* displayName, const char* binPath)
{
	return ServiceCtrl.Create(const_cast<char*>(serviceName), const_cast<char*>(displayName), const_cast<char*>(binPath));
}

bool ServiceCtrl_API::IsRunning(const char* serviceName)
{
	return ServiceCtrl.IsRunning(const_cast<char*>(serviceName));
}

bool ServiceCtrl_API::Start(const char* serviceName, bool force_admin)
{
	return ServiceCtrl.Start(const_cast<char*>(serviceName), force_admin);

}

bool ServiceCtrl_API::Stop(const char* serviceName)
{
	return ServiceCtrl.Stop(const_cast<char*>(serviceName));
}

bool ServiceCtrl_API::Restart(const char* serviceName)
{
	return ServiceCtrl.Restart(const_cast<char*>(serviceName));
}

bool ServiceCtrl_API::Delete(const char* serviceName)
{
	return ServiceCtrl.Stop(const_cast<char *>(serviceName));
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
