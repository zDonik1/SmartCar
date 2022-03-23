# ==== FINDING PACKAGES =========================================

# Qt
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

# BehaviorTree.CPP
find_package(BehaviorTreeV3 REQUIRED)

# OpenCV
find_package(OpenCV REQUIRED)


# ==== SUBMODULES =========================================

add_subdirectory(app)
add_subdirectory(camera)
