set(LIBNAME tools)

add_library(${LIBNAME}
    src/system.c
    src/network.c
    src/thread.c
    src/io.c
    src/hostent_parser.c
)

target_link_libraries(${LIBNAME}
    error
)