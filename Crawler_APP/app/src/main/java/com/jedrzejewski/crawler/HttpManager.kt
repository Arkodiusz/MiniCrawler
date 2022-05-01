package com.jedrzejewski.crawler

import com.android.volley.Request
import com.android.volley.RequestQueue
import com.android.volley.toolbox.StringRequest

object HttpManager {

//    private const val LOCAL_IP = "192.168.44.1"
    private const val LOCAL_IP = "192.168.1.109"

    fun sendMovementRequest(queue: RequestQueue, values: Pair<Int, Int>?,  onResponse: () -> Unit,  onError: () -> Unit) {
        if (values == null) {
            return
        }
        val url = "http://$LOCAL_IP/move?left=${values.first}&right=${values.second}"
        println(url)

        val stringRequest = StringRequest(
            Request.Method.GET,
            url,
            {
                onResponse()
            },
            {
                onError()
            }
        )
        queue.add(stringRequest)
    }
}