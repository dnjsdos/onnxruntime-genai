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


// OgaResult* OGA_API_CALL OgaProcessorProcessImages(const OgaMultiModalProcessor* p, const char* prompt, const OgaImages* images_p, OgaNamedTensors** input_tensors) {
//   OGA_TRY
//   auto& processor = *reinterpret_cast<const Generators::MultiModalProcessor*>(p);
//   auto* images = images_p ? reinterpret_cast<const Generators::Images*>(images_p) : nullptr;
//   if (processor.image_processor_ == nullptr)
//     throw std::runtime_error("Image processor is not available for this model.");

//   auto named_tensors = processor.image_processor_->Process(*processor.tokenizer_, prompt, images);
//   *input_tensors = reinterpret_cast<OgaNamedTensors*>(named_tensors.release());
//   return nullptr;
//   OGA_CATCH
// }

extern "C" JNIEXPORT jlong JNICALL
Java_ai_onnxruntime_genai_MultiModalProcessor_processorProcessImage(JNIEnv* env, jobject thiz, jlong processor_handle
                                                                    jstring prompt, jlong image_handle) {
  OgaMultiModalProcessor* processor = reinterpret_cast<OgaMultiModalProcessor*>(processor_handle);
  const OgaImage* image = reinterpret_cast<const OgaImage*>(image_handle);

  OgaNamedTensors* inputTensor = nullptr;
  if (ThrowIfError(env, OgaProcessorProcessImages(processor, prompt, image, &inputTensor))) {
    return 0;
  }

  return reinterpret_cast<jlong>(inputTensor);
}

// extern "C" JNIEXPORT jlong JNICALL
// Java_ai_onnxruntime_genai_Model_generate(JNIEnv* env, jobject thiz, jlong model_handle,
//                                          jlong generator_params_handle) {
//   const OgaModel* model = reinterpret_cast<const OgaModel*>(model_handle);
//   const OgaGeneratorParams* params = reinterpret_cast<const OgaGeneratorParams*>(generator_params_handle);
//   OgaSequences* sequences = nullptr;
//   if (ThrowIfError(env, OgaGenerate(model, params, &sequences))) {
//     return 0;
//   }

//   return reinterpret_cast<jlong>(sequences);
// }

// extern "C" JNIEXPORT jlong JNICALL
// java_ai_onnxruntime_genai_Model_createMultiModalProcessor(JNIEnv* env, jobject thiz,
//                                                           jlong model_handle) {
//   const OgaModel* model = reinterpret_cast<const OgaModel*>(model_handle);    

//   OgaMultiModalProcessor* processor = nullptr;
//   if(ThrowIfError(env, OgaCreateMultiModalProcessor(model, &processor))) {
//     return 0;
//   }

//   return reinterpret_cast<jlong>(processor);
// }

// OgaResult* OGA_API_CALL OgaCreateTokenizerStreamFromProcessor(const OgaMultiModalProcessor* p, OgaTokenizerStream** out) {
//   OGA_TRY
//   *out = reinterpret_cast<OgaTokenizerStream*>(
//       reinterpret_cast<const Generators::MultiModalProcessor*>(
//           p)
//           ->tokenizer_->CreateStream()
//           .release());
//   return nullptr;
//   OGA_CATCH
// }

extern "C" JNIEXPORT jlong JNICALL
Java_ai_onnxruntime_genai_MultiModalProcessor_createTokenizerStreamFromProcessor(JNIEnv* env, jobject thiz, jlong processor_handle) {
    OgaMultiModalProcessor* processor = reinterpret_cast<OgaMultiModalProcessor*>(processor_handle);

    OgaTokenizerStream* stream = nullptr;
    if (ThrowIfError(OgaCreateTokenizerStreamFromProcessor(processor, &stream))) {
        return 0;
    }

    return reinterpret_cast<jlong>(stream);
}
