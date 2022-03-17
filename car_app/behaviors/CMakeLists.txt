#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************


# ==== CONFIGURATION =========================================

set(BEHAVIORS_TARGET behaviors)


# ==== SOURCE FILES =========================================

set(HEADERS
    include/customporttypes.h
    include/move.h
)

set(SOURCES
    src/move.cpp
)


# ==== FINDING PACKAGES =========================================

find_package(BehaviorTreeV3 REQUIRED)


# ==== MAKING TARGET =========================================

add_library(${BEHAVIORS_TARGET} ${HEADERS} ${SOURCES})

target_link_libraries(${BEHAVIORS_TARGET}
    PUBLIC
        BT::behaviortree_cpp_v3
        services
)

target_include_directories(${BEHAVIORS_TARGET}
    PUBLIC
        include
)
