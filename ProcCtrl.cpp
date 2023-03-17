#include "ProcCtrl.h"

CProcCtrl ProcCtrl;

CProcCtrl::CProcCtrl() {
    m_hSnapShot = NULL;
    memset(&m_pe, 0, sizeof(m_pe));
}

CProcCtrl::~CProcCtrl() {}

bool CProcCtrl::StartProcess(const std::wstring& szPath) 
{
    PROCESS_INFORMATION pi = { 0 };
    STARTUPINFO si = { sizeof(si) };
    if (!CreateProcess(NULL, (LPWSTR)szPath.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) 
    {
        return false;
    }
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return true;
}

bool CProcCtrl::StopProcess(const std::wstring& szProcName) 
{
    m_hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    m_pe = { sizeof(m_pe) };
    if (Process32First(m_hSnapShot, &m_pe)) {
        do {
            if (wcscmp(m_pe.szExeFile, szProcName.c_str()) == 0) 
            {
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, m_pe.th32ProcessID);
                if (hProcess == NULL) 
                {
                    return false;
                }
                TerminateProcess(hProcess, 0);
                CloseHandle(hProcess);
                CloseHandle(m_hSnapShot);
                return true;
            }
        } while (Process32Next(m_hSnapShot, &m_pe));
    }
    CloseHandle(m_hSnapShot);
    return false;
}

bool CProcCtrl::IsProcessRunning(const std::wstring& szProcName) 
{
    m_hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    m_pe = { sizeof(m_pe) };
    if (Process32First(m_hSnapShot, &m_pe)) 
    {
        do {
            if (wcscmp(m_pe.szExeFile, szProcName.c_str()) == 0) 
            {
                CloseHandle(m_hSnapShot);
                return true;
            }
        } while (Process32Next(m_hSnapShot, &m_pe));
    }
    CloseHandle(m_hSnapShot);
    return false;
}

bool CProcCtrl::SetProcessPriority(const std::wstring& szProcName, DWORD dwPriority) 
{
    m_hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    m_pe = { sizeof(m_pe) };
    if (Process32First(m_hSnapShot, &m_pe)) 
    {
        do 
        {
            if (wcscmp(m_pe.szExeFile, szProcName.c_str()) == 0) 
            {
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_pe.th32ProcessID);
                if (hProcess == NULL) 
                {
                    return false;
                }
                SetPriorityClass(hProcess, dwPriority);
                CloseHandle(hProcess);
                CloseHandle(m_hSnapShot);
                return true;
            }
        } while (Process32Next(m_hSnapShot, &m_pe));
    }

    CloseHandle(m_hSnapShot);
    return false;
}

bool CProcCtrl::MonitorProcessResources(const std::wstring& szProcName, PROCESS_RESOURCE_USAGE& usage) 
{
    m_hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    m_pe = { sizeof(m_pe) };
    if (Process32First(m_hSnapShot, &m_pe)) {
        do {
            if (wcscmp(m_pe.szExeFile, szProcName.c_str()) == 0) {
                HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, m_pe.th32ProcessID);

                if (hProcess == NULL) 
                {
                    return false;
                }

                PROCESS_MEMORY_COUNTERS pmc;
                ZeroMemory(&pmc, sizeof(pmc));
                pmc.cb = sizeof(pmc);

                if (!GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) 
                {
                    CloseHandle(hProcess);
                    return false;
                }

                usage.workingSetSize = pmc.WorkingSetSize / 1024;
                usage.quotaPagedPoolUsage = pmc.QuotaPagedPoolUsage / 1024;
                usage.quotaNonPagedPoolUsage = pmc.QuotaNonPagedPoolUsage / 1024;
                usage.pagefileUsage = pmc.PagefileUsage / 1024;

                CloseHandle(hProcess);
                CloseHandle(m_hSnapShot);
                return true;
            }
        } while (Process32Next(m_hSnapShot, &m_pe));
    }
    CloseHandle(m_hSnapShot);
    return false;
}
