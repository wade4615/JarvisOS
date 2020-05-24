
add_definitions(${I18N_DEFS})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib
#    ${JARVISOS_SOURCE_DIR}/src/base/setup/lib
    ${JARVISOS_SOURCE_DIR}/sdk/lib/inflib
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/libs/zlib
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/drivers)

list(APPEND SOURCE
    spapisup/cabinet.c
    spapisup/fileqsup.c
    spapisup/infsupp.c
    chkdsk.c
    cmdcons.c
    console.c
    consup.c
    devinst.c
    format.c
    fslist.c
    genlist.c
    keytrans.c
    mui.c
    partlist.c
    progress.c
    usetup.c
    usetup.h)

add_executable(usetup ${SOURCE} usetup.rc)

if(USE_CLANG_CL)
    add_target_compile_flags(usetup "-Wno-invalid-source-encoding")
endif()

add_pch(usetup usetup.h SOURCE)
set_module_type(usetup nativecui)
target_link_libraries(usetup inflib setuplib zlib_solo ext2lib vfatlib btrfslib)
add_importlibs(usetup ntdll)
add_cd_file(TARGET usetup DESTINATION jarvisos/system32 NO_CAB NAME_ON_CD smss.exe FOR bootcd regtest)
