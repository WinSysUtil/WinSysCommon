#include "CommonAPI.h"

BOOL CreateDirectory(char* strPath)
{
	return FileCtrl.CreateDirectory(strPath);
}

BOOL FileExist(char* strPath)
{
	return FileCtrl.FileExists(strPath);
}

FileType GetType(char* strPath)
{
	return FileCtrl.GetType(strPath);
}

BOOL CopyFile(char* strSrc, char* strDst)
{
	return FileCtrl.CopyFile(strSrc, strDst);
}

BOOL GetFiles(char* strSrc, std::vector<std::string>* files)
{
	return FileCtrl.GetFiles(strSrc, files);
}
