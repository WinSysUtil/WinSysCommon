#pragma once
#include <Windows.h>
#pragma hdrstop


/**
 * 프로세스 리소스 사용량 체크시 사용되는 구조체.
 */
typedef struct _PROCESS_RESOURCE_USAGE {
    DWORD workingSetSize;
    DWORD quotaPagedPoolUsage;
    DWORD quotaNonPagedPoolUsage;
    DWORD pagefileUsage;
} PROCESS_RESOURCE_USAGE, * PPROCESS_RESOURCE_USAGE;


/**
 * 파일 타입을 갖는 Enum.
 */
typedef enum eFileType {
    kNone = 0,
    kFile,
    kDirectory
} FileType;
