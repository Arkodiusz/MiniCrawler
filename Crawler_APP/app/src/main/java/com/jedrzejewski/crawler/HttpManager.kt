package com.jedrzejewski.crawler

import com.android.volley.DefaultRetryPolicy
import com.android.volley.Request
import com.android.volley.RequestQueue
import com.android.volley.toolbox.StringRequest
import com.android.volley.toolbox.Volley
import com.jedrzejewski.crawler.Crawler.Companion.sentLeftSpeedLevel
import com.jedrzejewski.crawler.Crawler.Companion.sentRightSpeedLevel
import org.json.JSONObject

object HttpManager {

    private const val ESP_ACCESS_POINT_IP = "44.44.44.1"
//    private const val LOCAL_IP = "192.168.1.100"

    private lateinit var queue: RequestQueue
    private lateinit var context: MainActivity

    fun setupQueue(context: MainActivity) {
        this.context = context
        queue = Volley.newRequestQueue(context)
    }

    fun clearQueue() {
        queue.cancelAll{true}
    }

    fun sendMovementRequest(left: Int = 0, right: Int = 0) {
        if (::queue.isInitialized) {
            val url = "http://$ESP_ACCESS_POINT_IP/move?left=${left}&right=${right}"
            println("request  => $url")

            val stringRequest = StringRequest(
                Request.Method.GET,
                url,
                { response ->
                    val jsonResponse = JSONObject(response)
                    val ackLeft = jsonResponse.get("left")
                    val ackRight = jsonResponse.get("right")
                    println("response => $jsonResponse")
                    acknowledgeSentParameters(ackLeft as Int, ackRight as Int)
                },
                {
                    println("request $url cancelled")
                    resetSentParameters()
                }
            )
            stringRequest.retryPolicy = DefaultRetryPolicy(200, 0, DefaultRetryPolicy.DEFAULT_BACKOFF_MULT)
            queue.add(stringRequest)
        }
    }

    private fun acknowledgeSentParameters (left: Int, right: Int) {
        sentLeftSpeedLevel = left
        sentRightSpeedLevel = right
    }

    private fun resetSentParameters()  {
        sentLeftSpeedLevel = 0
        sentRightSpeedLevel = 0
    }
}