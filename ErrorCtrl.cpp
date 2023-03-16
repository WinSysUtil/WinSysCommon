#include "ErrorCtrl.h"

DWORD CErrorCtrl::GetLastError()
{
    return m_dwErr;
}

void CErrorCtrl::SetLastError(DWORD code)
{
    m_dwErr = code;
}
