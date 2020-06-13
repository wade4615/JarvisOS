//**********************************************************
//** DumpPartition copyright (c) 2020 Christopher D. Wade **
//** File: Print.cpp                                      **
//**********************************************************
#include "main.h"

void printFAT32BootSector(FAT32BootSectorPtr bootSector) {
    _tprintf(_T("OEM ID:\t\t\t\t \"%.8s\"\n"), bootSector->oemID);
    _tprintf(_T("Byte/Sector:\t\t\t %u\n"), bootSector->bytePerSector);
    _tprintf(_T("Sector/Cluster:\t\t\t %u\n"), bootSector->sectorPerCluster);
    _tprintf(_T("Number of FATS:\t\t\t %u\n"), bootSector->numberOfFATS);
    _tprintf(_T("Max Root Dir Entries:\t\t %u\n"), bootSector->maxRootDirEntries);
    _tprintf(_T("Sectors in Partition FAT16:\t %u\n"), bootSector->totalSectors16);
    _tprintf(_T("Media:\t\t\t\t %02X\n"), bootSector->bMedia);
    _tprintf(_T("Sectors in Partition FAT32:\t %u\n"), bootSector->totalSectors32);
    _tprintf(_T("Sectors/track:\t\t\t %u\n"), bootSector->sectorPerTrack);
    _tprintf(_T("Heads:\t\t\t\t %u\n"), bootSector->headNumber);
    _tprintf(_T("Hidden Sectors:\t\t\t %lu\n"), bootSector->hiddenSector);
    _tprintf(_T("Total Sectors:\t\t\t %s\n"), addCommas(bootSector->totalSectors));
    _tprintf(_T("Sectors/FAT:\t\t\t %s\n"), addCommas(bootSector->sectorsPerFAT));
    _tprintf(_T("Flags:\t\t\t\t %04X\n"), bootSector->flags);
    _tprintf(_T("FAT32 Version:\t\t\t %u\n"), bootSector->fat32Version);
    _tprintf(_T("Root Cluster:\t\t\t %lu\n"), bootSector->rootCluster);
    _tprintf(_T("FS Info Cluster:\t\t %lu\n"), bootSector->fsInfoCluster);
    _tprintf(_T("Backup Boot Sector:\t\t %u\n"), bootSector->backupBootSector);
    _tprintf(_T("Drive Number:\t\t\t %X\n"), bootSector->driveNumber);
    _tprintf(_T("Extended Signature:\t\t %X\n"), bootSector->extendedSignature);
    _tprintf(_T("Volume ID:\t\t\t %08lX\n"), bootSector->dBS_VolID);
    _tprintf(_T("Volume Name:\t\t\t \"%.11s\"\n"), bootSector->volumeName);
    _tprintf(_T("FAT Name:\t\t\t \"%.8s\"\n"), bootSector->FATName);
    _tprintf(_T("End Marker:\t\t\t %04X\n"), bootSector->endMarker);
    DWORD clusterSize = bootSector->bytePerSector * bootSector->sectorPerCluster;
    _tprintf(_T("Cluster Size:\t\t\t %s\n"), addCommas(clusterSize));
    ULONGLONG driveSize = (ULONGLONG) bootSector->totalSectors * 512LL;
    double sizeInGB = (driveSize) / (1024LL * 1024LL);
    if (sizeInGB < 1024.0) {
        _tprintf(_T("Drive Size:\t\t\t %s (%4.2lf MB)\n"), addCommas(driveSize), sizeInGB);
    } else {
        _tprintf(_T("Drive Size:\t\t\t %s (%4.2lf GB)\n"), addCommas(driveSize), sizeInGB / 1024LL);
    }
}

void printNTFSBootSector(NTFSBootSectorPtr bootSector) {
    DWORD sectorSize = bootSector->bytePerSector;
    DWORD clusterSize = bootSector->bytePerSector * bootSector->sectorPerCluster;
    DWORD recordSize = bootSector->clusterPerRecord >= 0 ? bootSector->clusterPerRecord * clusterSize : 1 << -bootSector->clusterPerRecord;
    LONGLONG totalCluster = bootSector->totalSector / bootSector->sectorPerCluster;
    LONGLONG driveSize = bootSector->totalSector * bootSector->bytePerSector;

    _tprintf(_T("OEM ID:\t\t\t\t \"%.8s\"\n"), bootSector->oemID);
    _tprintf(_T("Byte/Sector:\t\t\t %u\n"), bootSector->bytePerSector);
    _tprintf(_T("Sector/Cluster:\t\t\t %u\n"), bootSector->sectorPerCluster);
    _tprintf(_T("Media descriptor:\t\t %X\n"), bootSector->mediaDescriptor);
    _tprintf(_T("Sector/Track:\t\t\t %u\n"), bootSector->sectorPerTrack);
    _tprintf(_T("Head Number:\t\t\t %u\n"), bootSector->headNumber);
    _tprintf(_T("Hidden Sector:\t\t\t %s\n"), addCommas(bootSector->hiddenSector));
    _tprintf(_T("Total Sector:\t\t\t %s\n"), addCommas(bootSector->totalSector));
    _tprintf(_T("MFT Cluster:\t\t\t %s\n"), addCommas(bootSector->MFTCluster));
    _tprintf(_T("MFT Mirror Cluster:\t\t %llu\n"), bootSector->MFTMirrCluster);
    _tprintf(_T("Cluster/Record:\t\t\t %u\n"), bootSector->clusterPerRecord);
    _tprintf(_T("Cluster/Block:\t\t\t %u\n"), bootSector->clusterPerBlock);
    _tprintf(_T("Serial Number:\t\t\t %llX\n"), bootSector->serialNumber);
    _tprintf(_T("Check sum:\t\t\t %lX\n"), bootSector->checkSum);
    _tprintf(_T("End Marker:\t\t\t %X\n"), bootSector->endMarker);
    _tprintf(_T("Cluster Size:\t\t\t %s\n"), addCommas(clusterSize));
    _tprintf(_T("Record Size:\t\t\t %s\n"), addCommas(recordSize));
    double sizeInGB = (driveSize) / (1024LL * 1024LL);
    if (sizeInGB < 1024.0) {
        _tprintf(_T("Drive Size:\t\t\t %s (%4.2lf MB)\n"), addCommas(driveSize), sizeInGB);
    } else {
        _tprintf(_T("Drive Size:\t\t\t %s (%4.2lf GB)\n"), addCommas(driveSize), sizeInGB / 1024LL);
    }
}

