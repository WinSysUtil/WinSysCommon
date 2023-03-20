#include "ServiceCtrl.h"

CServiceCtrl ServiceCtrl;

CServiceCtrl::CServiceCtrl() {
    serviceHandle = NULL;
}

bool CServiceCtrl::Create(char* serviceName, char* displayName, char* binPath) {
    SC_HANDLE scmHandle = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
    if (scmHandle == NULL) {
        return false;
    }
    serviceHandle = CreateServiceA(scmHandle,
        serviceName,
        displayName,
        SERVICE_ALL_ACCESS,
        SERVICE_WIN32_OWN_PROCESS,
        SERVICE_AUTO_START,
        SERVICE_ERROR_NORMAL,
        binPath,
        NULL, NULL, NULL, NULL, NULL);
    CloseServiceHandle(scmHandle);
    if (serviceHandle == NULL) {
        return false;
    }

    SERVICE_SID_INFO serviceSidInfo = { 0 };
    serviceSidInfo.dwServiceSidType = SERVICE_SID_TYPE_UNRESTRICTED;
    if (!ChangeServiceConfig(serviceHandle, SERVICE_NO_CHANGE, SERVICE_NO_CHANGE, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL)) {
        return false;
    }

    return true;
}

bool CServiceCtrl::IsRunning(char* serviceName) {
    bool result = false;
    SC_HANDLE scmHandle = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if (scmHandle == NULL) {
        return false;
    }

    SC_HANDLE serviceHandle = OpenService(scmHandle, StrCtrl.AnsiStringToWideString(serviceName).c_str(), SERVICE_QUERY_STATUS);
    if (serviceHandle == NULL) {
        CloseServiceHandle(scmHandle);
        return false;
    }

    SERVICE_STATUS serviceStatus;
    if (QueryServiceStatus(serviceHandle, &serviceStatus)) {
        result = (serviceStatus.dwCurrentState == SERVICE_RUNNING);
    }

    CloseServiceHandle(serviceHandle);
    CloseServiceHandle(scmHandle);
    return result;
}

bool CServiceCtrl::Start(char* serviceName, bool force_admin) {
    std::wstring wstrServiceName = StrCtrl.AnsiStringToWideString(serviceName);
    if (force_admin) {
        // 관리자 권한으로 실행하기 위해 ShellExecute 함수를 사용합니다.
        SHELLEXECUTEINFO sei = { sizeof(sei) };
        sei.lpVerb = L"runas";
        sei.lpFile = wstrServiceName.c_str();
        sei.nShow = SW_SHOW;
        if (!ShellExecuteEx(&sei)) {
            return false;
        }
        return true;
    }
    else {
        serviceHandle = OpenService(NULL, wstrServiceName.c_str(), SERVICE_ALL_ACCESS);
        if (serviceHandle == NULL) {
            return false;
        }
        if (!StartService(serviceHandle, 0, NULL)) {
            return false;
        }
        return true;
    }
}

bool CServiceCtrl::Stop(char* serviceName) {
    serviceHandle = OpenServiceA(NULL, serviceName, SERVICE_ALL_ACCESS);
    if (serviceHandle == NULL) {
        return false;
    }
    SERVICE_STATUS status;
    if (!ControlService(serviceHandle, SERVICE_CONTROL_STOP, &status)) {
        return false;
    }
    return true;
}

bool CServiceCtrl::Restart(char* serviceName) {
    if (!Stop(serviceName)) {
        return false;
    }
    return Start(serviceName);
}

bool CServiceCtrl::Delete(char* serviceName) {
    serviceHandle = OpenServiceA(NULL, serviceName, SERVICE_ALL_ACCESS);
    if (serviceHandle == NULL) {
        return false;
    }
    if (!DeleteService(serviceHandle)) {
        return false;
    }
    CloseServiceHandle(serviceHandle);
    return true;
}

/*
* Example Code
int main() {
    CServiceCtrl service;
    const char* serviceName = "MyService";
    const char* displayName = "My Service";
    const char* binPath = "C:\\MyService\\MyService.exe";

    if (service.Create(serviceName, displayName, binPath)) {
        std::cout << "Service created successfully!" << std::endl;
    } else {
        std::cout << "Failed to create service!" << std::endl;
    }

    if (service.Start(serviceName)) {
        std::cout << "Service started successfully!" << std::endl;
    } else {
        std::cout << "Failed to start service!" << std::endl;
    }

    if (service.Stop(serviceName)) {
        std::cout << "Service stopped successfully!" << std::endl;
    } else {
        std::cout << "Failed to stop service!" << std::endl;
    }

    if (service.Restart(serviceName)) {
        std::cout << "Service restarted successfully!" << std::endl;
    } else {
        std::cout << "Failed to restart service!" << std::endl;
    }

    if (service.Delete(serviceName)) {
        std::cout << "Service deleted successfully!" << std::endl;
    } else {
        std::cout << "Failed to delete service!" << std::endl;
    }
    return 0;
}

*/