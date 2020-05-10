add_host_tool(pedump src/pedump.c
                     src/dumpexe.c)

target_link_libraries(pedump PRIVATE host_includes)
