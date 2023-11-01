package com.example.rgbcontroller.fragments


import android.bluetooth.BluetoothManager
import android.content.Context
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import com.example.rgbcontroller.Navigable
import com.example.rgbcontroller.databinding.ConnectionFragmentBinding


class ConnectionFragment: Fragment() {
    private lateinit var binding: ConnectionFragmentBinding

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        return ConnectionFragmentBinding.inflate(inflater, container, false).also {
            binding = it
        }.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        binding.connectBtn.setOnClickListener {vh ->
            if(checkBluetooth()){
                (activity as? Navigable)?.navigate(Navigable.Destination.List)
            }
        }
    }

    private fun checkBluetooth(): Boolean {
        val bluetoothManager = context?.getSystemService(Context.BLUETOOTH_SERVICE) as BluetoothManager
        val btAdapter = bluetoothManager.adapter
        return btAdapter != null && btAdapter.isEnabled
    }


    override fun onStart() {
        super.onStart()
    }
}