#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************


# ==== CONFIGURATION =========================================

set(IMAGEPROC_TARGET imageproc)


# ==== SOURCE FILES =========================================

set(HEADERS
    include/iimageprocessor.h
    include/imageprocessor.h
    include/abstractprocessstage.h
)

set(SOURCES
    src/imageprocessor.cpp
)

# ==== FINDING PACKAGES =========================================

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)


# ==== MAKING TARGET =========================================

add_library(${IMAGEPROC_TARGET} ${HEADERS} ${SOURCES})

target_link_libraries(${IMAGEPROC_TARGET}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        utils
)

target_include_directories(${IMAGEPROC_TARGET}
    PUBLIC
        include
)
