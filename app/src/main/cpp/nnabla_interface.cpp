/*
 * Copyright (C) 2018 Koichi Hatakeyama
 * All rights reserved.
 */

#include <jni.h>
#include <string>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <nbla_utils/nnp.hpp>

#include "nnabla_interface.hpp"

static NNablaInterface snn;

extern "C" JNIEXPORT void
JNICALL
Java_net_seeeno_deeplearning_MainActivity_nativeInitNeuralNetwork(
        JNIEnv *env,
        jobject mgr,
        jstring nnpPath,
        jstring network_name
        ) {

    const char *nnp_path = env->GetStringUTFChars(nnpPath, 0);
    const char *net_name = env->GetStringUTFChars(network_name, 0);
    snn.initialize(nnp_path, net_name);

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

    const float *predict_array = snn.predict(pgm_path);
    env->SetFloatArrayRegion(result, 0, 10, predict_array);

    return result;
}
