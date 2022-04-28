#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************


# ==== CONFIGURATION =========================================

set(CLIENT_APP_TARGET client_app)


# ==== SOURCE FILES =========================================

set(HEADERS
    include/imagereceiver.h
)

set(SOURCES
    src/main.cpp
    src/imagereceiver.cpp
)


# ==== FINDING PACKAGES =========================================

# Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network REQUIRED)


# ==== MAKING TARGET =========================================

add_executable(${CLIENT_APP_TARGET} ${HEADERS} ${SOURCES})

target_link_libraries(${CLIENT_APP_TARGET}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Network
        common
)

target_include_directories(${CLIENT_APP_TARGET}
    PUBLIC
        include
)

