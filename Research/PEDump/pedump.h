#ifndef PEDUMP_H_INCLUDED
#define PEDUMP_H_INCLUDED

#include <windows.h>
#include <winioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <locale.h>
#include <tchar.h>
#include <shellapi.h>
#include <time.h>

#define MakePtr(cast, ptr, addValue) ((cast)(ULONGLONG)((ULONGLONG)(ptr) + (ULONGLONG)(addValue)))

typedef struct
{
    DWORD   flag;
    PSTR    name;
} DWORD_FLAG_DESCRIPTIONS;

typedef struct
{
    WORD    flag;
    PSTR    name;
} WORD_FLAG_DESCRIPTIONS;

extern BOOL fShowRelocations;
extern BOOL fShowRawSectionData;
extern BOOL fShowSymbolTable;
extern BOOL fShowLineNumbers;
extern BOOL fShowIATentries;
extern BOOL fShowPDATA;
extern BOOL fShowResources;

void DumpExeFile(PIMAGE_DOS_HEADER dosHeader);

void DumpFile(TCHAR * filename);
TCHAR *ProcessCommandLine(int argc, TCHAR *argv[]);
void exitWithLastError(TCHAR *format,...);

#endif // PEDUMP_H_INCLUDED
