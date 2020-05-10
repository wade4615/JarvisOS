
add_definitions(
    -D__NTDRIVER__
    -DKERNEL)

include_directories(
    ${JARVISOS_SOURCE_DIR}/sdk/lib/drivers/sound/soundblaster
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/libs/sound)

add_library(audio time.c)
add_dependencies(audio bugcodes xdk)
