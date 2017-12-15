#include "Jni.h"

jclass mdr::Jni::findJavaClass(JNIEnv *env, const char *name) {
    jclass localRef = env->FindClass(name);
    jclass globalRef = (jclass) env->NewGlobalRef(localRef);
    env->DeleteLocalRef(localRef);
    return globalRef;
}

extern "C" {

JNIEXPORT jint
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    return JNI_VERSION_1_6;
}

}
