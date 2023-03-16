cmake_minimum_required(VERSION 3.5)

project(ivu3k VERSION 0.1 LANGUAGES CXX)

##########################
## GUI Setup
##########################

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

#set(PROJECT_SOURCES
#        main.cpp
#        registerswidget.h
#        registerswidget.cpp
#        mainwindow.cpp
#        mainwindow.h
#        mainwindow.ui
#        codewidget.h
#        codewidget.cpp
#        dramwidget.h
#        dramwidget.cpp
#        cachewidget.h
#        cachewidget.cpp
#        asm/assembler.h
#        asm/assembler.cpp
#        mem/registers.h
#)

###########################
# Library setup
###########################
#include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ivu3k
        MANUAL_FINALIZATION
        main.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ivu3k APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ivu3k SHARED
            main.cpp
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ivu3k
	  main.cpp
        )
    endif()
endif()

# Link Qt libraries
target_link_libraries(ivu3k PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Link project library
target_link_libraries(ivu3k PRIVATE asm_lib gui_lib)

set_target_properties(ivu3k PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ivu3k
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ivu3k)
endif()
