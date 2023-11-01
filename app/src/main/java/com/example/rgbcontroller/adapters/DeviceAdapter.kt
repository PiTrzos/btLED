package com.example.rgbcontroller.adapters

import android.annotation.SuppressLint
import android.os.Handler
import android.os.Looper
import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.core.os.HandlerCompat
import androidx.core.view.isVisible
import androidx.recyclerview.widget.RecyclerView
import com.example.rgbcontroller.BlueToothAllInOne
import com.example.rgbcontroller.databinding.ListItemBinding
import com.example.rgbcontroller.models.Device

class DeviceViewHolder(val binding: ListItemBinding) : RecyclerView.ViewHolder(binding.root){
    fun bind(device: Device){
        binding.productName.text = device.name
        binding.productNote.text = device.note
        binding.connectionInfo.text = device.connected
        binding.productImage.setImageResource(device.resId)
        if(device.connected == "connected"){
            binding.isSelected.isVisible = true
            binding.isSelected.isChecked = true
        }
    }
}

class DeviceAdapter: RecyclerView.Adapter<DeviceViewHolder>(){
    private val data = mutableListOf<Device>()
    private val handler: Handler = HandlerCompat.createAsync(Looper.getMainLooper())

    @SuppressLint("MissingPermission")
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): DeviceViewHolder {
        val binding = ListItemBinding.inflate(
            LayoutInflater.from(parent.context),
            parent,
            false
        )
        return DeviceViewHolder(binding).also { vh->
                binding.isSelected.setOnClickListener{
                    BlueToothAllInOne.pairedOutputStreams?.forEach {
                        if(it.note==binding.productNote.text){
                            it.isSelected = !it.isSelected
                        }
                    }
                }
        }
    }

    override fun getItemCount(): Int {
        return data.size
    }

    override fun onBindViewHolder(holder: DeviceViewHolder, position: Int) {
        holder.bind(data[position])
    }

    fun replace(newData: List<Device>){
        data.clear()
        data.addAll(newData)
        handler.post{
            notifyDataSetChanged()
        }
    }
}