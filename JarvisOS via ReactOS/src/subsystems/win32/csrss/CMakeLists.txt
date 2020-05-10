
include_directories(
    ${JARVISOS_SOURCE_DIR}/src/subsystems/win32/csrsrv/include
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/subsys)

add_executable(csrss csrss.c csrss.rc)
set_module_type(csrss nativecui)
target_link_libraries(csrss nt)
add_importlibs(csrss csrsrv ntdll)
add_dependencies(csrss psdk bugcodes)
add_cd_file(TARGET csrss DESTINATION jarvisos/system32 FOR all)
