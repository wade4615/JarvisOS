
spec2def(dxg.sys dxg.spec)

list(APPEND SOURCE
    main.c
    ddhmg.c
    d3d.c
    dd.c
    ddraw.c
    ddsurf.c
    eng.c
    historic.c
    dxg_int.h)

include_directories(
    ${JARVISOS_SOURCE_DIR}/src/win32ss/include)

add_library(dxg MODULE
    ${SOURCE}
    dxg.rc
    ${CMAKE_CURRENT_BINARY_DIR}/dxg.def)

set_module_type(dxg kernelmodedriver)
add_importlibs(dxg dxgthk ntoskrnl)
add_pch(dxg dxg_int.h SOURCE)
add_cd_file(TARGET dxg DESTINATION jarvisos/system32/drivers FOR all)
