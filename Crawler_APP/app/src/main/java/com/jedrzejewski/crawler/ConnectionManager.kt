package com.jedrzejewski.crawler

import java.net.Inet4Address
import java.net.NetworkInterface

object ConnectionManager {

    private const val DEMANDED_NETWORK_ID = "44.44.44"

    fun isConnectedToAp() : Boolean{
        val ipAddress = getIPAddress()
        println("ipAddress => $ipAddress")
        val ipField = ipAddress.split(".")
        if (ipField.size < 4) return false
        val foundNetworkId = "${ipField[0]}.${ipField[1]}.${ipField[2]}"
        return DEMANDED_NETWORK_ID == foundNetworkId
    }

    private fun getIPAddress(): String {
        NetworkInterface.getNetworkInterfaces()?.toList()?.map { networkInterface ->
            networkInterface.inetAddresses?.toList()?.find {
                !it.isLoopbackAddress && it is Inet4Address
            }?.let { return it.hostAddress.orEmpty() }
        }
        return ""
    }
}