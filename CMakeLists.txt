cmake_minimum_required(VERSION 3.4)

#Устанавливаем собственные флаги для режима сборки Debug
set(CMAKE_C_FLAGS_DEBUG "-ggdb3 -O0 -DDEBUG")

# Устанавливаем требования к стандарту компиляции и преврящяем все предупреждения в ошибки
add_definitions(-std=gnu99)
add_definitions(-Wall -Wpedantic -Werror)

# Директива #include должна искать хедеры от корня проекта
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(error)
add_subdirectory(tools)
add_subdirectory(main)