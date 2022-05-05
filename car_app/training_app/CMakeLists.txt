#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************


# ==== CONFIGURATION =========================================

set(CAR_TRAINING_APP_TARGET car_training_app)


# ==== SOURCE FILES =========================================

set(HEADERS
    include/controller.h
)

set(SOURCES
    src/main.cpp
    src/controller.cpp
)


# ==== FINDING PACKAGES =========================================

# Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)


# ==== MAKING TARGET =========================================

add_executable(${CAR_TRAINING_APP_TARGET} ${HEADERS} ${SOURCES})

target_link_libraries(${CAR_TRAINING_APP_TARGET}
    Qt${QT_VERSION_MAJOR}::Core
    peripherals
    camera
    network
)

target_include_directories(${CAR_TRAINING_APP_TARGET}
    PUBLIC
        include
)


# ==== INSTALLATION =========================================

install(TARGETS ${CAR_TRAINING_APP_TARGET} RUNTIME DESTINATION "/tmp/")
