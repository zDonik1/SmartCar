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
)

set(SOURCES
    src/picamera.cpp
)


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
