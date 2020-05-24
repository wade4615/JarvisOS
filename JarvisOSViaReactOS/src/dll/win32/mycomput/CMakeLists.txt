
add_library(mycomput MODULE
    mycomput.rc)

set_module_type(mycomput win32dll UNICODE ENTRYPOINT 0)

add_cd_file(TARGET mycomput DESTINATION jarvisos/system32 FOR all)
