package com.jedrzejewski.crawler

import com.android.volley.RequestQueue
import java.util.*

object CustomRequestQueue {

    private const val MAX_QUEUE_SIZE = 8

    private val unhandledRequests: Queue<Pair<Int, Int>> = LinkedList()
    private var sentRequestId: Int = 0
    private var nextRequestId: Int = 0

    private var busy = false

    fun process(queue: RequestQueue) {
        if (!busy && sentRequestId == nextRequestId) {
            if (!unhandledRequests.isEmpty()) {
                nextRequestId = sentRequestId + 1
                HttpManager.sendMovementRequest(queue, unhandledRequests.poll(), increaseCounter, reset)
            } else {
                sentRequestId = 0
                nextRequestId = 0
            }
        }
    }

    fun add(values: Pair<Int, Int>) {
        busy = true
        unhandledRequests.add(values)
        if (unhandledRequests.count() > MAX_QUEUE_SIZE) {
            unhandledRequests.remove()
        }
        busy = false
    }

    private var increaseCounter = {
        sentRequestId += 1
        println("Success! request $sentRequestId handled")
    }

    private var reset = {
        unhandledRequests.clear()
        add(Pair(0, 0))
        sentRequestId += 1
        println("Error! request $nextRequestId unhandled")
    }
}