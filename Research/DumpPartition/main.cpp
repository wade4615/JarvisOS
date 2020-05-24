#include "main.h"

void readAndPrintNTFSBootSector(HANDLE VolumeHandle, ULONGLONG offset){
    NTFSBootSector bootSector;
    DWORD read;

    seek(VolumeHandle, offset, FILE_BEGIN);
    ReadFile(VolumeHandle, &bootSector, sizeof bootSector, &read, NULL);
    if (read != sizeof bootSector) {
        _ftprintf(stderr, _T("Failed to read boot sector (%lx)\n"), GetLastError());
        exit(1);
    }
    printBootSector(&bootSector);
}

void readBootSectors(HANDLE VolumeHandle, MasterBootRecordPtr mbr){
    DWORD read;

    _tprintf(_T("\n"));
    for (int i=0; i<=3; i++){
        ULONGLONG beginByteOffset = (ULONGLONG)mbr->partionTable[i].lbaStart*512LL;
        if (mbr->partionTable[i].fileSystem==0x07){
            _tprintf(_T("\nBoot Sector for Partition Number: %d\n"), i);
            readAndPrintNTFSBootSector(VolumeHandle, beginByteOffset);
        }else if (mbr->partionTable[i].fileSystem==0x05){
            _tprintf(_T("\nBoot Sector for Extended Partition Number: %d\n"), i);
            readAndPrintExtendedPartion(VolumeHandle, beginByteOffset, _T("Extended Partition Number:"));
        }
    }
}

void readAndPrintExtendedPartion(HANDLE VolumeHandle, ULONGLONG offset, TCHAR * header){
    MasterBootRecord partitionData;
    DWORD read;

    seek(VolumeHandle, offset, FILE_BEGIN);
    ReadFile(VolumeHandle, &partitionData, sizeof partitionData, &read, NULL);
    if (read != sizeof partitionData) {
        _ftprintf(stderr, _T("read in %ld instead of %d in readAndPrintPartition (%lx)\n"), read, sizeof partitionData, GetLastError());
        exit(1);
    }
    printMasterBootRecord(header, &partitionData);
//    seek(VolumeHandle, offset, FILE_BEGIN);
//    readBootSectors(VolumeHandle, &partitionData);
}

void readAndPrintPartion(HANDLE VolumeHandle, ULONGLONG offset, TCHAR * header){
    MasterBootRecord partitionData;
    DWORD read;

    ReadFile(VolumeHandle, &partitionData, sizeof partitionData, &read, NULL);
    if (read != sizeof partitionData) {
        _ftprintf(stderr, _T("read in %ld instead of %d in readAndPrintPartion (%lx)\n"), read, sizeof partitionData, GetLastError());
        exit(1);
    }
    printMasterBootRecord(header, &partitionData);
    seek(VolumeHandle, offset, FILE_BEGIN);
    readBootSectors(VolumeHandle, &partitionData);
}

int __cdecl _tmain(int argc, const TCHAR *argv[]) {
    TCHAR VolumeName[] = _T("\\\\.\\PhysicalDrive0");

    HANDLE VolumeHandle;

    _tsetlocale(LC_NUMERIC, _T(""));

    VolumeHandle = CreateFile(VolumeName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, NULL);
    if (VolumeHandle == INVALID_HANDLE_VALUE) {
        _ftprintf(stderr, _T("Failed opening the volume '%s' (%lx)\n"), VolumeName, GetLastError());
        return 1;
    }
    readAndPrintPartion(VolumeHandle, 0, _T("Partition Number:"));
    CloseHandle(VolumeHandle);

    return 0;
}
