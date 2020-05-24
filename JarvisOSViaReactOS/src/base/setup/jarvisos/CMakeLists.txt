
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib
#    ${JARVISOS_SOURCE_DIR}/src/base/setup/lib
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/libs/zlib
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/drivers)

list(APPEND SOURCE
    spapisup/fileqsup.c
    spapisup/infsupp.c
    drivepage.c
    reactos.c
    treelist.c
    reactos.h)

file(GLOB reactos_rc_deps res/*.*)
add_rc_deps(reactos.rc ${reactos_rc_deps})
add_executable(jarvisos ${SOURCE} reactos.rc)
set_module_type(jarvisos win32gui UNICODE)
add_pch(jarvisos reactos.h SOURCE)
target_link_libraries(jarvisos uuid setuplib ext2lib vfatlib btrfslib)
add_importlibs(jarvisos advapi32 gdi32 user32 comctl32 shlwapi setupapi msvcrt kernel32 ntdll)
add_cd_file(TARGET jarvisos DESTINATION jarvisos NO_CAB FOR bootcd)
