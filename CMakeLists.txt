cmake_minimum_required(VERSION 3.10)

project(OdevProjesi VERSION 1.0)

# IntelliSense için (ÇOK ÖNEMLİ)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


project(OdevProjesi)

# C++ Sürümü
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# .h dosyaları include/ içinde
include_directories(${CMAKE_SOURCE_DIR}/include)

# main + src içindeki tüm .cpp dosyaları
add_executable(OdevProjesi
    main.cpp
    src/MSH.cpp
    src/HistoryStack.cpp
    src/Snapshot.cpp
)
