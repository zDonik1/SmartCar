#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************


# ==== CONFIGURATION =========================================

set(SMART_CAR_TARGET smart_car_app)

if (${CMAKE_CROSSCOMPILING})
    set(BEHAVIORS_PATH "/tmp/behaviors/")
else()
    set(BEHAVIORS_PATH "${CMAKE_CURRENT_BINARY_DIR}/behaviors/")
endif()


# ==== SOURCE FILES =========================================

set(HEADERS
    include/controller.h
    include/iimagesender.h
    include/imagesender.h
    src/imagesenderworker.h
    include/rmovecontroller.h
)

set(SOURCES
    src/main.cpp
    src/controller.cpp
    src/imagesender.cpp
    src/imagesenderworker.cpp
    src/rmovecontroller.cpp
)
set(BEHAVIORS
    behaviors/test_do_once.xml
)

# ==== FINDING PACKAGES =========================================

# Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network REQUIRED)


# ==== MAKING TARGET =========================================

add_executable(${SMART_CAR_TARGET} ${HEADERS} ${SOURCES} ${BEHAVIORS})

add_compile_definitions(BEHAVIORS_PATH="${BEHAVIORS_PATH}")

target_link_libraries(${SMART_CAR_TARGET}
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    peripherals
    behaviors
    camera
)

target_include_directories(${SMART_CAR_TARGET}
    PUBLIC
        include

    PRIVATE
        src
)


# ==== INSTALLATION =========================================

install(TARGETS ${SMART_CAR_TARGET} RUNTIME DESTINATION "/tmp/")
install(DIRECTORY behaviors/ DESTINATION ${BEHAVIORS_PATH})
