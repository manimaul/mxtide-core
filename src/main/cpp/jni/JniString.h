#ifndef MXTIDE_ANDROID_JNISTRING_H
#define MXTIDE_ANDROID_JNISTRING_H

#include <string>
#include <jni.h>

namespace mdr {
    class JniString {

    public:
        static void registerNative(JNIEnv *env);

        static std::string fromJni(JNIEnv *env, jstring str);

        static jstring toJni(JNIEnv *env, std::string &str);

    };
}


#endif //MXTIDE_ANDROID_JNISTRING_H
