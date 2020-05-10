
add_rpc_files(server
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/wine/epm.idl
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/wine/irot.idl)
    

list(APPEND SOURCE
    epmp.c
    irotp.c
    rpcss_main.c
    setup.c
    precomp.h
    ${CMAKE_CURRENT_BINARY_DIR}/epm_s.c
    ${CMAKE_CURRENT_BINARY_DIR}/irot_s.c)

include_directories(${JARVISOS_BINARY_DIR}/sdk/include/jarvisos/wine)
add_executable(rpcss ${SOURCE} rpcss.rc)

if(USE_CLANG_CL)
    add_target_compile_flags(rpcss "-Wno-cast-calling-convention")
endif()

target_link_libraries(rpcss ${PSEH_LIB} wine)
set_module_type(rpcss win32cui UNICODE)
add_importlibs(rpcss advapi32 rpcrt4 msvcrt kernel32 ntdll)
add_pch(rpcss precomp.h SOURCE)
add_cd_file(TARGET rpcss DESTINATION jarvisos/system32 FOR all)
