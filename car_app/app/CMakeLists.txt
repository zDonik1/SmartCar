#*************************************************************************
#*
#*   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
#*   @date 24/02/2022
#*
#*************************************************************************


# ==== CONFIGURATION =========================================

set(SMART_CAR_TARGET SmartCarApp)


# ==== MAKING TARGET =========================================

add_executable(${SMART_CAR_TARGET}
    main.cpp
)

target_link_libraries(${SMART_CAR_TARGET}
    peripherals
    services
)


# ==== INSTALLATION =========================================

if (${CMAKE_CROSSCOMPILING})
    install(TARGETS ${SMART_CAR_TARGET}
        RUNTIME DESTINATION "/tmp/")
endif()
