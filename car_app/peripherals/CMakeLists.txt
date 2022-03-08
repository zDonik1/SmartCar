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
    include/imotoractuator.h
    include/motoractuator.h
    include/iussensor.h
    include/ussensor.h
    src/usworker.h
    include/iirsensor.h
    include/irsensor.h
)

set(SOURCES
    src/picamera.cpp
    src/motoractuator.cpp
    src/ussensor.cpp
    src/usworker.cpp
    src/irsensor.cpp
)


# ==== FINDING PACKAGES =========================================

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

find_package(WiringPI REQUIRED)

find_package(OpenCV REQUIRED)


# ==== MAKING TARGET =========================================

add_library(${PERIPHERALS_TARGET} ${HEADERS} ${SOURCES})

target_link_libraries(${PERIPHERALS_TARGET}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core

    PRIVATE
        wiringPi
        ${OpenCV_LIBS}
)

target_include_directories(${PERIPHERALS_TARGET}
    PUBLIC
        include

    PRIVATE
        ${OpenCV_INCLUDE_DIRS}
)
