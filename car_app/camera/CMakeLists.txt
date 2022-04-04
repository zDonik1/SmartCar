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
    include/icamera.h
    include/iframe.h
    include/picamera.h
    src/cameraworker.h
)

set(SOURCES
    src/picamera.cpp
    src/cameraworker.cpp
)

add_compile_definitions(QT_NO_KEYWORDS)

# ==== FINDING PACKAGES =========================================

# Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

# wiringpi
find_package(WiringPI REQUIRED)

# pkg-config
find_package(PkgConfig REQUIRED)

# libcamera
pkg_check_modules(LIBCAMERA REQUIRED IMPORTED_TARGET libcamera)


# ==== MAKING TARGET =========================================

add_library(${PERIPHERALS_TARGET} ${HEADERS} ${SOURCES})

target_link_libraries(${PERIPHERALS_TARGET}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core

    PRIVATE
        wiringPi
        PkgConfig::LIBCAMERA
        ${OpenCV_LIBS}
)

target_include_directories(${PERIPHERALS_TARGET}
    PUBLIC
        include

    PRIVATE
        src
        ${OpenCV_INCLUDE_DIRS}
)
