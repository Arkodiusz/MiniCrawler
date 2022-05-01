package com.jedrzejewski.crawler

import android.content.pm.ActivityInfo
import android.os.Bundle
import android.view.View
import android.widget.SeekBar
import androidx.appcompat.app.AppCompatActivity
import com.android.volley.toolbox.Volley


class MainActivity : AppCompatActivity() {

    var leftSpeedLevel = 0
    var rightSpeedLevel  = 0

    @Override
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_REVERSE_LANDSCAPE
        hideStatusAndNavBars()

        val queue = Volley.newRequestQueue(this)

        val leftSeekBar = findViewById<SeekBar>(R.id.seekBarLeft)
        leftSeekBar?.setOnSeekBarChangeListener(object :
            SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seek: SeekBar, progress: Int, fromUser: Boolean) {
                val tempSpeedLevel = convertPercentageToRange(progress)
                if (tempSpeedLevel != leftSpeedLevel) {
                    leftSpeedLevel = tempSpeedLevel
                    HttpManager.sendMovementRequest(queue, leftSpeedLevel, rightSpeedLevel)
                }
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
                val tempSpeedLevel = convertPercentageToRange(progress)
                if (tempSpeedLevel != rightSpeedLevel) {
                    rightSpeedLevel = tempSpeedLevel
                    HttpManager.sendMovementRequest(queue, leftSpeedLevel, rightSpeedLevel)
                }
            }

            override fun onStartTrackingTouch(seek: SeekBar) {

            }

            override fun onStopTrackingTouch(seek: SeekBar) {
                seek.progress = 50
            }
        })
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

    private fun convertPercentageToRange(progress: Int): Int {
        //converts percentage to range from -10 to 10
        return (progress/100.0*20 - 10).toInt()
    }
}