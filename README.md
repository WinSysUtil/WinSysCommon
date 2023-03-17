# WinSysCommon
[![MSBuild](https://github.com/WinSysUtil/WinSysCommon/actions/workflows/msbuild.yml/badge.svg)](https://github.com/WinSysUtil/WinSysCommon/actions/workflows/msbuild.yml)

Windows 운영체제에서 파일 및 시스템 정보를 관리하기 위한 API를 제공합니다.


## 지원 기능
- 레지스트리
- 파일 시스템


## API 상세설명
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

### String Control API (StrCtrl_API)

- `AnsiStringToWideString` : ANSI 문자열을 UNICODE 문자열로 변환합니다.
- `WideStringToAnsiString` : UNICODE 문자열을 ANSI 문자열로 변환합니다.
