add_definitions(-DUNICODE -D_UNICODE -DRDBSS_TRACKER)

include_directories(${JARVISOS_SOURCE_DIR}/src/drivers/filesystems/mup)

list(APPEND SOURCE
    rxce.c)

add_library(rxce ${SOURCE})
add_dependencies(rxce bugcodes xdk)
