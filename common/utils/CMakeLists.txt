#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************


# ==== CONFIGURATION =========================================

set(UTILS_TARGET utils)


# ==== SOURCE FILES =========================================

set(HEADERS
    include/common.h
    include/frame.h
    include/vector.h
    include/utilities.h
)


# ==== FINDING PACKAGES =========================================

# OpenCV
find_package(OpenCV REQUIRED)


# ==== MAKING TARGET =========================================

add_library(${UTILS_TARGET} INTERFACE ${HEADERS})

target_link_libraries(${UTILS_TARGET}
    INTERFACE
        ${OpenCV_LIBS}
)

target_include_directories(${UTILS_TARGET}
    INTERFACE
        include
        ${OpenCV_INCLUDE_DIRS}
)
