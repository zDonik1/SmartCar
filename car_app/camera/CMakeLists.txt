#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************


# ==== CONFIGURATION =========================================

set(CAMERA_TARGET camera)


# ==== SOURCE FILES =========================================

set(HEADERS
    include/icamera.h
    include/lccamera.h
    include/imageprocessor.h
)

set(SOURCES
    src/lccamera.cpp
    src/imageprocessor.cpp
)

add_compile_definitions(QT_NO_KEYWORDS)


# ==== FINDING PACKAGES =========================================

# Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

# OpenCV
find_package(OpenCV REQUIRED)

# pkg-config
find_package(PkgConfig REQUIRED)

# libcamera
pkg_check_modules(LIBCAMERA REQUIRED IMPORTED_TARGET libcamera)


# ==== MAKING TARGET =========================================

add_library(${CAMERA_TARGET} ${HEADERS} ${SOURCES})

target_link_libraries(${CAMERA_TARGET}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        ${OpenCV_LIBS}
        common

    PRIVATE
        PkgConfig::LIBCAMERA
)

target_include_directories(${CAMERA_TARGET}
    PUBLIC
        include

    PRIVATE
        src
        ${OpenCV_INCLUDE_DIRS}
)
