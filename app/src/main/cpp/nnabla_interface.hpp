/*
 * Copyright (C) 2018 Koichi Hatakeyama
 * All rights reserved.
 */

#ifndef DEEPLEARNING_NNABLA_INTERFACE_H
#define DEEPLEARNING_NNABLA_INTERFACE_H

#include <nbla_utils/nnp.hpp>
#include <android/log.h>

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

class NNablaInterface {

private:
    nbla::utils::nnp::Nnp *mNnp = NULL;
    std::shared_ptr<nbla::utils::nnp::Executor> mExecutor;
    nbla::Context mContext{{"cpu:float"}, "CpuCachedArray", "0"};
    std::string mPgmFile;
    const char *TAG = "NativeCode";

    /** Read PGM image with MNIST shape.

    This easy implementation does not support all possible P5 PGM format.

   @param[in] filename Path to Raw PGM file (P5). 28x28 maxval must be 255.
   @param[out] data Data will be store into this array.
    */
    void read_pgm_mnist(const std::string &filename, uint8_t *data) {
        using namespace nbla;
        std::ifstream file(filename);
        std::string buff;

        // Read P5.
        getline(file, buff);
        NBLA_CHECK(buff == "P5", error_code::value, "Only P5 is supported (%s).",
                   buff.c_str());
        // Read comment line
        std::getline(file, buff);
        if (!buff.empty()) {
            NBLA_CHECK(buff[0] == '#', error_code::value,
                       "Comment line must start with #. (%s)", buff.c_str());
        }

        // Read image shape.
        std::getline(file, buff);
        std::stringstream ss(buff);
        int width;
        int height;
        ss >> width;
        ss >> height;
        NBLA_CHECK(width == 28 && height == 28, error_code::value,
                   "Image size must be 28 x 28 (given %d x %d).", width, height);

        // Read max value.
        std::getline(file, buff);
        ss.clear();
        ss.str(buff);
        int maxval;
        ss >> maxval;
        NBLA_CHECK(maxval == 255, error_code::value, "maxVal must be 255 (given %d).",
                   maxval);

        // Read image data.
        NBLA_CHECK(file.read((char *)data, width * height * sizeof(uint8_t)),
                   error_code::value, "Only read %d bytes", (int)(file.gcount()));
    }


public:
    bool initialize(std::string nnp_file, std::string network_name) {
        if (mNnp != NULL) {
            delete mNnp;
        }
        mNnp = new nbla::utils::nnp::Nnp(mContext);
        mNnp->add(nnp_file);
        mExecutor = mNnp->get_executor(network_name);
        mExecutor->set_batch_size(1);

        return true;
    }

    const float *predict(const int *pgm_data, const int len) {

        nbla::CgVariablePtr x = mExecutor->get_data_variables().at(0).variable;
        uint8_t *data = x->variable()->cast_data_and_get_pointer<uint8_t>(mContext);
        __android_log_print(ANDROID_LOG_VERBOSE, TAG, "Input Length: %d", len);
        __android_log_print(ANDROID_LOG_VERBOSE, TAG, "Buffer Size: %d", x->variable()->size());

        // Copy pgm data array to input buffer.
        for (int i=0; i < len; i++) {
            data[i] = (uint8_t)pgm_data[i];
            //__android_log_print(ANDROID_LOG_VERBOSE, TAG, "%d: 0x%02x", i, data[i]);
        }

        mExecutor->execute();
        nbla::CgVariablePtr y = mExecutor->get_output_variables().at(0).variable;
        const float *y_data = y->variable()->get_data_pointer<float>(mContext);

        return y_data;
    }
};

#endif //DEEPLEARNING_NNABLA_INTERFACE_H
