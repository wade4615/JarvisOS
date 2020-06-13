//**********************************************************
//** DumpPartition copyright (c) 2020 Christopher D. Wade **
//** File: FileIO.cpp                                      **
//**********************************************************
#include "main.h"

LONGLONG seek(HANDLE fileHandle, LONGLONG distance, DWORD MoveMethod) {
    LARGE_INTEGER li;
    li.QuadPart = distance;
    li.LowPart = SetFilePointer(fileHandle, li.LowPart, &li.HighPart, MoveMethod);
    if (li.LowPart == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR) {
        li.QuadPart = -1;
    }

    return li.QuadPart;
}
