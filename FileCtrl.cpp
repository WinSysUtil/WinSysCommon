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
	return CreateDirectory(wstrPath);
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
	return FileExists(wstrPath);
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

BOOL CFileCtrl::RemoveFile(std::wstring wstrPath)
{
	return RemoveFile(StrCtrl.WideStringToAnsiString(wstrPath));
}

BOOL CFileCtrl::RemoveFile(std::string wstrPath)
{
	return fs::remove(wstrPath);
}

BOOL CFileCtrl::FileVersion(std::string& strPath, std::string& version)
{
	std::wstring wstrPath = StrCtrl.AnsiStringToWideString(strPath);
	std::wstring wstrVersion;
	BOOL nRet = FileVersion(wstrPath, wstrVersion);
	if (TRUE == nRet)
		version.assign(wstrVersion.begin(), wstrVersion.end());
	

	return nRet;
}

BOOL CFileCtrl::FileVersion(std::wstring& strPath, std::wstring& version)
{
	DWORD  verHandle = 0;
	UINT   size = 0;
	LPBYTE lpBuffer = NULL;
	DWORD  verSize = GetFileVersionInfoSize(strPath.c_str(), &verHandle);

	BOOL nRet = FALSE;

	if (verSize != NULL)
	{
		LPSTR verData = new char[verSize];

		if (GetFileVersionInfo(strPath.c_str(), verHandle, verSize, verData))
		{
			if (VerQueryValue(verData, L"\\", (VOID FAR * FAR*) & lpBuffer, &size))
			{
				if (size)
				{
					VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)lpBuffer;
					if (verInfo->dwSignature == 0xfeef04bd)
					{
						int major = (verInfo->dwFileVersionMS >> 16) & 0xffff;
						int minor = (verInfo->dwFileVersionMS >> 0) & 0xffff;
						int build = (verInfo->dwFileVersionLS >> 16) & 0xffff;
						int revision = (verInfo->dwFileVersionLS >> 0) & 0xffff;

						version = std::format(L"{}.{}.{}.{}", major, minor, build, revision);

						nRet = TRUE;
					}
				}
			}
		}

		delete[] verData;
	}

	return nRet;
}

BOOL CFileCtrl::Is64BitFile(std::string& strPath)
{
	bool is64Bit = false;

	try {
		// 파일 정보 가져오기
		std::filesystem::path file(strPath);
		std::filesystem::file_status status = std::filesystem::status(file);

		// 파일이 regular 파일인 경우에만 처리
		if (std::filesystem::is_regular_file(status))
		{
			// 파일 크기 확인
			uintmax_t fileSize = std::filesystem::file_size(file);

			// PE 파일 헤더 크기 확인
			if (fileSize >= sizeof(IMAGE_DOS_HEADER) + sizeof(IMAGE_NT_HEADERS32) &&
				fileSize >= sizeof(IMAGE_DOS_HEADER) + sizeof(IMAGE_NT_HEADERS64))
			{
				// PE 파일 헤더 읽기
				std::ifstream fileStream(file, std::ios::binary);
				IMAGE_DOS_HEADER dosHeader;
				IMAGE_NT_HEADERS32 ntHeader32;
				IMAGE_NT_HEADERS64 ntHeader64;
				fileStream.read(reinterpret_cast<char*>(&dosHeader), sizeof(IMAGE_DOS_HEADER));
				fileStream.read(reinterpret_cast<char*>(&ntHeader32), sizeof(IMAGE_NT_HEADERS32));
				if (ntHeader32.OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC)
				{
					// 32-bit 파일
					is64Bit = false;
				}
				else
				{
					fileStream.seekg(std::ios::beg);
					fileStream.read(reinterpret_cast<char*>(&ntHeader64), sizeof(IMAGE_NT_HEADERS64));
					if (ntHeader64.OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
					{
						// 64-bit 파일
						is64Bit = true;
					}
				}
				fileStream.close();
			}
		}
	}
	catch (const std::filesystem::filesystem_error& ex)
	{
	
	}

	return is64Bit;
}
