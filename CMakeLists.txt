cmake_minimum_required(VERSION 3.10)


project(OdevProjesi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(OdevProjesi 
    main.cpp 
    src/Logger.cpp
    src/Device.cpp
    src/Light.cpp
    src/Camera.cpp
    src/Detector.cpp
    src/TV.cpp
    src/Alarm.cpp
    src/DeviceManager.cpp
    src/DeviceFactory.cpp
)