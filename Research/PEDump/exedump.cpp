//==================================
// PEDUMP - Matt Pietrek 1994-1998
// FILE: PEDUMP.C
//==================================
#include "pedump.h"

WORD_FLAG_DESCRIPTIONS ImageFileHeaderCharacteristics[] =
{
{ IMAGE_FILE_RELOCS_STRIPPED, "RELOCS_STRIPPED" },
{ IMAGE_FILE_EXECUTABLE_IMAGE, "EXECUTABLE_IMAGE" },
{ IMAGE_FILE_LINE_NUMS_STRIPPED, "LINE_NUMS_STRIPPED" },
{ IMAGE_FILE_LOCAL_SYMS_STRIPPED, "LOCAL_SYMS_STRIPPED" },
{ IMAGE_FILE_AGGRESIVE_WS_TRIM, "AGGRESIVE_WS_TRIM" },
// { IMAGE_FILE_MINIMAL_OBJECT, "MINIMAL_OBJECT" }, // Removed in NT 3.5
// { IMAGE_FILE_UPDATE_OBJECT, "UPDATE_OBJECT" },   // Removed in NT 3.5
// { IMAGE_FILE_16BIT_MACHINE, "16BIT_MACHINE" },   // Removed in NT 3.5
{ IMAGE_FILE_BYTES_REVERSED_LO, "BYTES_REVERSED_LO" },
{ IMAGE_FILE_32BIT_MACHINE, "32BIT_MACHINE" },
{ IMAGE_FILE_DEBUG_STRIPPED, "DEBUG_STRIPPED" },
// { IMAGE_FILE_PATCH, "PATCH" },
{ IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP, "REMOVABLE_RUN_FROM_SWAP" },
{ IMAGE_FILE_NET_RUN_FROM_SWAP, "NET_RUN_FROM_SWAP" },
{ IMAGE_FILE_SYSTEM, "SYSTEM" },
{ IMAGE_FILE_DLL, "DLL" },
{ IMAGE_FILE_UP_SYSTEM_ONLY, "UP_SYSTEM_ONLY" },
{ IMAGE_FILE_BYTES_REVERSED_HI, "BYTES_REVERSED_HI" }
};

WORD_FLAG_DESCRIPTIONS DllCharacteristics[] =
{
{ IMAGE_DLLCHARACTERISTICS_WDM_DRIVER, "WDM_DRIVER" },
};

char *ImageDirectoryNames[] = {
    "EXPORT", "IMPORT", "RESOURCE", "EXCEPTION", "SECURITY", "BASERELOC",
    "DEBUG", "COPYRIGHT", "GLOBALPTR", "TLS", "LOAD_CONFIG",
    "BOUND_IMPORT", "IAT",  // These two entries added for NT 3.51
	"DELAY_IMPORT" };		// This entry added in NT 5

#define NUMBER_IMAGE_DIRECTORY_ENTRYS (sizeof(ImageDirectoryNames)/sizeof(char *))
#define NUMBER_DLL_CHARACTERISTICS (sizeof(DllCharacteristics) / sizeof(WORD_FLAG_DESCRIPTIONS))
#define NUMBER_IMAGE_HEADER_FLAGS (sizeof(ImageFileHeaderCharacteristics) / sizeof(WORD_FLAG_DESCRIPTIONS))

PSTR GetMachineTypeName(WORD wMachineType) {
    switch( wMachineType) {
        case IMAGE_FILE_MACHINE_I386: 	return "32 bit x86";
        case IMAGE_FILE_MACHINE_AMD64: 	return "64 bit AMD x86";
        case IMAGE_FILE_MACHINE_IA64: 	return "64 bit Itanium x86";
        // case IMAGE_FILE_MACHINE_I860:return "i860";
        case IMAGE_FILE_MACHINE_R3000:  return "R3000";
		case 160:                       return "R3000 big endian";
        case IMAGE_FILE_MACHINE_R4000:  return "R4000";
		case IMAGE_FILE_MACHINE_R10000: return "R10000";
        case IMAGE_FILE_MACHINE_ALPHA:  return "Alpha";
        case IMAGE_FILE_MACHINE_POWERPC:return "PowerPC";
        default:    					return "unknown";
    }
}

void DumpHeader(PIMAGE_FILE_HEADER pImageFileHeader) {
    UINT headerFieldWidth = 30;
    UINT i;

    printf("File Header\n");
    printf("  %-*s%04X (%s)\n", headerFieldWidth, "Machine:", pImageFileHeader->Machine, GetMachineTypeName(pImageFileHeader->Machine));
    printf("  %-*s%04X\n",      headerFieldWidth, "Number of Sections:", pImageFileHeader->NumberOfSections);
    printf("  %-*s%08X -> %s\n",headerFieldWidth, "TimeDateStamp:", pImageFileHeader->TimeDateStamp, ctime((time_t *)&pImageFileHeader->TimeDateStamp));
    printf("  %-*s%08X\n",      headerFieldWidth, "PointerToSymbolTable:", pImageFileHeader->PointerToSymbolTable);
    printf("  %-*s%08X\n",      headerFieldWidth, "NumberOfSymbols:", pImageFileHeader->NumberOfSymbols);
    printf("  %-*s%04X\n",      headerFieldWidth, "SizeOfOptionalHeader:", pImageFileHeader->SizeOfOptionalHeader);
    printf("  %-*s%04X\n",      headerFieldWidth, "Characteristics:", pImageFileHeader->Characteristics);
    for ( i=0; i < NUMBER_IMAGE_HEADER_FLAGS; i++) {
        if (pImageFileHeader->Characteristics & ImageFileHeaderCharacteristics[i].flag){
     printf( "    %s\n",        ImageFileHeaderCharacteristics[i].name );
        }
    }
}

