#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************

# ==== FINDING PACKAGES =========================================

# BehaviorTree.CPP
find_package(BehaviorTreeV3 REQUIRED)


# ==== SUBMODULES =========================================

add_subdirectory(app)
add_subdirectory(training_app)
add_subdirectory(peripherals)

set(AUTOMOC_ON ${CMAKE_AUTOMOC})
set(AUTORCC_ON ${CMAKE_AUTORCC})
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)
add_subdirectory(behaviors)
set(CMAKE_AUTOMOC ${AUTOMOC_ON})
set(CMAKE_AUTOMOC ${AUTORCC_ON})
