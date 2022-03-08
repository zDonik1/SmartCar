#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************


# ==== CONFIGURATION =========================================

set(SERVICES_TARGET services)


# ==== SOURCE FILES =========================================

set(HEADERS
    include/imovement.h
    include/movement.h
    include/iusobstacledetector.h
    include/usobstacledetector.h
    include/ilinetracer.h
    include/doublelinetracer.h
    include/iirobstacledetector.h
    include/irobstacledetector.h
    include/vector.h
)

set(SOURCES
    src/movement.cpp
    src/usobstacledetector.cpp
    src/doublelinetracer.cpp
    src/irobstacledetector.cpp
)
# ==== MAKING TARGET =========================================

add_library(${SERVICES_TARGET} ${HEADERS} ${SOURCES})

target_link_libraries(${SERVICES_TARGET}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        peripherals
)

target_include_directories(${SERVICES_TARGET}
    PUBLIC
        include
)
