package com.didi.androidnative

import android.annotation.SuppressLint
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import com.didi.androidnative.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    @SuppressLint("SetTextI18n")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // 项目创建默认的例子
//        binding.sampleText.text = stringFromJNI()
        // 演示JNI 静态注册，运行时通过对应的方法名查找，需要时间去查找
        binding.staticBtn.setOnClickListener {
            binding.staticBtn.text = drawFromJNI()
        }
        // 演示 JNI 动态注册，加载动态库时，调用固定的方法，我们在这个方法中将要实现的 JNI 方法注册到系统中，这样运行时速度更快
        val dynamicLib = DynamicLib()
        binding.dynamicBtn.setOnClickListener {
            val result = dynamicLib.plus(2, 3)
            val str = dynamicLib.arrayDemo(arrayOf("Apple", "Banana", "Orange", "Pear", "nuts"))
            binding.dynamicBtn.text = "${dynamicLib.stringFromJNI("I from java goto native")} $result $str"
        }
    }

    /**
     * A native method that is implemented by the 'androidnative' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    private external fun drawFromJNI(): String

    companion object {
        // Used to load the 'androidnative' library on application startup.
        init {
            System.loadLibrary("androidnative")
        }
    }
}