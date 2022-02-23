cmake_minimum_required(VERSION 3.14)

project(SmartCar LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# setting cmake scripts directory
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)


# ==== FINDING PACKAGES =========================================

# Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

# wiringpi
find_package(WiringPI REQUIRED)

# raspicam
find_package(Raspicam REQUIRED)

# BehaviorTree.CPP
find_package(BehaviorTreeV3 REQUIRED)


# ==== MAKING TARGET =========================================

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
    Qt${QT_VERSION_MAJOR}::Core
    wiringPi
    BT::behaviortree_cpp_v3
)


# ==== INSTALLATION =========================================

if (${CMAKE_CROSSCOMPILING})
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "/tmp/")
endif()
