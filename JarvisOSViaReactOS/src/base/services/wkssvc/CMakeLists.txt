
include_directories(${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/idl)
add_rpc_files(server ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/idl/wkssvc.idl)
spec2def(wkssvc.dll wkssvc.spec ADD_IMPORTLIB)

add_library(wkssvc MODULE
    domain.c
    rpcserver.c
    wkssvc.c
    wkssvc.rc
    ${CMAKE_CURRENT_BINARY_DIR}/wkssvc_s.c
    ${CMAKE_CURRENT_BINARY_DIR}/wkssvc.def)

set_module_type(wkssvc win32dll UNICODE)
target_link_libraries(wkssvc wine)
add_importlibs(wkssvc advapi32 rpcrt4 msvcrt kernel32 ntdll)
add_cd_file(TARGET wkssvc DESTINATION jarvisos/system32 FOR all)
