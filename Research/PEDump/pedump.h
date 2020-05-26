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

void DumpFile(TCHAR * filename);
TCHAR *ProcessCommandLine(int argc, TCHAR *argv[]);


#endif // PEDUMP_H_INCLUDED
