cmake_minimum_required(VERSION 3.16)
project(tiktacktoe VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(SFML_INC_DIR "${CMAKE_SOURCE_DIR}/include")
set(SFML_LIB_DIR "${CMAKE_SOURCE_DIR}/library")

add_executable(tiktacktoe main.cpp)

target_include_directories(tiktacktoe PRIVATE ${SFML_INC_DIR})

set(SFML_LIBS
    ${SFML_LIB_DIR}/sfml-graphics.lib
    ${SFML_LIB_DIR}/sfml-window.lib
    ${SFML_LIB_DIR}/sfml-system.lib
    ${SFML_LIB_DIR}/sfml-audio.lib
    ${SFML_LIB_DIR}/sfml-network.lib
)


if (WIN32)

    list(APPEND SFML_LIBS ${SFML_LIB_DIR}/sfml-main-s.lib)
    target_link_libraries(tiktacktoe PRIVATE ${SFML_LIBS})

    target_link_libraries(tiktacktoe PRIVATE
        opengl32
        winmm
        gdi32
        ws2_32
    )
else()
    target_link_libraries(tiktacktoe PRIVATE ${SFML_LIBS})
endif()

set_target_properties(tiktacktoe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)


