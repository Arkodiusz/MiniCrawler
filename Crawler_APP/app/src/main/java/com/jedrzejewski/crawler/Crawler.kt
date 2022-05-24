package com.jedrzejewski.crawler

import android.app.Application
import android.widget.Button

class Crawler: Application() {

    companion object {
        var leftSpeedLevel = 0
        var rightSpeedLevel  = 0
        var sentLeftSpeedLevel = 0
        var sentRightSpeedLevel  = 0
        var actualIsConnectedToAP = false
        lateinit var wifiLamp : Button
    }
}