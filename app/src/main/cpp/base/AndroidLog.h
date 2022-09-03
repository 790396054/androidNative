//
// Created by andy on 2022/9/3.
//

//头文件只有被其他CPP文件依赖以后才能正常导入
#include <android/log.h>
#include <jni.h>

#ifndef ANDROIDNATIVE_ANDROIDLOG_H
#define ANDROIDNATIVE_ANDROIDLOG_H

#define TAG "AndroidNative"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型

#endif //ANDROIDNATIVE_ANDROIDLOG_H
