cmake_minimum_required(VERSION 3.13)

project( Neuton
    VERSION 1.0
    DESCRIPTION "Neuton TinyML library."
    LANGUAGES
        C
)

option(NEUTON_FAST_BUILD "Fast C sources build" OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(source/dsp)
add_subdirectory(source/nn)
add_subdirectory(source/utils)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories (${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        Neuton::DSP
        Neuton::NN
        Neuton::Utils
)