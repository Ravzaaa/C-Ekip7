cmake_minimum_required(VERSION 3.0)
project(MSH_Project CXX)

set(CMAKE_CXX_STANDARD 98) 

# BÜTÜN KAYNAK DOSYALARINI LİSTELE
set(SOURCE_FILES
    src/main.cpp
    src/Logger.cpp
    src/DataManager.cpp
)

add_executable(msh_app ${SOURCE_FILES})

# BAŞLIK (HEADER) YOLLARINI GÖSTER
target_include_directories(msh_app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)