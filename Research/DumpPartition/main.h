#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <windows.h>
#include <winioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <locale.h>
#include <tchar.h>
#include <shellapi.h>

#define LO(x)   ((x) & 0xFF)
#define HI(x)   (((x)>>8) & 0xFF)

#pragma pack(push, 1)
typedef struct _PartitionEntry {
    BYTE bootType;
    BYTE beginHead;
    WORD beginSectorCylinder;
    BYTE fileSystem;
    BYTE endHead;
    WORD endSectorCylinder;
    DWORD lbaStart;
    DWORD partitionSize;
} PartitionEntry,*PartitionEntryPtr;

typedef struct _MasterBootRecord {
    BYTE initialProgramLoader[446];
    PartitionEntry partionTable[4];
    WORD signature;
} MasterBootRecord, *MasterBootRecordPtr;

typedef struct _NTFSBootSector {
    BYTE        jump[3];
    BYTE        oemID[8];
    WORD        bytePerSector;
    BYTE        sectorPerCluster;
    WORD        reserved;
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
    WORD        endMarker;
} NTFSBootSector, *NTFSBootSectorPtr;

typedef struct _FAT32BootSector {
    BYTE jump[3];
    BYTE oemID[8];
    WORD bytePerSector;
    BYTE sectorPerCluster;
    WORD reserved1;
    BYTE numberOfFATS;
    WORD maxRootDirEntries;
    WORD totalSectors16;
    BYTE bMedia;
    WORD totalSectors32;
    WORD sectorPerTrack;
    WORD headNumber;
    DWORD hiddenSector;
    DWORD totalSectors;
    DWORD sectorsPerFAT;
    WORD flags;
    WORD fat32Version;
    DWORD rootCluster;
    WORD fsInfoCluster;
    WORD backupBootSector;
    BYTE Reserved2[12];
    BYTE driveNumber;
    BYTE Reserved1;
    BYTE extendedSignature;
    DWORD dBS_VolID;
    BYTE volumeName[11];
    BYTE FATName[8];
    BYTE code[420];
    WORD endMarker;
} FAT32BootSector, *FAT32BootSectorPtr;

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

void exitWithLastError(TCHAR *format,...);

void readAndPrintFAT32BootSector(HANDLE VolumeHandle, ULONGLONG offset, int i);
void readAndPrintNTFSBootSector(HANDLE VolumeHandle, ULONGLONG offset);
void handleMasterBootRecord(HANDLE VolumeHandle, ULONGLONG start, TCHAR *text, MasterBootRecordPtr mbr);
void dumpDrive(TCHAR *VolumeName);

void printFAT32BootSector(FAT32BootSectorPtr bootSector);
void printNTFSBootSector(NTFSBootSectorPtr bootSector);
void printMasterBootRecord(TCHAR *text,PartitionEntryPtr entry, int i);

TCHAR *addCommas(ULONGLONG f);

LONGLONG seek (HANDLE fileHandle, LONGLONG distance, DWORD MoveMethod);

#endif // MAIN_H_INCLUDED
