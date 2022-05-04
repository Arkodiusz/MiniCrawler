package com.jedrzejewski.crawler

import androidx.appcompat.app.AppCompatActivity
import com.android.volley.DefaultRetryPolicy
import com.android.volley.Request
import com.android.volley.RequestQueue
import com.android.volley.toolbox.StringRequest
import com.android.volley.toolbox.Volley
import org.json.JSONObject

object HttpManager {

    private const val ESP_ACCESS_POINT_IP = "44.44.44.1"
//    private const val LOCAL_IP = "192.168.1.100"

    private lateinit var queue: RequestQueue

    fun setupQueue(context: AppCompatActivity) {
        queue = Volley.newRequestQueue(context)
    }

    fun clearQueue() {
        queue.cancelAll{true}
    }

    fun sendMovementRequest(left: Int = 0, right: Int = 0, acknowledge: (Int, Int) -> Unit, reset: () -> Unit  ) {
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
                    acknowledge(ackLeft as Int, ackRight as Int)
                },
                {
                    println("request $url cancelled")
                    reset()
                }
            )
            stringRequest.retryPolicy = DefaultRetryPolicy(200, 0, DefaultRetryPolicy.DEFAULT_BACKOFF_MULT)
            queue.add(stringRequest)
        }
    }
}