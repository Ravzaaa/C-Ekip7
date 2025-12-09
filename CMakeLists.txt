cmake_minimum_required(VERSION 3.10)

# Proje Adı
project(MSH_Project)

# C++ Sürümü
set(CMAKE_CXX_STANDARD 17)

# Header dosyalarımız 'include' klasöründe, bunu tanıtıyoruz
include_directories(include)

# Programı oluşturacak dosyaları tek tek yazıyoruz.
# Dosyalar 'src' klasöründe olduğu için başına 'src/' ekliyoruz.
add_executable(MSH_Project 
    src/main.cpp 
    src/MSH.cpp
)