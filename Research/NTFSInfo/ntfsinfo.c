//**********************************************************
//** NTFSInfo copyright (c) 2020 Christopher D. Wade      **
//** File: NTFSInfo.c                                     **
//**********************************************************
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <tchar.h>
#include <shellapi.h>

#define NRH_FILE_TYPE  0x454C4946
#define ATTRIBUTE_TYPE_DATA 0x80
#define ATTRIBUTE_TYPE_END 0xFFFFFFFF

typedef struct _NTFS_RECORD_HEADER {
    ULONG Type;
    USHORT UsaOffset;
    USHORT UsaCount;
    ULONGLONG Lsn;
} NTFS_RECORD_HEADER, *PNTFS_RECORD_HEADER;

typedef struct _FILE_RECORD_HEADER {
    NTFS_RECORD_HEADER Ntfs;
    USHORT SequenceNumber;
    USHORT LinkCount;
    USHORT AttributeOffset;
    USHORT Flags;
    ULONG BytesInUse;
    ULONG BytesAllocated;
    ULONGLONG BaseFileRecord;
    USHORT NextAttributeNumber;
} FILE_RECORD_HEADER, *PFILE_RECORD_HEADER;

typedef struct _NTFS_ATTR_RECORD {
    ULONG Type;
    ULONG Length;
    UCHAR IsNonResident;
    UCHAR NameLength;
    USHORT NameOffset;
    USHORT Flags;
    USHORT Instance;
    union {
        struct {
            ULONG ValueLength;
            USHORT ValueOffset;
            UCHAR Flags;
            UCHAR Reserved;
        } Resident;
        struct {
            ULONGLONG LowestVCN;
            ULONGLONG HighestVCN;
            USHORT MappingPairsOffset;
            USHORT CompressionUnit;
            UCHAR Reserved[4];
            LONGLONG AllocatedSize;
            LONGLONG DataSize;
            LONGLONG InitializedSize;
            LONGLONG CompressedSize;
        } NonResident;
    };
} NTFS_ATTR_RECORD, *PNTFS_ATTR_RECORD;

static TCHAR *MetaDataFiles[] = { _T("$MFT\t\t"), _T("$MFTMirr\t"), _T("$LogFile\t"), _T("$Volume\t\t"), _T("$AttrDef\t"), _T("."), _T("$Bitmap\t\t"), _T("$Boot\t\t"), _T("$BadClus\t"), _T("$Quota\t\t"), _T("$UpCase\t\t"), _T("$Extended\t"),
NULL, };

#define DOT     _T('.')
#define COMMA   _T(',')
#define MAX     50

static TCHAR commas[MAX]; // Where the result is

TCHAR* addCommas(ULONGLONG f) {
    TCHAR tmp[MAX];            // temp area
    _stprintf(tmp, _T("%I64u"), f);    // refine %f if you need
    TCHAR *dot = _tcschr(tmp, DOT); // do we have a DOT?
    TCHAR *src, *dst; // source, dest

    if (dot) {            // Yes
        dst = commas + MAX - _tcslen(dot) - 1; // set dest to allow the fractional part to fit
        strcpy(dst, dot);               // copy that part
        *dot = 0;       // 'cut' that frac part in tmp
        src = --dot;    // point to last non frac char in tmp
        dst--;          // point to previous 'free' char in dest
    } else {                // No
        src = tmp + _tcslen(tmp) - 1;    // src is last char of our float string
        dst = commas + MAX - 1;         // dst is last char of commas
    }

    int len = strlen(tmp);        // len is the mantissa size
    int cnt = 0;                  // char counter

    do {
        if (*src <= '9' && *src >= '0') {  // add comma is we added 3 digits already
            if (cnt && !(cnt % 3))
                *dst-- = COMMA;
            cnt++; // mantissa digit count increment
        }
        *dst-- = *src--;
    } while (--len);

    return dst + 1; // return pointer to result
}

