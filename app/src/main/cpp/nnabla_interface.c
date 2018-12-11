//
// Created by hatake on 2018/12/11.
//

//#include <nbla_utils/nnp.hpp>

//#include <cassert>
//#include <fstream>
//#include <iomanip>
//#include <iostream>
//#include <sstream>
//#include <string>

#include <jni.h>

#define ABI "armeabi-v8a"

jstring
Java_com_sonymobile_deeplearning_MainActivity_stringFromJNI( JNIEnv* env, jobject thiz )
{
    //return (*env)->NewStringUTF(env, "Hello from JNI !  Compiled with ABI " ABI ".");
    return (*env)->NewStringUTF(env, "Hello from JNI !  Compiled with ABI ");

}
