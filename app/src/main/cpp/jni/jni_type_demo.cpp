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

// 验证 cpp 调用 Java 的方法和属性
void objCall(JNIEnv *env, jobject instance, jobject animal) {
    jclass jcls = env->GetObjectClass(animal);
    // 访问 Java 字段
    jfieldID field = env->GetFieldID(jcls, "name", "Ljava/lang/String;");
    jstring val = env->NewStringUTF("native update");
    env->SetObjectField(animal, field, val);

    jfieldID jAge = env->GetFieldID(jcls, "age", "I");
    env->SetIntField(animal, jAge, 12);

    // 调用 Java 实例方法 CallVoidMethod 调用返回值为 void 的实例方法
    jmethodID jmethodId = env->GetMethodID(jcls, "eat", "(Ljava/lang/String;)V");
    env->CallVoidMethod(animal, jmethodId, env->NewStringUTF("cpp food"));

    // 调用 Java 静态方法，CallStaticIntMethod 返回值为 int 的静态方法，参数为 int
    jmethodID staticId = env->GetStaticMethodID(jcls, "isDog", "(I)I");
    jint javaInt = env->CallStaticIntMethod(jcls, staticId, 1024);
    LOGD("我 是 Java 的返回值：%d", javaInt);

    // 调用 Java 方法，参数是 string 数组
    jmethodID arrStaticMethod = env->GetStaticMethodID(jcls, "staticArrayMethod", "([Ljava/lang/String;I)Ljava/lang/String;");
    jint size = 3;
    jobjectArray jObjArr = env->NewObjectArray(size, env->FindClass("java/lang/String"), nullptr);
    for (int i = 0; i < size; ++i) {
        // TODO 此处如何 将 数字 i拼接到返回值的字符串中？
        env->SetObjectArrayElement(jObjArr, i, env->NewStringUTF("string in cpp"));
    }
    auto js = (jstring)env->CallStaticObjectMethod(jcls, arrStaticMethod, jObjArr, size);
    jboolean isCopy = false;
    const char *c = env->GetStringUTFChars(js, &isCopy);
    LOGD("接收到 Java 的 string 返回值 %s", c);
    env->ReleaseStringUTFChars(js, c);
}