
include_directories(${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/dll/devmgr)

add_executable(devmgmt devmgmt.c devmgmt.rc)
set_module_type(devmgmt win32gui UNICODE)
add_importlibs(devmgmt devmgr msvcrt kernel32)
add_cd_file(TARGET devmgmt DESTINATION jarvisos/system32 FOR all)
