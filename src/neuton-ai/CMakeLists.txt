cmake_minimum_required(VERSION 3.13)

project( Neuton_TinyML
    VERSION 1.0
    DESCRIPTION "Neuton TinyML downloadable solution library."
    LANGUAGES
        C
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/neuton/include)

add_subdirectory(neuton)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        Neuton
)