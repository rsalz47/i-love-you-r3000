file(GLOB LIB_SOURCES *.cpp)
file(GLOB LIB_HEADERS *.h)
file(GLOB LIB_UI *.ui)

add_library(gui_lib STATIC ${LIB_SOURCES} ${LIB_HEADERS} ${LIB_UI})
target_include_directories (gui_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(gui_lib PRIVATE Qt6::Widgets)
target_include_directories(gui_lib PRIVATE ${CMAKE_SOURCE_DIR}/src)
