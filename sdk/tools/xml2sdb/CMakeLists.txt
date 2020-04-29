
add_definitions(-DSDBWRITE_HOSTTOOL=1)

list(APPEND SOURCE
    main.cpp
    tinyxml2.cpp
    xml2sdb.cpp
    xml2sdb.h
    ${JARVISOS_SOURCE_DIR}/src/dll/appcompat/apphelp/sdbwrite.c
    ${JARVISOS_SOURCE_DIR}/src/dll/appcompat/apphelp/sdbstringtable.c)

include_directories(
    ${JARVISOS_SOURCE_DIR}/src/dll/appcompat/apphelp
    ${JARVISOS_SOURCE_DIR}/sdk/include/jarvisos/appcompat)
add_host_tool(xml2sdb ${SOURCE})
target_link_libraries(xml2sdb PRIVATE host_includes)

if(MSVC)
    # Disable warning "'=': conversion from 'a' to 'b', possible loss of data"
    add_target_compile_flags(xml2sdb "/wd4244")
else()
    add_target_compile_flags(xml2sdb "-fshort-wchar")
endif()
