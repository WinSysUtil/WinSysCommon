# WinSysCommon
[![MSBuild](https://github.com/WinSysUtil/WinSysCommon/actions/workflows/msbuild.yml/badge.svg)](https://github.com/WinSysUtil/WinSysCommon/actions/workflows/msbuild.yml)

Windows 운영체제에서 파일 및 시스템 정보를 관리하기 위한 API를 제공합니다.


## 지원 기능

- [X] 레지스트리 제어
- [X] 파일시스템 제어
- [X] 윈도우시스템 제어
- [X] 프로세스 제어
- [X] 서비스 제어
- [X] 문자열 제어


## API 상세설명

### Registry Controkl API (RegCtrl_API)

- `GetRegistry` : 레지스트리 값을 가져옵니다.
- `SetRegistry` : 레지스트리 값을 설정합니다.
- `DeleteRegistry` : 레지스트리 값을 삭제합니다.

### File Control API (FileCtrl_API)

- `CreateDirectory` : 디렉토리를 생성합니다.
- `FileExist` : 파일의 존재 여부를 확인합니다.
- `GetType` : 파일의 타입을 확인합니다.
- `CopyFile` : 파일을 복사합니다.
- `GetFiles` : 디렉토리 내 모든 파일을 가져옵니다.

### System Control API (SysCtrl_API)

- `GetEnviroment` : 시스템 환경 변수 값을 가져옵니다.
- `SetEnviroment` : 시스템 환경 변수 값을 설정합니다.
- `GetSystemTimeEx` : 시스템 시간을 가져옵니다.

### Process Control API (ProcCtrl_API)

- `StartProcess` : 프로세스를 실행합니다.
- `StopProcess` : 프로세스를 중지합니다.
- `IsProcessRunning` : 프로세스가 실행 중인지 확인합니다.
- `SetProcessPriority` : 프로세스 우선순위를 설정합니다.
- `MonitorProcessResources` : 프로세스의 자원 사용량을 모니터링합니다.
- `IsProcessElevated` : 현재 프로세스가 관리자 권한을 갖는지 확인합니다.

### Service Control API (ServiceCtrl_API)

- `Create` : 서비스를 생성합니다.
- `Start` : 서비스를 시작합니다.
- `Stop` : 서비스를 중지합니다.
- `Restart` : 서비스를 재시작합니다.
- `Delete` : 서비스를 삭제합니다.

### String Control API (StrCtrl_API)

- `AnsiStringToWideString` : ANSI 문자열을 UNICODE 문자열로 변환합니다.
- `WideStringToAnsiString` : UNICODE 문자열을 ANSI 문자열로 변환합니다.


