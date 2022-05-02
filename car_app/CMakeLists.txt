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
add_subdirectory(peripherals)
add_subdirectory(services)
add_subdirectory(behaviors)
add_subdirectory(camera)
