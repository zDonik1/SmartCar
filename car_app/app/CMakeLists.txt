#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************


# ==== CONFIGURATION =========================================

set(CAR_APP_TARGET SmartCarApp)


# ==== SOURCE FILES =========================================

set(HEADERS
    include/icontroller.h
    include/controller.h
)

set(SOURCES
    src/main.cpp
    src/controller.cpp
)

# ==== FINDING PACKAGES =========================================

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)


# ==== MAKING TARGET =========================================

add_executable(${CAR_APP_TARGET} ${HEADERS} ${SOURCES})

target_link_libraries(${CAR_APP_TARGET}
    behavior
)

target_include_directories(${CAR_APP_TARGET}
    PUBLIC
        include
)


# ==== INSTALLATION =========================================

if (${CMAKE_CROSSCOMPILING})
    install(TARGETS ${CAR_APP_TARGET}
        RUNTIME DESTINATION "/tmp/")
endif()
