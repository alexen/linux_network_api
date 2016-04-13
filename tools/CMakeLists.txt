set(LIBNAME tools)

add_library(${LIBNAME}
    src/system.c
    src/network.c
    src/thread.c
    src/io.c
)

target_link_libraries(${LIBNAME}
    error
)