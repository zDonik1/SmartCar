#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************


# ==== CONFIGURATION =========================================

set(NETWORK_TARGET network)


# ==== SOURCE FILES =========================================

set(HEADERS
    include/iimagereceiver.h
    include/imagereceiver.h
    include/iimagesender.h
    include/imagesender.h
    src/imagesenderworker.h
    include/remotemovement.h
    include/rmovecontroller.h
)

set(SOURCES
    src/imagereceiver.cpp
    src/imagesender.cpp
    src/imagesenderworker.cpp
    src/remotemovement.cpp
    src/rmovecontroller.cpp
)


# ==== FINDING PACKAGES =========================================

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Network REQUIRED)


# ==== MAKING TARGET =========================================

add_library(${NETWORK_TARGET} ${HEADERS} ${SOURCES})

target_link_libraries(${NETWORK_TARGET}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Network
        services
        utils
)

target_include_directories(${NETWORK_TARGET}
    PUBLIC
        include

    PRIVATE
        src
)
