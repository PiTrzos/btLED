package com.example.rgbcontroller

import android.bluetooth.BluetoothSocket
import java.io.OutputStream

class OutputStreamPlus(private val os: OutputStream, private val n: String,private val soc: BluetoothSocket) {
    val outputStream: OutputStream = os
    val note: String = n
    var isSelected: Boolean = true
    val socket: BluetoothSocket = soc
}
