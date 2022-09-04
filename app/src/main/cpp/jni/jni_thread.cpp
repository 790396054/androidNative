#include <AndroidLog.h>
#include <pthread.h>
#include <jvm.h>
#include <unistd.h>

//
// Created by andy on 2022/9/4.
//

jmethodID globalMethodId;
jobject globalObj;

void *printThreadHello(void *) {
    LOGD("Hello cpp thread");
    return nullptr;
}

struct ThreadRunArgs {
    int id;
    int result;
};

void *printThreadArgs(void *arg) {
    auto *args = static_cast<ThreadRunArgs *>(arg);
    LOGD("Hello cpp thread %d", args->id);
    return nullptr;
}

// 创建线程，不带参数
extern "C"
JNIEXPORT void JNICALL
Java_com_didi_androidnative_JniLoad_createNativeThread(JNIEnv *env, jobject thiz) {
    pthread_t handless;
    int result = pthread_create(&handless, nullptr, printThreadHello, nullptr);
    if (result == 0) {
        LOGD("create thread success");
    } else {
        LOGD("create thread failed");
    }
}

// 创建线程，将参数传递给子线程
extern "C"
JNIEXPORT void JNICALL
Java_com_didi_androidnative_JniLoad_createNativeThreadWithArgs(JNIEnv *env, jobject thiz) {
    pthread_t handless;
    auto *args = new ThreadRunArgs;
    args->id = 12;
    args->result = 1024;
    int result = pthread_create(&handless, nullptr, printThreadArgs, args);
    if (result == 0) {
        LOGD("create thread args success");
    } else {
        LOGD("create thread args failed");
    }
}

void *printThreadJoin(void *arg) {
    auto *args = static_cast<ThreadRunArgs *>(arg);
    struct timeval begin{};
    gettimeofday(&begin, nullptr);
    LOGD("start time is %ld", begin.tv_sec);
    sleep(3);
    struct timeval end{};
    gettimeofday(&end, nullptr);
    LOGD("end time is %ld", end.tv_sec);
    LOGD("Time used is %ld", end.tv_sec - begin.tv_sec);
    return args;
}

// join主线程，子线程完成，主线程继续运行。可以拿到子线程的运行结果
extern "C"
JNIEXPORT void JNICALL
Java_com_didi_androidnative_JniLoad_joinNativeThread(JNIEnv *env, jobject thiz) {
    pthread_t handles;
    auto *args = new ThreadRunArgs;
    args->id = 2;
    args->result = 100;
    pthread_create(&handles, nullptr, printThreadJoin, args);

    void *ret = nullptr;

    pthread_join(handles, &ret);
    // 拿到子线程的返回值
    auto threadResult = static_cast<ThreadRunArgs *>(ret);
    LOGD("result is %d", threadResult->id);
    LOGD("result is %d", threadResult->result);
}

// 子线程调用java方法
extern "C"
JNIEXPORT void JNICALL
Java_com_didi_androidnative_JniLoad_nativeCallback(JNIEnv *env, jobject thiz, jobject call_back) {
    jclass jcls = env->GetObjectClass(call_back);
    jmethodID mid = env->GetMethodID(jcls, "callback", "()V");
    env->CallVoidMethod(call_back, mid);
}

void * callBanck(void *) {
    // JNIEnv 不能跨线程传递，需要借助 JavaVM 获取 JNIEnv
    JavaVM *vm = getJvm();
    if (vm == nullptr) {
        LOGD("子线程 JavaVM 获取失败");
        return nullptr;
    }
    JNIEnv *env = nullptr;
    // 获取到 JNIEnv
    int t = vm->AttachCurrentThread(&env, nullptr);
    LOGD("子线程 JNIENV 获取结果 %d", t);
    if (t == 0) {
        env->CallVoidMethod(globalObj, globalMethodId);
        vm->DetachCurrentThread();
    }
    return nullptr;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_didi_androidnative_JniLoad_nativeTheradCallback(JNIEnv *env, jobject thiz, jobject call_back) {
    pthread_t handless;
    // 保存为全局变量，方便子线程访问该对象
    globalObj = env->NewGlobalRef(call_back);
    jclass jcls = env->GetObjectClass(call_back);
    globalMethodId = env->GetMethodID(jcls, "callback", "()V");
    pthread_create(&handless, nullptr, callBanck, nullptr);
}