package com.example.rgbcontroller

import android.annotation.SuppressLint
import android.bluetooth.BluetoothDevice
import java.io.IOException
import java.io.OutputStream
import java.nio.charset.Charset
import java.util.*
import java.util.concurrent.atomic.AtomicBoolean
import kotlin.concurrent.thread

class BlueToothAllInOne {

    companion object{
        private val UUID_RFCOMM_GENERIC: UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB")
        var pairedDevices: MutableSet<BluetoothDevice>? = null
        var pairedOutputStreams: Set<OutputStreamPlus>? = null
        var OutputCalculated: AtomicBoolean = AtomicBoolean(false)


        fun sendToAll(str: String){
            for(stream in pairedOutputStreams!!){
                thread {
                    if (stream.socket.isConnected && stream.isSelected) {

                        stream.outputStream.write(str.toByteArray(Charset.defaultCharset()))
                        stream.outputStream.flush()

                    }
                }
            }
        }

        @SuppressLint("MissingPermission")
        fun getAllStreams() {
            thread {
                val pairedSocketsNew: MutableSet<OutputStreamPlus> = mutableSetOf()
                for (device in pairedDevices!!) {
                        val mBTSocket =
                            device.createInsecureRfcommSocketToServiceRecord(UUID_RFCOMM_GENERIC)
                        val mBTOutputStream: OutputStream = mBTSocket.outputStream
                        try {
                            mBTSocket.connect()
                            pairedSocketsNew.add(OutputStreamPlus(mBTOutputStream, device.address, mBTSocket))
                        } catch (e: IOException) {

                        }
                }
                pairedOutputStreams = pairedSocketsNew
                OutputCalculated.set(true)
            }
        }

        fun closeAllStreams(){
            thread{
                for(stream in pairedOutputStreams!!){
                    stream.outputStream.close()
                }
            }
        }
    }

}