void printMasterBootRecord(TCHAR *text, PartitionEntryPtr entry, int i) {
    if (entry->fileSystem != 0x00) {
        _tprintf(_T("\n%s %d\n"), text, i);
        if (entry->bootType == 0x80) {
            _tprintf(_T("Boot type:\t\t\t 0x%X (bootable)\n"), entry->bootType & 0xFF);
        } else {
            _tprintf(_T("Boot type:\t\t\t 0x%X (not bootable)\n"), entry->bootType & 0xFF);
        }
        _tprintf(_T("Begin Head:\t\t\t %d\n"), entry->beginHead & 0xFF);
        int bsector = HI(entry->beginSectorCylinder) | ((LO(entry->beginSectorCylinder) & 0xC0) >> 2);
        int bcylinder = entry->beginSectorCylinder & 0x3F;
        _tprintf(_T("Begin sector :\t\t\t %u\n"), bsector);
        _tprintf(_T("Begin cylinder :\t\t %u\n"), bcylinder);
        if (entry->fileSystem == 0x07) {
            _tprintf(_T("File System:\t\t\t 0x%02X (NTFS)\n"), entry->fileSystem & 0xFF);
        } else if (entry->fileSystem == 0x0C) {
            _tprintf(_T("File System:\t\t\t 0x%02X (FAT32 with LBA)\n"), entry->fileSystem & 0xFF);
        } else if (entry->fileSystem == 0x82) {
            _tprintf(_T("File System:\t\t\t 0x%02X (Linux Swap)\n"), entry->fileSystem & 0xFF);
        } else if (entry->fileSystem == 0x83) {
            _tprintf(_T("File System:\t\t\t 0x%02X (Linux Drive)\n"), entry->fileSystem & 0xFF);
        } else if (entry->fileSystem == 0x02) {
            _tprintf(_T("File System:\t\t\t 0x%02X (Linux Root)\n"), entry->fileSystem & 0xFF);
        } else if (entry->fileSystem == 0x0F) {
            _tprintf(_T("File System:\t\t\t 0x%02X (Extended with LBA)\n"), entry->fileSystem & 0xFF);
        } else if (entry->fileSystem == 0x05) {
            _tprintf(_T("File System:\t\t\t 0x%02X (Extended with CHS)\n"), entry->fileSystem & 0xFF);
        } else {
            _tprintf(_T("File System:\t\t\t 0x%02X (Unknown)\n"), entry->fileSystem & 0xFF);
        }
        ULONGLONG endSector = (ULONGLONG) entry->lbaStart + (ULONGLONG) entry->partitionSize;
        _tprintf(_T("End Head:\t\t\t %d\n"), entry->endHead & 0xFF);
        int esector = HI(entry->endSectorCylinder) | ((LO(entry->endSectorCylinder) & 0xC0) >> 2);
        int ecylinder = entry->endSectorCylinder & 0x3F;
        _tprintf(_T("End sector :\t\t\t %u\n"), esector);
        _tprintf(_T("End cylinder :\t\t\t %u\n"), ecylinder);
        _tprintf(_T("Begin Absolute Sector:\t\t %s\n"), addCommas(entry->lbaStart));
        _tprintf(_T("End Absolute Sector:\t\t %s\n"), addCommas(endSector));
        _tprintf(_T("Size in Sectors:\t\t %s\n"), addCommas(entry->partitionSize));

        ULONGLONG beginByteOffset = (ULONGLONG) entry->lbaStart * 512LL;
        ULONGLONG endByteOffset = beginByteOffset + (ULONGLONG) entry->partitionSize * 512LL;
        ULONGLONG sizeOfPartition = endByteOffset - beginByteOffset;
        _tprintf(_T("Begin Byte offset:\t\t %s\n"), addCommas(beginByteOffset));
        _tprintf(_T("End Byte offset:\t\t %s\n"), addCommas(endByteOffset));
        double sizeInGB = (sizeOfPartition) / (1024LL * 1024LL);
        if (sizeInGB < 1024.0) {
            _tprintf(_T("Size:\t\t\t\t %s (%4.2lf MB)\n"), addCommas(sizeOfPartition), sizeInGB);
        } else {
            _tprintf(_T("Size:\t\t\t\t %s (%4.2lf GB)\n"), addCommas(sizeOfPartition), sizeInGB / 1024LL);
        }
    }
}
