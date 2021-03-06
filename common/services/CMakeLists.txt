#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************


# ==== CONFIGURATION =========================================

set(SERVICES_TARGET services)


# ==== SOURCE FILES =========================================

set(HEADERS
    include/imovement.h
    include/movement.h
    include/iusobstacledetector.h
    include/usobstacledetector.h
    include/iavoider.h
    include/avoider.h
    include/doublelinetracer.h
    include/obstacleavoider.h
    include/debugmovement.h
)

set(SOURCES
    src/movement.cpp
    src/usobstacledetector.cpp
    src/avoider.cpp
    src/doublelinetracer.cpp
    src/obstacleavoider.cpp
    src/debugmovement.cpp
)


# ==== FINDING PACKAGES =========================================

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)


# ==== MAKING TARGET =========================================

add_library(${SERVICES_TARGET} ${HEADERS} ${SOURCES})

target_link_libraries(${SERVICES_TARGET}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        iperipherals
        utils
)

target_include_directories(${SERVICES_TARGET}
    PUBLIC
        include
)
