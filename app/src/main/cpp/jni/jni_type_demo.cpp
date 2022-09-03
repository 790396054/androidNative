//
// Created by andy on 2022/9/3.
//
#include "jni_type_demo.h"

// 数组传递 demo，cpp 和 Java 之间的转换
jstring arrayDemo(JNIEnv *env, jobject jobj, jobjectArray str_array) {

    jsize size = env->GetArrayLength(str_array);
    LOGD("数组长度 %d", size);
    jboolean isCopy = false;
    for (int i = 0; i < size; ++i) {
        auto element = static_cast<jstring>(env->GetObjectArrayElement(str_array, i));
        const char *str = env->GetStringUTFChars(element, &isCopy);
        LOGD("数组的第 %d 个元素 %s", i, str);
        env->ReleaseStringUTFChars(element, str);
    }
    return env->NewStringUTF("I from CPP");
}