find_library(RASPICAM_LIBRARIES NAMES raspicam)
find_path(RASPICAM_INCLUDE_DIRS
    NAMES raspicam.h
    HINTS ${CMAKE_SYSROOT}/usr/local/include/raspicam
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Raspicam DEFAULT_MSG RASPICAM_LIBRARIES RASPICAM_INCLUDE_DIRS)
