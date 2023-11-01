package com.example.rgbcontroller.fragments

import android.annotation.SuppressLint
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothManager
import android.content.Context
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.LinearLayoutManager
import com.example.rgbcontroller.BlueToothAllInOne
import com.example.rgbcontroller.R
import com.example.rgbcontroller.adapters.DeviceAdapter
import com.example.rgbcontroller.databinding.ConnectedDevicesFragmentBinding
import com.example.rgbcontroller.models.Device
import kotlin.concurrent.thread


class ConnectedDevicesFragment : Fragment(){
    private lateinit var binding: ConnectedDevicesFragmentBinding
    lateinit var pairedDevices: Set<BluetoothDevice>
    private var adapter: DeviceAdapter? = null

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        return ConnectedDevicesFragmentBinding.inflate(inflater, container, false).also {
            binding = it
        }.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        pairedDevices = getListOfPairedDevices()

        BlueToothAllInOne.pairedDevices = pairedDevices.toMutableSet()
        BlueToothAllInOne.getAllStreams()

        adapter = DeviceAdapter()

        binding.deviceList.let {
            it.adapter = adapter
            it.layoutManager = LinearLayoutManager(requireContext())
        }

    }

    override fun onStart() {
        super.onStart()
        loadData()
    }

    @SuppressLint("MissingPermission")
    private fun getListOfPairedDevices(): Set<BluetoothDevice> {
        val bluetoothManager = context?.getSystemService(Context.BLUETOOTH_SERVICE) as BluetoothManager
        return bluetoothManager.adapter.bondedDevices
    }
    @SuppressLint("MissingPermission")
    private fun loadData() {
        thread {
            while (!BlueToothAllInOne.OutputCalculated.get()){
                Thread.sleep(500)
            }
            val devices = BlueToothAllInOne.pairedDevices?.map {entity->
                var isConnected: String
                if(BlueToothAllInOne.pairedOutputStreams?.map { a->a.note }!!.contains(entity.address)){
                    isConnected = "connected"
                }else{
                    isConnected = "disconnected"
                }
                Device(
                    entity.name,
                    entity.address,
                    isConnected,
                    R.drawable.led
                )
            }
            devices?.let { adapter?.replace(it) }
        }
    }

}