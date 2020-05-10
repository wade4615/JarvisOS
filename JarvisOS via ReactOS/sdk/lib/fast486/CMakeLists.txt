
include_directories(${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/libs/fast486)

list(APPEND SOURCE
    debug.c
    fast486.c
    opcodes.c
    opgroups.c
    extraops.c
    common.c
    fpu.c)

add_library(fast486 ${SOURCE})
add_dependencies(fast486 xdk)
