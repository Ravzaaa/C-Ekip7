cmake_minimum_required(VERSION 3.10)

project(OdevProjesi VERSION 1.0)

# C++ Sürümü
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# IntelliSense için (ÇOK ÖNEMLİ)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Tüm kaynak (source) dosyalarınızı tanımlıyoruz (Geliştirici 1-7'nin tüm dosyaları)
set(SOURCE_FILES
    # Ana dosya
    main.cpp

    # Tüm src dosyaları
    src/Alarm.cpp
    src/Camera.cpp
    src/DataManager.cpp
    src/Detector.cpp
    src/Device.cpp
    src/DeviceFactory.cpp
    src/DeviceManager.cpp
    src/HistoryStack.cpp
    src/Light.cpp
    src/Logger.cpp
    src/ModeBuilder.cpp
    src/ModeDirector.cpp
    src/ModeManager.cpp
    src/MSH.cpp
    src/SecurityHandlers.cpp
    src/SecurityManager.cpp
    src/Snapshot.cpp
    src/Timer.cpp
    src/TV.cpp
)

# Yürütülebilir dosyayı oluştur
add_executable(OdevProjesi ${SOURCE_FILES})

# include/ klasörünü başlık dosyaları için dahil et
target_include_directories(OdevProjesi PRIVATE include)