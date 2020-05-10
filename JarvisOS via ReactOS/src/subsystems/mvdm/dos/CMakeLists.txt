
include_directories(${JARVISOS_SOURCE_DIR}/src/subsystems/mvdm/dos)
add_asm16_bin(command ${CMAKE_CURRENT_BINARY_DIR}/command.com 0x0100 command.S)
add_cd_file(TARGET command FILE ${CMAKE_CURRENT_BINARY_DIR}/command.com DESTINATION jarvisos/system32 FOR all)
