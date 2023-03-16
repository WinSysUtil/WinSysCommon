#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <filesystem>
#pragma hdrstop

#include "StrCtrl.h"
#include "ErrorCtrl.h"


#ifdef CreateDirectory
#undef CreateDirectory
#endif

#ifdef CopyFile
#undef CopyFile
#endif

class CFileCtrl;
extern CFileCtrl FileCtrl;

typedef enum eFileType {
	kNone = 0,
	kFile,
	kDirectory
} FileType;

class CFileCtrl : protected CErrorCtrl, protected CStrCtrl
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
	
};

