
add_subdirectory(cmicontrol)
add_subdirectory(cpl)

set_cpp()

# for WaveRT support
remove_definitions(-D_WIN32_WINNT=0x502)
add_definitions(-D_WIN32_WINNT=0x600)

list(APPEND SOURCE
    adapter.cpp
    common.cpp
    mintopo.cpp
    minwave.cpp
    precomp.h)

add_library(cmipci MODULE
    ${SOURCE}
    guid.cpp
    cmipci.rc)

target_link_libraries(cmipci stdunk libcntpr uuid)
set_module_type(cmipci wdmdriver UNICODE)
add_importlibs(cmipci portcls hal ntoskrnl)

if(USE_CLANG_CL OR (NOT MSVC))
    add_target_compile_flags(cmipci "-Wno-write-strings -Wno-switch")
endif()

add_pch(cmipci precomp.h SOURCE)
add_cd_file(TARGET cmipci DESTINATION jarvisos/system32/drivers FOR all)

if(ARCH STREQUAL "i386")
    add_cd_file(FILE "${CMAKE_CURRENT_SOURCE_DIR}/CM8738-x32.inf" DESTINATION jarvisos/inf FOR all)
else()
    add_cd_file(FILE "${CMAKE_CURRENT_SOURCE_DIR}/CM8738-x64.inf" DESTINATION jarvisos/inf FOR all)
endif()
