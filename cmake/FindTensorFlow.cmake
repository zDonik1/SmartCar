find_library(TENSORFLOW_LIBRARIES
    NAMES tensorflow
    HINTS /usr/local/lib
    REQUIRED)
find_path(TENSORFLOW_INCLUDE_DIRS
    NAMES tensorflow/lite/interpreter.h
    HINTS /usr/local/include
    REQUIRED)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(TensorFlow DEFAULT_MSG TENSORFLOW_LIBRARIES TENSORFLOW_INCLUDE_DIRS)
