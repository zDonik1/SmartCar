#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************


# ==== CONFIGURATION =========================================

set(CLIENT_TRAINING_APP_TARGET client_training_app)


# ==== SOURCE FILES =========================================

set(HEADERS
    include/controller.h
)

set(SOURCES
    src/main.cpp
    src/controller.cpp
)

set(RESOURCES
    qml.qrc
)


# ==== FINDING PACKAGES =========================================

# Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Quick REQUIRED)


# ==== MAKING TARGET =========================================

add_executable(${CLIENT_TRAINING_APP_TARGET} ${HEADERS} ${SOURCES} ${RESOURCES})

target_link_libraries(${CLIENT_TRAINING_APP_TARGET}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Quick
        network
)

target_include_directories(${CLIENT_TRAINING_APP_TARGET}
    PUBLIC
        include
)

