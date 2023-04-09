file(GLOB LIB_HEADERS *.h)

option(GUI "build with GUI" ON)

if(GUI)
    add_library(asm_lib STATIC assembler.cpp ${LIB_HEADERS})
    target_include_directories (asm_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

    target_include_directories(asm_lib PRIVATE ${CMAKE_SOURCE_DIR}/src)
else()
    cmake_minimum_required(VERSION 3.13)
    set(CMAKE_CXX_STANDARD 17)
    project(asm)
    add_executable(asm assembler.cpp asm_main.cpp ${LIB_HEADERS})
    target_include_directories (asm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endif()
