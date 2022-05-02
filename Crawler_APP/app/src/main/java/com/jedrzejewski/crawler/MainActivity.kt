package com.jedrzejewski.crawler

import android.content.pm.ActivityInfo
import android.os.Bundle
import android.view.View
import android.widget.SeekBar
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.Lifecycle
import androidx.lifecycle.lifecycleScope
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch

class MainActivity : AppCompatActivity() {

    var leftSpeedLevel = 0
    var rightSpeedLevel  = 0
    var sentLeftSpeedLevel = 0
    var sentRightSpeedLevel  = 0

    @Override
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_REVERSE_LANDSCAPE
        hideStatusAndNavBars()

        HttpManager.setupQueue(this)

        lifecycleScope.launch() {
            processHttpRequest()
        }

        val leftSeekBar = findViewById<SeekBar>(R.id.seekBarLeft)
        leftSeekBar?.setOnSeekBarChangeListener(object :
            SeekBar.OnSeekBarChangeListener {

            override fun onProgressChanged(seek: SeekBar, progress: Int, fromUser: Boolean) {
                leftSpeedLevel = convertPercentageToRange(progress)
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
                rightSpeedLevel = convertPercentageToRange(progress)
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
        HttpManager.sendMovementRequest(0, 0, acknowledge, reset)
    }

    private val acknowledge: (Int, Int) -> Unit = { left, right ->
        sentLeftSpeedLevel = left
        sentRightSpeedLevel = right
    }

    private val reset = {
        sentLeftSpeedLevel = 0
        sentRightSpeedLevel = 0
    }

    private suspend fun processHttpRequest() {
        while (true) {
            //TODO: if connection is ok
            if (lifecycle.currentState.isAtLeast(Lifecycle.State.RESUMED)) {
                if (leftSpeedLevel != sentLeftSpeedLevel || rightSpeedLevel != sentRightSpeedLevel) {
                    HttpManager.sendMovementRequest(leftSpeedLevel, rightSpeedLevel, acknowledge, reset)
                }
            }
            delay(250)
        }
    }

    private fun convertPercentageToRange(progress: Int): Int {
        //converts percentage to range from -10 to 10
        return (progress/100.0*20 - 10).toInt()
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
}