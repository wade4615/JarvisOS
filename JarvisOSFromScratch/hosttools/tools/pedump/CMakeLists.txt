add_host_tool(pedump src/pedump.c)

target_link_libraries(pedump PRIVATE host_includes)
