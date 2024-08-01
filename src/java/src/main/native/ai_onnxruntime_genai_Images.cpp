/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT License.
 */
#include <jni.h>
#include "ort_genai_c.h"
#include "utils.h"

using namespace Helpers;

extern "C" JNIEXPORT jlong JNICALL
Java_ai_onnxruntime_genai_Images_loadImage(JNIEnv* env, jobject thiz, jstring image_path) {
    CString c_image_path{env, image_path};    

    OgaImages* images = nullptr;
    if(ThrowIfError(env, OgaLoadImage(c_image_path, &images))) {
        return 0;
    }

    return reinterpret_cast<jlong>(images);
}

extern "C" JNIEXPORT void JNICALL
Java_ai_onnxruntime_genai_Images_destroyImage(JNIEnv* env, jobject thiz, jlong image_handle) {
    OgaImages* image = reinterpret_cast<OgaImages*>(image_handle);
    OgaDestroyImages(image);
}