void DumpOptionalHeader(PIMAGE_OPTIONAL_HEADER optionalHeader){
    UINT width = 30;
    char *s;
    UINT i;

    printf("Optional Header\n");
    printf("  %-*s%04X\n", width, "Magic", optionalHeader->Magic);
    printf("  %-*s%u.%02u\n", width, "linker version", optionalHeader->MajorLinkerVersion, optionalHeader->MinorLinkerVersion);
    printf("  %-*s%X\n", width, "size of code", optionalHeader->SizeOfCode);
    printf("  %-*s%X\n", width, "size of initialized data", optionalHeader->SizeOfInitializedData);
    printf("  %-*s%X\n", width, "size of uninitialized data", optionalHeader->SizeOfUninitializedData);
    printf("  %-*s%X\n", width, "entrypoint RVA", optionalHeader->AddressOfEntryPoint);
    printf("  %-*s%X\n", width, "base of code", optionalHeader->BaseOfCode);
#ifndef _WIN64
    printf("  %-*s%X\n", width, "base of data", optionalHeader->BaseOfData);
#endif
    printf("  %-*s%X\n", width, "image base", optionalHeader->ImageBase);

    printf("  %-*s%X\n", width, "section align", optionalHeader->SectionAlignment);
    printf("  %-*s%X\n", width, "file align", optionalHeader->FileAlignment);
    printf("  %-*s%u.%02u\n", width, "required OS version", optionalHeader->MajorOperatingSystemVersion, optionalHeader->MinorOperatingSystemVersion);
    printf("  %-*s%u.%02u\n", width, "image version", optionalHeader->MajorImageVersion, optionalHeader->MinorImageVersion);
    printf("  %-*s%u.%02u\n", width, "subsystem version", optionalHeader->MajorSubsystemVersion, optionalHeader->MinorSubsystemVersion);
    printf("  %-*s%X\n", width, "Win32 Version", optionalHeader->Win32VersionValue);
    printf("  %-*s%X\n", width, "size of image", optionalHeader->SizeOfImage);
    printf("  %-*s%X\n", width, "size of headers", optionalHeader->SizeOfHeaders);
    printf("  %-*s%X\n", width, "checksum", optionalHeader->CheckSum);
    switch(optionalHeader->Subsystem) {
        case IMAGE_SUBSYSTEM_NATIVE: s = "Native"; break;
        case IMAGE_SUBSYSTEM_WINDOWS_GUI: s = "Windows GUI"; break;
        case IMAGE_SUBSYSTEM_WINDOWS_CUI: s = "Windows character"; break;
        case IMAGE_SUBSYSTEM_OS2_CUI: s = "OS/2 character"; break;
        case IMAGE_SUBSYSTEM_POSIX_CUI: s = "Posix character"; break;
        default: s = "unknown";
    }
    printf("  %-*s%04X (%s)\n", width, "Subsystem", optionalHeader->Subsystem, s);

// Marked as obsolete in MSDN CD 9
    printf("  %-*s%04X\n", width, "DLL flags", optionalHeader->DllCharacteristics);
    for (i=0; i < NUMBER_DLL_CHARACTERISTICS; i++) {
        if (optionalHeader->DllCharacteristics & DllCharacteristics[i].flag) {
            printf( "  %-*s%s", width, " ", DllCharacteristics[i].name);
        }
    }
    if (optionalHeader->DllCharacteristics)
        printf("\n");

    printf("  %-*s%X\n", width, "stack reserve size", optionalHeader->SizeOfStackReserve);
    printf("  %-*s%X\n", width, "stack commit size",  optionalHeader->SizeOfStackCommit);
    printf("  %-*s%X\n", width, "heap reserve size",  optionalHeader->SizeOfHeapReserve);
    printf("  %-*s%X\n", width, "heap commit size",   optionalHeader->SizeOfHeapCommit);
    printf("  %-*s%X\n", width, "RVAs & sizes", optionalHeader->NumberOfRvaAndSizes);

    printf("\nData Directory\n");
    for ( i=0; i < optionalHeader->NumberOfRvaAndSizes; i++) {
        printf( "  %-12s rva: %08X  size: %08X\n",
            (i >= NUMBER_IMAGE_DIRECTORY_ENTRYS) ? "unused" : ImageDirectoryNames[i],
            optionalHeader->DataDirectory[i].VirtualAddress,
            optionalHeader->DataDirectory[i].Size);
    }
}

void DumpExeFile(PIMAGE_DOS_HEADER dosHeader){
    ULONGLONG base = (ULONGLONG)dosHeader;
    PIMAGE_NT_HEADERS pNTHeader = MakePtr(PIMAGE_NT_HEADERS, dosHeader, dosHeader->e_lfanew);
    if (pNTHeader->Signature != IMAGE_NT_SIGNATURE) {
        exitWithLastError("Not a Portable Executable (PE) EXE\n");
        return;
    }
    DumpHeader((PIMAGE_FILE_HEADER)&pNTHeader->FileHeader);
    printf("\n");
    DumpOptionalHeader((PIMAGE_OPTIONAL_HEADER)&pNTHeader->OptionalHeader);
    printf("\n");
}
