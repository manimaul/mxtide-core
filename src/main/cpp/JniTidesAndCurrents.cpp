#include <jni.h>
#include "TidesAndCurrents.h"

extern "C" {

JNIEXPORT jlong JNICALL
Java_com_mxmariner_mxtide_internal_TidesAndCurrents_create(JNIEnv *env,
                                                           jclass obj) {
    return reinterpret_cast<jlong>(new mdr::TidesAndCurrents());
}

JNIEXPORT void JNICALL
Java_com_mxmariner_mxtide_internal_TidesAndCurrents_delete(JNIEnv *env,
                                                           jclass obj,
                                                           jlong ptr) {
    delete reinterpret_cast<mdr::TidesAndCurrents *>(ptr);
}

JNIEXPORT void JNICALL
Java_com_mxmariner_mxtide_internal_TidesAndCurrents_addHarmonicsFile(JNIEnv *env,
                                                                     jclass type,
                                                                     jlong ptr,
                                                                     jstring pPath) {
    const char *path = (*env).GetStringUTFChars(pPath, NULL);
    mdr::TidesAndCurrents *tidesAndCurrents = reinterpret_cast<mdr::TidesAndCurrents *>(ptr);
    tidesAndCurrents->addHarmonicsFile(path);
    (*env).ReleaseStringUTFChars(pPath, path);
}

JNIEXPORT jint JNICALL
Java_com_mxmariner_mxtide_internal_TidesAndCurrents_stationCount(JNIEnv *env,
                                                                 jclass type,
                                                                 jlong ptr) {
    mdr::TidesAndCurrents *tidesAndCurrents = reinterpret_cast<mdr::TidesAndCurrents *>(ptr);
    return static_cast<jint>(tidesAndCurrents->stationCount());
}

}