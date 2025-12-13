cmake_minimum_required(VERSION 3.10)

project(OdevProjesi VERSION 1.0)

# C++ Sürümü
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

# SİHİRLİ KISIM: src klasöründeki TÜM .cpp dosyalarını otomatik bul
file(GLOB SOURCES "src/*.cpp")

# Çalıştırılabilir dosyayı oluştur
# (Ana main dosyamız + src içindeki tüm dosyalar)
add_executable(OdevProjesi 
    main.cpp 
    ${SOURCES}
)