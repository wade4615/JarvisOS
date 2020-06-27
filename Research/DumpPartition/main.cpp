//**********************************************************
//** DumpPartition copyright (c) 2020 Christopher D. Wade **
//** File: Main.cpp                                      **
//**********************************************************
#include "main.h"

void exitWithLastError(TCHAR *format, ...) {
    LPVOID lpMsgBuf;
    DWORD lastError = GetLastError();

    va_list args;
    va_start(args, format);

    if (lastError) {
        FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS, NULL, lastError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL);
        _ftprintf(stderr, _T("\n"));
        _vftprintf(stderr, format, args);
        _ftprintf(stderr, _T("GetLastError()=%d: %s\n"), lastError, lpMsgBuf);
    } else {
        _ftprintf(stderr, _T("\n"));
        _vftprintf(stderr, format, args);
    }
    va_end(args);
    LocalFree(lpMsgBuf);
    exit(lastError);
}

HANDLE openVolume(TCHAR *VolumeName) {
    DWORD read;

    HANDLE VolumeHandle = CreateFile(VolumeName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, NULL);
    if (VolumeHandle == INVALID_HANDLE_VALUE) {
        exitWithLastError(_T("Failed opening the volume '%s'\n"), VolumeName);
    }
    return VolumeHandle;
}

void readAndPrintNTFSBootSector(HANDLE VolumeHandle, ULONGLONG offset, int i) {
    NTFSBootSector bootSector;
    DWORD read;

    seek(VolumeHandle, offset, FILE_BEGIN);
    ReadFile(VolumeHandle, &bootSector, sizeof bootSector, &read, NULL);
    if (read != sizeof bootSector) {
        exitWithLastError(_T("Failed to read boot sector (%lx)\n"), GetLastError());
    }
    _tprintf(_T("\nBoot sector for partition %d\n"), i);
    printNTFSBootSector(&bootSector);
}

void readAndPrintFAT32BootSector(HANDLE VolumeHandle, ULONGLONG offset, int i) {
    FAT32BootSector bootSector;
    DWORD read;

    seek(VolumeHandle, offset, FILE_BEGIN);
    ReadFile(VolumeHandle, &bootSector, sizeof(bootSector), &read, NULL);
    if (read != sizeof(bootSector)) {
        exitWithLastError(_T("Failed to read fat32 boot sector (bytes=%d) (%lx)\n"), sizeof(bootSector), GetLastError());
    }
    _tprintf(_T("\nBoot sector for partition %d\n"), i);
    printFAT32BootSector(&bootSector);
}

void readAndPrintMasterBootSector(HANDLE VolumeHandle, ULONGLONG offset, int i) {
    MasterBootRecord bootSector1;
    DWORD read;

    seek(VolumeHandle, offset, FILE_BEGIN);
    ReadFile(VolumeHandle, &bootSector1, sizeof bootSector1, &read, NULL);
    if (read != sizeof bootSector1) {
        exitWithLastError(_T("Failed to read boot sector (%lx)\n"), GetLastError());
    }
    _tprintf(_T("\nBoot sector for partition %d\n"), i);
    handleMasterBootRecord(VolumeHandle, offset, _T("Extended Partition Master Boot Record"), &bootSector1);
}

void handleMasterBootRecord(HANDLE VolumeHandle, ULONGLONG start, TCHAR *text, MasterBootRecordPtr mbr) {
    for (int i = 0; i <= 3; i++) {
        printMasterBootRecord(text, &mbr->partionTable[i], i);
        ULONGLONG offset = start + mbr->partionTable[i].lbaStart * 512LL;
        if (mbr->partionTable[i].fileSystem == 0x07) {
            readAndPrintNTFSBootSector(VolumeHandle, offset, i);
        } else if (mbr->partionTable[i].fileSystem == 0x0C) {
            readAndPrintFAT32BootSector(VolumeHandle, offset, i);
        } else if (mbr->partionTable[i].fileSystem == 0x05) {
            readAndPrintMasterBootSector(VolumeHandle, offset, i);
        }
    }
}

void dumpDrive(TCHAR *VolumeName) {
    HANDLE VolumeHandle;
    MasterBootRecord partitionData;
    DWORD read;

    VolumeHandle = openVolume(VolumeName);
    seek(VolumeHandle, 0, FILE_BEGIN);
    ReadFile(VolumeHandle, &partitionData, sizeof partitionData, &read, NULL);
    if (read != sizeof partitionData) {
        exitWithLastError(_T("read in %ld instead of %d in dumpDrive (%lx)\n"), read, sizeof partitionData, GetLastError());
    }
    _tprintf(_T("\nVolume %s\n"), VolumeName);
    handleMasterBootRecord(VolumeHandle, 0, (TCHAR*) _T("Master Boot Record Partition Number:"), &partitionData);
    CloseHandle(VolumeHandle);
}

int _tmain(int argc, const TCHAR *argv[]) {
    _tsetlocale(LC_NUMERIC, _T(""));
    dumpDrive(_T("\\\\.\\PhysicalDrive0"));
    dumpDrive(_T("\\\\.\\PhysicalDrive1"));
    dumpDrive(_T("\\\\.\\PhysicalDrive2"));
    dumpDrive(_T("\\\\.\\PhysicalDrive3"));
    dumpDrive(_T("\\\\.\\PhysicalDrive4"));
    return 0;
}
