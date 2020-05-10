
add_definitions(-D__WINESRC__)
include_directories(${JARVISOS_SOURCE_DIR}/sdk/include/wine)
add_executable(netsh netsh.c)
target_link_libraries(netsh wine)
set_module_type(netsh win32cui UNICODE)
add_importlibs(netsh msvcrt kernel32 ntdll)
add_cd_file(TARGET netsh DESTINATION jarvisos/system32 FOR all)
