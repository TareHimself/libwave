cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(libwave VERSION 1.0.0 DESCRIPTION "WAVE decoding and encoding")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
# Build a shared library named after the project from the files in `src/`
# file(GLOB_RECURSE SOURCE_FILES "src/*.cc" "src/*.hh")

add_library(${PROJECT_NAME} SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/libwave.cc)

set_target_properties(${PROJECT_NAME} PROPERTIES 
VERSION ${PROJECT_VERSION}
PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/libwave.hh
)

set(LIBWAVE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
# install(TARGETS ${PROJECT_NAME}
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


