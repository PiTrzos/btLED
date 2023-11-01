package com.example.rgbcontroller.adapters

import android.graphics.Color
import android.os.Handler
import android.os.Looper
import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.core.os.HandlerCompat
import androidx.core.view.isVisible
import androidx.recyclerview.widget.RecyclerView
import com.example.rgbcontroller.BlueToothAllInOne
import com.example.rgbcontroller.databinding.ListItemBinding
import com.example.rgbcontroller.models.RGBMode

class ModeViewHolder(val binding: ListItemBinding) : RecyclerView.ViewHolder(binding.root){
    fun bind(product: RGBMode){
        binding.productName.text = product.name
        binding.productNote.text = product.note
        binding.productImage.setImageResource(product.resId)
        binding.connectionInfo.isVisible = false
        binding.connectionInfo.text = product.id.toString()
    }
}

class ModeAdapter: RecyclerView.Adapter<ModeViewHolder>(){
    companion object{
        var listData: MutableList<ListItemBinding> = mutableListOf()
        var needChange: Boolean = false
    }
    private val data = mutableListOf<RGBMode>()
    private val handler: Handler = HandlerCompat.createAsync(Looper.getMainLooper())
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ModeViewHolder {
        val binding = ListItemBinding.inflate(
            LayoutInflater.from(parent.context),
            parent,
            false
        )
        listData.add(binding)
        return ModeViewHolder(binding).also { vh->
            binding.root.setOnClickListener{
                if (BlueToothAllInOne.OutputCalculated.get()){
                    for (bind in listData){
                        bind.root.setCardBackgroundColor(Color.DKGRAY)
                    }
                    binding.root.setCardBackgroundColor(Color.parseColor("#BB86FC"))
                    BlueToothAllInOne.sendToAll("M${binding.connectionInfo.text}\n")
                    needChange = true
                }
            }
        }
    }

    override fun getItemCount(): Int {
        return data.size
    }

    override fun onBindViewHolder(holder: ModeViewHolder, position: Int) {
        holder.bind(data[position])
    }

    fun replace(newData: List<RGBMode>){
        data.clear()
        data.addAll(newData)
        handler.post{
            notifyDataSetChanged()
        }
    }
}