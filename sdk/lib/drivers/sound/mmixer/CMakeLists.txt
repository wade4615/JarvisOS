
add_definitions(
    -DUNICODE -D_UNICODE
    -DNDEBUG=1)

include_directories(${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/libs/sound)

list(APPEND SOURCE
    controls.c
    filter.c
    midi.c
    mixer.c
    sup.c
    wave.c
    topology.c
    precomp.h)

add_library(mmixer ${SOURCE})
add_pch(mmixer precomp.h SOURCE)
add_dependencies(mmixer bugcodes xdk)
