//
// Created by hatake on 2018/12/11.
//

#include <jni.h>
#include <string>

#include <nbla_utils/nnp.hpp>

extern "C" JNIEXPORT jstring
JNICALL
Java_net_seeeno_deeplearning_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hi from C++";
    return env->NewStringUTF(hello.c_str());
}

//using nbla::Context;

extern "C" JNIEXPORT void
JNICALL
Java_net_seeeno_deeplearning_MainActivity_initNetwork(
        JNIEnv *env,
        jobject
        ) {

    //using namespace nbla;

    const std::string nnp_file("network_file.nnp");
    const std::string input_bin("5.pgm");
    const std::string executor_name("Runtime");

    nbla::Context cpu_ctx{{"cpu:float"}, "CpuCachedArray", "0"};
    nbla::Context ctx = cpu_ctx;

    // Create a Nnp object
    nbla::utils::nnp::Nnp nnp(ctx);

}