int __cdecl _tmain(int argc, const TCHAR *argv[]) {
    TCHAR VolumeName[] = _T("\\\\.\\C:");
    HANDLE VolumeHandle;
    NTFS_VOLUME_DATA_BUFFER VolumeInfo;
    DWORD LengthReturned;
    ULONGLONG VolumeSize;
    ULONGLONG MftClusters;
    UINT File = 0;
    PNTFS_FILE_RECORD_OUTPUT_BUFFER OutputBuffer;

    if (argc > 1) {
        TCHAR Letter = argv[1][0];

        if ((Letter >= 'A' && Letter <= 'Z') || (Letter >= 'a' && Letter <= 'z')) {
            VolumeName[4] = Letter;
        }
    }

    _tsetlocale(LC_NUMERIC, _T(""));

    VolumeHandle = CreateFile(VolumeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, NULL);
    if (VolumeHandle == INVALID_HANDLE_VALUE) {
        _ftprintf(stderr, _T("Failed opening the volume '%s' (%lx)\n"), VolumeName, GetLastError());
        return 1;
    }

    if (!DeviceIoControl(VolumeHandle, FSCTL_GET_NTFS_VOLUME_DATA, NULL, 0, &VolumeInfo, sizeof(VolumeInfo), &LengthReturned, NULL)) {
        _ftprintf(stderr, _T("Failed requesting volume '%s' data (%lx)\n"), VolumeName, GetLastError());
        CloseHandle(VolumeHandle);
        return 1;
    }

    if (LengthReturned < sizeof(VolumeInfo)) {
        _ftprintf(stderr, _T("Failed reading volume '%s' data (%lx)\n"), VolumeName, GetLastError());
        CloseHandle(VolumeHandle);
        return 1;
    }

    _tprintf(_T("Volume Size\n-----------\n"));
    VolumeSize = VolumeInfo.TotalClusters.QuadPart * VolumeInfo.BytesPerCluster;
    _tprintf(_T("Volume size\t\t: %s Bytes\n"), addCommas(VolumeSize));
    _tprintf(_T("Total sectors\t\t: %s\n"), addCommas(VolumeInfo.NumberSectors.QuadPart));
    _tprintf(_T("Total clusters\t\t: %s\n"), addCommas(VolumeInfo.TotalClusters.QuadPart));
    _tprintf(_T("Free clusters\t\t: %s\n"), addCommas(VolumeInfo.FreeClusters.QuadPart));
    ULONGLONG VolumeLeftSize = VolumeInfo.FreeClusters.QuadPart * VolumeInfo.BytesPerCluster;
    ULONGLONG percent = (VolumeInfo.FreeClusters.QuadPart * 100) / VolumeInfo.TotalClusters.QuadPart;
    _tprintf(_T("Free space\t\t: %s Bytes (%I64u%% of drive)\n"), addCommas(VolumeLeftSize), percent);

    _tprintf(_T("\nAllocation Size\n---------------\n"));
    _tprintf(_T("Bytes per sector\t: %s\n"), addCommas(VolumeInfo.BytesPerSector));
    _tprintf(_T("Bytes per cluster\t: %s\n"), addCommas(VolumeInfo.BytesPerCluster));
    _tprintf(_T("Bytes per MFT record:\t: %s\n"), addCommas(VolumeInfo.BytesPerFileRecordSegment));
    _tprintf(_T("Clusters per MFT record\t: %s\n"), addCommas(VolumeInfo.ClustersPerFileRecordSegment));

    _tprintf(_T("\nMFT Information\n---------------\n"));
    _tprintf(_T("MFT size\t\t: %s Bytes (%s%% of drive)\n"), addCommas(VolumeInfo.MftValidDataLength.QuadPart >> 20), addCommas((VolumeInfo.MftValidDataLength.QuadPart * 100) / VolumeSize));
    _tprintf(_T("MFT start cluster\t: %s\n"), addCommas(VolumeInfo.MftStartLcn.QuadPart));
    _tprintf(_T("MFT zone clusters\t: %s - %s\n"), addCommas(VolumeInfo.MftZoneStart.QuadPart), addCommas(VolumeInfo.MftZoneEnd.QuadPart));
    MftClusters = VolumeInfo.MftZoneEnd.QuadPart - VolumeInfo.MftZoneStart.QuadPart;
    _tprintf(_T("MFT zone size\t\t: %s Bytes (%s%% of drive)\n"), addCommas((MftClusters * VolumeInfo.BytesPerCluster) >> 20), addCommas((MftClusters * 100) / VolumeInfo.TotalClusters.QuadPart));
    _tprintf(_T("MFT mirror start\t: %s\n"), addCommas(VolumeInfo.Mft2StartLcn.QuadPart));

    _tprintf(_T("\nMeta-Data files\n---------------\n"));
    OutputBuffer = HeapAlloc(GetProcessHeap(), 0, VolumeInfo.BytesPerFileRecordSegment + sizeof(NTFS_FILE_RECORD_OUTPUT_BUFFER));
    while (MetaDataFiles[File] != NULL) {
        NTFS_FILE_RECORD_INPUT_BUFFER InputBuffer;
        PFILE_RECORD_HEADER FileRecord;
        PNTFS_ATTR_RECORD Attribute;
        ULONGLONG Size = 0;

        if (File == 5) {
            ++File;
            continue;
        }

        InputBuffer.FileReferenceNumber.QuadPart = File;
        if (!DeviceIoControl(VolumeHandle, FSCTL_GET_NTFS_FILE_RECORD, &InputBuffer, sizeof(InputBuffer), OutputBuffer, VolumeInfo.BytesPerFileRecordSegment + sizeof(NTFS_FILE_RECORD_OUTPUT_BUFFER), &LengthReturned, NULL)) {
            ++File;
            continue;
        }

        if (OutputBuffer->FileReferenceNumber.QuadPart != File) {
            ++File;
            continue;
        }

        FileRecord = (PFILE_RECORD_HEADER) OutputBuffer->FileRecordBuffer;
        if (FileRecord->Ntfs.Type != NRH_FILE_TYPE) {
            ++File;
            continue;
        }

        Attribute = (PNTFS_ATTR_RECORD) ((ULONG_PTR) FileRecord + FileRecord->AttributeOffset);
        while (Attribute < (PNTFS_ATTR_RECORD) ((ULONG_PTR) FileRecord + FileRecord->BytesInUse) && Attribute->Type != ATTRIBUTE_TYPE_END) {
            if (Attribute->Type == ATTRIBUTE_TYPE_DATA) {
                Size = (Attribute->IsNonResident) ? Attribute->NonResident.AllocatedSize : Attribute->Resident.ValueLength;
                break;
            }

            Attribute = (PNTFS_ATTR_RECORD) ((ULONG_PTR) Attribute + Attribute->Length);
        }

        _tprintf(_T("%s%I64u bytes\n"), MetaDataFiles[File], Size);

        ++File;
    }

    HeapFree(GetProcessHeap(), 0, OutputBuffer);
    CloseHandle(VolumeHandle);

    return 0;
}
