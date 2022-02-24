#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************


cmake_minimum_required(VERSION 3.14)

project(SmartCar LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# setting cmake scripts directory
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)


# ==== SUBMODULES =========================================

add_subdirectory(car_app)
