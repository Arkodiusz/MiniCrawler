package com.jedrzejewski.crawler

import androidx.lifecycle.Lifecycle
import com.jedrzejewski.crawler.Crawler.Companion.actualIsConnectedToAP
import com.jedrzejewski.crawler.Crawler.Companion.leftSpeedLevel
import com.jedrzejewski.crawler.Crawler.Companion.rightSpeedLevel
import com.jedrzejewski.crawler.Crawler.Companion.sentLeftSpeedLevel
import com.jedrzejewski.crawler.Crawler.Companion.sentRightSpeedLevel
import kotlinx.coroutines.delay

object HttpRequestCoroutine {

    var noRequestCounter = 0

    suspend fun start() {
        while(true) {
            processHttpRequest()
            delay(250)
        }
    }

    private fun convert(progress: Int): Int {
        //converts percentage to range from -10 to 10
        return (progress/100.0*20 - 10).toInt()
    }

    private fun processHttpRequest() {
        if (MainActivity().lifecycle.currentState.isAtLeast(Lifecycle.State.INITIALIZED)) {
            if (actualIsConnectedToAP) {
                if (leftSpeedLevel != sentLeftSpeedLevel || rightSpeedLevel != sentRightSpeedLevel || noRequestCounter >= 8) {
                    HttpManager.sendMovementRequest(convert(leftSpeedLevel), convert(rightSpeedLevel))
                    noRequestCounter = 0
                } else {
                    noRequestCounter++
                }
            }
        }
        println("noRequestCounter $noRequestCounter")
    }
}