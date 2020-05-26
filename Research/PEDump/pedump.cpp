//==================================
// PEDUMP - Matt Pietrek 1994-1998
// FILE: PEDUMP.C
//==================================
#include "pedump.h"

// Global variables set here, and used in EXEDUMP.C and OBJDUMP.C
BOOL fShowRelocations = FALSE;
BOOL fShowRawSectionData = FALSE;
BOOL fShowSymbolTable = FALSE;
BOOL fShowLineNumbers = FALSE;
BOOL fShowIATentries = FALSE;
BOOL fShowPDATA = FALSE;
BOOL fShowResources = FALSE;

char HelpText[] =
"PEDUMP - Win32/COFF EXE/OBJ/LIB file dumper - 1998 Matt Pietrek\n\n"
"Syntax: PEDUMP [switches] filename\n\n"
"  /A    include everything in dump\n"
"  /B    show base relocations\n"
"  /H    include hex dump of sections\n"
"  /I    include Import Address Table thunk addresses\n"
"  /L    include line number information\n"
"  /P    include PDATA (runtime functions)\n"
"  /R    include detailed resources (stringtables and dialogs)\n"
"  /S    show symbol table\n";

void exitWithLastError(TCHAR *format,...) {
    LPVOID lpMsgBuf;
    DWORD lastError = GetLastError();

    va_list args;
    va_start(args, format);

    if (lastError) {
        FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS, NULL, lastError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL);
        _ftprintf(stderr, _T("\n"));
        _vftprintf(stderr, format, args);
        _ftprintf(stderr, _T("GetLastError()=%d: %s\n"), lastError, lpMsgBuf);
    } else {
        _ftprintf(stderr, _T("\n"));
        _vftprintf(stderr, format, args);
    }
    va_end(args);
    LocalFree(lpMsgBuf);
    exit(lastError);
}

void DumpFile(TCHAR * filename){
    HANDLE hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hFile == INVALID_HANDLE_VALUE) {
       exitWithLastError(_T("Couldn't open file with CreateFile()\n"));
       return;
    }
    HANDLE hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (hFileMapping == 0) {
        CloseHandle(hFile);
        exitWithLastError(_T("Couldn't open file mapping with CreateFileMapping()\n"));
        return;
    }
    LPVOID lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
    if (lpFileBase == 0) {
        CloseHandle(hFileMapping);
        CloseHandle(hFile);
        exitWithLastError(_T("Couldn't map view of file with MapViewOfFile()\n"));
        return;
    }

    _tprintf(_T("Dump of file %s\n\n"), filename);

    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)lpFileBase;
	PIMAGE_FILE_HEADER pImgFileHdr = (PIMAGE_FILE_HEADER)lpFileBase;
    if (dosHeader->e_magic == IMAGE_DOS_SIGNATURE) {
        DumpExeFile(dosHeader);
    }

    UnmapViewOfFile(lpFileBase);
    CloseHandle(hFileMapping);
    CloseHandle(hFile);

}

TCHAR *ProcessCommandLine(int argc, TCHAR *argv[]){
    int i;

    for ( i=1; i < argc; i++){
        _tcsupr(argv[i]);

        // Is it a switch character?
        if ((argv[i][0] == '-') || (argv[i][0] == '/')) {
            if (argv[i][1] == 'A') {
                fShowRelocations = TRUE;
                fShowRawSectionData = TRUE;
                fShowSymbolTable = TRUE;
                fShowLineNumbers = TRUE;
                fShowIATentries = TRUE;
                fShowPDATA = TRUE;
				fShowResources = TRUE;
            }
            else if (argv[i][1] == _T('H'))
                fShowRawSectionData = TRUE;
            else if (argv[i][1] == _T('L'))
                fShowLineNumbers = TRUE;
            else if (argv[i][1] == _T('P'))
                fShowPDATA = TRUE;
            else if (argv[i][1] == _T('B'))
                fShowRelocations = TRUE;
            else if (argv[i][1] == _T('S'))
                fShowSymbolTable = TRUE;
            else if (argv[i][1] == _T('I'))
                fShowIATentries = TRUE;
            else if (argv[i][1] == _T('R'))
                fShowResources = TRUE;
        }
        else {    // Not a switch character.  Must be the filename
            return argv[i];
        }
    }

	return NULL;
}

int _tmain(int argc, TCHAR *argv[]) {
    if (argc == 1) {
        _tprintf(HelpText);
        return 1;
    }

    TCHAR *filename = ProcessCommandLine(argc, argv);
    if (filename){
        DumpFile(filename);
    }
    return 0;
}
