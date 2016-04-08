set(LIBNAME wrapfunc)

add_library(${LIBNAME}
    src/network.c
    src/thread.c
)

target_link_libraries(${LIBNAME}
    error
)