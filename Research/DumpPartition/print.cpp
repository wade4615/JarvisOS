#include "main.h"

void printBootSector(NTFSBootSectorPtr bootSector){
    DWORD sectorSize = bootSector->bytePerSector;
    DWORD clusterSize = bootSector->bytePerSector * bootSector->sectorPerCluster;
    DWORD recordSize = bootSector->clusterPerRecord >= 0 ? bootSector->clusterPerRecord * clusterSize : 1 << -bootSector->clusterPerRecord;
    LONGLONG totalCluster = bootSector->totalSector / bootSector->sectorPerCluster;
    LONGLONG driveSize = bootSector->totalSector * bootSector->bytePerSector;

    _tprintf(_T("OEM ID:\t\t\t\t \"%s\"\n"), bootSector->oemID);
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
    double sizeInGB = (driveSize)/(1024LL*1024LL);
    if (sizeInGB<1024.0){
        _tprintf(_T("Drive Size:\t\t\t %s (%4.2lf MB)\n"), addCommas(driveSize), sizeInGB);
    } else{
        _tprintf(_T("Drive Size:\t\t\t %s (%4.2lf GB)\n"), addCommas(driveSize), sizeInGB/1024LL);
    }
}

void printMasterBootRecord(const TCHAR *text, MasterBootRecordPtr mbr){
    for (int i=0; i<=3; i++){
        if (mbr->partionTable[i].fileSystem!=0x00){
            _tprintf(_T("\n%s %d\n"),text, i);
            if (mbr->partionTable[i].bootType == 0x80) {
                _tprintf(_T("Boot type:\t\t\t 0x%X (bootable)\n"),mbr->partionTable[i].bootType&0xFF);
            } else {
                _tprintf(_T("Boot type:\t\t\t 0x%X (not bootable)\n"),mbr->partionTable[i].bootType&0xFF);
            }
            _tprintf(_T("Begin Head:\t\t\t %d\n"),mbr->partionTable[i].beginHead&0xFF);
            int bsector = mbr->partionTable[i].beginSectorCylinder&0x3F;
            int bcylinder = mbr->partionTable[i].beginSectorCylinder<<6;
            _tprintf(_T("Begin sector :\t\t\t %u\n"), bsector);
            _tprintf(_T("Begin cylinder :\t\t %u\n"), bcylinder);
            if (mbr->partionTable[i].fileSystem==0x07){
                _tprintf(_T("File System:\t\t\t 0x%02X (NTFS,HPFS,IFS,exFAT, or QNX)\n"), mbr->partionTable[i].fileSystem&0xFF);
            } else if (mbr->partionTable[i].fileSystem==0x83){
                _tprintf(_T("File System:\t\t\t 0x%02X (Linux Drive)\n"), mbr->partionTable[i].fileSystem&0xFF);
            } else if (mbr->partionTable[i].fileSystem==0x02){
                _tprintf(_T("File System:\t\t\t 0x%02X (Linux Root)\n"), mbr->partionTable[i].fileSystem&0xFF);
            } else if (mbr->partionTable[i].fileSystem==0x0F){
                _tprintf(_T("File System:\t\t\t 0x%02X (Extended with LBA)\n"), mbr->partionTable[i].fileSystem&0xFF);
            } else if (mbr->partionTable[i].fileSystem==0x05){
                _tprintf(_T("File System:\t\t\t 0x%02X (Extended with CHS)\n"), mbr->partionTable[i].fileSystem&0xFF);
            } else {
                _tprintf(_T("File System:\t\t\t 0x%02X (Unknown)\n"), mbr->partionTable[i].fileSystem&0xFF);
            }
            ULONGLONG endSector = (ULONGLONG)mbr->partionTable[i].lbaStart + (ULONGLONG)mbr->partionTable[i].partitionSize;
            _tprintf(_T("End Head:\t\t\t %d\n"),mbr->partionTable[i].endHead&0xFF);
            int esector = mbr->partionTable[i].endSectorCylinder&0x3F;
            int ecylinder = mbr->partionTable[i].endSectorCylinder<<6;
            _tprintf(_T("End sector :\t\t\t %u\n"), esector);
            _tprintf(_T("End cylinder :\t\t\t %u\n"), ecylinder);
            _tprintf(_T("Begin Absolute Sector:\t\t %s\n"), addCommas(mbr->partionTable[i].lbaStart));
            _tprintf(_T("End Absolute Sector:\t\t %s\n"), addCommas(endSector));
            _tprintf(_T("Size in Sectors:\t\t %s\n"), addCommas(mbr->partionTable[i].partitionSize));

            ULONGLONG beginByteOffset = (ULONGLONG)mbr->partionTable[i].lbaStart*512LL;
            ULONGLONG endByteOffset = beginByteOffset + (ULONGLONG)mbr->partionTable[i].partitionSize*512LL;
            ULONGLONG sizeOfPartition = endByteOffset - beginByteOffset;
            _tprintf(_T("Begin Byte offset:\t\t %s\n"), addCommas(beginByteOffset));
            _tprintf(_T("End Byte offset:\t\t %s\n"), addCommas(endByteOffset));
            double sizeInGB = (sizeOfPartition)/(1024LL*1024LL);
            if (sizeInGB<1024.0){
                _tprintf(_T("Size:\t\t\t\t %s (%4.2lf MB)\n"), addCommas(sizeOfPartition), sizeInGB);
            } else{
                _tprintf(_T("Size:\t\t\t\t %s (%4.2lf GB)\n"), addCommas(sizeOfPartition), sizeInGB/1024LL);
            }
        }
    }
}
