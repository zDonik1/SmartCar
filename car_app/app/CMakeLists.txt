#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************


# ==== CONFIGURATION =========================================

set(SMART_CAR_TARGET smart_car_app)


# ==== SOURCE FILES =========================================

set(HEADERS
    include/imagesender.h
)

set(SOURCES
    src/main.cpp
    src/imagesender.cpp
)


# ==== FINDING PACKAGES =========================================

# Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network REQUIRED)


# ==== MAKING TARGET =========================================

add_executable(${SMART_CAR_TARGET} ${HEADERS} ${SOURCES})

target_link_libraries(${SMART_CAR_TARGET}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Network
        camera
)

target_include_directories(${SMART_CAR_TARGET}
    PUBLIC
        include
)

# ==== INSTALLATION =========================================

install(TARGETS ${SMART_CAR_TARGET} RUNTIME DESTINATION "/tmp/")
