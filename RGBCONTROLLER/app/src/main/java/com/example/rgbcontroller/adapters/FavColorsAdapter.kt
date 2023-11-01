package com.example.rgbcontroller.adapters

import android.annotation.SuppressLint
import android.content.Context
import android.graphics.Color
import android.graphics.drawable.ColorDrawable
import android.os.Handler
import android.os.Looper
import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.core.graphics.blue
import androidx.core.graphics.green
import androidx.core.graphics.red
import androidx.core.os.HandlerCompat
import androidx.recyclerview.widget.RecyclerView
import com.example.rgbcontroller.BlueToothAllInOne
import com.example.rgbcontroller.data.FavColorDatabase
import com.example.rgbcontroller.databinding.ListColorItemBinding
import com.example.rgbcontroller.models.ColorData
import kotlin.concurrent.thread

class FavColorsViewHolder(val binding: ListColorItemBinding) : RecyclerView.ViewHolder(binding.root){
    fun bind(data: ColorData){
        binding.rgbTEXT.text = data.rgbString
        binding.color.setBackgroundColor(data.color)
    }
}

class FavColorsAdapter(private val con: Context): RecyclerView.Adapter<FavColorsViewHolder>(){
    private val data = mutableListOf<ColorData>()
    private val handler: Handler = HandlerCompat.createAsync(Looper.getMainLooper())
    @SuppressLint("MissingPermission")
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): FavColorsViewHolder {
        val binding = ListColorItemBinding.inflate(
            LayoutInflater.from(parent.context),
            parent,
            false
        )
        listData.add(binding)
        return FavColorsViewHolder(binding).also { vh->
            binding.root.setOnClickListener{
                if (BlueToothAllInOne.OutputCalculated.get()){
                    val color = binding.color.background as ColorDrawable
                    setGray()
                    binding.root.setCardBackgroundColor(Color.parseColor("#BB86FC"))
                    BlueToothAllInOne.sendToAll("T${color.color.red} ${color.color.green} ${color.color.blue}\n")
                }
            }
            binding.deleteBtn.setOnClickListener {
                thread {
                    FavColorDatabase.open(con).colors.deleteColorById(binding.rgbTEXT.text.toString())
                    loadData()
                }
            }
        }
    }

    companion object{
        var listData: MutableList<ListColorItemBinding> = mutableListOf()
    }
    private fun setGray() {
        for (col in listData){
            col.root.setCardBackgroundColor(Color.DKGRAY)
        }
    }



    override fun getItemCount(): Int {
        return data.size
    }

    override fun onBindViewHolder(holder: FavColorsViewHolder, position: Int) {
        holder.bind(data[position])
    }

    fun replace(newData: List<ColorData>){
        data.clear()
        data.addAll(newData)
        handler.post{
            notifyDataSetChanged()
        }
    }
    private fun loadData() {
        thread {
            val colors =  FavColorDatabase.open(con).colors.getAllColors().map { entity ->
                ColorData(
                    entity.RGBstr,
                    entity.color
                )
            }
            replace(colors)
        }
    }
}