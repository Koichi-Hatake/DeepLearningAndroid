cmake_minimum_required(VERSION 3.4.1)
link_directories(app/src/main/jniLibs/arm64-v8a)
set(PROJECT_SOURCE_DIR C:/Project/DeepLearning/App/DeepLearning)

add_library( # Specifies the name of the library.
             nnabla_android

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             app/src/main/cpp/nnabla_interface.cpp )

find_library( # Defines the name of the path variable that stores the
        # location of the NDK library.
        log-lib

        # Specifies the name of the NDK library that
        # CMake needs to locate.
        log )

include_directories(app/src/main/cpp/include)
target_link_libraries(
        nnabla_android nnabla nnabla_utils

        # Links the log library to the target library.
        ${log-lib} )

set_property(TARGET nnabla_android PROPERTY CXX_STANDARD 11)
