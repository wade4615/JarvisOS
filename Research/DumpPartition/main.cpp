#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <tchar.h>
#include <shellapi.h>
#include <vector>
#include <functional>

using namespace std;

#pragma pack(push, 1)
typedef struct _PartitionEntry {
    BYTE bootType;
    BYTE beginHead;
    WORD beginSectorCylinder;
    BYTE fileSystem;
    BYTE endHead;
    WORD endSectorCylinder;
    DWORD beginSector;
    DWORD endSector;
} PartitionEntry,*PartitionEntryPtr;

typedef struct _MasterBootRecord {
    BYTE initialProgramLoader[446];
    PartitionEntry partionTable[4];
    WORD signature;
} MasterBootRecord, *MasterBootRecordPtr;

typedef struct _BootSector {
    BYTE        jump[3];
    BYTE        oemID[8];
    WORD        bytePerSector;
    BYTE        sectorPerCluster;
    BYTE        reserved[2];
    BYTE        zero1[3];
    BYTE        unused1[2];
    BYTE        mediaDescriptor;
    BYTE        zeros2[2];
    WORD        sectorPerTrack;
    WORD        headNumber;
    DWORD       hiddenSector;
    BYTE        unused2[8];
    LONGLONG    totalSector;
    LONGLONG    MFTCluster;
    LONGLONG    MFTMirrCluster;
    signed char clusterPerRecord;
    BYTE        unused3[3];
    signed char clusterPerBlock;
    BYTE        unused4[3];
    LONGLONG    serialNumber;
    DWORD       checkSum;
    BYTE        bootCode[0x1aa];
    BYTE        endMarker[2];
} BootSector, *BootSectorPtr;

typedef struct _RecordHeader {
    BYTE        signature[4];
    WORD        updateOffset;
    WORD        updateNumber;
    LONGLONG    logFile;
    WORD        sequenceNumber;
    WORD        hardLinkCount;
    WORD        attributeOffset;
    WORD        flag;
    DWORD       usedSize;
    DWORD       allocatedSize;
    LONGLONG    baseRecord;
    WORD        nextAttributeID;
    BYTE        unsed[2];
    DWORD       MFTRecord;
} RecordHeader, *RecordHeaderPtr;

typedef struct _AttributeHeaderR {
    DWORD       typeID;
    DWORD       length;
    BYTE        formCode;
    BYTE        nameLength;
    WORD        nameOffset;
    WORD        flag;
    WORD        attributeID;
    DWORD       contentLength;
    WORD        contentOffset;
    WORD        unused;
} AttributeHeaderR, *AttributeHeaderRPtr;

typedef struct _AttributeHeaderNR {
    DWORD       typeID;
    DWORD       length;
    BYTE        formCode;
    BYTE        nameLength;
    WORD        nameOffset;
    WORD        flag;
    WORD        attributeID;
    LONGLONG    startVCN;
    LONGLONG    endVCN;
    WORD        runListOffset;
    WORD        compressSize;
    DWORD       zero;
    LONGLONG    contentDiskSize;
    LONGLONG    contentSize;
    LONGLONG    initialContentSize;
}AttributeHeaderNR, *AttributeHeaderNRPtr;

typedef struct _FileName {
    LONGLONG    parentDirectory;
    LONGLONG    dateCreated;
    LONGLONG    dateModified;
    LONGLONG    dateMFTModified;
    LONGLONG    dateAccessed;
    LONGLONG    logicalSize;
    LONGLONG    diskSize;
    DWORD       flag;
    DWORD       reparseValue;
    BYTE        nameLength;
    BYTE        nameType;
    BYTE        name[1];
}FileName, *FileNamePtr;

typedef struct _AttributeRecord {
    DWORD       typeID;
    WORD        recordLength;
    BYTE        nameLength;
    BYTE        nameOffset;
    LONGLONG    lowestVCN;
    LONGLONG    recordNumber;
    WORD        sequenceNumber;
    WORD        reserved;
}AttributeRecord, *AttributeRecordPtr;
#pragma pack(pop)

struct Run {
    LONGLONG    offset;
    LONGLONG    length;
    Run(): offset(0LL), length(0LL) {}
    Run(LONGLONG offset, LONGLONG length): offset(offset), length(length) {}
};

#define DOT     _T('.')
#define COMMA   _T(',')
#define MAX     50

static TCHAR commas[MAX]; // Where the result is

TCHAR *addCommas(ULONGLONG f)
{
    TCHAR tmp[MAX];            // temp area
    _stprintf(tmp, _T("%I64u"), f);    // refine %f if you need
    TCHAR *dot = _tcschr(tmp, DOT); // do we have a DOT?
    TCHAR *src,*dst; // source, dest

    if (dot)              // Yes
    {
        dst = commas+MAX-_tcslen(dot)-1; // set dest to allow the fractional part to fit
        strcpy(dst, dot);               // copy that part
        *dot = 0;       // 'cut' that frac part in tmp
        src = --dot;    // point to last non frac char in tmp
        dst--;          // point to previous 'free' char in dest
    }
    else                  // No
    {
        src = tmp+_tcslen(tmp)-1;    // src is last char of our float string
        dst = commas+MAX-1;         // dst is last char of commas
    }

    int len = strlen(tmp);        // len is the mantissa size
    int cnt = 0;                  // char counter

    do
    {
        if ( *src<='9' && *src>='0' )    // add comma is we added 3 digits already
        {
            if (cnt && !(cnt % 3)) *dst-- = COMMA;
            cnt++; // mantissa digit count increment
        }
        *dst-- = *src--;
    }
    while (--len);

    return dst+1; // return pointer to result
}

