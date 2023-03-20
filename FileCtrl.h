#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <filesystem>
#include <format>
#pragma comment(lib, "version.lib")
#pragma hdrstop

#include "StrCtrl.h"
#include "ErrorCtrl.h"
#include "CommonStruct.h"

#ifdef CreateDirectory
#undef CreateDirectory
#endif

#ifdef CopyFile
#undef CopyFile
#endif

class CFileCtrl;
extern CFileCtrl FileCtrl;

class CFileCtrl : protected CErrorCtrl
{
public:

public:
	CFileCtrl();
	virtual ~CFileCtrl();

public:
	
	/**
	 * 디렉토리를 생성하는 기능.
	 * 
	 * \param strPath - 생성할 디렉토리의 경로
	 * \return 성공(TRUE), 실패(FALSE)
	 */
	BOOL CreateDirectory(std::string strPath);
	/**
	 * 디렉토리를 생성하는 기능.
	 *
	 * \param strPath - 생성할 디렉토리의 경로
	 * \return 성공(TRUE), 실패(FALSE)
	 */
	BOOL CreateDirectory(std::wstring strPath);

	/**
	 * 파일의 존재 여부를 확인하는 기능.
	 * 
	 * \param strPath - 파일의 경로
	 * \return 성공(TRUE), 실패(FALSE)
	 */
	BOOL FileExists(std::string strPath);
	/**
	 * 파일의 존재 여부를 확인하는 기능.
	 *
	 * \param strPath - 파일의 경로
	 * \return 성공(TRUE), 실패(FALSE)
	 */
	BOOL FileExists(std::wstring strPath);

	/**
	 * 파일의 타입 정보를 가져오는 기능.
	 * 
	 * \param strPath - 검사할 파일의 경로
	 * \return 
	 */
	FileType GetType(std::string strPath);
	/**
	 * 파일의 타입 정보를 가져오는 기능.
	 *
	 * \param strPath - 검사할 파일의 경로
	 * \return
	 */
	FileType GetType(std::wstring strPath);

	/**
	 * 파일을 복사하는 기능.
	 * 
	 * \param strSrc - 복사할 파일의 경로
	 * \param strDst - 복사된 파일의 경로 
	 * \return 성공(TRUE), 실패(FALSE)
	 */
	BOOL CopyFile(std::string strSrc, std::string strDst);
	/**
	 * 파일을 복사하는 기능.
	 *
	 * \param strSrc - 복사할 파일의 경로
	 * \param strDst - 복사된 파일의 경로
	 * \return 성공(TRUE), 실패(FALSE)
	 */
	BOOL CopyFile(std::wstring wstrSrc, std::wstring wstrDst);

	/**
	 * 디렉토리에 파일 목록을 가져오는 기능.
	 * 
	 * \param strPath - 파일의 경로
	 * \param files - 파일을 받아올 공간
	 * \return 성공(TRUE), 실패(FALSE)
	 */
	BOOL GetFiles(std::string strPath, std::vector<std::string>* files);
	/**
	 * 디렉토리에 파일 목록을 가져오는 기능.
	 *
	 * \param strPath - 파일의 경로
	 * \param files - 파일을 받아올 공간
	 * \return 성공(TRUE), 실패(FALSE)
	 */
	BOOL GetFiles(std::wstring wstrPath, std::vector<std::wstring>* files);

	/**
	 * 파일을 삭제하는 기능.
	 * 
	 * \param wstrPath - 삭제할 파일의 경로
	 * \return 성공(TRUE), 실패(FALSE)
	 */
	BOOL RemoveFile(std::wstring wstrPath);
	/**
	 * 파일(디렉토리 구분 없이)을 삭제하는 기능.
	 *
	 * \param wstrPath - 삭제할 파일의 경로
	 * \return 성공(TRUE), 실패(FALSE)
	 */
	BOOL RemoveFile(std::string wstrPath);

	/**
	 * 파일의 버전을 얻는 기능 .
	 * 
	 * \param strPath - 버전을 얻을 파일 경로 
	 * \param version - 버전 정보가 담길 공간
	 * \return 성공(TRUE), 실패(FALSE)
	 */
	BOOL FileVersion(std::string& strPath, std::string& version);
	/**
	 * 파일의 버전을 얻는 기능 .
	 *
	 * \param strPath - 버전을 얻을 파일 경로
	 * \param version - 버전 정보가 담길 공간
	 * \return 성공(TRUE), 실패(FALSE)
	 */
	BOOL FileVersion(std::wstring& strPath, std::wstring& version);
	
};

