
include_directories(${JARVISOS_SOURCE_DIR}/src/win32ss/include)

add_library(gditools
    gditools.c)

add_dependencies(gditools xdk)
