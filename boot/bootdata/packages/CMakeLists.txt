#jarvisos.dff

# jarvisos.dff is the concatenation of two files:
# - jarvisos.dff.in, which is a static one and can be altered to
#   add custom modules/files to jarvisos.cab
# - jarvisos.dff.dyn (dyn as in dynamic) which is generated at generation
#   time by our cmake scripts (from jarvisos.dff.cmake, which contains
#   generator expressions)
# If you want to slip-stream anything into the bootcd, then you want to alter jarvisos.dff.in

# Idea taken from there : http://www.cmake.org/pipermail/cmake/2010-July/038028.html
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/concat.cmake "
    file(READ \${SRC1} S1)
    file(READ \${SRC2} S2)
    file(WRITE \${DST} \"\${S1}\${S2}\")
")

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/jarvisos.dff.cmake "")

# This generates jarvisos.dff.dyn by processing the generator expressions
file(GENERATE
     OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/jarvisos.dff.$<CONFIG>.dyn
     INPUT ${CMAKE_CURRENT_BINARY_DIR}/jarvisos.dff.cmake)

# This finalizes jarvisos.dff by concat-ing the two files: one generated and one static containing the optional file.
# please keep it this way as it permits to add files to jarvisos.dff.in without having to run cmake again
# and also avoids rebuilding jarvisos.cab in case nothing changes after a cmake run
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/jarvisos.dff
    COMMAND ${CMAKE_COMMAND} -D SRC1=${CMAKE_CURRENT_SOURCE_DIR}/jarvisos.dff.in
                             -D SRC2=${CMAKE_CURRENT_BINARY_DIR}/jarvisos.dff.$<CONFIG>.dyn
                             -D DST=${CMAKE_CURRENT_BINARY_DIR}/jarvisos.dff.maydiff
                             -P ${CMAKE_CURRENT_BINARY_DIR}/concat.cmake
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
                             ${CMAKE_CURRENT_BINARY_DIR}/jarvisos.dff.maydiff
                             ${CMAKE_CURRENT_BINARY_DIR}/jarvisos.dff
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/jarvisos.dff.in
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/jarvisos.dff.$<CONFIG>.dyn)

add_custom_target(
    jarvisos_cab_inf
    COMMAND native-cabman -C ${CMAKE_CURRENT_BINARY_DIR}/jarvisos.dff -L ${CMAKE_CURRENT_BINARY_DIR} -I -P ${JARVISOS_SOURCE_DIR}
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/jarvisos.dff native-cabman)

add_cd_file(
    TARGET jarvisos_cab_inf
    FILE ${CMAKE_CURRENT_BINARY_DIR}/jarvisos.inf
    DESTINATION jarvisos
    NO_CAB FOR bootcd regtest)
