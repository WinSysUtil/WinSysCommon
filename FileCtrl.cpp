#include "FileCtrl.h"

namespace fs = std::filesystem;

CFileCtrl FileCtrl;

CFileCtrl::CFileCtrl()
{
}

CFileCtrl::~CFileCtrl()
{
}


BOOL CFileCtrl::CreateDirectory(std::string strPath)
{
	auto wstrPath = StrCtrl.AnsiStringToWideString(strPath);
	return CreateDirectory(strPath);
}

BOOL CFileCtrl::CreateDirectory(std::wstring strPath)
{
	BOOL ret = fs::create_directories(strPath);
	if (FALSE == ret)
	{
		DWORD dwErr = ::GetLastError();
		SetLastError(dwErr);
	}

	return ret;
}

BOOL CFileCtrl::FileExists(std::string strPath)
{
	auto wstrPath = StrCtrl.AnsiStringToWideString(strPath);
	return FileExists(strPath);
}

BOOL CFileCtrl::FileExists(std::wstring strPath)
{
	return fs::exists(strPath);
}

FileType CFileCtrl::GetType(std::string strPath)
{
	auto wstrPath = StrCtrl.AnsiStringToWideString(strPath);
	return GetType(wstrPath);
}

FileType CFileCtrl::GetType(std::wstring strPath)
{
	FileType type = kNone;
	if (fs::exists(strPath) == TRUE)
	{
		if (fs::is_directory(strPath) == TRUE)
			type = FileType::kDirectory;
		else
			type = FileType::kFile;
	}

	return type;
}

BOOL CFileCtrl::CopyFile(std::string strSrc, std::string strDst)
{
	return CopyFile(StrCtrl.AnsiStringToWideString(strSrc), StrCtrl.AnsiStringToWideString(strDst));
}

BOOL CFileCtrl::CopyFile(std::wstring wstrSrc, std::wstring wstrDst)
{
	BOOL ret = FALSE;
	
	if (TRUE == FileExists(wstrSrc))
		ret = fs::copy_file(wstrSrc, wstrDst);

	if (FALSE == ret)
	{
		DWORD dwErr = ::GetLastError();
		SetLastError(dwErr);
	}

	return ret;
}

BOOL CFileCtrl::GetFiles(std::string strPath, std::vector<std::string>* files)
{
	std::vector<std::wstring> tmpFiles;
	BOOL ret = FALSE;
	ret = GetFiles(std::wstring(strPath.begin(), strPath.end()), &tmpFiles);
	if (TRUE == ret)
	{
		for (auto& file : tmpFiles)
			files->push_back(std::string(file.begin(), file.end()));
		
	}

	return ret;
}

BOOL CFileCtrl::GetFiles(std::wstring strPath, std::vector<std::wstring>* files)
{
	BOOL ret = FALSE;
	if (nullptr != files && FileType::kDirectory == GetType(strPath))
	{
		for (const auto& entry : fs::directory_iterator(strPath)) 
			files->push_back(entry.path());
		ret = TRUE;
	}


	return ret;
}
