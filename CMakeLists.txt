cmake_minimum_required(VERSION 3.4.1)
link_directories(app/src/main/jniLibs/arm64-v8a)
set(PROJECT_SOURCE_DIR C:/Project/MachineLearning/DeepLearning)

add_library( # Specifies the name of the library.
             nnabla_android

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             app/src/main/cpp/nnabla_interface.cpp )

set(INCLUDE_DIR
        c:/Project/DeepLearning/nnabla-master/include
        )

include_directories("${INCLUDE_DIR}")

#find_library(nnabla NAMES libnnabla.so PATHS app/src/main/jniLibs/arm64-v8a)
#find_library(nnabla_utils NAMES libnnabla_utils.so PATHS app/src/main/jniLibs/arm64-v8a)
#find_library(nnabla  libnnabla.so )
#set_target_properties(lib_opencv PROPERTIES IMPORTED_LOCATION ${pathToProject}/app/src/main/jniLibs/${ANDROID_ABI}/libopencv_java3.so)

#add_library(nnabla SHARED IMPORTED)
#add_library(nnabla_utils SHARED IMPORTED)
#set_target_properties(nnabla PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/app/src/main/jniLibs/arm64-v8a/libnnabla.so)
#set_target_properties(nnabla_utils PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/app/src/main/jniLibs/arm64-v8a/libnnabla_utils.so)

##set_target_properties(nnabla PROPERTIES IMPORTED_LOCATION app/src/main/jniLibs/armeabi-v7a/libnnabla.so)
##set_target_properties(nnabla_utils PROPERTIES IMPORTED_LOCATION app/src/main/jniLibs/armeabi-v7a/libnnabla_utils.so)

message("Hi")
message(${ANDROID_ABI})
#message(${nnabla})
#message(${nnabla_utils})

target_link_libraries(nnabla_android nnabla nnabla_utils)
#target_link_libraries(nnablaif-lib ${nnabla} ${nnabla_utils})
#target_link_libraries(nnablaif-lib ${nnabla_utils})
#target_link_libraries(nnablaif-lib nnabla nnabla_utils)
set_property(TARGET nnabla_android PROPERTY CXX_STANDARD 11)
