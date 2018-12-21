cmake_minimum_required(VERSION 3.4.1)
link_directories(app/src/main/jniLibs/arm64-v8a)
set(PROJECT_SOURCE_DIR C:/Project/MachineLearning/DeepLearning)

add_library( # Specifies the name of the library.
             nnabla_android

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             app/src/main/cpp/nnabla_interface.cpp )

include_directories(app/src/main/cpp/include)
target_link_libraries(nnabla_android nnabla nnabla_utils)

set_property(TARGET nnabla_android PROPERTY CXX_STANDARD 11)
