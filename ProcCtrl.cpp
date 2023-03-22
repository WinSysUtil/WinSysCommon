#include "ProcCtrl.h"

CProcCtrl ProcCtrl;

CProcCtrl::CProcCtrl() {
    m_hSnapShot = NULL;
    memset(&m_pe, 0, sizeof(m_pe));
}

CProcCtrl::~CProcCtrl() {}

bool CProcCtrl::StartProcess(const std::wstring& szPath, DWORD& dwPid) 
{
    PROCESS_INFORMATION pi = { 0 };
    STARTUPINFO si = { sizeof(si) };
    if (!CreateProcess(NULL, (LPWSTR)szPath.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) 
    {
        return false;
    }

    dwPid = pi.dwProcessId;

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

bool CProcCtrl::IsProcessRunning(const std::wstring& szProcName, DWORD& dwPID)
{
    m_hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    m_pe = { sizeof(m_pe) };
    if (Process32First(m_hSnapShot, &m_pe)) 
    {
        do {
            if (wcscmp(m_pe.szExeFile, szProcName.c_str()) == 0) 
            {
                dwPID = m_pe.th32ProcessID;
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

int CProcCtrl::InjectDLL(const std::wstring& wstrDllPath, DWORD dwPID)
{
    int nRet = ERROR_SUCCESS;
    std::wstring wstrDllName = wstrDllPath.substr(wstrDllPath.rfind(L"\\") + 1);
    if (true == IsInjected(wstrDllName, dwPID))
        return nRet;

    // 대상 프로세스 핸들
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);


    // LoadLibraryA 이므로 ANSI 타입으로 처리해줘야함.
    auto strDllPath = StrCtrl.WideStringToAnsiString(wstrDllPath);

    // LoadLibraryA 함수 주소 가져오기
    LPVOID loadLibraryAddress = (LPVOID)GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "LoadLibraryA");

    // DLL 경로를 대상 프로세스 메모리에 쓰기
    LPVOID dllAddress = VirtualAllocEx(hProcess, NULL, strDllPath.length() + 1, MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(hProcess, dllAddress, strDllPath.c_str(), strDllPath.length() + 1, NULL);

    // 쓰여진 DLL 경로를 LoadLibraryA 함수 주소로 전달하여 DLL Injection 수행
    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddress, dllAddress, 0, NULL);

    // 인젝션에 실패한 경우
    if (hThread == NULL)
    {
        nRet = ERROR_INVALID_PARAMETER;
    }

    // 핸들과 메모리 해제
    CloseHandle(hProcess);
    VirtualFreeEx(hProcess, dllAddress, strDllPath.length() + 1, MEM_RELEASE);

    return nRet;
}

bool CProcCtrl::IsInjected(const std::wstring& wstrDllPath, DWORD dwPID)
{
    m_hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
    if (m_hSnapShot == INVALID_HANDLE_VALUE) {
        return false;
    }

    MODULEENTRY32 me32 = { sizeof(me32) };
    if (!Module32First(m_hSnapShot, &me32)) {
        CloseHandle(m_hSnapShot);
        return false;
    }

    do {
        if (wstrDllPath.compare(me32.szModule) == 0) {
            CloseHandle(m_hSnapShot);
            return true;
        }
    } while (Module32Next(m_hSnapShot, &me32));

    CloseHandle(m_hSnapShot);
    return false;
}