
include_directories(
    ${JARVISOS_SOURCE_DIR}/src/drivers/filesystems/btrfs)

add_library(btrfslib btrfslib.c)
add_dependencies(btrfslib psdk)
