cmake_minimum_required(VERSION 3.10)

project(OdevProjesi)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OdevProjesi 
    main.cpp
    src/Device.cpp
    src/Logger.cpp
)

target_include_directories(OdevProjesi PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)