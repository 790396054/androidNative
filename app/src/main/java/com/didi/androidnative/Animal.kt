package com.didi.androidnative

import android.util.Log

data class Animal(var name: String, var age: Int = 0) {

    fun eat(food: String) {
        Log.d(Constants.TAG, "eat: $food")
    }

    companion object {
        @JvmStatic
        fun isDog(age: Int): Int {
            Log.d(Constants.TAG, "线程 ${Thread.currentThread().name} 我是 Java 静态方法 $age")
            return 89
        }

        @JvmStatic
        fun staticArrayMethod(array: Array<String>, num: Int): String {
            for (s in array) {
                Log.d(Constants.TAG, "我是 Java 静态数组方法 $s, $num")
            }
            return "java String return 线程 ${Thread.currentThread().name} "
        }
    }
}