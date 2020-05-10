#ifndef _Format_H_
#define _Format_H_

void DumpExeFile(PIMAGE_DOS_HEADER dosHeader);
void DumpDbgFile(PIMAGE_SEPARATE_DEBUG_HEADER pImageSepDbgHeader);
void DumpObjFile(PIMAGE_FILE_HEADER pImageFileHeader);
void DumpROMImage(PIMAGE_ROM_HEADERS pROMHeader);
void DumpLibFile(LPVOID lpFileBase);

#endif
