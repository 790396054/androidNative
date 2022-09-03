package com.didi.androidnative

class DynamicLib {

    companion object {
        init {
            System.loadLibrary("dynamic-lib")
        }
    }

    external fun stringFromJNI(msg: String): String

    external fun plus(a: Int, b: Int): Int

    external fun arrayDemo(array: Array<String>): String
}