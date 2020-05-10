
add_subdirectory(fonts)
add_subdirectory(inf)
add_subdirectory(nls)
add_subdirectory(sdb)
add_subdirectory(themes)
add_subdirectory(vgafonts)

add_cd_file(FILE ${CMAKE_CURRENT_SOURCE_DIR}/drivers/etc/hosts DESTINATION jarvisos/system32/drivers/etc FOR all)
add_cd_file(FILE ${CMAKE_CURRENT_SOURCE_DIR}/drivers/etc/KDBinit DESTINATION jarvisos/system32/drivers/etc FOR all)
add_cd_file(FILE ${CMAKE_CURRENT_SOURCE_DIR}/drivers/etc/networks DESTINATION jarvisos/system32/drivers/etc FOR all)
add_cd_file(FILE ${CMAKE_CURRENT_SOURCE_DIR}/drivers/etc/protocol DESTINATION jarvisos/system32/drivers/etc FOR all)
add_cd_file(FILE ${CMAKE_CURRENT_SOURCE_DIR}/drivers/etc/services DESTINATION jarvisos/system32/drivers/etc FOR all)
add_cd_file(FILE ${CMAKE_CURRENT_SOURCE_DIR}/sounds/ReactOS_LogOn.wav DESTINATION jarvisos/media FOR all)

add_cd_file(FILE ${CMAKE_CURRENT_SOURCE_DIR}/systemcompatible.manifest DESTINATION jarvisos/winsxs/manifests FOR all)
add_cd_file(FILE ${CMAKE_CURRENT_SOURCE_DIR}/forwardcompatible.manifest DESTINATION jarvisos/winsxs/manifests FOR all)
