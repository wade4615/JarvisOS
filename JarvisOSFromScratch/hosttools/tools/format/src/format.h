#ifndef _Format_H_
#define _Format_H_

typedef unsigned char BYTE;
typedef unsigned short WORD;
//typedef unsigned int DWORD;

#pragma pack(push, 1)
typedef struct tagFAT_BOOTSECTOR32 {
    // Common fields.
    BYTE sJmpBoot[3];
    BYTE sOEMName[8];
    WORD wBytsPerSec;
    BYTE bSecPerClus;
    WORD wRsvdSecCnt;
    BYTE bNumFATs;
    WORD wRootEntCnt;
    WORD wTotSec16; // if zero, use dTotSec32 instead
    BYTE bMedia;
    WORD wFATSz16;
    WORD wSecPerTrk;
    WORD wNumHeads;
    DWORD dHiddSec;
    DWORD dTotSec32;
    // Fat 32/16 only
    DWORD dFATSz32;
    WORD wExtFlags;
    WORD wFSVer;
    DWORD dRootClus;
    WORD wFSInfo;
    WORD wBkBootSec;
    BYTE Reserved[12];
    BYTE bDrvNum;
    BYTE Reserved1;
    BYTE bBootSig; // == 0x29 if next three fields are ok
    DWORD dBS_VolID;
    BYTE sVolLab[11];
    BYTE sBS_FilSysType[8];

} FAT_BOOTSECTOR32;

typedef struct {
    DWORD dLeadSig;         // 0x41615252
    BYTE sReserved1[480];   // zeros
    DWORD dStrucSig;        // 0x61417272
    DWORD dFree_Count;      // 0xFFFFFFFF
    DWORD dNxt_Free;        // 0xFFFFFFFF
    BYTE sReserved2[12];    // zeros
    DWORD dTrailSig;     // 0xAA550000
} FAT_FSINFO;

#pragma pack(pop)

// This is just so it will build with old versions of Visual Studio. Yeah, I know...
#ifndef IOCTL_DISK_GET_PARTITION_INFO_EX
#define IOCTL_DISK_GET_PARTITION_INFO_EX    CTL_CODE(IOCTL_DISK_BASE, 0x0012, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef struct _PARTITION_INFORMATION_MBR {
    BYTE PartitionType;
    BOOLEAN BootIndicator;
    BOOLEAN RecognizedPartition;
    DWORD HiddenSectors;
} PARTITION_INFORMATION_MBR, *PPARTITION_INFORMATION_MBR;

typedef struct _PARTITION_INFORMATION_GPT {
    GUID PartitionType;                 // Partition type. See table 16-3.
    GUID PartitionId;                   // Unique GUID for this partition.
    DWORD64 Attributes;                 // See table 16-4.
    WCHAR Name[36];                    // Partition Name in Unicode.
} PARTITION_INFORMATION_GPT, *PPARTITION_INFORMATION_GPT;

typedef enum _PARTITION_STYLE {
    PARTITION_STYLE_MBR, PARTITION_STYLE_GPT, PARTITION_STYLE_RAW
} PARTITION_STYLE;

typedef struct _PARTITION_INFORMATION_EX {
    PARTITION_STYLE PartitionStyle;
    LARGE_INTEGER StartingOffset;
    LARGE_INTEGER PartitionLength;
    DWORD PartitionNumber;
    BOOLEAN RewritePartition;
    union {
        PARTITION_INFORMATION_MBR Mbr;
        PARTITION_INFORMATION_GPT Gpt;
    } DUMMYUNIONNAME;
} PARTITION_INFORMATION_EX, *PPARTITION_INFORMATION_EX;
#endif

#ifndef FSCTL_ALLOW_EXTENDED_DASD_IO
#define FSCTL_ALLOW_EXTENDED_DASD_IO 0x00090083
#endif

#endif
