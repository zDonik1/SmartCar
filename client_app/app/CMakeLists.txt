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

set(RESOURCES
    qml.qrc
)

# ==== FINDING PACKAGES =========================================

# Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Network Gui Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network Gui Quick REQUIRED)


# ==== MAKING TARGET =========================================

add_executable(${CLIENT_APP_TARGET} ${HEADERS} ${SOURCES} ${RESOURCES})

target_link_libraries(${CLIENT_APP_TARGET}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Quick
        common
)

target_include_directories(${CLIENT_APP_TARGET}
    PUBLIC
        include
)

