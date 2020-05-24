
include_directories(
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/idl
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/wine)

add_definitions(-D__WINESRC__)
spec2def(netapi32.dll netapi32.spec ADD_IMPORTLIB)
add_rpc_files(client
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/idl/atsvc.idl
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/idl/browser.idl
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/idl/dssetup.idl
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/idl/netdfs.idl
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/idl/netlogon.idl
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/idl/srvsvc.idl
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/idl/wkssvc.idl)

list(APPEND SOURCE
    apibuf.c
    browser.c
    dfs.c
    display.c
    dssetup.c
    group_new.c
    local_group.c
    misc.c
    nbcmdqueue.c
    nbnamecache.c
    nbt.c
    netapi32.c
    netbios.c
    netlogon.c
    obsolete.c
    schedule.c
    srvsvc.c
    user.c
    utils.c
    wksta.c
    wksta_new.c
    netapi32.h
    ${CMAKE_CURRENT_BINARY_DIR}/atsvc_c.c
    ${CMAKE_CURRENT_BINARY_DIR}/browser_c.c
    ${CMAKE_CURRENT_BINARY_DIR}/dssetup_c.c
    ${CMAKE_CURRENT_BINARY_DIR}/netdfs_c.c
    ${CMAKE_CURRENT_BINARY_DIR}/netlogon_c.c
    ${CMAKE_CURRENT_BINARY_DIR}/srvsvc_c.c
    ${CMAKE_CURRENT_BINARY_DIR}/wkssvc_c.c)

add_library(netapi32 MODULE
    ${SOURCE}
    ${CMAKE_CURRENT_BINARY_DIR}/netapi32_stubs.c
    ${CMAKE_CURRENT_BINARY_DIR}/netapi32.def)

set_module_type(netapi32 win32dll)
target_link_libraries(netapi32 wine ${PSEH_LIB})
add_delay_importlibs(netapi32 samlib secur32)
add_importlibs(netapi32 iphlpapi ws2_32 advapi32 rpcrt4 msvcrt kernel32 ntdll)
add_pch(netapi32 netapi32.h SOURCE)
add_cd_file(TARGET netapi32 DESTINATION jarvisos/system32 FOR all)
