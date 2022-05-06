#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************


# ==== CONFIGURATION =========================================

set(IPERIPHERALS_TARGET iperipherals)


# ==== SOURCE FILES =========================================

set(HEADERS
    include/imotoractuator.h
    include/isensor.h
    include/iussensor.h
    include/iirsensor.h
    include/icamera.h
)

set(SOURCES
    src/iussensor.cpp
    src/iirsensor.cpp
)


# ==== FINDING PACKAGES =========================================

# Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)


# ==== MAKING TARGET =========================================

add_library(${IPERIPHERALS_TARGET} ${HEADERS} ${SOURCES})

target_link_libraries(${IPERIPHERALS_TARGET}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        utils
)

target_include_directories(${IPERIPHERALS_TARGET}
    PUBLIC
        include
)
