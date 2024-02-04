cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(libwave VERSION 1.0.0 DESCRIPTION "WAVE decoding and encoding")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


add_library(${PROJECT_NAME} SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/libwave.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/libwave.hpp)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include> 
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION include/
)

install(
    TARGETS libwave
    EXPORT libwave-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

install(
    EXPORT libwave-targets
    FILE libwaveConfig.cmake
    NAMESPACE libwave::
    DESTINATION lib/cmake/libwave
)


