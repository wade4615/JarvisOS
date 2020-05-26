//==================================
// PEDUMP - Matt Pietrek 1994-1998
// FILE: PEDUMP.C
//==================================
#include "pedump.h"

void DumpExeFile(PIMAGE_DOS_HEADER dosHeader){
    ULONGLONG base = (ULONGLONG)dosHeader;
    PIMAGE_NT_HEADERS pNTHeader = MakePtr(PIMAGE_NT_HEADERS, dosHeader, dosHeader->e_lfanew);
    if (pNTHeader->Signature != IMAGE_NT_SIGNATURE) {
        exitWithLastError("Not a Portable Executable (PE) EXE\n");
        return;
    }
}
