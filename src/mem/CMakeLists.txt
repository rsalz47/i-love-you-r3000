file(GLOB LIB_HEADERS *.h)

option(GUI "build with GUI" ON)

if(GUI)
  add_library(mem_lib STATIC memory.cpp cache.cpp  ${LIB_HEADERS})
  target_include_directories (mem_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  
  target_include_directories(mem_lib PRIVATE ${CMAKE_SOURCE_DIR}/src)
else()
  cmake_minimum_required(VERSION 3.13)
  set(CMAKE_CXX_STANDARD 17)
  project(mem-driver)
  add_executable(mem-driver mem-driver.cpp ${LIB_HEADERS})
  target_include_directories (mem-driver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endif()
