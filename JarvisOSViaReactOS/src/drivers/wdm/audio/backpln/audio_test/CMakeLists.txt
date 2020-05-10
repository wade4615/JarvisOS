
add_definitions(-DPC_NO_IMPORTS)

include_directories(
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/libs/sound
    ${JARVISOS_SOURCE_DIR}/src/drivers/wdm/audio/legacy/wdmaud
    ${JARVISOS_SOURCE_DIR}/sdk/lib/3rdparty/libsamplerate)

add_executable(audio_test audio_test.c)
set_module_type(audio_test win32cui)
target_link_libraries(audio_test libsamplerate)
add_importlibs(audio_test setupapi ksuser msvcrt kernel32)
add_dependencies(audio_test bugcodes)
