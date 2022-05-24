package com.jedrzejewski.crawler

import android.content.pm.ActivityInfo
import android.os.Bundle
import android.view.View
import android.widget.SeekBar
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.lifecycleScope
import com.jedrzejewski.crawler.Crawler.Companion.actualIsConnectedToAP
import com.jedrzejewski.crawler.Crawler.Companion.leftSpeedLevel
import com.jedrzejewski.crawler.Crawler.Companion.rightSpeedLevel
import com.jedrzejewski.crawler.Crawler.Companion.sentLeftSpeedLevel
import com.jedrzejewski.crawler.Crawler.Companion.sentRightSpeedLevel
import com.jedrzejewski.crawler.Crawler.Companion.wifiLamp
import kotlinx.coroutines.launch

class MainActivity : AppCompatActivity() {

    @Override
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_REVERSE_LANDSCAPE
        hideStatusAndNavBars()

        HttpManager.setupQueue(this)
        lifecycleScope.launch() {
            HttpRequestCoroutine.start()
        }

        wifiLamp = findViewById(R.id.button)
        lifecycleScope.launch() {
            ConnectionStatusCoroutine.start()
        }

        val leftSeekBar = findViewById<SeekBar>(R.id.seekBarLeft)
        leftSeekBar?.setOnSeekBarChangeListener(object :
            SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seek: SeekBar, progress: Int, fromUser: Boolean) {
                leftSpeedLevel = progress
            }
            override fun onStartTrackingTouch(seek: SeekBar) {
            }
            override fun onStopTrackingTouch(seek: SeekBar) {
                seek.progress = 50
            }
        })

        val rightSeekBar = findViewById<SeekBar>(R.id.seekBarRight)
        rightSeekBar?.setOnSeekBarChangeListener(object :
            SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seek: SeekBar, progress: Int, fromUser: Boolean) {
                rightSpeedLevel = progress
            }
            override fun onStartTrackingTouch(seek: SeekBar) {
            }
            override fun onStopTrackingTouch(seek: SeekBar) {
                seek.progress = 50
            }
        })
    }


    @Override
    override fun onPause() {
        super.onPause()
        sentLeftSpeedLevel = 0
        sentRightSpeedLevel = 0
        HttpManager.clearQueue()
        HttpManager.sendMovementRequest(0, 0)
    }

    @Override
    @Suppress("DEPRECATION")
    override fun onWindowFocusChanged(hasFocus: Boolean) {
        super.onWindowFocusChanged(hasFocus)
        if (hasFocus) {
            window.decorView.systemUiVisibility = View.SYSTEM_UI_FLAG_LAYOUT_STABLE or
                    View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION or
                    View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN or View.SYSTEM_UI_FLAG_HIDE_NAVIGATION or
                    View.SYSTEM_UI_FLAG_FULLSCREEN or View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
        }
    }

    @Suppress("DEPRECATION")
    private fun hideStatusAndNavBars() {
        val flags = View.SYSTEM_UI_FLAG_LAYOUT_STABLE or
                View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION or
                View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN or View.SYSTEM_UI_FLAG_HIDE_NAVIGATION or
                View.SYSTEM_UI_FLAG_FULLSCREEN or View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY

        window.decorView.systemUiVisibility = flags
        val decorView = window.decorView
        decorView.setOnSystemUiVisibilityChangeListener { visibility ->
            if (visibility and View.SYSTEM_UI_FLAG_FULLSCREEN == 0) {
                decorView.systemUiVisibility = flags
            }
        }
    }

    fun toast(message: String) {
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show()
    }
}