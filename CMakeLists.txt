cmake_minimum_required(VERSION 3.10)

project(OdevProjesi VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include klasörünü tanıttık
include_directories(include)

# DERLENECEK TÜM KAYNAK DOSYALARI
add_executable(OdevProjesi
    main.cpp
    src/Device.cpp
    src/Light.cpp
    src/Camera.cpp
    src/TV.cpp
    src/Alarm.cpp
    src/Detector.cpp
    
)


# Header yolu (modern CMake stili)
target_include_directories(OdevProjesi PUBLIC ${CMAKE_SOURCE_DIR}/include)
if (MSVC)
    target_compile_options(OdevProjesi PRIVATE /W4)
else()
    target_compile_options(OdevProjesi PRIVATE -Wall -Wextra -pedantic)
endif()


