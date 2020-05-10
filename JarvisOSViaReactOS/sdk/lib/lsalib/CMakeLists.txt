
include_directories(${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/subsys)

add_library(lsalib lsa.c)
add_dependencies(lsalib xdk)

add_library(ntlsalib lsa.c)
add_target_compile_definitions(ntlsalib _NTSYSTEM_)
add_dependencies(ntlsalib xdk)
