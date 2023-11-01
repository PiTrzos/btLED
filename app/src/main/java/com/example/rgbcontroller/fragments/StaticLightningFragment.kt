package com.example.rgbcontroller.fragments

import android.annotation.SuppressLint
import android.app.AlertDialog
import android.graphics.*
import android.os.Bundle
import android.view.*
import android.widget.EditText
import android.widget.SeekBar
import android.widget.TextView
import androidx.core.view.drawToBitmap
import androidx.core.widget.addTextChangedListener
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.rgbcontroller.BlueToothAllInOne
import com.example.rgbcontroller.R
import com.example.rgbcontroller.data.FavColorDatabase
import com.example.rgbcontroller.adapters.FavColorsAdapter
import com.example.rgbcontroller.adapters.ModeAdapter
import com.example.rgbcontroller.data.model.FavColorEntity
import com.example.rgbcontroller.databinding.StaticLightningFragmentBinding
import com.example.rgbcontroller.models.ColorData
import kotlin.concurrent.thread


class StaticLightningFragment: Fragment() {
    private lateinit var binding: StaticLightningFragmentBinding
    private var click: Int = 0
    private var recentRed: Int = 0
    private var recentGreen: Int = 0
    private var recentBlue: Int = 0
    private lateinit var adapter: FavColorsAdapter

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        return StaticLightningFragmentBinding.inflate(inflater, container, false).also {
            binding = it
        }.root
    }

    @SuppressLint("ClickableViewAccessibility")
    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        adapter = context?.let { FavColorsAdapter(it) }!!

        binding.RGBspectrum.setOnTouchListener { v, event ->
            if (BlueToothAllInOne.OutputCalculated.get()){
                val x: Int = event.x.toInt()
                val y: Int = event.y.toInt()
                val pixel = v!!.drawToBitmap().getPixel(x, y)

                val redValue: Int = Color.red(pixel)
                val blueValue: Int = Color.blue(pixel)
                val greenValue: Int = Color.green(pixel)

                if (redValue + blueValue + greenValue > 50) {
                    recentGreen = greenValue
                    recentRed = redValue
                    recentBlue = blueValue
                    BlueToothAllInOne.sendToAll("T$redValue $greenValue $blueValue\n")
                }

                if(ModeAdapter.needChange){
                    for (bind in ModeAdapter.listData){
                        bind.root.setCardBackgroundColor(Color.DKGRAY)
                    }
                    ModeAdapter.needChange = false
                }
            }
            true
        }

        binding.BrightnessSeekBar.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener{
            override fun onProgressChanged(seekBar: SeekBar, progress: Int, fromUser: Boolean) {
                if (BlueToothAllInOne.OutputCalculated.get()){
                    BlueToothAllInOne.sendToAll("B$progress\n") //maybe delay?
                }
            }

            override fun onStartTrackingTouch(seekBar: SeekBar) {
                // you can probably leave this empty
            }

            override fun onStopTrackingTouch(seekBar: SeekBar) {
                // you can probably leave this empty
            }
        })

        binding.onOffBtn.setOnClickListener{
            if (BlueToothAllInOne.OutputCalculated.get()){
                if(click%2==0){
                    BlueToothAllInOne.sendToAll("B0\n") //maybe delay?
                    click++
                }else{
                    BlueToothAllInOne.sendToAll("B125\n") //maybe delay?
                    binding.BrightnessSeekBar.progress = 125
                    click=0
                }
            }
        }
        binding.favColorsBtn.setOnClickListener {
            favColorsAlert()
        }
        binding.saveColorBtn.setOnClickListener {
            saveColorAlert()
        }

    }

    private fun favColorsAlert() {
        val alertLayout = layoutInflater.inflate(R.layout.alert_fav_colors_layout,null)
        val colorList = alertLayout.findViewById<RecyclerView>(R.id.colorList)
        colorList.let {
            it.adapter = adapter
            it.layoutManager = LinearLayoutManager(requireContext())
        }

        val dialog = AlertDialog.Builder(requireContext())
            .setView(alertLayout)
            .setNegativeButton("BACK") { dialog, whichButton ->
                for (col in FavColorsAdapter.listData){
                    col.root.setCardBackgroundColor(Color.DKGRAY)
                }
                dialog.dismiss()}
            .setOnCancelListener {
                for (col in FavColorsAdapter.listData){
                    col.root.setCardBackgroundColor(Color.DKGRAY)
                }
            }
        dialog.show()

    }

    override fun onStart() {
        super.onStart()
        loadData()
    }

    private fun loadData() {
        thread {
            val colors =  FavColorDatabase.open(requireContext()).colors.getAllColors().map { entity ->
                ColorData(
                    entity.RGBstr,
                    entity.color
                )
            }
            adapter.replace(colors)
        }
    }

    @SuppressLint("InflateParams")
    fun saveColorAlert(){
        val alertLayout = layoutInflater.inflate(R.layout.alert_layout,null)
        val colorPreview = alertLayout.findViewById<TextView>(R.id.colorPreview)

        val redValue= alertLayout.findViewById<EditText>(R.id.redValue)
        redValue.setText(recentRed.toString())
        val greenValue= alertLayout.findViewById<EditText>(R.id.greenValue)
        greenValue.setText(recentGreen.toString())
        val blueValue= alertLayout.findViewById<EditText>(R.id.blueValue)
        blueValue.setText(recentBlue.toString())


        colorPreview.setBackgroundColor(Color.rgb(redValue.text.toString().toInt(),greenValue.text.toString().toInt(),blueValue.text.toString().toInt()))

        redValue.addTextChangedListener {
            var r = redValue.text.toString()
            var g = greenValue.text.toString()
            var b = blueValue.text.toString()

            if(r==""){
                r = "0"
            }
            if(g==""){
                g = "0"
            }
            if(b==""){
                b = "0"
            }
            if(r.toInt()>255){
                r=255.toString()
                redValue.setText(255.toString())
            }
            if(g.toInt()>255){
                g=255.toString()
                greenValue.setText(255.toString())
            }
            if(b.toInt()>255){
                b=255.toString()
                blueValue.setText(255.toString())
            }
            colorPreview.setBackgroundColor(Color.rgb(r.toInt(),g.toInt(),b.toInt()))
            alertLayout.invalidate()
        }
        greenValue.addTextChangedListener {
            var r = redValue.text.toString()
            var g = greenValue.text.toString()
            var b = blueValue.text.toString()

            if(r==""){
                r = "0"
            }
            if(g==""){
                g = "0"
            }
            if(b==""){
                b = "0"
            }
            if(r.toInt()>255){
                r=255.toString()
                redValue.setText(255.toString())
            }
            if(g.toInt()>255){
                g=255.toString()
                greenValue.setText(255.toString())
            }
            if(b.toInt()>255){
                b=255.toString()
                blueValue.setText(255.toString())
            }
            colorPreview.setBackgroundColor(Color.rgb(r.toInt(),g.toInt(),b.toInt()))
            alertLayout.invalidate()
        }
        blueValue.addTextChangedListener {
            var r = redValue.text.toString()
            var g = greenValue.text.toString()
            var b = blueValue.text.toString()

            if(r==""){
                r = "0"
            }
            if(g==""){
                g = "0"
            }
            if(b==""){
                b = "0"
            }
            if(r.toInt()>255){
                r=255.toString()
                redValue.setText(255.toString())
            }
            if(g.toInt()>255){
                g=255.toString()
                greenValue.setText(255.toString())
            }
            if(b.toInt()>255){
                b=255.toString()
                blueValue.setText(255.toString())
            }
            colorPreview.setBackgroundColor(Color.rgb(r.toInt(),g.toInt(),b.toInt()))
            alertLayout.invalidate()
        }

        val dialog = AlertDialog.Builder(requireContext())
            .setView(alertLayout)
            .setPositiveButton("SAVE") { dialog, whichButton ->
                val color = Color.rgb(redValue.text.toString().toInt(),greenValue.text.toString().toInt(),blueValue.text.toString().toInt())
                saveToColorDatabase(color,"RGB:(${redValue.text},${greenValue.text},${blueValue.text})")
                dialog.dismiss()}
            .setNegativeButton("CANCEL") { dialog, whichButton ->
                dialog.dismiss()}

        dialog.show()
    }

    private fun saveToColorDatabase(color: Int, RGBstr: String) {
        thread {
            val newColor =  FavColorEntity(
                RGBstr = RGBstr,
                color = color
            )
            FavColorDatabase.open(requireContext()).colors.addColor(newColor)
            loadData()
        }
    }
}