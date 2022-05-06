#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************


# ==== CONFIGURATION =========================================

set(PERIPHERALS_TARGET peripherals)


# ==== SOURCE FILES =========================================

set(HEADERS
    include/motoractuator.h
    include/ussensor.h
    src/usworker.h
    include/irsensor.h
    include/lccamera.h
)

set(SOURCES
    src/motoractuator.cpp
    src/ussensor.cpp
    src/usworker.cpp
    src/irsensor.cpp
    src/lccamera.cpp
)

add_compile_definitions(QT_NO_KEYWORDS)


# ==== FINDING PACKAGES =========================================

# Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

# wiringPi
find_package(WiringPI REQUIRED)

# OpenCV
#find_package(OpenCV REQUIRED)

# pkg-config
find_package(PkgConfig REQUIRED)

# libcamera
pkg_check_modules(LIBCAMERA REQUIRED IMPORTED_TARGET libcamera)


# ==== MAKING TARGET =========================================

add_library(${PERIPHERALS_TARGET} ${HEADERS} ${SOURCES})

target_link_libraries(${PERIPHERALS_TARGET}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
#        ${OpenCV_LIBS}
        iperipherals

    PRIVATE
        wiringPi
        PkgConfig::LIBCAMERA
)

target_include_directories(${PERIPHERALS_TARGET}
    PUBLIC
        include

#    PRIVATE
#        ${OpenCV_INCLUDE_DIRS}
)
