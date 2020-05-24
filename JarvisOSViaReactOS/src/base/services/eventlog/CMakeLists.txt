
include_directories(
    ${JARVISOS_SOURCE_DIR}/sdk/lib/evtlib
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/subsys
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/idl
    ${CMAKE_CURRENT_BINARY_DIR})

add_rpc_files(server ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/idl/eventlogrpc.idl)

list(APPEND SOURCE
    eventlog.c
    eventsource.c
    logport.c
    rpc.c
    file.c
    eventlog.h
    ${CMAKE_CURRENT_BINARY_DIR}/eventlogrpc_s.c)

add_executable(eventlog ${SOURCE} eventlog.rc)
add_pch(eventlog eventlog.h SOURCE)

if(NOT MSVC)
    target_link_libraries(eventlog ${PSEH_LIB})
endif()

set_module_type(eventlog win32cui UNICODE)
target_link_libraries(eventlog evtlib)
add_importlibs(eventlog advapi32 rpcrt4 msvcrt kernel32 ntdll)
add_cd_file(TARGET eventlog DESTINATION jarvisos/system32 FOR all)
