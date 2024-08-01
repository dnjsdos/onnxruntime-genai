/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the MIT License.
 */
#include <jni.h>
#include "ort_genai_c.h"
#include "utils.h"

using namespace Helpers;


extern "C" JNIEXPORT void JNICALL
Java_ai_onnxruntime_genai_MultiModalProcessor_destroyMultiModalProcessor(JNIEnv* env, jobject thiz, jlong processor_handle) {
  OgaMultiModalProcessor* processor = reinterpret_cast<OgaMultiModalProcessor*>(processor_handle);
  OgaDestroyMultiModalProcessor(processor);
}

extern "C" JNIEXPORT jlong JNICALL
Java_ai_onnxruntime_genai_MultiModalProcessor_processorProcessImage(JNIEnv* env, jobject thiz, jlong processor_handle,
                                                                    jstring prompt, jlong image_handle) {
  OgaMultiModalProcessor* processor = reinterpret_cast<OgaMultiModalProcessor*>(processor_handle);
  const OgaImages* image = reinterpret_cast<const OgaImages*>(image_handle);

  CString c_prompt{env, prompt};

  OgaNamedTensors* inputTensor = nullptr;
  if (ThrowIfError(env, OgaProcessorProcessImages(processor, c_prompt, image, &inputTensor))) {
    return 0;
  }

  return reinterpret_cast<jlong>(inputTensor);
}

extern "C" JNIEXPORT jlong JNICALL
Java_ai_onnxruntime_genai_MultiModalProcessor_createTokenizerStreamFromProcessor(JNIEnv* env, jobject thiz, jlong processor_handle) {
    OgaMultiModalProcessor* processor = reinterpret_cast<OgaMultiModalProcessor*>(processor_handle);

    OgaTokenizerStream* stream = nullptr;
    
    if (ThrowIfError(env, OgaCreateTokenizerStreamFromProcessor(processor, &stream))) {
        return 0;
    }

    return reinterpret_cast<jlong>(stream);
}
