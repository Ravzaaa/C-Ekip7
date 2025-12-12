cmake_minimum_required(VERSION 3.10)

project(OdevProjesi)

cmake_minimum_required(VERSION 3.10)

project(OdevProjesi VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include klasörünü tanıttık
include_directories(include)

# DERLENECEK TÜM KAYNAK DOSYALARI
add_executable(OdevProjesi
    main.cpp
    src/Logger.cpp
    src/DataManager.cpp
)