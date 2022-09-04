package com.didi.androidnative;

public class JniLoad {

    static {
        System.loadLibrary("androidnative");
    }

    public native String stringFromJNI();

    public native String drawFromJNI();

    // 在 JNI 层调用 operation 发生异常，jni 处理异常。保证不奔溃
    public native void nativeInvokeJavaException();

    // JNI 调用 Java 方法时，发生的异常
    public native void nativeThrowJavaException() throws IllegalArgumentException;

    // cpp 调用这个 Java 方法，会抛出异常，需要 cpp 处理。
    private int operation() {
        return 10 / 0;
    }

    // JNI 创建子线程
    public native void createNativeThread();

    public native void createNativeThreadWithArgs();

    public native void joinNativeThread();

    // JNI 调用接口
    public native void nativeCallback(IThreadCallBack callBack);

    // JNI 子线程调用 Java 的方法
    public native void nativeTheradCallback(IThreadCallBack callBack);
}

interface IThreadCallBack {
    void callback();
}