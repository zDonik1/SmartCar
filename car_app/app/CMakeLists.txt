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
    set(MODELS_PATH "/tmp/models/")
else()
    set(BEHAVIORS_PATH "${CMAKE_CURRENT_BINARY_DIR}/behaviors/")
    set(MODELS_PATH "${CMAKE_CURRENT_BINARY_DIR}/models/")
endif()


# ==== SOURCE FILES =========================================

set(HEADERS
    include/controller.h
)

set(SOURCES
    src/main.cpp
    src/controller.cpp
)

set(BEHAVIORS
    behaviors/test_do_once.xml
    behaviors/test_follow_lane.xml
)


# ==== FINDING PACKAGES =========================================

# Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

# TensorFlow Lite
find_library(TFLITE_LIBRARIES
    NAMES tflite
    HINTS "${CMAKE_CURRENT_SOURCE_DIR}/3rd/tflite"
    NO_CMAKE_FIND_ROOT_PATH)


# ==== MAKING TARGET =========================================

add_executable(${SMART_CAR_TARGET} ${HEADERS} ${SOURCES} ${BEHAVIORS})

add_compile_definitions(
    BEHAVIORS_PATH="${BEHAVIORS_PATH}"
    MODELS_PATH="${MODELS_PATH}"
)


target_link_libraries(${SMART_CAR_TARGET}
    Qt${QT_VERSION_MAJOR}::Core
    ${TFLITE_LIBRARIES}
    peripherals
    behaviors
    network
    imageproc
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
install(DIRECTORY models/ DESTINATION ${MODELS_PATH})
