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

void DumpFile(TCHAR * filename){
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
            else if ( argv[i][1] == 'H' )
                fShowRawSectionData = TRUE;
            else if ( argv[i][1] == 'L' )
                fShowLineNumbers = TRUE;
            else if ( argv[i][1] == 'P' )
                fShowPDATA = TRUE;
            else if ( argv[i][1] == 'B' )
                fShowRelocations = TRUE;
            else if ( argv[i][1] == 'S' )
                fShowSymbolTable = TRUE;
            else if ( argv[i][1] == 'I' )
                fShowIATentries = TRUE;
            else if ( argv[i][1] == 'R' )
                fShowResources = TRUE;
        }
        else {    // Not a switch character.  Must be the filename
            return argv[i];
        }
    }

	return NULL;
}

int _tmain(int argc, TCHAR *argv[]) {
    TCHAR *filename;

    if (argc == 1) {
        _tprintf(HelpText);
        return 1;
    }

    filename = ProcessCommandLine(argc, argv);
    if (filename){
        DumpFile(filename);
    }
    return 0;
}