void printBootSector(BootSectorPtr bootSector){
    printf("OEM ID:\t\t \"%s\"\n", bootSector->oemID);
    DWORD sectorSize = bootSector->bytePerSector;
    DWORD clusterSize = bootSector->bytePerSector * bootSector->sectorPerCluster;
    DWORD recordSize = bootSector->clusterPerRecord >= 0 ? bootSector->clusterPerRecord * clusterSize : 1 << -bootSector->clusterPerRecord;
    LONGLONG totalCluster = bootSector->totalSector / bootSector->sectorPerCluster;

    _tprintf(_T("Byte/Sector:\t %u\n"), sectorSize);
    _tprintf(_T("Sector/Cluster:\t %u\n"), bootSector->sectorPerCluster);
    _tprintf(_T("Total Sector:\t %s\n"), addCommas(bootSector->totalSector));
    _tprintf(_T("Cluster of MFT:\t %s\n"), addCommas(bootSector->MFTCluster));
    _tprintf(_T("Cluster/Record:\t %u\n"), bootSector->clusterPerRecord);
    _tprintf(_T("Cluster Size:\t %s\n"), addCommas(clusterSize));
    _tprintf(_T("Record Size:\t %s\n"), addCommas(recordSize));
}

void printMasterBootRecord(MasterBootRecordPtr mbr){
    for (int i=0; i<=3; i++){
        _tprintf(_T("\nPartition Number: %d\n"), i);
        if (mbr->partionTable[i].bootType == 0x80) {
            _tprintf(_T("Boot type:\t\t\t 0x%X (bootable)\n"),mbr->partionTable[i].bootType&0xFF);
        } else {
            _tprintf(_T("Boot type:\t\t\t 0x%X (not bootable)\n"),mbr->partionTable[i].bootType&0xFF);
        }
        _tprintf(_T("Begin Head:\t\t\t %d\n"),mbr->partionTable[i].beginHead&0xFF);
        _tprintf(_T("Begin Sector Cylinder:\t\t %s\n"), addCommas(mbr->partionTable[i].beginSectorCylinder));
        if (mbr->partionTable[i].fileSystem==0x07){
            _tprintf(_T("File System:\t\t\t 0x%02X (NTFS,HPFS,IFS,exFAT, or QNX)\n"), mbr->partionTable[i].fileSystem&0xFF);
        } else if (mbr->partionTable[i].fileSystem==0x05){
            _tprintf(_T("File System:\t\t\t 0x%02X (Extended partition)\n"), mbr->partionTable[i].fileSystem&0xFF);
        } else if (mbr->partionTable[i].fileSystem==0x00){
            _tprintf(_T("File System:\t\t\t 0x%02X (not a valid partition)\n"), mbr->partionTable[i].fileSystem&0xFF);
        } else {
            _tprintf(_T("File System:\t\t\t 0x%02X (Unknown)\n"), mbr->partionTable[i].fileSystem&0xFF);
        }
        _tprintf(_T("End Head:\t\t\t %d\n"),mbr->partionTable[i].endHead&0xFF);
        _tprintf(_T("End Sector Cylinder:\t\t %s\n"), addCommas(mbr->partionTable[i].endSectorCylinder));
        _tprintf(_T("Begin Absolute Sector:\t\t %s\n"), addCommas(mbr->partionTable[i].beginSector));
        _tprintf(_T("End absolute Sector:\t\t %s\n"), addCommas(mbr->partionTable[i].endSector));

        ULONGLONG beginByteOffset = (ULONGLONG)mbr->partionTable[i].beginSector*512LL;
        ULONGLONG endByteOffset = (ULONGLONG)mbr->partionTable[i].endSector*512LL;
        ULONGLONG sizeOfPartition = endByteOffset - beginByteOffset;
        _tprintf(_T("Begin Byte offset:\t\t %s\n"), addCommas(beginByteOffset));
        _tprintf(_T("End Byte offset:\t\t %s\n"), addCommas(endByteOffset));
        if (mbr->partionTable[i].fileSystem!=0x05){
            _tprintf(_T("Size           :\t\t %s\n"), addCommas(sizeOfPartition));
        }
    }
}

int __cdecl _tmain(int argc, const TCHAR *argv[]) {
    TCHAR VolumeName[] = _T("\\\\.\\PhysicalDrive0");

    HANDLE VolumeHandle;

    _tsetlocale(LC_NUMERIC, _T(""));

    VolumeHandle = CreateFile(VolumeName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, NULL);
    if (VolumeHandle == INVALID_HANDLE_VALUE)
    {
        _ftprintf(stderr, _T("Failed opening the volume '%s' (%lx)\n"), VolumeName, GetLastError());
        return 1;
    }

    MasterBootRecord mbr;
    DWORD read;
    ReadFile(VolumeHandle, &mbr, sizeof mbr, &read, NULL);
    if (read != sizeof mbr)
    {
        throw _T("Failed to read boot sector");
    }

    printMasterBootRecord(&mbr);

    CloseHandle(VolumeHandle);
    return 0;
}
