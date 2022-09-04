package com.didi.androidnative

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.TextView
import com.didi.androidnative.Constants.TAG
import com.didi.androidnative.databinding.ActivityMainBinding
import java.lang.Exception
import java.lang.IllegalArgumentException

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    private val jniLoad = JniLoad()

    @SuppressLint("SetTextI18n")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.exceptionBtn.setOnClickListener {
            try {
                jniLoad.nativeThrowJavaException()
            } catch (e: IllegalArgumentException) {
                Log.d(Constants.TAG, "onCreate: ${e.message}")
            }
            jniLoad.nativeInvokeJavaException()
        }
        // 演示JNI 静态注册，运行时通过对应的方法名查找，需要时间去查找
        binding.staticBtn.setOnClickListener {
            binding.staticBtn.text = jniLoad.drawFromJNI()
        }
        // 演示 JNI 动态注册，加载动态库时，调用固定的方法，我们在这个方法中将要实现的 JNI 方法注册到系统中，这样运行时速度更快
        val dynamicLib = DynamicLib()
        val animal = Animal("KeLe");
        binding.dynamicBtn.setOnClickListener {
            val result = dynamicLib.plus(2, 3)
            val str = dynamicLib.arrayDemo(arrayOf("Apple", "Banana", "Orange", "Pear", "nuts"))
            binding.dynamicBtn.text = "${dynamicLib.stringFromJNI("I from java goto native")} $result $str"
            dynamicLib.objDemo(animal)
            Log.d(Constants.TAG, "onCreate: animal = $animal")
        }

        binding.bitmapBtn.setOnClickListener {

        }

        binding.threadBtn.setOnClickListener {
            jniLoad.createNativeThread()
            jniLoad.createNativeThreadWithArgs()
            jniLoad.joinNativeThread()
        }

        binding.threadCallBtn.setOnClickListener {
            jniLoad.nativeCallback {
                Log.d(TAG, "nativeCallback: ${Thread.currentThread().name}")
            }
            jniLoad.nativeTheradCallback {
                Log.d(TAG, "nativeTheradCallback: ${Thread.currentThread().name}")
            }
        }
    }
}