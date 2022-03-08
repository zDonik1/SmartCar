#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************


# ==== CONFIGURATION =========================================

set(BEHAVIOR_TARGET behavior)


# ==== SOURCE FILES =========================================

set(HEADERS
)

set(SOURCES
)


# ==== FINDING PACKAGES =========================================

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

find_package(BehaviorTreeV3 REQUIRED)


# ==== MAKING TARGET =========================================

add_library(${BEHAVIOR_TARGET} ${HEADERS} ${SOURCES})

target_link_libraries(${BEHAVIOR_TARGET}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        BT::behaviortree_cpp_v3
)

target_include_directories(${BEHAVIOR_TARGET}
    PUBLIC
        include
)
