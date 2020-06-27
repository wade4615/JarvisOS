//**********************************************************
//** NTFSDump copyright (c) 2020 Christopher D. Wade      **
//** File: Main.cpp                                       **
//**********************************************************
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <tchar.h>
#include <shellapi.h>

#pragma pack(push, 1)
struct BootSector {
        BYTE jump[3];
        BYTE oemID[8];
        WORD bytePerSector;
        BYTE sectorPerCluster;
        BYTE reserved[2];
        BYTE zero1[3];
        BYTE unused1[2];
        BYTE mediaDescriptor;
        BYTE zeros2[2];
        WORD sectorPerTrack;
        WORD headNumber;
        DWORD hiddenSector;
        BYTE unused2[8];
        LONGLONG totalSector;
        LONGLONG MFTCluster;
        LONGLONG MFTMirrCluster;
        signed char clusterPerRecord;
        BYTE unused3[3];
        signed char clusterPerBlock;
        BYTE unused4[3];
        LONGLONG serialNumber;
        DWORD checkSum;
        BYTE bootCode[0x1aa];
        BYTE endMarker[2];
};

struct RecordHeader {
        BYTE signature[4];
        WORD updateOffset;
        WORD updateNumber;
        LONGLONG logFile;
        WORD sequenceNumber;
        WORD hardLinkCount;
        WORD attributeOffset;
        WORD flag;
        DWORD usedSize;
        DWORD allocatedSize;
        LONGLONG baseRecord;
        WORD nextAttributeID;
        BYTE unsed[2];
        DWORD MFTRecord;
};

struct AttributeHeaderR {
        DWORD typeID;
        DWORD length;
        BYTE formCode;
        BYTE nameLength;
        WORD nameOffset;
        WORD flag;
        WORD attributeID;
        DWORD contentLength;
        WORD contentOffset;
        WORD unused;
};

struct AttributeHeaderNR {
        DWORD typeID;
        DWORD length;
        BYTE formCode;
        BYTE nameLength;
        WORD nameOffset;
        WORD flag;
        WORD attributeID;
        LONGLONG startVCN;
        LONGLONG endVCN;
        WORD runListOffset;
        WORD compressSize;
        DWORD zero;
        LONGLONG contentDiskSize;
        LONGLONG contentSize;
        LONGLONG initialContentSize;
};

struct FileName {
        LONGLONG parentDirectory;
        LONGLONG dateCreated;
        LONGLONG dateModified;
        LONGLONG dateMFTModified;
        LONGLONG dateAccessed;
        LONGLONG logicalSize;
        LONGLONG diskSize;
        DWORD flag;
        DWORD reparseValue;
        BYTE nameLength;
        BYTE nameType;
        BYTE name[1];
};

struct AttributeRecord {
        DWORD typeID;
        WORD recordLength;
        BYTE nameLength;
        BYTE nameOffset;
        LONGLONG lowestVCN;
        LONGLONG recordNumber;
        WORD sequenceNumber;
        WORD reserved;
};
#pragma pack(pop)

struct Run {
        LONGLONG offset;
        LONGLONG length;
        Run() : offset(0LL), length(0LL) {
        }
        Run(LONGLONG offset, LONGLONG length) : offset(offset), length(length) {
        }
};

int __cdecl _tmain(int argc, TCHAR *argv[]) {
    TCHAR drive[] = _T("\\\\?\\_:");
    LONGLONG targetRecord = -1;
    TCHAR *outputFile = NULL;

    switch (argc) {
        case 2:
        drive[4] = argv[1][0];
            break;
        case 4:
        drive[4] = argv[1][0];
        targetRecord = _tstoi64(argv[2]);
        outputFile = argv[3];
            break;
        default:
        _tprintf(_T("Usage:\n"));
        _tprintf(_T("  ntfsdump DriveLetter\n"));
        _tprintf(_T("  ntfsdump DriveLetter RecordIndex OutputFileName\n"));
        throw 0;
    }
    return 0;
}
