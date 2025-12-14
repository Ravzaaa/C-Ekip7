cmake_minimum_required(VERSION 3.10)

project(OdevProjesi)

cmake_minimum_required(VERSION 3.10)


project(OdevProjesi)

# C++ Sürümü
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# include klasörünü tanıttık
include_directories(include)

# DERLENECEK TÜM KAYNAK DOSYALARI
add_executable(OdevProjesi
    main.cpp
    src/Logger.cpp
    src/DataManager.cpp
)