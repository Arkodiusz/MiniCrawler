package com.jedrzejewski.crawler

import androidx.appcompat.app.AppCompatActivity
import com.android.volley.Request
import com.android.volley.RequestQueue
import com.android.volley.toolbox.StringRequest
import com.android.volley.toolbox.Volley

object HttpManager {

//    private const val LOCAL_IP = "192.168.44.1"
    private const val LOCAL_IP = "192.168.1.100"

    private lateinit var queue: RequestQueue

    fun setupQueue(context: AppCompatActivity) {
        queue = Volley.newRequestQueue(context)
    }

    fun sendMovementRequest(left: Int = 0, right: Int = 0) {
        if (::queue.isInitialized) {
            val url = "http://$LOCAL_IP/move?left=${left}&right=${right}"
            println(url)

            val stringRequest = StringRequest(
                Request.Method.GET,
                url,
                {
                },
                {
                }
            )
            queue.add(stringRequest)
        }
    }
}