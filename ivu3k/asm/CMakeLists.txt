add_library(asm STATIC assembler.h assembler.cpp)
target_include_directories(asm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_link_libraries(asm PUBLIC Qt6::Gui)
