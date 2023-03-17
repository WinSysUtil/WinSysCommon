#pragma once
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#pragma hdrstop

#include "StrCtrl.h"
#include "ErrorCtrl.h"

class CSysCtrl;
extern CSysCtrl SysCtrl;

class CSysCtrl : protected CErrorCtrl
{
public:
	CSysCtrl();
	virtual ~CSysCtrl();

public:
	BOOL GetEnviroment(std::string key, std::string& value);
	BOOL GetEnviroment(std::wstring key, std::wstring& value);
	BOOL SetEnviroment(std::string key, std::string value);
	BOOL SetEnviroment(std::wstring key, std::wstring value);

	BOOL GetSystemTime(std::string & strTime);
};

