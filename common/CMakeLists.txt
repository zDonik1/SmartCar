#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************


# ==== CONFIGURATION =========================================

set(COMMON_TARGET common)


# ==== SOURCE FILES =========================================

set(HEADERS
    include/frame.h
    include/common.h
)

set(SOURCES
)


# ==== FINDING PACKAGES =========================================

# Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

# OpenCV
find_package(OpenCV REQUIRED)


# ==== MAKING TARGET =========================================

add_library(${COMMON_TARGET} ${HEADERS} ${SOURCES})

target_link_libraries(${COMMON_TARGET}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        ${OpenCV_LIBS}
)

target_include_directories(${COMMON_TARGET}
    PUBLIC
        include
        ${OpenCV_INCLUDE_DIRS}
)
