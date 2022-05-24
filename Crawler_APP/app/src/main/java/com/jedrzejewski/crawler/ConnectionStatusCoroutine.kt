package com.jedrzejewski.crawler

import android.graphics.Color
import android.widget.Toast
import androidx.lifecycle.Lifecycle
import com.jedrzejewski.crawler.Crawler.Companion.actualIsConnectedToAP
import com.jedrzejewski.crawler.Crawler.Companion.wifiLamp
import kotlinx.coroutines.delay

object ConnectionStatusCoroutine {

    private var lastIsConnectedToAP = false

    suspend fun start() {
        while(true) {
            checkConnection()
            delay(1000)
        }
    }

    private fun checkConnection() {
        actualIsConnectedToAP = ConnectionManager.isConnectedToAp()
        if (actualIsConnectedToAP != lastIsConnectedToAP && MainActivity().lifecycle.currentState.isAtLeast(
                Lifecycle.State.INITIALIZED)) {
            if (actualIsConnectedToAP) {
                wifiLamp.setBackgroundColor(Color.GREEN)
//                MainActivity().toast("Connected to vehicle!")
            } else {
                wifiLamp.setBackgroundColor(Color.RED)
//                MainActivity().toast("Disconnected from vehicle!")
            }
            lastIsConnectedToAP = actualIsConnectedToAP
            println("connection => $actualIsConnectedToAP, IP: ${ConnectionManager.getIpAddress()}")
        }
    }
}