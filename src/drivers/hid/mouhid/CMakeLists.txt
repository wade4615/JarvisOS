
add_definitions(-DDEBUG_MODE)
include_directories(${JARVISOS_SOURCE_DIR}/src/ntoskrnl/include)
add_library(mouhid MODULE mouhid.c mouhid.rc)
set_module_type(mouhid kernelmodedriver)
add_importlibs(mouhid ntoskrnl hal hidparse)
add_cd_file(TARGET mouhid DESTINATION jarvisos/system32/drivers FOR all)
