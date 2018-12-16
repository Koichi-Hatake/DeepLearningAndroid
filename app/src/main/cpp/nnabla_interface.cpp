/*
 * Copyright (C) 2018 K.Hatakeyama
 * All rights reserved.
 */

#include <jni.h>
#include <string>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <nbla_utils/nnp.hpp>

#include "nnabla_interface.hpp"

extern AAssetManager*	asset_manager;

static NNablaInterface snn;

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
Java_net_seeeno_deeplearning_MainActivity_nativeInitNeuralNetwork(
        JNIEnv *env,
        jobject mgr,
        jstring nnpPath,
        jstring network_name
        ) {

    //using namespace nbla;
    //const std::string nnp_file("network_file.nnp");
    //const std::string input_bin("5.pgm");
    //const std::string executor_name("Runtime");

    //asset_manager = AAssetManager_fromJava(env, mgr);		// asset読み込みマネージャー
    //AAsset*	_asset = AAssetManager_open(asset_manager, name, AASSET_MODE_BUFFER);

    //nbla::Context cpu_ctx{{"cpu:float"}, "CpuCachedArray", "0"};
    //nbla::Context ctx = cpu_ctx;

    const char *nnp_path = env->GetStringUTFChars(nnpPath, 0);
    const char *net_name = env->GetStringUTFChars(network_name, 0);
    snn.initialize(nnp_path, net_name);

    // Create a Nnp object
    //nbla::utils::nnp::Nnp nnp(ctx);

}

extern "C" JNIEXPORT const jfloatArray JNICALL
Java_net_seeeno_deeplearning_MainActivity_nativePredict(
        JNIEnv *env,
        jobject obj,
        jstring pgmPath /*,
        jfloatArray pgmData*/
        ) {
    jfloatArray result;

    const char *pgm_path = env->GetStringUTFChars(pgmPath, 0);

    //jfloat *data = env->GetFloatArrayElements(pgmData, 0);
    //jsize  len = env->GetArrayLength(pgmData);
    result = env->NewFloatArray(10);

    //const float *predict_array = snn.predict(&data[0], pgm_path, len);
    const float *predict_array = snn.predict(NULL, pgm_path, 0);
    //env->ReleaseFloatArrayElements(pgmData, data, 0);
    env->SetFloatArrayRegion(result, 0, 10, predict_array);
    return result;
}