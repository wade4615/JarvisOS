#include "main.h"

HANDLE openVolume(TCHAR *VolumeName){
    DWORD read;

    HANDLE VolumeHandle = CreateFile(VolumeName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, NULL);
    if (VolumeHandle == INVALID_HANDLE_VALUE) {
        _ftprintf(stderr, _T("Failed opening the volume '%s' (%lx)\n"), VolumeName, GetLastError());
        exit(1);
    }
    return VolumeHandle;
}

void readAndPrintNTFSBootSector(HANDLE VolumeHandle, ULONGLONG offset, int i){
    NTFSBootSector bootSector;
    DWORD read;

    seek(VolumeHandle, offset, FILE_BEGIN);
    ReadFile(VolumeHandle, &bootSector, sizeof bootSector, &read, NULL);
    if (read != sizeof bootSector) {
        _ftprintf(stderr, _T("Failed to read boot sector (%lx)\n"), GetLastError());
        exit(1);
    }
    _tprintf(_T("\nBoot sector for partition %d\n"), i);
    printBootSector(&bootSector);
}

void readAndPrintMasterBootSector(HANDLE VolumeHandle, ULONGLONG offset, int i){
    MasterBootRecord bootSector1;
    DWORD read;

    seek(VolumeHandle, offset, FILE_BEGIN);
    ReadFile(VolumeHandle, &bootSector1, sizeof bootSector1, &read, NULL);
    if (read != sizeof bootSector1) {
        _ftprintf(stderr, _T("Failed to read boot sector (%lx)\n"), GetLastError());
        exit(1);
    }
    _tprintf(_T("\nBoot sector for partition %d\n"), i);
    handleMasterBootRecord(VolumeHandle, offset, _T("Extended Partition Master Boot Record"), &bootSector1);
}

void handleMasterBootRecord(HANDLE VolumeHandle, ULONGLONG start, TCHAR *text, MasterBootRecordPtr mbr){
    for (int i=0; i<=3; i++){
        printMasterBootRecord(text, &mbr->partionTable[i], i);
        ULONGLONG offset = start + mbr->partionTable[i].lbaStart*512LL;
        if (mbr->partionTable[i].fileSystem == 0x07){
            readAndPrintNTFSBootSector(VolumeHandle, offset, i);
        } else if (mbr->partionTable[i].fileSystem == 0x05){
            readAndPrintMasterBootSector(VolumeHandle, offset, i);
        }
    }
}

void dumpDrive(TCHAR *VolumeName){
    HANDLE VolumeHandle;
    MasterBootRecord partitionData;
    DWORD read;

    VolumeHandle = openVolume(VolumeName);
    seek(VolumeHandle, 0, FILE_BEGIN);
    ReadFile(VolumeHandle, &partitionData, sizeof partitionData, &read, NULL);
    if (read != sizeof partitionData) {
        _ftprintf(stderr, _T("read in %ld instead of %d in readAndPrintPartition (%lx)\n"), read, sizeof partitionData, GetLastError());
        exit(1);
    }
    _tprintf(_T("\nVolume %s\n"),VolumeName);
    handleMasterBootRecord(VolumeHandle, 0, (TCHAR *)_T("Partition Number:"), &partitionData);
    CloseHandle(VolumeHandle);
}

int __cdecl _tmain(int argc, const TCHAR *argv[]) {
    _tsetlocale(LC_NUMERIC, _T(""));
    dumpDrive(_T("\\\\.\\PhysicalDrive0"));
    dumpDrive(_T("\\\\.\\PhysicalDrive1"));
    return 0;
}
