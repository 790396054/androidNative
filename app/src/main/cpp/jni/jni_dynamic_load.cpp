//
// Created by andy on 2022/9/3.
//

#include <jni.h>
#include <AndroidLog.h>
#include <string>
#include "jni_type_demo.h"

#define JAVA_CLASS "com/didi/androidnative/DynamicLib"

jint sum(JNIEnv *env, jobject jobj, jint x, jint y) {
    LOGD("Java 传递的整型参数 x = %d,  y = %d", x, y);
    return x + y;
}

jstring getMessage(JNIEnv *env, jobject jobj, jstring str) {
    // Java 字符串转换为 cpp 字符
    jboolean isCopy = false;
    const char *cppStr = env->GetStringUTFChars(str, &isCopy);
    jsize length = env->GetStringLength(str);
    LOGD("调用了 getMessage 方法, %s ， 长度 %d", cppStr, length);
    env->ReleaseStringUTFChars(str, cppStr);
    // cpp 字符转换为 Java 字符
    return env->NewStringUTF(cppStr);
}

static JNINativeMethod gMethods[] = {
        {"plus",          "(II)I",                                  (void *) sum},
        {"stringFromJNI", "(Ljava/lang/String;)Ljava/lang/String;", (void *) getMessage},
        {"arrayDemo", "([Ljava/lang/String;)Ljava/lang/String;", (void *) arrayDemo}
};

#define NELEM(x) ((int)(sizeof(x)/sizeof((x)[0])))

int registerNativeMethods(JNIEnv *env, const char *name, const JNINativeMethod *method, jint nMethods) {
    jclass jcls;
    jcls = env->FindClass(name);
    if (jcls == nullptr) {
        return JNI_FALSE;
    }
//    jclass super = env->GetSuperclass(jcls);
//    LOGD("registerNativeMethods:%p", super);
    if (env->RegisterNatives(jcls, method, nMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

/*
 * Prototypes for functions exported by loadable shared libs.  These are
 * called by JNI, not provided by JNI.
 * 动态库加载的时候，会先调用这个方法。
 */
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = nullptr;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_FALSE;
    }
    if (registerNativeMethods(env, JAVA_CLASS, gMethods, NELEM(gMethods)) != JNI_TRUE) {
        return JNI_FALSE;
    }
    LOGD("动态库加载完成");
    return JNI_VERSION_1_6;
}

