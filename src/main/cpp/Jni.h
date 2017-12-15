#ifndef PROJECT_JNI_H
#define PROJECT_JNI_H

#include <jni.h>
#include "JniTidesAndCurrents.h"

/*
 * How to find java class,field and method signatures:
 * $unzip /Library/Java/JavaVirtualMachines/jdk1.8.0_74.jdk/Contents/Home/jre/lib/rt.jar
 * $javap -s ./java/lang/Object.class
 * $javap -s fla-android/authentication/build/intermediates/classes/debug/com/nordstrom/authentication/ForesterJni\$Callback.class
 *
 * http://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/types.html
 */
namespace mdr {
    class Jni {

    public:
        static jclass findJavaClass(JNIEnv *env, const char *name);
    };
}

#endif //PROJECT_JNI_H
