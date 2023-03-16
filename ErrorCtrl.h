#pragma once
#include <Windows.h>
#pragma hdrstop

class CErrorCtrl
{
public:
	DWORD GetLastError();

protected:
	DWORD m_dwErr;
	void SetLastError(DWORD code);
};

