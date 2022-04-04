# ==== FINDING PACKAGES =========================================

# BehaviorTree.CPP
find_package(BehaviorTreeV3 REQUIRED)

# OpenCV
find_package(OpenCV REQUIRED)


# ==== SUBMODULES =========================================

add_subdirectory(app)
add_subdirectory(camera)
