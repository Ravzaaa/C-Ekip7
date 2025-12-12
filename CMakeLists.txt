cmake_minimum_required(VERSION 3.10)

project(OdevProjesi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OdevProjesi
    main.cpp
    src/ModeBuilder.cpp
    src/ModeDirector.cpp   # src klasöründeki .cpp dosyaları
)

# include klasörünü projeye tanıtıyoruz
target_include_directories(OdevProjesi PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
