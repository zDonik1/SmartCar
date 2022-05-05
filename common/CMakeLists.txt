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
    include/common.h
    include/frame.h
    include/vector.h
)


# ==== FINDING PACKAGES =========================================

# OpenCV
find_package(OpenCV REQUIRED)


# ==== MAKING TARGET =========================================

add_library(${COMMON_TARGET} INTERFACE ${HEADERS})

target_link_libraries(${COMMON_TARGET}
    INTERFACE
        ${OpenCV_LIBS}
)

target_include_directories(${COMMON_TARGET}
    INTERFACE
        include
        ${OpenCV_INCLUDE_DIRS}
)
