#include <AndroidLog.h>
//
// Created by andy on 2022/9/4.
//

extern "C"
JNIEXPORT void JNICALL
Java_com_didi_androidnative_JniLoad_nativeInvokeJavaException(JNIEnv *env, jobject thiz) {

    jclass jcls = env->FindClass("com/didi/androidnative/JniLoad");
    jmethodID mid = env->GetMethodID(jcls, "operation", "()I");
    // 查找构造方法
    jmethodID mid2 = env->GetMethodID(jcls, "<init>", "()V");
    // 调用构造方法，实例化对象。
    jobject jobj = env->NewObject(jcls, mid2);
    env->CallIntMethod(jobj, mid);
    // 也可以检查是否发生异常。
//     jthrowable jthrow = env->ExceptionOccurred();
    // 检查当前环境是否发生异常，(类似于 Java 的 try {})
    if (env->ExceptionCheck()) {
        // 处理异常，类似于 Java 的 catch
        env->ExceptionDescribe();
        LOGD("catch exception from native");
    }
    // 清楚异常
    env->ExceptionClear();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_didi_androidnative_JniLoad_nativeThrowJavaException(JNIEnv *env, jobject thiz) {
    jclass jcls = env->FindClass("java/lang/IllegalArgumentException");
    env->ThrowNew(jcls, "native throw exception");
}