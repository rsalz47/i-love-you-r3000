file(GLOB LIB_SOURCES *.cpp)
file(GLOB LIB_HEADERS *.h)
file(GLOB LIB_UI *.ui)

add_library(asm_lib STATIC ${LIB_SOURCES} ${LIB_HEADERS} ${LIB_UI})
target_include_directories (asm_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

      
# target_link_libraries(${LIB_NAME} PUBLIC Qt6::Widgets)
target_include_directories(asm_lib PRIVATE ${CMAKE_SOURCE_DIR}/src)
# target_link_libraries(ivu3k_lib PUBLIC asm_lib)
